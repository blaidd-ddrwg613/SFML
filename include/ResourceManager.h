/*
MIT License

Copyright (c) 2018 Jack Featherstone

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

DEPENDENCIES:
std::string
std::map
sf::Texture
sf::SoundBuffer
std::vector
std::filesystem
std::stringstream
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <filesystem>

/*

SPECIFICATIONS:
SFML 2.5.1
2018 Q4

This class has been created with the idea of increasing performance in a large
scale game application that references a large amount of textures. With the
implementation of this class, it will be easier to store references to all
textures used, such that no texture is loaded twice, wasting precious memory.
As of now, this class has been redisgned to hold sound files as well, with the
same intention of increasing performance as before

The basic structure of the class will be a map that holds the loaded references
and a method that will allow for the user to both access and create entries
fluidly.
*/

class ResourceManager {

private:
    /**
     * @brief This map will hold pointers to all of the textures necessary.
     * The key for the map will be the path to the file, such that we can not only access
     * the texture through this, but differentiate between similarly named files in
     * different locations. It is defined as static such that no instance of the class
     * needs to be created.
     */
    static std::map<std::string, sf::Texture*> m_textureMap;
    static std::string m_invalidTexture;
    const static std::string DEFAULT_INVALID_TEXTURE;

public:

    /***************************
     *    TEXTURE METHODS
     **************************/

    /**
     * @brief Get the Texture that is at the given file path. If this texture has been previously
     * loaded, a pointer to the previous object will be returned. Otherwise, a new pointer entry will be
     * created in the texture map and returned.
     *
     * @param filePath The (relative to project folder or absolute) location of the texture file
     * @return sf::Texture* A pointer to the texture at the given file path
     */
    static sf::Texture* GetTexture(const std::string filePath);

    /**
     * @brief Returns the size of the m_textureMap object
     *
     * @return int The number of texture entries loaded in the resource manager
     */
    static int GetNumberOfTextures();

    /**
     * @brief Set the Invalid Texture Path to a new value. Can be relative to the project folder or
     * an absolute path.
     *
     * @param filePath The new file that will be referenced when a texture is not found.
     */
    static void setInvalidTexturePath(const std::string filePath);

    /**
     * @brief Get the Invalid Texture Path.
     *
     * @return std::string The file that will be referenced when a texture is not found.
     */
    static std::string GetInvalidTexturePath();

    /**
     * @brief Delete all of the pointers held in m_textureMap and clear the respective entries
     */
    static void ClearTextures();

    /************************
     *        MISC
     ************************/

    /**
     * @brief A simple method to find whether a string is contained in a vector
     *
     * @param vec The vector of reference strings
     * @param str The string that may or may not be present in the vector
     * @return true The string is found in the vector
     * @return false The string is not found in the vector
     */
    static bool Contains(std::vector<std::string> vec, std::string str);
};
