// ============================================================
//  excuse_generator.cpp
//  A beginner-friendly C++ program that generates random,
//  dramatic student excuses for classroom settings.
//
//  UI layout uses a single BOX_WIDTH constant so every border,
//  separator, and text row is always the same width — even when
//  the student name or excuse text is very long.
// ============================================================

#include <iostream>   // for cin / cout
#include <string>     // for std::string
#include <vector>     // for std::vector
#include <sstream>    // for std::istringstream (word-wrap helper)
#include <cstdlib>    // for srand(), rand()
#include <ctime>      // for time()

// ─────────────────────────────────────────────────────────────
//  Layout constants — change BOX_WIDTH to resize everything.
//  BOX_WIDTH = total characters between the two '║' borders.
// ─────────────────────────────────────────────────────────────
const int BOX_WIDTH   = 60;   // inner width (excludes the two '║')
const int TEXT_INDENT = 2;    // spaces before text inside a box row

// ─────────────────────────────────────────────────────────────
// Helper: trim leading/trailing whitespace from a string.
// ─────────────────────────────────────────────────────────────
std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

// ─────────────────────────────────────────────────────────────
// Helper: replace every {name} placeholder with the real name.
// ─────────────────────────────────────────────────────────────
std::string fillTemplate(const std::string& tmpl, const std::string& name) {
    const std::string placeholder = "{name}";
    std::string result = tmpl;
    size_t pos = 0;
    while ((pos = result.find(placeholder, pos)) != std::string::npos) {
        result.replace(pos, placeholder.length(), name);
        pos += name.length();
    }
    return result;
}

// ─────────────────────────────────────────────────────────────
// UI helpers — all output goes through these so the box always
// stays the correct width.
// ─────────────────────────────────────────────────────────────

// Print the top border:  ╔══...══╗
void printTop() {
    std::cout << "\xe2\x95\x94";                    // ╔
    for (int i = 0; i < BOX_WIDTH; ++i)
        std::cout << "\xe2\x95\x90";               // ═
    std::cout << "\xe2\x95\x97\n";                 // ╗
}

// Print a separator row: ╠══...══╣
void printSep() {
    std::cout << "\xe2\x95\xa0";                    // ╠
    for (int i = 0; i < BOX_WIDTH; ++i)
        std::cout << "\xe2\x95\x90";               // ═
    std::cout << "\xe2\x95\xa3\n";                 // ╣
}

// Print the bottom border: ╚══...══╝
void printBottom() {
    std::cout << "\xe2\x95\x9a";                    // ╚
    for (int i = 0; i < BOX_WIDTH; ++i)
        std::cout << "\xe2\x95\x90";               // ═
    std::cout << "\xe2\x95\x9d\n";                 // ╝
}

// Print one padded row:  ║  <text>               ║
// The text area is (BOX_WIDTH - TEXT_INDENT) chars wide.
// If the text is shorter, spaces pad it to the right edge.
void printRow(const std::string& text) {
    const int contentWidth = BOX_WIDTH - TEXT_INDENT;

    // Truncate only as a last resort (single word longer than box)
    std::string display = text;
    if ((int)display.size() > contentWidth)
        display = display.substr(0, contentWidth - 1) + "\xe2\x80\xa6"; // …

    int padding = contentWidth - (int)display.size();

    std::cout << "\xe2\x95\x91";                    // ║
    for (int i = 0; i < TEXT_INDENT; ++i)
        std::cout << ' ';
    std::cout << display;
    for (int i = 0; i < padding; ++i)
        std::cout << ' ';
    std::cout << "\xe2\x95\x91\n";                 // ║
}

// Print an empty padded row (blank line inside the box)
void printEmptyRow() { printRow(""); }

// Print a centred title row inside the box.
void printCentred(const std::string& text) {
    // Clamp to BOX_WIDTH if the text itself is somehow too wide
    std::string display = text;
    if ((int)display.size() > BOX_WIDTH)
        display = display.substr(0, BOX_WIDTH - 1) + "\xe2\x80\xa6";

    int space    = BOX_WIDTH - (int)display.size();
    int leftPad  = space / 2;
    int rightPad = space - leftPad;

    std::cout << "\xe2\x95\x91";                    // ║
    for (int i = 0; i < leftPad;  ++i) std::cout << ' ';
    std::cout << display;
    for (int i = 0; i < rightPad; ++i) std::cout << ' ';
    std::cout << "\xe2\x95\x91\n";                 // ║
}

// ─────────────────────────────────────────────────────────────
// Word-wrap helper: break 'text' into lines that each fit
// within maxWidth characters, splitting only at spaces.
// Returns a vector of lines — never wider than maxWidth.
// ─────────────────────────────────────────────────────────────
std::vector<std::string> wordWrap(const std::string& text, int maxWidth) {
    std::vector<std::string> lines;
    std::istringstream stream(text);
    std::string word, currentLine;

    while (stream >> word) {
        if (!currentLine.empty() &&
            (int)(currentLine.size() + 1 + word.size()) <= maxWidth) {
            // Word fits on the current line
            currentLine += ' ';
            currentLine += word;
        } else if (currentLine.empty()) {
            // Edge case: single word longer than maxWidth — hard-break it
            while ((int)word.size() > maxWidth) {
                lines.push_back(word.substr(0, maxWidth));
                word = word.substr(maxWidth);
            }
            currentLine = word;
        } else {
            // Flush current line, start a new one with this word
            lines.push_back(currentLine);
            currentLine = word;
        }
    }
    if (!currentLine.empty())
        lines.push_back(currentLine);

    return lines;
}

// ─────────────────────────────────────────────────────────────
// Build and return the collection of excuse templates.
// ─────────────────────────────────────────────────────────────
std::vector<std::string> buildExcuses() {
    std::vector<std::string> excuses;

    excuses.push_back(
    "{name} could not submit the homework because a seagull "
    "swooped down, snatched the assignment right off the desk, "
    "and vanished into the horizon before anyone could react.");

    excuses.push_back(
    "According to {name}, the family cat sat on the laptop "
    "keyboard and with uncanny precision deleted the entire "
    "project folder while {name} blinked.");

    excuses.push_back(
    "{name} was on the way to school when a film crew mistook "
    "{name} for a background actor, handed over a costume, and "
    "the shoot ran four hours longer than expected.");

    excuses.push_back(
    "The textbook belonging to {name} apparently spontaneously "
    "combusted at exactly 11:58 PM, two minutes before the "
    "deadline, as witnessed by three bewildered houseplants.");

    excuses.push_back(
    "{name} tried to print the essay, but the printer produced "
    "a single ominous fortune-cookie slip that read: "
    "Grades are merely a social construct.");

    excuses.push_back(
    "A travelling magician knocked on {name}'s door asking for "
    "a volunteer. {name} raised a hand, was levitated over the "
    "roof, and didn't land until well after class had ended.");

    excuses.push_back(
    "{name} insists the homework WAS done, but upon opening "
    "the backpack this morning found only a harmonica, a "
    "single chopstick, and a post-it note that said oops.");

    excuses.push_back(
    "Due to a freak solar flare, every electronic device in "
    "{name}'s home reset to factory settings at midnight, "
    "taking the finished assignment into the digital void.");

    excuses.push_back(
    "{name} was fully prepared until a neighbour's parrot "
    "escaped, flew into the room, recited the entire essay "
    "aloud, then refused to let {name} write it down.");

    excuses.push_back(
    "Scientists visited {name}'s address last night because a "
    "wormhole briefly opened in the bedroom. {name} is fine, "
    "but the homework slipped through and is now in 1987.");

    excuses.push_back(
    "{name} completed every question, but on the way in "
    "a strong gust of wind turned the pages into a paper "
    "airplane that achieved lift-off and hasn't been seen since.");

    excuses.push_back(
    "The study group at {name}'s house got so competitive "
    "that everyone forgot they were studying and accidentally "
    "founded a small philosophical debate society instead.");

    return excuses;
}

// ─────────────────────────────────────────────────────────────
// Main entry point
// ─────────────────────────────────────────────────────────────
int main() {

    // Seed the random-number generator with the current time
    // so we get a different result each time the program runs.
    srand(static_cast<unsigned int>(time(nullptr)));

    // ── Welcome banner ────────────────────────────────────────
    // No emoji inside the box: emoji are 2 columns wide and
    // cause the right border to drift on most terminals.
    // Plain ASCII keeps the width calculation exact.
    printTop();
    printEmptyRow();
    printCentred("Student Excuse Generator  v1.0");
    printEmptyRow();
    printBottom();

    std::cout << '\n';

    // ── Get student name ─────────────────────────────────────
    std::string studentName;

    while (true) {
        std::cout << " Enter the student's name: ";
        std::getline(std::cin, studentName);
        studentName = trim(studentName);

        if (!studentName.empty()) break;

        std::cout << "  [!] Name cannot be blank. Please try again.\n\n";
    }

    // ── Load excuses and pick one at random ──────────────────
    std::vector<std::string> excuses = buildExcuses();
    int index = rand() % static_cast<int>(excuses.size());

    // Replace {name} placeholder with the real student name
    std::string finalExcuse = fillTemplate(excuses[index], studentName);

    // ── Build the header label ────────────────────────────────
    // Format: "Official Excuse for: <name>"
    // Truncate the name with '…' if it would overflow the row.
    const int contentWidth  = BOX_WIDTH - TEXT_INDENT;
    const std::string labelPrefix = "Official Excuse for: ";
    std::string nameDisplay = studentName;

    if ((int)(labelPrefix.size() + nameDisplay.size()) > contentWidth) {
        int maxNameLen = contentWidth - (int)labelPrefix.size() - 1;
        if (maxNameLen < 1) maxNameLen = 1;
        nameDisplay = nameDisplay.substr(0, maxNameLen) + "\xe2\x80\xa6"; // …
    }

    // ── Word-wrap the excuse to fit inside the box ───────────
    std::vector<std::string> excuseLines = wordWrap(finalExcuse, contentWidth);

    // ── Build the footer label ────────────────────────────────
    std::string footerText = "Excuse #" + std::to_string(index + 1)
                           + " of " + std::to_string(excuses.size());

    // ── Print the result box ──────────────────────────────────
    std::cout << '\n';
    printTop();
    printEmptyRow();
    printRow(labelPrefix + nameDisplay);
    printSep();
    printEmptyRow();
    for (const std::string& line : excuseLines)
        printRow(line);
    printEmptyRow();
    printSep();
    printCentred(footerText);
    printBottom();
    std::cout << '\n';

    return 0;
}
