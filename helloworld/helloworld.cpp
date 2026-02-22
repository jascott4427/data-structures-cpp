#include <iostream>
#include <limits>

int main()
{
    // Print to terminal
    std::cout << "Hello, world!";

    // reset any error flags
    std::cin.clear();

    // ignore any characters in the input buffer until we find a newline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // get one more char from the user (waits for user to press enter)
    std::cin.get();

    return 0;
}
