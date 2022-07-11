#pragma once

#include <memory>

#include "box2d/box2d.h"
#include "Macros.h"

// A templete class that responsible for creat game objects
template <typename T>
class Factory 
{
public:

    using FuncType = std::shared_ptr<T>(*)(const sf::Vector2f &, b2World &, const sf::Vector2f&);

    static std::shared_ptr<T> create(const char &, const sf::Vector2f &, b2World &, const sf::Vector2f&);

    static bool registerObject(const char &, FuncType);

private:
    Factory() = default;
    Factory(const Factory&) = delete;
    static auto & getMap()
    {
        static std::unordered_map<char, FuncType> map;
        return map;
    }
};

//-----------------------------------------------
template<typename T>
std::shared_ptr<T> Factory<T>::create(const char & name, const sf::Vector2f & position,
                                      b2World & world, const sf::Vector2f & dimension)
{
    // checks if the object is registered
    auto it = Factory::getMap().find(name);

    if(it == Factory::getMap().end())
        return nullptr;

    return it->second(position, world, dimension);
}

//-----------------------------------------------
// Registers the object to the factory
template<typename T>
bool Factory<T>::registerObject(const char & o, Factory::FuncType f)
{
    Factory::getMap().emplace(o, f);
    return true;
}
