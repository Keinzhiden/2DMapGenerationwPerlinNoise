#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <noise/noise.h>
#include <iostream>
#include <map>
#include <chrono>

using namespace noise;

class Generation {
public:
    Generation();
    ~Generation();

    sf::Color sky;
    sf::Color red;
    sf::Color green;
    sf::Color dirt;
    sf::Color topGrass;
    sf::Color stone;
    sf::Color diamond;
    sf::Color gold;
    sf::Color water;
    sf::Color sand;
    sf::Color caveBackGround;
    sf::Color snow;
    sf::Color wood;
    sf::Color foliage;
    sf::Color lava;
    sf::Color obsidian;



    sf::Color colorTile;

    enum TileType
    {
        tileSky,
        tileDirt,
        tileTopGrass,
        tileWater,
        tileSand,
        tileCave,
        tileStone,
        tileDiamond,
        tileGold,
        tileSnow,
        tileWood,
        tileFoliage,
        tileLava,
        tileObsidian
    };


    const static unsigned int nbTiles = 14;
    sf::Color* tileColor[nbTiles];
    
    const static unsigned int xTiles = 200;
    const static unsigned int yTiles = 200;

    const unsigned int xWindowsHeight = 1000;
    const unsigned int yWindowsWidth = 1000;
    TileType tabPerlin[xTiles][yTiles];
    sf::Vector2f size;

    sf::Vector2i dir;

    float Speed;
    int index;
    

    //HEIGHT
    module::Perlin mountain;
    module::Billow baseFlatTerrain;
    module::ScaleBias flatTerrain;
    module::Perlin terrainType;
    module::Select finalTerrain;
    int height;
    int baseHeightForGround;
    int heightMulitplier;
    double xOffset;
    double yOffset;


    //CAVE
    module::Perlin cave;


    //ORE
    module::Perlin stonePerlin;
    module::Perlin orePerlin;
    double getStoneValueFromStartingHeight(int j);

    //TREES AND SNOW
    module::Perlin snowPerlin;
    module::Perlin treeFrequencyPerlin;
    module::Perlin treeZonePerlin;
    module::Perlin heightTreeTrunk;
    module::Perlin treeFrequencySpawnPerlin;
    module::ScaleBias offsetTreeTrunk;
    const float HighFrequencyTree = 2;
    const float LowFrequencyTree = 0.25;
    double getSnowValueFromStartingHeight(int j);

    //HELL
    module::Perlin hellHeightMap;
    module::Perlin normalToHellHeightMap;
    const int hellHeightMultiplier = 4;
    const int hellCeillingHeight = 50;
    const int hellFloorHeight = 30;
    int baseNormalToHellHeight;
    int baseHellToFloorHeight;
    int heightCeillingHeightCurrent;
    int heightHellFloorHeightCurrent;


    //Render
    sf::Image imagePerlin;
    sf::Texture texture;
    sf::Sprite SpritePerlin;
    void setPixelsColorFromTile(sf::Vector2f size, int x, int y, TileType tile);
    sf::Sprite Render();
    void moveTab(sf::Vector2i dir);

    //Generation
    void StartGeneration();
    void GenerateHeightDirtWater(int newi = 0, int newj = 0, int maxi = xTiles, int maxj = yTiles);
    void GenerateCaves(int newi = 0, int newj = 0, int maxi = xTiles, int maxj = yTiles);
    void GenerateStoneAndOres(int newi = 0, int newj = 0, int maxi = xTiles, int maxj = yTiles);
    void TrySpawnOres(int i,int j,TileType &currentTile );
    bool GetOreValueFromStartingHeight(int i, int j, int minHeight, int heightMaxSpawnValue, TileType ore, TileType& currentTile, double seedOffset, double valueWhenHeightInferior, double valueWhenHeightSuperior, double ratioSpawn);
    void TrySpawntree(int i);
    void SpawnTreeAt(int i,int j);
    void SpawnFoliageAt(int i, int j);
    void GenerateTreesAndSnow(int newi = 0, int newj = 0, int maxi = xTiles, int maxj = yTiles);
    void GenerateHell();


    void SpriteUpdateOnInput();
    
    
    double step = 0.05;
    double timeRatio;
    double ratioTimeTile;

    const int HeightTreeMultiplier = 2;
    const int heightMaxStoneValue = -400;
    const int minYoffset = -550;
    int StartingHeight;

private:


    sf::Clock deltaClock;

};


