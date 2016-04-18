#include "Graphics.h"


Graphics::Graphics(bool load, Graphics::Type type)
{
	vscale_ = hscale_ = 1.0f;
	rotation_ = 0.0f;
	width_ = height_ = 0.0f;

	// This is probably a figure
	texture_ = 0;
	type_ = type;

	if (load) this->load(new hgeSprite(texture_, 0.0f, 0.0f, 0, 0));
}
Graphics::Graphics(const char* textureFile, bool load, Graphics::Type type)
{
	// Modifiers
	vscale_ = hscale_ = 1.0f;
	rotation_ = 0.0f;
	
	// Load the texture, throw an exception if something is wrong
	texture_ = Component::getHge()->Texture_Load(textureFile);
	type_ = type;

	// Get dimensions from the texture
	width_ = static_cast<float>(Component::getHge()->Texture_GetWidth(texture_, true));
	height_ = static_cast<float>(Component::getHge()->Texture_GetHeight(texture_, true));

	if (load) this->load(new hgeSprite(texture_, 0.0f, 0.0f, width_, height_));

	printf("Loaded texture: %s [%dx%d]\n", textureFile, static_cast<int>(width_), static_cast<int>(height_));
}
void Graphics::load(hgeSprite* sprite)
{
	assets_.push_back(sprite);
	assets_.back()->SetHotSpot(width_ * 0.5f, height_ * 0.5f);
}
Graphics::~Graphics()
{
	for (size_t i = 0; i < assets_.size(); i++)
	{
		delete assets_[i];
		assets_[i] = nullptr;
	}

	// Free the texture if it was loaded.
	if (texture_ != 0)
		Component::getHge()->Texture_Free(texture_);
}

void Graphics::setScale(float scale, bool gradual, Graphics::Planes plane)
{
	switch (plane)
	{
		case Graphics::ALL: 
		case Graphics::NONE: {
			if (gradual) {
				hscale_ += scale;
				vscale_ += scale;
			} else  {
				hscale_ = scale;
				vscale_ = scale;
			}
			break;
		}
		
		case Graphics::HORIZONTAL: {
			hscale_ = gradual ? hscale_ + scale : scale;
			break;
		}

		case Graphics::VERTICAL: {
			vscale_ = gradual ? vscale_ + scale : scale;
			break;
		}
	}
}
void Graphics::setFlip(Graphics::Planes plane)
{
	switch (plane)
	{
		case Graphics::NONE:       flip_[0] = flip_[1] = false;         break;
		case Graphics::HORIZONTAL: flip_[0] = false;  flip_[1] = true;  break;
		case Graphics::VERTICAL:   flip_[0] = true;   flip_[1] = false; break;
		case Graphics::ALL:        flip_[0] = flip_[1] = true;          break;
	}

	for (size_t i = 0; i < assets_.size(); i++)
		assets_[i]->SetFlip(flip_[0], flip_[1]);
}
void Graphics::setCenter(float centerX, float centerY)
{
	for (size_t i = 0; i < assets_.size(); i++)
		assets_[i]->SetHotSpot(centerX, centerY);
}
void Graphics::setCenter(float center)
{
	setCenter(center, center);
}
void Graphics::setRotation(float rotation, bool gradual)
{
	// Easing sets a value gradually
	if (gradual)
		rotation_ += rotation;
	else
		rotation_ = rotation;
}
void Graphics::setZ(float x, int index)
{
	for (size_t i = 0; i < assets_.size(); i++)
		assets_[i]->SetZ(x, index);
}
void Graphics::setColor(DWORD color, int alpha)
{
	for (size_t i = 0; i < assets_.size(); i++)
		assets_[i]->SetColor(color, alpha);
}
void Graphics::setBlendMode(int blend)
{
	for (size_t i = 0; i < assets_.size(); i++)
		assets_[i]->SetBlendMode(blend);
}
void Graphics::setRectangle(float x, float y, float width, float height)
{
	for (size_t i = 0; i < assets_.size(); i++)
		assets_[i]->SetTextureRect(x, y, width, height);
}
void Graphics::setWidth(float width)
{
	width_ = width;
}
void Graphics::setHeight(float height)
{
	height_ = height;
}
HTEXTURE Graphics::getTexture() const
{
	return texture_;
}
float Graphics::getWidth() const
{
	return width_;
}
float Graphics::getHeight() const
{
	return height_;
}
float Graphics::getVScale() const
{
	return vscale_;
}
float Graphics::getHScale() const
{
	return hscale_;
}
float Graphics::getRotation() const
{
	return rotation_;
}
hgeRect Graphics::getBoundingBox() const
{
	return boundingBox_;
}
GraphicAssets Graphics::getAssets() const
{
	return assets_;
}
void Graphics::render(float x, float y, size_t asset, float rotation, float hscale, float vscale)
{
	// If the default values are set use the values that reside inside the class
	float rotationValue = (rotation == 0.0f) ? rotation_ : rotation;
	float hscaleValue = (hscale == 1.0f) ? hscale_ : hscale;
	float vscaleValue = (vscale == 1.0f) ? vscale_ : vscale;

	assets_[asset]->RenderEx(x, y, rotationValue, hscaleValue, vscaleValue);
	assets_[asset]->GetBoundingBoxEx(x, y, rotationValue, hscaleValue, vscaleValue, &boundingBox_);

	// If this is an animation, update it continuosly
	if (type_ == Graphics::ANIMATION)
		static_cast<hgeAnimation*>(assets_[asset])->Update(Component::getHge()->Timer_GetDelta());
}
void Graphics::render(size_t asset, Renderer& renderer)
{
	Graphics::render(renderer.getX(), renderer.getY(), asset, renderer.getRotation(), renderer.getHScale(), renderer.getVScale());
}

// 
// Renders the Renderer object using the default renderer type
// 
// 
void Graphics::render(Renderer& renderer)
{
	Graphics::render(renderer.getX(), renderer.getY(), renderer.getAsset(), renderer.getRotation(), renderer.getHScale(), renderer.getVScale());
}


// REMOVE?
// Renders a pair
// 
void Graphics::render(std::pair<size_t, Renderer>& pair)
{
	Graphics::render(pair.first, pair.second);
}

// 
// Renders a collection of Renderer objects
// 
void Graphics::render(std::vector<Renderer>& container)
{
	for (size_t i = 0; i < container.size(); i++)
		Graphics::render(i, container[i]); // Graphics::render(i, collection.at(i));
}










Graphics::Renderer::Renderer(float x, float y, float rotation, float hscale, float vscale)
{
	// Default asset is '0'
	asset_ = 0;
	x_ = x;
	y_ = y;
	rotation_ = rotation;
	hscale_ = hscale;
	vscale_ = vscale;
}
Graphics::Renderer::~Renderer()
{
}
void Graphics::Renderer::setAsset(size_t asset)
{
	asset_ = asset;
}
void Graphics::Renderer::setX(float x)
{
	x_ = x;
}
void Graphics::Renderer::setY(float y)
{
	y_ = y;
}
void Graphics::Renderer::setPoint(Point& point)
{
	x_ = point.getX();
	y_ = point.getY();
}
void Graphics::Renderer::setRotation(float rotation, bool gradual)
{
	rotation_ = (gradual) ? rotation + rotation_ : rotation;
}
void Graphics::Renderer::setScale(float scale, bool gradual, Graphics::Planes plane)
{
	switch (plane)
	{
	case Graphics::ALL:
	case Graphics::NONE:
	{
						   setHScale(scale, gradual);
						   setVScale(scale, gradual);
						   break;
	}

	case Graphics::HORIZONTAL: setHScale(scale, gradual); break;
	case Graphics::VERTICAL:   setVScale(scale, gradual); break;
	}
}
void Graphics::Renderer::setVScale(float vscale, bool gradual)
{
	vscale_ = (gradual) ? vscale + vscale_ : vscale;
}
void Graphics::Renderer::setHScale(float hscale, bool gradual)
{
	hscale_ = (gradual) ? hscale + hscale_ : hscale;
}

size_t Graphics::Renderer::getAsset() const
{
	return asset_;
}
Point Graphics::Renderer::getPoint() const
{
	return Point(x_, y_);
}
float Graphics::Renderer::getX() const
{
	return x_;
}
float Graphics::Renderer::getY() const
{
	return y_;
}
float Graphics::Renderer::getVScale() const
{
	return vscale_;
}
float Graphics::Renderer::getHScale() const
{
	return hscale_;
}
float Graphics::Renderer::getRotation() const
{
	return rotation_;
}