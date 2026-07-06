#include <array>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string_view>
#include <thread>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

// Enable ANSI escape sequence support on modern Windows consoles.
void enableAnsiSupport() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD mode = 0;
    if (!GetConsoleMode(hOut, &mode)) return;

    SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
}

// Clear the terminal and move the cursor to the top-left corner.
void clearScreen() {
    std::cout << "\033[2J\033[H";
}

int main() {
    using namespace std::chrono_literals;

    enableAnsiSupport();

    const std::vector<std::vector<std::string_view>> fonts = {
        {
            " 6666   777777 ",
            "6      7    7  ",
            "66666      7   ",
            "6   6     7    ",
            " 666     7     "
        },
        {
            " ####    ####### ",
            "#    #        #  ",
            "#  ###       #   ",
            "#    #      #    ",
            " ####      #     "
        },
        {
            "  *****    ******* ",
            " *        *     *  ",
            " ******         *  ",
            " *    *        *   ",
            "  ****        *    "
        },
        {
            "  @@@@     @@@@@@@ ",
            " @        @     @  ",
            " @@@@          @   ",
            " @   @        @    ",
            "  @@@        @     "
        }
    };

    const std::array<const char*, 8> colors = {
        "\033[1;31m", // red
        "\033[1;32m", // green
        "\033[1;33m", // yellow
        "\033[1;34m", // blue
        "\033[1;35m", // magenta
        "\033[1;36m", // cyan
        "\033[1;91m", // light red
        "\033[1;95m"  // light magenta
    };

    std::size_t step = 0;

    while (true) {
        clearScreen();

        // Select the current ASCII-art style and color cyclically.
        const auto& font = fonts[step % fonts.size()];
        const char* color = colors[step % colors.size()];

        std::cout << color << "\n\n";
        for (const auto& line : font) {
            std::cout << "        " << line << '\n';
        }

        // Reset terminal formatting after drawing the number.
        std::cout << "\033[0m" << std::flush;

        std::this_thread::sleep_for(250ms);

        clearScreen();
        std::this_thread::sleep_for(250ms);

        ++step;
    }

    return 0;
}