#include <sstream>
#include <iostream>

unsigned long esphomeColorToHex(esphome::Color color)
{
    return ((color.r & 0xff) << 16) + ((color.g & 0xff) << 8) + (color.b & 0xff);
}

static std::vector<std::string> splitSelectValues(const char* lineToSplit)
{
    std::stringstream origStream;
    origStream << lineToSplit;
    std::vector<std::string> lineList;
    std::string curLine;
    while (std::getline(origStream, curLine))
    {
        // Only add non empty lines.
        if (!curLine.empty())
            lineList.push_back(curLine);
    }

    return lineList;
}