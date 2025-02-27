#include "ResourceManager.h"

/***************************
 *     DECLARATIONS
 **************************/

std::map<std::string, sf::Texture*> ResourceManager::m_textureMap;

const std::string ResourceManager::DEFAULT_INVALID_TEXTURE = RESOURCES_PATH"snake.png";
std::string ResourceManager::m_invalidTexture = ResourceManager::DEFAULT_INVALID_TEXTURE;

/***************************
 *    TEXTURE METHODS
 **************************/

sf::Texture* ResourceManager::GetTexture(const std::string filePath) {

    // Search through the map to see if there is already an entry
    for (auto element: m_textureMap) {
        //std::cout << element.first << " " << filePath << std::endl;

        // We also want to check that the path is not invalid, as otherwise it would just be
        // stuck as invalid, because it would technically have an entry in the map
        if (element.first == filePath && element.first != m_invalidTexture)
            return element.second;
    }

    // If the code has made it to this point, it hasn't found a matching entry
    // in the map. We use the new keyword because we want to store these variables
    // outside the stack
    sf::Texture* texture = new sf::Texture();

    // If the texture doesn't load properly, we assign our invalid texture to it
    if (!texture->loadFromFile(filePath)) {
        texture->loadFromFile(m_invalidTexture);
    }

    m_textureMap[filePath] = texture;

    return m_textureMap[filePath];
}

int ResourceManager::GetNumberOfTextures() {
    return m_textureMap.size();
}

void ResourceManager::ClearTextures() {

    // First we delete all the pointers
    for (auto element: m_textureMap) {
        delete element.second;
    }

    // And now clear all the entries
    m_textureMap.clear();
}

std::string ResourceManager::GetInvalidTexturePath() {
    return m_invalidTexture;
}

/******************************
 *           MISC
 *****************************/

bool ResourceManager::Contains(std::vector<std::string> vec, std::string str) {
    for (std::string s: vec) {
        if (s == str)
            return true;
    }
    return false;
}
