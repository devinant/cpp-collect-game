#include "Tileset.h"

Tileset::Tileset(const char* texture)
	: graphics_(texture, false)
{
	size_t nTiles = Component::getHge()->System_GetState(HGE_SCREENWIDTH) % static_cast<int>(graphics_.getWidth());
	nTextureCols_ = static_cast<size_t>(graphics_.getWidth() / nTiles);
	nTextureRows_ = static_cast<size_t>(graphics_.getHeight() / nTiles);
	nCols_ = (Component::getHge()->System_GetState(HGE_SCREENWIDTH) / nTiles);
	nRows_ = (Component::getHge()->System_GetState(HGE_SCREENHEIGHT) / nTiles);

	tileDimension_ = static_cast<float>(nTiles);

	// Reserve the size
	graphicsRender_.reserve(nCols_ * nRows_);
}

Tileset::~Tileset() {}

float Tileset::getTileDimension() const
{
	return tileDimension_;
}
size_t Tileset::getTextureCols() const
{
	return nTextureCols_;
}
size_t Tileset::getTextureRows() const
{
	return nTextureRows_;
}
size_t Tileset::getCols() const
{
	return nCols_;
}
size_t Tileset::getRows() const
{
	return nRows_;
}

//
// BEWARE: This function uses Tileset::computeCoord(), it modifies Tileset::computedX_ and Tileset::computedY_ 
// when called.
//
bool Tileset::load(const char* map)
{
	bool success = false;

	// Open the map and try to load all the values
	std::ifstream file(map);

	if (file.is_open())
	{
		// Set the new "hotspot" for each tile.
		computedTileCenter_ = tileDimension_ * 0.5f;

		for (size_t i = 0; i < nCols_ * nRows_; i++)
		{
			file >> computedTile_;
			file >> computedRotation_;

			// Compute coordinates for local tiles
			computeCoord(computedTile_, nTextureCols_); 
			graphics_.load(new hgeSprite(graphics_.getTexture(), static_cast<float>(computedX_), static_cast<float>(computedY_), tileDimension_, tileDimension_));

			// Compute coordinates for global tiles
			computeCoord(i, nCols_);

			graphicsRender_.push_back(
				Graphics::Renderer(
					static_cast<float>(computedX_)+computedTileCenter_, 
					static_cast<float>(computedY_)+computedTileCenter_, 
					(computedRotation_ * 0.01745329251f)
				)
			);
		}

		// Normalize
		graphics_.setCenter(computedTileCenter_);

		success = true;
		file.close();
	}

	return success;
}

// 
// BEWARE: This function modifies Tileset::computedX_ and Tileset::computedY_
// 
void Tileset::computeCoord(size_t dot, size_t columns)
{
	computedX_ = (dot % columns) * static_cast<size_t>(tileDimension_);
	computedY_ = (dot / columns) * static_cast<size_t>(tileDimension_);
}
void Tileset::render()
{
	graphics_.render(graphicsRender_);
}