#include "item.h"
#include "../user_interface/application_window.h"

Item::Item(std::string kind, Coord top_left, int height, int width, int id):
    kind(kind), top_left(top_left), height(height), width(width),
    id(id)
{
    bottom_right = Coord(top_left.x + width, top_left.y - height);
}

Item::Item(std::string kind, Coord top_left, Coord bottom_right, int id):
    kind(kind), top_left(top_left), bottom_right(bottom_right),
    id(id)
{
    height = top_left.y - bottom_right.y;
    width = bottom_right.x - top_left.x;
}

Item::Item(std::string kind, Coord top_left, Coord bottom_right, int height, int width, int id):
    kind(kind), top_left(top_left), bottom_right(bottom_right),
    height(height), width(width), id(id) {}

void Item::changeParameters(std::map<std::string, std::string> options)
{
    saveParameters();
    std::map<std::string, std::function<void(const std::string&)>> parameterMap = {
        {"height", [this](const std::string& value) { height = std::stoi(value); }},
        {"width", [this](const std::string& value) { width = std::stoi(value); }},
        {"top_left", [this](const std::string& value) { top_left = Coord(value); }},
        {"bottom_right", [this](const std::string& value) { bottom_right = Coord(value); }},
    };

    for (const auto& [option, value] : options)
    {
        auto it = parameterMap.find(option);
        if (it != parameterMap.end())
            it->second(value);
    }
}

void Item::undoParametersChange()
{
    top_left = std::get<Coord>(prevParameters.find("top_left")->second);
    bottom_right = std::get<Coord>(prevParameters.find("bottom_right")->second);;
    height = std::get<int>(prevParameters.find("height")->second);
    width = std::get<int>(prevParameters.find("width")->second);
}

void Item::saveParameters()
{
    prevParameters["top_left"] = top_left;
    prevParameters["bottom_right"] = bottom_right;
    prevParameters["height"] = height;
    prevParameters["width"] = width;
}

void Item::setKind(const std::string& newKind)
{
    kind = newKind;
}

const std::string& Item::getKind() const
{
    return kind;
}

void Item::setTopLeft(const Coord& newTopLeft)
{
    top_left = newTopLeft;
}

const Coord& Item::getTopLeft() const
{
    return top_left;
}

void Item::setBottomRight(const Coord& newBottomRight)
{
    bottom_right = newBottomRight;
}

const Coord& Item::getBottomRight() const
{
    return bottom_right;
}

void Item::setHeight(int newHeight)
{
    height = newHeight;
}

int Item::getHeight() const
{
    return height;
}

void Item::setWidth(int newWidth)
{
    width = newWidth;
}

int Item::getWidth() const
{
    return width;
}

void Item::setId(int newId)
{
    id = newId;
}

int Item::getId() const
{
    return id;
}

Item& Item::operator=(const Item& other)
{
    if (this == &other)
        return *this;

    kind = other.kind;
    top_left = other.top_left;
    bottom_right = other.bottom_right;
    width = other.width;
    height = other.height;
    id = other.id;

    return *this;
}
