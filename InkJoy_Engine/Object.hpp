#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "VectorMath.h"

namespace ENGINE
{
	class Object
	{
	public:
		Object();
		void TranslateTo(int x, int y);
		void Translate(int x, int y);
		void Rotate(float angles);
		void Scale(float scaleX, float scaleY);
		void SetColor(Vec4<float> Color);
		virtual void Draw(sf::RenderWindow* renderer, sf::Texture& texture, bool TakeSubTexture = false);
		void Draw(sf::RenderWindow* renderer, sf::Texture& texture, std::vector<Vec2<int>> AtlasIndicies,
			      int XincrementSize, int YincrementSize, int SubtextureCount, int FrameDelay, bool PlayAnimation);

		Vec2<float> Position;
		float angles = 0.0f;
		sf::IntRect DestRec;
		sf::IntRect SourceRec;
		Vec2<float> scale;
		Vec4<float> Color;

	protected:

		Vec2<int> Size;
		int CurrentIndex = 0;
		int FrameCounter = 0;
	};

}