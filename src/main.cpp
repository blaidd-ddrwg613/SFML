#include <iostream>
#include <cmath>
#include "ResourceManager.h"

int wWidth = 1080;
int wHeight = 720;
std::string wTitle = "SFML Window";
std::vector<int> walk{0, 48, (48*2), (48*3)};
sf::Rect<int> playerRect;
sf::Sprite playerSprite;
sf::Texture playerTexture;
float frameSpeed = 9;
float frameCounter = 0;
int currentFrame = 0;

int main()
{
	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), wTitle);

	sf::Clock clock;

    playerTexture = *ResourceManager::GetTexture(RESOURCES_PATH"textures/character/Basic Character Spritesheet.png");

    playerRect = {48, 0, 48, 48};
    playerSprite.setTexture(playerTexture);
    playerSprite.setTextureRect(playerRect);
    playerSprite.scale(4,4);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::Resized)
			{
				wWidth = event.size.width;
                wHeight = event.size.height;
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
		}

		//calculate the delta time
		sf::Time deltaTime = clock.restart();
		float deltaTimeSeconds = deltaTime.asSeconds();

		//make sure delta time stays within normal bounds, like between one FPS and zero FPS
		deltaTimeSeconds = std::min(deltaTimeSeconds, 1.f);
		deltaTimeSeconds = std::max(deltaTimeSeconds, 0.f);

        // Update Code

        frameCounter += deltaTimeSeconds * frameSpeed;
        currentFrame = static_cast<int>(std::fmod(frameCounter, 8.0f));

        if (currentFrame > walk.size()) currentFrame = 0;

        playerRect.left = walk[currentFrame];
        playerSprite.setTextureRect(playerRect);

//        if ((float)frameCounter >= (60 / (float)frameSpeed))
//        {
//            frameCounter = 0;
//            currentFrame++;
//
//            if (currentFrame > walk.size()) currentFrame = 0;
//
//            playerRect.left = walk[currentFrame];
//            playerSprite.setTextureRect(playerRect);
//        }

		//game code....
		window.clear();
		window.draw(playerSprite);

		window.display();
	}

    ResourceManager::ClearTextures();

	return 0;
}