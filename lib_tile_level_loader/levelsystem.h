#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>

#define ls LevelSystem


class LevelSystem {
	
	public:
		enum TILE {EMPTY, START, END, WALL, ENEMY, WAYPOINT};
		static void loadLevelFile(const std::string&, float tileSize = 100.f);
		static void render(sf::RenderWindow &window);
		static sf::Color getColor(TILE t);
		static void setColor(TILE t, sf::Color c);
		static int getWidth();
		static int getHeight();
		// static TILE getTile(sf::Vector2ul);
		static TILE getTile();
		// static sf::Vector2f getTilePosition(sf::Vector2ul);
		static sf::Vector2f getTilePosition();
		static TILE getTileAt(sf::Vector2f);
		
	protected:
		static std::unique_ptr<TILE[]> _tiles;
		static size_t _width;
		static size_t _height;
		static float _tileSize;
		static std::map<TILE, sf::Color> _colours;
		static std::vector<std::unique_ptr<sf::RectangleShape>> _sprites;
		static void buildSprites();

	private:
		LevelSystem() = delete;
		~LevelSystem() = delete;
		
	 
};
		




		