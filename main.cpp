#include "graphic/TextPresentationController.hpp"
#include <iostream>

int main()
{
    TextPresentationController controller = TextPresentationController();
    std::cout << controller.getWelcomeMessage();
    bool isGameStarted = controller.promptUserToStartAGame();
    if(isGameStarted)
    {
        while(!controller.promptUserToShoot())
        {
        }
        std::cout << controller.getCongratulationsMessage();
    }
    return 0;
}
