#include "graphic/TextPresentationController.hpp"
#include <iostream>

int main()
{
    TextPresentationController controller = TextPresentationController();
    std::cout << controller.getWelcomeMessage();
    bool startGame = controller.promptUserToStartAGame();
    while(startGame)
    {
        while(!controller.promptUserToShoot())
        {
        }
        std::cout << std::endl << controller.getCongratulationsMessage();
        startGame = controller.promptUserToStartAGame();
    }
    return 0;
}
