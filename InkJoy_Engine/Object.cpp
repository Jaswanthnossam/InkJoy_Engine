#include "Object.hpp"

ENGINE::Object::Object()
{
	this->angles = 0.0f;
	this->scale = { 1.0f,1.0f };
	this->Position = { 0.0f,0.0f };
	this->Color = { 255,255,255,255 };
	this->SourceRec = { 0,0,0,0 };
	DestRec = SourceRec;
}

void ENGINE::Object::TranslateTo(int x, int y)
{
	this->Position.x = x;
	this->Position.y = y;
}

void ENGINE::Object::Translate(int x, int y)
{
	this->Position.x += x;
	this->Position.y += y;
}

void ENGINE::Object::Rotate(float angles)
{
	this->angles += angles;
}

void ENGINE::Object::Scale(float scaleX, float scaleY)
{
	this->scale.x *= scaleX;
	this->scale.y *= scaleY;
}

void ENGINE::Object::SetColor(Vec4<float> Color)
{
	this->Color = Color;
}

void ENGINE::Object::Draw(sf::RenderWindow* renderer , sf::Texture& texture, bool TakeSubTexture)
{
	    sf::Sprite sprite;
	    if (TakeSubTexture)
	    {
			sprite = sf::Sprite(texture,this->SourceRec);
		}
		else
		{
			sprite = sf::Sprite(texture);
		}
		sprite.setPosition(Position.x, Position.y);
		sprite.setRotation(angles);
		sprite.setScale({ scale.x,scale.y });
		sprite.setColor({ (sf::Uint8)Color.x,(sf::Uint8)Color.y,(sf::Uint8)Color.z,(sf::Uint8)Color.w });
		renderer->draw(sprite);	
}

void ENGINE::Object::Draw(sf::RenderWindow* renderer, sf::Texture& texture,std::vector<Vec2<int>> AtlasIndicies, 
	int XincrementSize, int YincrementSize, int SubtextureCount, int FrameDelay, bool PlayAnimation)
{
	FrameCounter++;

	auto& AtlasIndex = AtlasIndicies[CurrentIndex];
	SourceRec.left = AtlasIndex.x * XincrementSize;
	SourceRec.top = AtlasIndex.y * YincrementSize;

	SourceRec.width = XincrementSize;
	SourceRec.height = YincrementSize;

	Draw(renderer, texture, true);

	if (FrameCounter >= FrameDelay && PlayAnimation)
	{
		CurrentIndex++;
		if (CurrentIndex == SubtextureCount)
		{
			CurrentIndex = 0;
		}

		FrameCounter = 0;
	}
}
