#include "MapLoader.h"

MapLoader::MapLoader() 
{
	width = 512; height = 512; //Default values, these get changed.	
	tileCount = width * height;
}

std::shared_ptr<Map> MapLoader::loadMap(const char *mapFilePath)
{
	loadMapFile(mapFilePath);
	
	//Removes the extra characters
	for (int i = 0; i < 3; ++i) 
	{
		tilesetTextureFilePath.erase(tilesetTextureFilePath.begin());
	}

	loadMapTilesheet(tilesetTextureFilePath, sf::Vector2u(TILE_SIZE, TILE_SIZE), width, height);

	map = std::make_shared<Map>(Map(width, height, v, v2, v3, tilesetTexture, collisionObjects));

	//Reset, not really necesarilly
	v.resize(0);
	v2.resize(0);
	v3.resize(0);

	return map;
}

void MapLoader::createQuad(sf::VertexArray &va, int x, int y, const sf::Vector2u &tileSize, int tilesetTextureX, const std::vector<int> &layergIDs, int i)
{
	va.setPrimitiveType(sf::Quads);
	va.resize(width * height * 4);

	sf::Vertex *quad = &va[(tileCoordinates[i].x + (tileCoordinates[i].y * width)) * 4];

	//define the quad
	quad[0].position = sf::Vector2f(tileCoordinates[i].x * tileSize.x, tileCoordinates[i].y * tileSize.y);
	quad[1].position = sf::Vector2f((tileCoordinates[i].x + 1) * tileSize.x, tileCoordinates[i].y * tileSize.y);
	quad[2].position = sf::Vector2f((tileCoordinates[i].x + 1) * tileSize.x, (tileCoordinates[i].y + 1) * tileSize.y);
	quad[3].position = sf::Vector2f(tileCoordinates[i].x * tileSize.x, (tileCoordinates[i].y + 1) * tileSize.y);

	//gIDs[i] = tileCoordinates[i].x + (tileCoordinates[i].y * width);

	int tileTextureY = std::ceil(layergIDs[i] / tilesetTextureX);
	int tileTextureX = layergIDs[i] - (tileTextureY * tilesetTextureX) - 1;

	//std::cout << layergIDs[0] << std::endl;

	//std::cout << "X: " << tileTextureX << " " << "Y: " << tileTextureY << std::endl;

	//define its 4 texture coordinates (where it is on the tilesheet)
	quad[0].texCoords = sf::Vector2f(tileTextureX * tileSize.x, tileTextureY * tileSize.y);
	quad[1].texCoords = sf::Vector2f((tileTextureX * tileSize.x) + tileSize.x, tileTextureY * tileSize.y);
	quad[2].texCoords = sf::Vector2f((tileTextureX * tileSize.x) + tileSize.x, (tileTextureY * tileSize.y) + tileSize.y);
	quad[3].texCoords = sf::Vector2f(tileTextureX * tileSize.x, (tileTextureY * tileSize.y) + tileSize.y);
}

//Width and height are in tiles (multiply by tileSize if you want in pixels)
//TODO: Does not work for images with certain widths/heights (believe the error is in creating the quad, need to fix)
//TODO: Divide map into separate vertex arrays
void MapLoader::loadMapTilesheet(std::string tileset, const sf::Vector2u &tileSize, unsigned int width, unsigned int height) 
{
	tilesetTexture.loadFromFile(tileset);

	int tilesetTextureX = tilesetTexture.getSize().x / tileSize.x;
	int tilesetTextureY = tilesetTexture.getSize().y / tileSize.y;

	for (int i = 0; i < (width * height); ++i)
	{
		createQuad(v, tileCoordinates[i].x, tileCoordinates[i].y, tileSize, tilesetTextureX, layerOnegIDs, i);

		if (layerTwogIDs[i] != 0) 
			createQuad(v2, tileCoordinates[i].x, tileCoordinates[i].y, tileSize, tilesetTextureX, layerTwogIDs, i);

		if (layerThreegIDs[i] != 0)
			createQuad(v3, tileCoordinates[i].x, tileCoordinates[i].y, tileSize, tilesetTextureX, layerThreegIDs, i);
	}
}

//TODO: Add error checking
bool MapLoader::loadMapFile(const char *filePath)
{
	rapidxml::xml_document<> doc;

	std::ifstream file(filePath);

	std::stringstream buffer;

	buffer << file.rdbuf();

	file.close();

	std::string content(buffer.str());

	doc.parse<0>(&content[0]);

	std::vector<int> gids;
	int x = 0;
	int y = 0;

	std::vector<Coordinate> coordinates;

	rapidxml::xml_node<> *pRoot = doc.first_node();

	//Get the tileset file
	rapidxml::xml_node<> *tilesetNode = pRoot->first_node("tileset");
	tilesetTextureFilePath = tilesetNode->first_node("image")->first_attribute("source")->value();

	rapidxml::xml_attribute<> *tileCountAttribute = tilesetNode->first_attribute("tilecount");
	
	int tileCount = atoi(tileCountAttribute->value());

	//Get width and height
	rapidxml::xml_node<> *layer1Node = pRoot->first_node("layer");
	rapidxml::xml_attribute<> *widthAttribute = layer1Node->first_attribute("width");
	rapidxml::xml_attribute<> *heightAttribute = layer1Node->first_attribute("height");

	int width = atoi(widthAttribute->value());
	int height = atoi(heightAttribute->value());

	layerOnegIDs.reserve(width * height);
	layerTwogIDs.reserve(width * height);
	layerThreegIDs.reserve(width * height);

	//std::cout << width << " " << height << std::endl;

	//Get objects and put them in the vector
	for (rapidxml::xml_node<> *objectLayerNode = pRoot->first_node("objectgroup"); objectLayerNode; objectLayerNode = objectLayerNode->next_sibling()) 
	{
		for (rapidxml::xml_node<> *objectNode = objectLayerNode->first_node("object"); objectNode; objectNode = objectNode->next_sibling())
		{
			collisionObjects.push_back(sf::FloatRect(atoi(objectNode->first_attribute("x")->value()), atoi(objectNode->first_attribute("y")->value()),
				atoi(objectNode->first_attribute("width")->value()), atoi(objectNode->first_attribute("height")->value())));
		}
	}

	int j = 0; //Layer counting variable

	for(rapidxml::xml_node<> *layerNode = pRoot->first_node("layer"); layerNode; layerNode = layerNode->next_sibling())
	{
		rapidxml::xml_node<> *dataNode = layerNode->first_node("data");

		for(rapidxml::xml_node<> *tileNode = dataNode->first_node("tile"); tileNode; tileNode = tileNode->next_sibling()) 
		{
			if(j == 0)
				layerOnegIDs.push_back(atoi(tileNode->first_attribute("gid")->value())); //gID = sprite to be drawn
			else if(j == 1)
				layerTwogIDs.push_back(atoi(tileNode->first_attribute("gid")->value()));
			else if(j == 2)
				layerThreegIDs.push_back(atoi(tileNode->first_attribute("gid")->value()));

			coordinates.push_back(Coordinate(x, y)); //Coordinate struct declared globaly in stdafx.h

			//	new tile(gid, x, y)

			if(x >= width - 1)
			{
				++y;

				x = 0;
			}
			else
			{
				++x;
			}

		}

		++j;

	}

	this->width = width;
	this->height = height;
	this->tileCount = tileCount;

	tileCoordinates = coordinates;

	return true;
}

MapLoader::~MapLoader()
{

}


