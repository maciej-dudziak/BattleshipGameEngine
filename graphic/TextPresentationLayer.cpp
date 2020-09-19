#include "TextPresentationLayer.hpp"

TextPresentationLayer::TextPresentationLayer()
{
}

TextPresentationLayer::~TextPresentationLayer()
{
}

std::string TextPresentationLayer::getTextPresentation(int gameboardSize)
{
    std::string output;
    int gameboardLen = sqrt(gameboardSize);
    output.append(addGameboardHeader(gameboardLen));

    int noOfSpacesToFill = 2*gameboardLen - 1;
    for(int i = 1; i < gameboardLen+1; i++)
    {
        output.append("\n").append(std::to_string(i));
        output.append(noOfSpacesToFill, ' ');
    }
    return output;
}

std::string TextPresentationLayer::getTextPresentation(std::vector<char> inputData)
{
    std::string output;
    int gameboardLen = sqrt(inputData.size());
    output.append(addGameboardHeader(gameboardLen));

    for(int i = 0; i < gameboardLen; i++)
    {
        output.append("\n").append(std::to_string(i+1));
        for(int j = 0; j < gameboardLen; j++)
        {
            output.append(1, inputData.at(i*gameboardLen + j)).append(" ");
        }
    }
    return output;
}

std::string TextPresentationLayer::getHitOrMissMessage(bool isHit)
{
    std::string result = isHit ? "Hit" : "Miss";
    return "Shot result: " + result + "\n";
}

std::string TextPresentationLayer::addGameboardHeader(int gameboardLen)
{
    std::string output;
    for(int i = 1; i < gameboardLen+1; i++)
    {
        output.append(" ").append(std::to_string(i));
    }
    return output;
}