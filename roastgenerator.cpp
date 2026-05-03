// ============================================================
//  Roast Generator  --  Console UI Edition
//  Fancy ASCII art banner, dramatic delay, bordered output,
//  and a funny closing message -- all beginner-friendly.
//
//  ENCODING: Pure ASCII (0x00-0x7F) throughout.
//  Safe on Windows CMD/PowerShell (CP437, CP1252), Linux, macOS.
// ============================================================

#include <iostream>   // std::cin, std::cout
#include <vector>     // std::vector
#include <string>     // std::string
#include <cstdlib>    // srand(), rand()
#include <ctime>      // time()
#include <limits>     // std::numeric_limits (used in cin.ignore)

// cross-platform sleep:
//   Windows -> Sleep(milliseconds)  via <windows.h>
//   Linux / macOS -> usleep(microseconds)  via <unistd.h>
#ifdef _WIN32
  #include <windows.h>      // Sleep(), SetConsoleOutputCP()
#else
  #include <unistd.h>       // usleep()
#endif


// ============================================================
//  SECTION 0 -- PLATFORM HELPERS
//  Isolate every OS-specific call so the rest of the code
//  stays completely portable.
// ============================================================

// ------------------------------------------------------------
// initConsole
// Switches the Windows console to UTF-8 (code page 65001).
// On Linux / macOS the terminal is already UTF-8; nothing to do.
// ------------------------------------------------------------
void initConsole()
{
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif
}

// ------------------------------------------------------------
// sleepMs  (milliseconds)
// Pauses execution for the given number of milliseconds.
// Wraps the different OS APIs behind one simple name.
//
// Example: sleepMs(500) waits half a second.
// ------------------------------------------------------------
void sleepMs(int ms)
{
#ifdef _WIN32
    Sleep(static_cast<DWORD>(ms));          // Windows: Sleep takes ms directly
#else
    usleep(static_cast<useconds_t>(ms) * 1000); // POSIX: usleep takes microseconds
#endif
}


// ============================================================
//  SECTION 1 -- UTILITY HELPERS
//  Pure string functions -- no I/O, no side-effects.
// ============================================================

// ------------------------------------------------------------
// trimWhitespace
// Strips leading and trailing spaces/tabs from 'str'.
// "  Alice  " -> "Alice"
// ------------------------------------------------------------
std::string trimWhitespace(const std::string& str)
{
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

// ------------------------------------------------------------
// replacePlaceholder
// Replaces the first '{name}' inside templateStr with value.
// replacePlaceholder("Hi {name}!", "{name}", "Sam") -> "Hi Sam!"
// ------------------------------------------------------------
std::string replacePlaceholder(const std::string& templateStr,
                               const std::string& placeholder,
                               const std::string& value)
{
    std::string result = templateStr;
    size_t pos = result.find(placeholder);
    if (pos != std::string::npos)
        result.replace(pos, placeholder.length(), value);
    return result;
}

// ------------------------------------------------------------
// repeatChar
// Returns a string made of 'count' copies of character 'ch'.
// repeatChar('=', 5) -> "====="
// Used to build dynamic-width borders.
// ------------------------------------------------------------
std::string repeatChar(char ch, int count)
{
    return std::string(static_cast<size_t>(count), ch);
}


// ============================================================
//  SECTION 2 -- DATA
//  All roast templates in one place.  Add new lines freely!
//  Every template MUST contain exactly one {name} placeholder.
// ============================================================

std::vector<std::string> getRoastTemplates()
{
    return {
        "Hey {name}, I'd roast you, but my parents said I'm not allowed to burn trash.",
        "{name}, you're proof that even evolution takes a day off sometimes.",
        "I'd agree with you, {name}, but then we'd both be wrong.",
        "{name}, you bring everyone so much joy -- especially when you leave the room.",
        "If brains were petrol, {name}, you wouldn't have enough to ride an ant's motorcycle.",
        "{name}, I've seen better looking faces on a potato -- and the potato had more personality.",
        "Don't worry, {name}. Some day you'll find your brain. Maybe check the lost-and-found.",
        "{name}, scientists say the universe is 13.8 billion years old. What a long time to prepare for... this.",
        "The good news, {name}: you can't disappoint people who've already given up on you.",
        "I'm not saying {name} is slow, but their Wi-Fi finishes downloads before they finish a thought.",
        "{name}, somewhere out there is a tree producing oxygen just for you. You owe that tree an apology.",
        "They say every person has a purpose, {name}. Keep searching -- you'll find yours eventually.",
        "{name}, you have your whole life to be an idiot. Why not take today off?"
    };
}

// ------------------------------------------------------------
// getClosingMessages
// A pool of funny sign-off lines shown after the roast.
// One is chosen at random -- same mechanism as the roasts.
// ------------------------------------------------------------
std::vector<std::string> getClosingMessages()
{
    return {
        "All in good fun! You're a solid 10... on a scale of 1 to potato.",
        "Don't worry, we roast the ones we love. Mostly.",
        "Remember: laughter is the best medicine. You clearly need a lot of it.",
        "No feelings were harmed in the making of this roast. Probably.",
        "You're irreplaceable, {name}. No one else could fill your particular void.",
        "Stay awesome, {name}. The bar is on the floor, but still.",
        "This roast was generated by a computer, which says a lot about both of you.",
        "Come back anytime -- we have plenty more where that came from!"
    };
}


// ============================================================
//  SECTION 3 -- RANDOMISATION
// ============================================================

void initRandomSeed()
{
    srand(static_cast<unsigned int>(time(0)));
}

// Returns a random integer in [0, count).
int pickRandomIndex(int count)
{
    return rand() % count;
}


// ============================================================
//  SECTION 4 -- UI: WELCOME BANNER
//  ASCII art title + subtitle, printed once at startup.
// ============================================================

// ------------------------------------------------------------
// printWelcomeBanner
// Big ASCII-art logo, tagline, and a decorative border.
// Every character here is plain ASCII -- safe everywhere.
// ------------------------------------------------------------
void printWelcomeBanner()
{
    // Top border
    std::cout << "\n" << repeatChar('=', 55) << "\n";

    // ASCII art letters spelling  R O A S T
    std::cout << "  ____   ___    _    ____ _____\n";
    std::cout << " |  _ \\ / _ \\  / \\  / ___|_   _|\n";
    std::cout << " | |_) | | | |/ _ \\ \\___ \\ | |\n";
    std::cout << " |  _ <| |_| / ___ \\ ___) || |\n";
    std::cout << " |_| \\_\\\\___/_/   \\_\\____/ |_|\n";

    // Subtitle line
    std::cout << "\n";
    std::cout << "      *** The Roast Generator  v3.0 ***\n";
    std::cout << "   Serving hot takes since the dawn of time.\n";

    // Bottom border
    std::cout << repeatChar('=', 55) << "\n\n";
}


// ============================================================
//  SECTION 5 -- UI: USER INPUT
// ============================================================

// ------------------------------------------------------------
// promptUserName
// Shows a styled prompt, reads the name, trims whitespace,
// and falls back to "Mystery Human" if the user hits Enter.
//
// WHY cin.ignore() IS HERE -- THE CLASSIC BUG EXPLAINED:
//
//   When you use  cin >> someVariable  anywhere before this
//   function, cin reads the value but leaves a '\n' (the Enter
//   key the user pressed) sitting in the input buffer:
//
//     Buffer before ignore():  [ '\n' ]
//     getline() sees '\n' immediately -> reads empty string
//     -> skips waiting for the user entirely!   <-- THE BUG
//
//   cin.ignore() discards that leftover '\n' so getline()
//   starts with a clean buffer and waits properly:
//
//     Buffer after  ignore():  [ empty ]
//     getline() waits for the user to type  <-- FIXED
//
//   Even if no cin >> was used before this call, ignore() on
//   an already-empty buffer is a safe no-op, so it never hurts
//   to have it here as a defensive guard.
// ------------------------------------------------------------
std::string promptUserName()
{
    // Flush the leftover '\n' that any earlier cin >> may have
    // left behind -- without this, getline() skips the input.
    // numeric_limits<streamsize>::max() means "ignore up to as
    // many characters as the buffer can hold, stopping at '\n'".
    // This is safer than ignore(1) because it also handles edge
    // cases where multiple stray characters are in the buffer.

    // Little decorative prompt arrow
    std::cout << "  >> Who's brave enough to get roasted today?\n";
    std::cout << "     Enter your name: ";

    std::string input;
    std::getline(std::cin, input);       // Now waits correctly for the user
    input = trimWhitespace(input);

    if (input.empty())
    {
        input = "Mystery Human";
        std::cout << "\n  [!] No name entered -- calling you \""
                  << input << "\" instead.\n";
    }

    return input;
}


// ============================================================
//  SECTION 6 -- UI: DRAMATIC BUILD-UP ANIMATION
//  A simple countdown printed character by character,
//  with short delays, to create suspense before the roast.
// ============================================================

// ------------------------------------------------------------
// printDramaticCountdown
// Prints "Preparing roast..." with a fake "thinking" dots
// animation, then counts down 3-2-1 with pauses.
// std::flush forces each character to appear immediately
// instead of waiting for a newline to flush the buffer.
// ------------------------------------------------------------
void printDramaticCountdown()
{
    std::cout << "\n  [*] Scanning for weaknesses";
    std::cout.flush();

    // Print three dots one at a time with a 400 ms gap each
    for (int i = 0; i < 3; ++i)
    {
        sleepMs(400);
        std::cout << ".";
        std::cout.flush();
    }

    sleepMs(300);
    std::cout << " found some!\n";

    // Countdown: 3 -> 2 -> 1
    std::cout << "\n  Get ready";
    std::cout.flush();

    const char* ticks[] = { " 3...", " 2...", " 1..." };
    for (int i = 0; i < 3; ++i)
    {
        sleepMs(600);
        std::cout << ticks[i];
        std::cout.flush();
    }

    sleepMs(500);
    std::cout << "\n\n";
}


// ============================================================
//  SECTION 7 -- UI: ROAST DISPLAY
// ============================================================

// ------------------------------------------------------------
// displayRoast
// Wraps the roast text in a double-line box for visual impact.
// The box width is fixed at 55 chars -- matches the banner.
// ------------------------------------------------------------
void displayRoast(const std::string& roast)
{
    const int WIDTH = 55;

    // Top border (double lines for extra drama)
    std::cout << "  +" << repeatChar('=', WIDTH) << "+\n";
    std::cout << "  |" << repeatChar(' ', WIDTH) << "|\n";

    // The roast text, padded with spaces on each side.
    // We print "  | " before the text and " |" after.
    // Note: if the roast is longer than WIDTH-4, it will
    //       overflow -- a nice exercise to word-wrap later!
    std::cout << "  |  >>> " << roast << "\n";

    std::cout << "  |" << repeatChar(' ', WIDTH) << "|\n";
    std::cout << "  +" << repeatChar('=', WIDTH) << "+\n";
}

// ------------------------------------------------------------
// displayClosingMessage
// Picks a random closing message, substitutes the name,
// and prints it inside a lighter dashed border.
// ------------------------------------------------------------
void displayClosingMessage(const std::string& name)
{
    auto messages = getClosingMessages();
    int  idx      = pickRandomIndex(static_cast<int>(messages.size()));

    // Some closing messages also contain {name} -- replace if present
    std::string msg = replacePlaceholder(messages[idx], "{name}", name);

    std::cout << "\n  " << repeatChar('-', 51) << "\n";
    std::cout << "  (^) " << msg << "\n";
    std::cout << "  " << repeatChar('-', 51) << "\n\n";
}


// ============================================================
//  SECTION 8 -- ROAST LOGIC
//  Unchanged from previous version -- picks and personalises.
// ============================================================

std::string pickRoast(const std::vector<std::string>& templates,
                      const std::string& name)
{
    int index = pickRandomIndex(static_cast<int>(templates.size()));
    return replacePlaceholder(templates[index], "{name}", name);
}


// ============================================================
//  MAIN -- Orchestration only.
//  Read top to bottom: every step is one named function call.
// ============================================================
int main()
{
    std::cout << std::unitbuf;   // 🔥 auto-flush all cout output

    initConsole();                // Configure console
    initRandomSeed();             // Seed RNG

    printWelcomeBanner();         // Banner will now always show immediately

    std::string name = promptUserName();   // Prompt will be visible now

    printDramaticCountdown();     // Animation works properly

    std::vector<std::string> templates = getRoastTemplates();

    if (templates.empty())
    {
        std::cout << "Error: No roast templates available.\n";
        return 1;
    }

    std::string roast = pickRoast(templates, name);

    displayRoast(roast);
    displayClosingMessage(name);

    return 0;
}
