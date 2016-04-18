#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Component.h"
#include "Point.h"
#include <vector>
#include <hgeanim.h>

typedef std::vector<hgeSprite*> GraphicAssets;

class Graphics : public Component
{
public:
	enum Planes { NONE, HORIZONTAL, VERTICAL, ALL };
	enum Type { FIGURE, SPRITE, ANIMATION };

	class Renderer
	{
	public:
		Renderer(float x = 0.0f, float y = 0.0f, float rotation = 0.0f, float hscale = 1.0f, float vscale = 1.0f);
		~Renderer();
		void setAsset(size_t asset);
		void setX(float x);
		void setY(float y);
		void setPoint(Point& point);
		void setRotation(float rotation, bool gradual = false);
		void setScale(float scale, bool gradual = false, Graphics::Planes plane = Graphics::NONE);
		void setVScale(float vscale, bool gradual = false);
		void setHScale(float hscale, bool gradual = false);
		
		size_t getAsset() const;
		float getX() const;
		float getY() const;
		Point getPoint() const;
		float getRotation() const;
		float getVScale() const;
		float getHScale() const;
		
	private:
		size_t asset_;
		float x_;
		float y_;
		float centerX_;
		float centerY_;
		float rotation_;
		float hscale_;
		float vscale_;
	};

	Graphics(bool load = true, Graphics::Type type = Graphics::FIGURE);
	Graphics(const char* textureFile, bool loadTexture = true, Graphics::Type type = Graphics::FIGURE);
	
	virtual ~Graphics();
	
	void load(hgeSprite* asset);

	void setScale(float scale, bool gradual = false, Graphics::Planes plane = Graphics::NONE);
	void setFlip(Graphics::Planes plane = Graphics::NONE);
	void setCenter(float centerX, float centerY);
	void setCenter(float center = 0.0f);
	void setRotation(float rotation, bool gradual = false);
	void setZ(float x, int index = -1);
	void setColor(DWORD color, int alpha = -1);
	void setBlendMode(int blend);
	void setRectangle(float x, float y, float width, float height);

	void setWidth(float width);
	void setHeight(float height);

	// Accessing structured values
	HTEXTURE getTexture() const;
	float getWidth() const;
	float getHeight() const;
	float getVScale() const;
	float getHScale() const;
	float getRotation() const;

	hgeRect getBoundingBox() const;
	GraphicAssets getAssets() const;

	void render(float x, float y, size_t asset = 0, float rotation = 0.0f, float hscale = 1.0f, float vscale = 1.0f);
	
	//
	// Removal?: Renderer now contains the asset by default
	void render(size_t asset, Renderer& object);
	//

	void render(Renderer& renderer);

	//
	// Removal?: Renderer now contains the asset by default
	void render(std::pair<size_t, Renderer>& pair);
	//

	void render(std::vector<Renderer>& container);
	
private:
	float width_;
	float height_;
	float vscale_;
	float hscale_;
	float rotation_;
	bool flip_[2];

	HTEXTURE texture_;
	hgeRect boundingBox_;
	
	// Used by the renderer to decide how to render to asset
	Graphics::Type type_;

protected:
	GraphicAssets assets_; // Back compability;
};
#endif