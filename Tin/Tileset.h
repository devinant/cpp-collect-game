#ifndef TILESET_H
#define TILESET_H

#include<fstream>
#include "Graphics.h"

class Tileset
{
public:
	Tileset(const char* texture);
	virtual ~Tileset();

	float getTileDimension() const;
	size_t getTextureCols() const;
	size_t getTextureRows() const;
	size_t getCols() const;
	size_t getRows() const;
	
	// http://stackoverflow.com/questions/20791894/assign-tilemap-tiles-and-numerical-value-for-2d-game
	void computeCoord(size_t dot, size_t columns);
	bool load(const char* map);
	void render();

private:
	float tileDimension_;
	
	// These are all calculated values and
	// should not be modified
	size_t nTextureCols_;
	size_t nTextureRows_;
	size_t nCols_;
	size_t nRows_;

	// These values are used for computations
	// and are only used by this class.
	size_t computedX_;
	size_t computedY_;
	size_t computedTile_;
	float computedRotation_;
	float computedTileCenter_;

	Graphics graphics_;
	std::vector<Graphics::Renderer> graphicsRender_;
};
#endif