#pragma once
#include "Generation.h"



Generation::Generation() {
    sky = sf::Color(sf::Uint8(125), sf::Uint8(125), sf::Uint8(255), sf::Uint8(255));
    red = sf::Color(sf::Uint8(255), sf::Uint8(0), sf::Uint8(0), sf::Uint8(255));
    green = sf::Color(sf::Uint8(0), sf::Uint8(255), sf::Uint8(0), sf::Uint8(255));
    dirt = sf::Color(sf::Uint8(155), sf::Uint8(118), sf::Uint8(83), sf::Uint8(255));
    topGrass = sf::Color(sf::Uint8(10), sf::Uint8(255), sf::Uint8(10), sf::Uint8(255));
    stone = sf::Color(sf::Uint8(125), sf::Uint8(125), sf::Uint8(125), sf::Uint8(255));
    colorTile = sf::Color(sf::Uint8(0), sf::Uint8(0), sf::Uint8(0), sf::Uint8(255));
    diamond = sf::Color(sf::Uint8(188), sf::Uint8(242), sf::Uint8(255), sf::Uint8(255));
    gold = sf::Color(sf::Uint8(255), sf::Uint8(215), sf::Uint8(0), sf::Uint8(255));
    water = sf::Color(sf::Uint8(0), sf::Uint8(0), sf::Uint8(255), sf::Uint8(255));
    sand = sf::Color(sf::Uint8(255), sf::Uint8(191), sf::Uint8(0), sf::Uint8(255));
    caveBackGround = sf::Color(sf::Uint8(55), sf::Uint8(55), sf::Uint8(55), sf::Uint8(255));
    snow = sf::Color(sf::Uint8(255), sf::Uint8(255), sf::Uint8(255), sf::Uint8(255));
    wood = sf::Color(sf::Uint8(202), sf::Uint8(164), sf::Uint8(114), sf::Uint8(255));
    foliage = sf::Color(sf::Uint8(80), sf::Uint8(96), sf::Uint8(84), sf::Uint8(255));
    lava = sf::Color(sf::Uint8(81), sf::Uint8(6), sf::Uint8(13), sf::Uint8(255));
    obsidian = sf::Color(sf::Uint8(68), sf::Uint8(80), sf::Uint8(85), sf::Uint8(255));

    tileColor[0] = &sky;
    tileColor[1] = &dirt;
    tileColor[2] = &topGrass;
    tileColor[3] = &water;
    tileColor[4] = &sand;
    tileColor[5] = &caveBackGround;
    tileColor[6] = &stone;
    tileColor[7] = &diamond;
    tileColor[8] = &gold;
    tileColor[9] = &snow;
    tileColor[10] = &wood;
    tileColor[11] = &foliage;
    tileColor[12] = &lava;
    tileColor[13] = &obsidian;

    /*tilesColor.push_back(sky);
    tilesColor.push_back(dirt);
    tilesColor.push_back(topGrass);
    tilesColor.push_back(water);
    tilesColor.push_back(sand);*/

    //HEIGHT
    baseFlatTerrain.SetFrequency(0.2);
    baseFlatTerrain.SetPersistence(0.5);
    flatTerrain.SetSourceModule(0, baseFlatTerrain);
    flatTerrain.SetScale(0.001);


    terrainType.SetFrequency(0.10);

    terrainType.SetPersistence(0.015);

    mountain.SetPersistence(0.05);
    mountain.SetFrequency(1);
    mountain.SetOctaveCount(3);

    finalTerrain.SetSourceModule(0, flatTerrain);
    finalTerrain.SetSourceModule(1, mountain);
    finalTerrain.SetControlModule(terrainType);
    finalTerrain.SetBounds(0.0, 1000.0);
    finalTerrain.SetEdgeFalloff(0.125);
    ratioTimeTile = 0.002;

    //CAVE
    cave.SetOctaveCount(2);

    // STONE AND ORE
    stonePerlin.SetOctaveCount(2);
    stonePerlin.SetFrequency(0.5);

    orePerlin.SetOctaveCount(2);
    orePerlin.SetFrequency(1);

    // TREES AND SNOW
    treeZonePerlin.SetFrequency(0.05);
    treeZonePerlin.SetOctaveCount(1);

    treeFrequencyPerlin.SetOctaveCount(3);
    treeFrequencySpawnPerlin.SetOctaveCount(4);
    treeFrequencySpawnPerlin.SetFrequency(6);
    offsetTreeTrunk.SetSourceModule(0,heightTreeTrunk);
    offsetTreeTrunk.SetBias(1);


    snowPerlin.SetFrequency(0.075);
    snowPerlin.SetOctaveCount(2);

    // HELL
    normalToHellHeightMap.SetFrequency(2);
    normalToHellHeightMap.SetOctaveCount(3);

    

}

Generation::~Generation() {

    
}
sf::Sprite Generation::Render() {
    sf::Time dt = deltaClock.getElapsedTime();
    dt.asSeconds();
    for (auto i = 0; i < xTiles; i++) {
        for (auto j = 0; j < yTiles; j++) {
            setPixelsColorFromTile(size, i, j, tabPerlin[i][j]);
        }
    }
    texture.loadFromImage(imagePerlin);
    SpritePerlin.setTexture(texture);
    std::cout << "/ Render : " << deltaClock.getElapsedTime().asSeconds() - dt.asSeconds() << " s " << std::endl;
    return SpritePerlin;
}

void Generation::setPixelsColorFromTile(sf::Vector2f size,int i, int j, TileType tile) {
    for (unsigned int k = 0; k < (size.x); k++) {
        for (unsigned int l = 0; l < (size.y); l++) {
            imagePerlin.setPixel(i * size.x + k, j * size.y + l, *tileColor[tile]);
        }
    }
}


        
void Generation::GenerateHeightDirtWater(int newi ,int newj,int maxi,int maxj )
{
    TileType currentTile;
    //std::cout << StartingHeight << std::endl;
    for (auto i = newi; i < maxi; i++) {

        double value = finalTerrain.GetValue((xOffset + i) * step, 0.0, 0.0);
        value = value * -1;
        if (value < -1.0) value = -1.0;
        if (value > 1.0) value = 1.0;
        height = height + int(value * heightMulitplier);
        for (auto j = newj; j < maxj; j++) {
            if (j > height) {
                colorTile = dirt;
                currentTile = tileDirt;
            }
            else if (j == height) {
                if (j > StartingHeight) {
                    colorTile = sand;
                    currentTile = tileSand;
                }
                else {
                    colorTile = topGrass;
                    currentTile = tileTopGrass;
                }
            }
            else {
                if (j > StartingHeight) {
                    colorTile = water;
                    currentTile = tileWater;
                }
                else {
                    colorTile = sky;
                    currentTile = tileSky;
                }
            }
            tabPerlin[i][j] = currentTile;
        }
    }
}


void Generation::GenerateCaves(int newi, int newj, int maxi , int maxj) {
    TileType currentTile;
    for (auto i = newi; i < maxi; i++){
        for (auto j = newj; j < maxj; j++) {
            double value = cave.GetValue((xOffset + i) * step, (yOffset + j) * step,0.0);
       
            if (tabPerlin[i][j] == tileDirt || tabPerlin[i][j] == tileTopGrass) {
                if (value > -0.15) {
                    /*if (tabPerlin[i][j] == tileDirt) {
                        colorTile = dirt;
                        currentTile = tileDirt;
                    }
                    else {
                        colorTile = topGrass;
                        currentTile = tileTopGrass;
                    }*/
                    currentTile = tabPerlin[i][j];
                }
                else {
                    colorTile = caveBackGround;
                    currentTile = tileCave;
                }
                tabPerlin[i][j] = currentTile;
            }
        }
    }
}
double Generation::getStoneValueFromStartingHeight(int j) {
    int currentheight = StartingHeight - j;
    
    if (currentheight > 0) {
        return 0.7;
    }
    else {
        if (currentheight < heightMaxStoneValue) {
            return -0.8;
        }
        return (currentheight * -1.6 / heightMaxStoneValue) + 0.8;
    }
    
}

bool Generation::GetOreValueFromStartingHeight(int i,int j, int minHeight,int heightMaxSpawnValue,TileType ore,TileType &currentTile,double seedOffset,double valueWhenHeightInferior,double valueWhenHeightSuperior,double ratioSpawn) {
    int currentheight = StartingHeight - j;
    double value = orePerlin.GetValue((xOffset + i) * step, (yOffset + j) * step, seedOffset);
    if (value < -1.0) value = -1;
    if (value > 1.0) value = 1;
    double valueSpawn = 3;
    if (currentheight > -minHeight) {
        valueSpawn = valueWhenHeightInferior;
    }
    else {
        if (currentheight < -heightMaxSpawnValue) {
            valueSpawn = valueWhenHeightSuperior;
        }
        else {
            valueSpawn = (-(currentheight * ratioSpawn / -heightMaxSpawnValue)) + valueWhenHeightInferior;
        }
        
    }

    if (value > valueSpawn) {
        currentTile = ore;
        return true;
    }
    return false;

}
void Generation::GenerateStoneAndOres(int newi, int newj, int maxi, int maxj){
    TileType currentTile;
    for (auto i = newi; i < maxi; i++) {
        for (auto j = newj; j < maxj; j++) {
            double value = stonePerlin.GetValue((xOffset + i) * step, (yOffset + j) * step, 0.0);

            if (tabPerlin[i][j] == tileDirt || tabPerlin[i][j] == tileTopGrass) {

                if (value > getStoneValueFromStartingHeight(j)) {                    
                    
                    colorTile = stone;
                    currentTile = tileStone;

                    TrySpawnOres(i,j,currentTile);


                }
                else {
                    if (tabPerlin[i][j] == tileDirt) {
                        colorTile = dirt;
                        currentTile = tileDirt;
                    }
                    else {
                        colorTile = topGrass;
                        currentTile = tileTopGrass;
                    }
                }
                tabPerlin[i][j] = currentTile;
            }
        }
    }
}
void Generation::TrySpawnOres(int i,int j,TileType &currentTile) {

    if(GetOreValueFromStartingHeight(i, j, 300, 400, tileDiamond,currentTile, 10000,1,1,0.2)){}
    else {
        GetOreValueFromStartingHeight(i, j, 150, 500, tileGold, currentTile, 40000, 0.95, 0.75, 0.2);
    }
    
}
double Generation::getSnowValueFromStartingHeight(int j) {
    int currentheight = StartingHeight - j;

    if (currentheight < -10) {
        return 1;
    }
    else {
        if (currentheight > 50) {
            return -0.5;
        }
        else {
            return (-(currentheight * 0.75 / 50)) + 0.55;
        }
        
    }
}

void Generation::TrySpawntree(int i) {
    for (auto j = 0; j < yTiles - 1; j++) {
        if (tabPerlin[i][j] == tileSky && (tabPerlin[i][j + 1] != tileSky && tabPerlin[i][j + 1] != tileCave && tabPerlin[i][j + 1] != tileWater)) {
            if (treeFrequencySpawnPerlin.GetValue((xOffset + i) * step, 0.0, 0.0) > 0.3) {
                SpawnTreeAt(i, j);
            }             
        }
    }
}

void Generation::SpawnTreeAt(int i,int j) {
    double value = offsetTreeTrunk.GetValue((xOffset + i) * step, 0.0, 0.0);
    if (value < 0) value = value * -1;
     int TrunkSize = value * HeightTreeMultiplier + 2;

     for (auto k = 0; k < TrunkSize; k++) {
         if (j-k > 0)tabPerlin[i][j - k] = tileWood;
     }
     SpawnFoliageAt(i, j - TrunkSize);
}

void Generation::SpawnFoliageAt(int i, int j) {
    for (auto l = -1; l < 2; l++) {
        for (auto k = 0; k < 2; k++) {
            if ((j - k > 0) && (i + l) > 0) {
                if(tabPerlin[i+l][j - k] == tileSky) tabPerlin[i + l][j - k]  = tileFoliage;
            }
        }
    }
}

void Generation::GenerateTreesAndSnow(int newi, int newj, int maxi, int maxj) {

    for (auto i = newi; i < maxi; i++) {
        
        double zoneSelection = treeZonePerlin.GetValue((xOffset + i) * step,0.0,0.0);
        float valueZone = 0;
        if (zoneSelection > 0) {
            treeFrequencyPerlin.SetFrequency(HighFrequencyTree);
            valueZone = -1.0;
        }
        else {
            treeFrequencyPerlin.SetFrequency(LowFrequencyTree);
            valueZone = 0.2;
        }

        if (treeFrequencyPerlin.GetValue((xOffset + i) * step, 0.0, 0.0) > valueZone) {
            TrySpawntree(i);
        }
    }



    for (auto i = newi; i < maxi; i++) {
        double value = snowPerlin.GetValue((xOffset + i) * step, 0.0, 0.0);
        for (auto j = newj; j < maxj; j++) {
            if (value > getSnowValueFromStartingHeight(j)) {
                if (tabPerlin[i][j] == tileSky && (tabPerlin[i][j + 1] != tileSky && tabPerlin[i][j + 1] != tileCave)) {
                    tabPerlin[i][j] = tileSnow;
                    break;
                }
            }
        }
    }
    
}
void Generation::GenerateHell() {
    int currentHeight = StartingHeight;
    TileType currentTile;
    for (auto i = 0; i < xTiles; i++) {   
        double valueCeiling = normalToHellHeightMap.GetValue((xOffset + i) * step, 0.0, 0.0);
        double valueFloor = hellHeightMap.GetValue((xOffset + i) * step, 0.0, 0.0);
        valueCeiling = valueCeiling * -1;
        valueFloor = valueFloor * -1;
        if (valueCeiling < -1.0) valueCeiling = -1.0;
        if (valueCeiling > 1.0) valueCeiling = 1.0;

        if (valueFloor < -1.0) valueFloor = -1.0;
        if (valueFloor > 1.0) valueFloor = 1.0;

        heightCeillingHeightCurrent = heightCeillingHeightCurrent + int(valueCeiling * hellHeightMultiplier);
        heightHellFloorHeightCurrent = heightHellFloorHeightCurrent + int(valueFloor * hellHeightMultiplier / 2);
        for (auto j = 0; j < yTiles; j++) {
            if (currentHeight - j > heightCeillingHeightCurrent) {
                currentTile = tabPerlin[i][j];
            }
            else {
                if (currentHeight - j > heightHellFloorHeightCurrent) {
                    if (currentHeight - j < minYoffset + hellFloorHeight) {
                        currentTile = tileLava;
                    }
                    else {
                        currentTile = tileCave;
                    }
                           
                }
                else {             
                    currentTile = tileObsidian;
                        
                }
                    
            }        
            tabPerlin[i][j] = currentTile;
        }
    }
}

void Generation::StartGeneration() {
    height = 0;
    StartingHeight = 100;
    baseHeightForGround = 0;
    heightMulitplier = 8;
    xOffset = 0;
    yOffset = 0;

    baseNormalToHellHeight = minYoffset + hellFloorHeight + hellCeillingHeight;
    baseHellToFloorHeight = minYoffset + hellFloorHeight;

    size.x = xWindowsHeight / xTiles;
    size.y = yWindowsWidth / yTiles;
    imagePerlin.create(yWindowsWidth, xWindowsHeight, sf::Color::Black);

    baseHeightForGround = StartingHeight;

    height = baseHeightForGround;
    heightCeillingHeightCurrent = baseNormalToHellHeight;
    heightHellFloorHeightCurrent = baseHellToFloorHeight;


    long long t1 = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::srand((unsigned int)t1);
    double seed = int(rand() % 10000) * 500;
    normalToHellHeightMap.SetSeed(seed);
    hellHeightMap.SetSeed(seed);
    treeFrequencyPerlin.SetSeed(seed);
    treeFrequencySpawnPerlin.SetSeed(seed);
    treeZonePerlin.SetSeed(seed);
    snowPerlin.SetSeed(seed);
    orePerlin.SetSeed(seed);
    cave.SetSeed(seed);
    stonePerlin.SetSeed(seed);
    mountain.SetSeed(seed);
    terrainType.SetSeed(seed);
    GenerateHeightDirtWater();
    GenerateCaves();
    GenerateStoneAndOres();
    GenerateTreesAndSnow();
}
void Generation::SpriteUpdateOnInput() {
    sf::Time dt = deltaClock.restart();
    sf::Vector2i dirValue;
    int newi = 0;
    int newj = 0;
    int maxi = xTiles;
    int maxj = yTiles;
    if (timeRatio >= ratioTimeTile) {
        xOffset = xOffset + dir.x;
        yOffset = yOffset + dir.y;
        dirValue.x = dir.x;
        dirValue.y = dir.y;
        timeRatio = 0;
        double value;
        double valueforHellCeiling;
        double valueforHellFloor;
        if (dirValue.x < 0) {
             value = finalTerrain.GetValue((xOffset) * step, 0.0, 0.0);
             valueforHellCeiling = normalToHellHeightMap.GetValue((xOffset)*step, 0.0, 0.0);
             valueforHellFloor = hellHeightMap.GetValue((xOffset)*step, 0.0, 0.0);
        }
        else {
            value = finalTerrain.GetValue((xOffset - 1) * step, 0.0, 0.0);
            valueforHellCeiling = normalToHellHeightMap.GetValue((xOffset - 1)*step, 0.0, 0.0);
            valueforHellFloor = hellHeightMap.GetValue((xOffset - 1) * step, 0.0, 0.0);
        }


        if (dirValue.x != 0) {
            value = value * -1;
            valueforHellCeiling = valueforHellCeiling * -1;
            valueforHellFloor = valueforHellFloor * -1;
            if (dir.x > 0) {
                baseHeightForGround = baseHeightForGround + int(value * heightMulitplier);
                baseNormalToHellHeight = baseNormalToHellHeight + int(valueforHellCeiling * hellHeightMultiplier);
                baseHellToFloorHeight = baseHellToFloorHeight + int(valueforHellFloor * hellHeightMultiplier/2);
                newi = maxi -1;
                newj = 0;
            }
            else {
                baseHeightForGround = baseHeightForGround - int(value * heightMulitplier);
                baseNormalToHellHeight = baseNormalToHellHeight - int(valueforHellCeiling * hellHeightMultiplier);
                baseHellToFloorHeight = baseHellToFloorHeight - int(valueforHellFloor * hellHeightMultiplier/2);
                newi = 0;
                maxi = 1;
                newj = 0;
            }
        }
        if (dirValue.y != 0) {
            if (dir.y > 0) {
                newi = 0;
                newj = maxj;
            }
            else {
                newi = 0;
                newj = 0;
                maxj = 1;
            }
        }
        if ((StartingHeight - int(yTiles) - dirValue.y) < minYoffset) {
            dirValue.y = 0;
            yOffset--;
            
        }
        baseHeightForGround -= dirValue.y;
        StartingHeight -= dirValue.y;
        height = baseHeightForGround;
        heightCeillingHeightCurrent = baseNormalToHellHeight;
        heightHellFloorHeightCurrent = baseHellToFloorHeight;
    }
    else {
        dirValue.x = 0;
        dirValue.y = 0;
    }


    if (dirValue.x != 0 || dirValue.y != 0) {
        //moveTab(dirValue);
        //std::cout << StartingHeight << std::endl;
        //GenerateHeightDirtWater(newi,newj,maxi,maxj);
        //GenerateCaves(newi, newj, maxi, maxj);
        //GenerateStoneAndOres(newi, newj, maxi, maxj);
        //GenerateTreesAndSnow(newi, newj, maxi, maxj);
        
        GenerateHeightDirtWater();
        GenerateCaves();
        GenerateStoneAndOres();
        GenerateTreesAndSnow();

        GenerateHell();
        dirValue.x = 0;
        dirValue.y = 0;
        
        std::cout << "Generation : " << dt.asSeconds() << " s";
    }
    timeRatio += dt.asSeconds();
   
}

void Generation::moveTab(sf::Vector2i dir) {
    if (dir.x > 0) {
        for (auto i = 0; i < xTiles - 1; i++) {
                double value = finalTerrain.GetValue((xOffset + i) * step, 0.0, 0.0);
                value = value * -1;
                if (value < -1.0) value = -1.0;
                if (value > 1.0) value = 1.0;
                height = height + int(value * heightMulitplier);
            
            for (auto j = 0; j < yTiles; j++) {
                tabPerlin[i][j] = tabPerlin[i + 1][j];
            }
        }

    }
    else if (dir.x < 0) {
        for (auto i = xTiles-1; i >= 1; i--) {
            for (auto j = 0; j < yTiles; j++) {
                tabPerlin[i][j] = tabPerlin[i - 1][j];
            }

        }
    }
    if (dir.y > 0) {
        /*for (auto i = 0; i < xTiles; i++) {
            for (auto j = 0; j < yTiles-1; j++) {
                tabPerlin[i][j] = tabPerlin[i][j+1];
            }

        }*/
        GenerateHeightDirtWater();
        GenerateCaves();
        GenerateStoneAndOres();
        GenerateTreesAndSnow();
    }
    else if (dir.y < 0) {
        /*for (auto i = 0; i < xTiles; i++) {
            for (auto j = yTiles - 1; j >= 1; j--) {
                tabPerlin[i][j] = tabPerlin[i][j - 1];
            }

        }*/
        GenerateHeightDirtWater();
        GenerateCaves();
        GenerateStoneAndOres();
        GenerateTreesAndSnow();
    }
}

