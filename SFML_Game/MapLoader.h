#pragma once

#include <vector>
#include "Map.h"

class MapLoader
{
	public:
		MapLoader();
		~MapLoader();

		std::shared_ptr<Map> loadMap(const char *mapFilePath);

		std::shared_ptr<Map> getMap() const { return map; }
	private:
		void createQuad(sf::VertexArray &va, int x, int y, const sf::Vector2u &tileSize, int tilesetTextureX, const std::vector<int> &layergIDs, int i);
		void loadMapTilesheet(std::string tileset, const sf::Vector2u &tileSize, unsigned int width, unsigned int height);
		bool loadMapFile(const char *filePath);

		sf::VertexArray v;
		sf::VertexArray v2;
		sf::VertexArray v3;

		sf::Texture tilesetTexture;

		std::vector<sf::FloatRect> collisionObjects;

		std::vector<Coordinate> tileCoordinates;
		std::vector<int> layerOnegIDs;
		std::vector<int> layerTwogIDs;
		std::vector<int> layerThreegIDs;

		std::shared_ptr<Map> map;

		int width, height;
		int tileCount;

		std::string tilesetTextureFilePath;
};