#include <iostream>
#include <windows.h>
#include <cmath>
#define PI  3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145648566923460348610
struct Point {
    int x;
    int y;
};

// Function to simulate pressing and releasing the left mouse button
void clickMouse(bool down) {
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = down ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(INPUT));
}

int main() {
    // Give the user information about the program
    std::cout << "Press 'E' to make a circle in the counter-clockwise direction." << std::endl;
    std::cout << "Press 'Q' to make a circle in the clockwise direction." << std::endl;
    std::cout << "Press 'W' to move the mouse to the center of the screen." << std::endl;
    std::cout << "Press 'ESC' to exit the program." << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;
    // Get the smoothness of the circle
    int smoothness = 1;
    int pixelOffset = 0;
    std::cout << "Enter the smoothness of the circle (lower value for smoother circle): ";
    std::cin >> smoothness;
    std::cout << "-------------------------------------------------------------" << std::endl;
    std::cout << "Offset for the center of the circle (y-axis): ";
    std::cin >> pixelOffset;
    std::cout << "-------------------------------------------------------------" << std::endl;
    std::cout << "Circle is ready to be drawn." << std::endl;




    // Get the height and width of the screen
    int height = GetSystemMetrics(SM_CYSCREEN);
    int width = GetSystemMetrics(SM_CXSCREEN);

    // Define center of the screen in (x,y) coordinates
    Point center = { (width / 2), (height / 2) + pixelOffset };

    // Set the radius of the circle (in pixels away from the center of the screen)
    int radius = 200;

    // Define the number of steps for smoother movement
    int numSteps = 360;

    if (smoothness < 3) {
        numSteps = (360 * 2) + 350;
    }
    const double stepSize = smoothness * PI / numSteps;

    // Check if the "E" key is pressed
    while (true) {
        if (GetAsyncKeyState(0x45)) {
            // Make a circle in the counter-clockwise direction
            // Wait a second before starting the circle
            Sleep(1000);

            // Press the left mouse button down
            clickMouse(true);

            for (int i = 0; i < numSteps; i++) {
                // Calculate the angle
                double angle = i * stepSize;

                // Calculate the x and y coordinates of the circle
                int x = center.x + static_cast<int>(radius * cos(angle));
                int y = center.y + static_cast<int>(radius * sin(angle));

                // Move the mouse to the calculated (x,y) coordinates
                SetCursorPos(x, y);

                // Sleep for a short duration to control the speed of movement
                Sleep(10); // Adjust sleep duration as needed for smoother movement
            }

            // Release the left mouse button
            clickMouse(false);

            break;
        }

        // Check to see if the "Q" key is pressed
        if (GetAsyncKeyState(0x51)) {
            // Make a circle in the clockwise direction
            // Wait a second before starting the circle
            Sleep(1000);

            // Press the left mouse button down
            clickMouse(true);

            for (int i = numSteps - 1; i >= 0; i--) {
                // Calculate the angle
                double angle = i * stepSize;

                // Calculate the x and y coordinates of the circle
                int x = center.x + static_cast<int>(radius * cos(angle));
                int y = center.y + static_cast<int>(radius * sin(angle));

                // Move the mouse to the calculated (x,y) coordinates
                SetCursorPos(x, y);

                // Sleep for a short duration to control the speed of movement
                Sleep(10); // Adjust sleep duration as needed for smoother movement
            }

            // Release the left mouse button
            clickMouse(false);

            break;
        }

        // Check to see if the "W" key is pressed
        if (GetAsyncKeyState(0x57)) {
            SetCursorPos(center.x, center.y);
        }

        // Check to see if the "ESC" key is pressed
        if (GetAsyncKeyState(VK_ESCAPE)) {
            break;
        }
    }

    return 0;
}
