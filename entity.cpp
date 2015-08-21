#include "entity.hpp"

Entity::Entity()
    : m_texture()
{

}

void Entity::load(std::string texturefilename)
{
    m_texture.loadFromFile(texturefilename);
    this->setTexture(m_texture);
    this->setOrigin(this->getGlobalBounds().width/2, this->getGlobalBounds().height/2);
}

Entity::~Entity()
{
    delete this;
}

