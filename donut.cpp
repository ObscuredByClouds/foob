#include <stdio.h>
#include <cmath>
#include <cstring>

#include <windows.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <conio.h>
using namespace std;

char ESC = '\x1b';
char BEL = '\x07';
struct csi_obj
{
} CSI;
ostream &operator<<(ostream &os, csi_obj o)
{
    os << ESC << '[';
    return os;
}
struct osc_obj
{
} OSC;
ostream &operator<<(ostream &os, osc_obj o)
{
    os << ESC << ']';
    return os;
}
struct sgr_obj
{
    ostream *os = {};
} SGR;
const sgr_obj &operator<<(ostream &os, sgr_obj o)
{
    SGR.os = &os;
    return SGR;
}
ostream &operator<<(const sgr_obj &o, const string &args)
{
    *SGR.os << CSI << args << 'm';
    return *SGR.os;
}
struct title_obj
{
    ostream *os = {};
} TITLE;
const title_obj &operator<<(ostream &os, title_obj o)
{
    TITLE.os = &os;
    return TITLE;
}
ostream &operator<<(const title_obj &o, const string &new_title)
{
    *TITLE.os << OSC << "0;" << new_title << BEL;
    return *TITLE.os;
}

string rgbBG(int r, int g, int b)
{
    stringstream ss;
    ss << "48;2;" << r << ';' << g << ';' << b;
    return ss.str();
}
string rgbFG(int r, int g, int b)
{
    stringstream ss;
    ss << "38;2;" << r << ';' << g << ';' << b;
    return ss.str();
}

struct rvector
{
    vector<int> data;
    rvector(initializer_list<int> il) : data(il) {}
    int &operator[](int pos)
    {
        return pos < 0
                   ? *(data.end() + pos)
                   : data.at(pos);
    }
};

struct Windows10_console_API
{
    Windows10_console_API()
    {
        DWORD dwMode;
        HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOutput == INVALID_HANDLE_VALUE)
            throw logic_error("API function \"GetStdHandle\" failed");
        else if (hOutput == NULL)
            throw logic_error("No handle associated with console");
        if (!GetConsoleMode(hOutput, &dwMode))
            throw logic_error("API function \"GetConsoleMode\" failed");
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        if (!SetConsoleMode(hOutput, dwMode))
            throw logic_error("API function \"SetConsoleMode\" failed");
    }
};

void layout(int r, int g, int b)
{
    for (int i = 0; i < 256; i++)
    {
        if ((!(i % 32)) && i != 0)
            cout << SGR << "49" << endl;
        cout << SGR << rgbFG(i + r * (255 - 2 * i), i + g * (255 - 2 * i), i + b * (255 - 2 * i));
        cout << SGR << rgbBG(i * r, i * g, i * b);
        cout << setw(3) << i << '|';
    }
    cout << endl;
}

void layout_examples()
{
    cout << TITLE << "Colors Layout" << CSI << "H" << CSI << "0J" << CSI << "?25l";
    for (int i = 1; i < 8; i++)
    {
        layout(i % 8 / 4, i % 4 / 2, i % 2);
    }
    while (!(kbhit() && getch() == 27))
        ;
}

void Flow()
{
    using range = vector<int>;
    enum _rgb
    {
        r,
        g,
        b
    };
    rvector bg{0, 0, 255}, fg{255, 0, 255};
    int i = -1, m = 0;
    cout << CSI << "H" << CSI << "0J" << CSI << "?25l" << CSI << "0;0r";
    stringstream ss;
    ss << setfill('0');
    while (!(kbhit() && getch() == 27))
    {
        ++i %= 255 * 6;
        m = i / 255;
        m & 1 ? bg[m / 2 - 1]-- : bg[m / 2]++;
        m = (m + 1) % 6;
        m & 1 ? fg[m / 2 - 1]-- : fg[m / 2]++;
        cout << CSI << "H"
             << SGR << rgbBG(bg[r], bg[g], bg[b])
             << SGR << rgbFG(fg[r], fg[g], fg[b]);
        for (int i : range(29))
        {
            for (int i : range(5))
                cout << "\
\316\316\316\316\316\316\316\316\316\316\316\316\
\316\316\316\316\316\316\316\316\316\316\316\316";
            cout << '\b' << '\n';
        }
        ss.str({});
        ss << "BG[r|g|b] [" << setw(3) << bg[r] << '|'
           << setw(3) << bg[g] << '|'
           << setw(3) << bg[b]
           << "] FG[r|g|b] [" << setw(3) << fg[r] << '|'
           << setw(3) << fg[g] << '|'
           << setw(3) << fg[b] << ']';
        cout << TITLE << ss.str();
    }
}

void donut()
{
    int k;
    vector<int> b(1760);
    vector<int> empty(1760);
    float A = 0, B = 0, i, j, z[1760];
    vector<int> colors{70, 81, 98, 116, 133, 150, 168, 185, 202, 220, 237, 255};
    cout << TITLE << "Donut" << CSI << "H" << CSI << "0J" << CSI << "?25l" << CSI << "0;0r";
    while (!(kbhit() && getch() == 27))
    {
        b = empty;
        memset(z, 0, 7040);
        for (j = 0; j < 6.28; j += 0.07)
            for (i = 0; 6.28 > i; i += 0.02)
            {
                float c = sin(i), d = cos(j), e = sin(A), f = sin(j),
                      g = cos(A), h = d + 2, D = 1 / (c * h * e + f * g + 5),
                      l = cos(i), m = cos(B), n = sin(B), t = c * h * g - f * e;
                int x = 40 + 30 * D * (l * h * m - t * n), y = 12 + 15 * D * (l * h * n + t * m),
                    o = x + 80 * y, N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
                if (22 > y && y > 0 &&
                    0 < x && x < 80 &&
                    D > z[o])
                {
                    z[o] = D;
                    b[o] = N > 0 ? colors[N] : 70;
                }
            }
        printf("\x1b[H\n ");
        for (k = 2; k < 1761; k++)
        {
            if (k % 80)
            {
                if (b[k - 1] == b[k])
                {
                    cout << ' ';
                }
                else
                {
                    if (b[k])
                    {
                        cout << "\x1b[48;2;" << b[k] << ";0;0m ";
                    }
                    else
                    {
                        cout << "\x1b[49m ";
                    }
                }
            }
            else
            {
                cout << '\n';
            }
        }
        A += 0.04;
        B += 0.02;
    }
}

int main()
{
    Windows10_console_API enable;
again:
    cout << SGR << "39" << SGR << "49"
         << TITLE << "Your choice?" << CSI << "H" << CSI << "0J" << CSI << "1J"
         << "1 Layout examples\n2 Flow\n3 Donut\nESC to exit\n";
    char c = getch();
    cout << c << '\b';
    switch (c)
    {
    case '1':
        layout_examples();
        goto again;
        break;
    case '2':
        Flow();
        goto again;
        break;
    case '3':
        donut();
        goto again;
        break;
    case '\033':
        break;
    default:
        goto again;
        break;
    }
}
