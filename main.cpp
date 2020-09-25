#include "graphic/TextPresentationController.hpp"
#include <iostream>

int main()
{
    TextPresentationController controller = TextPresentationController();
    std::cout << controller.getWelcomeMessage();
    bool startGame = controller.carryStartGameSequence();
    while(startGame)
    {
        while(!controller.carryTurnSequence())
        {
        }
        std::cout << std::endl << controller.getCongratulationsMessage();
        startGame = controller.carryStartGameSequence();
    }
    return 0;
}
