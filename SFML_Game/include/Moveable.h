#pragma once

class Moveable
{
	public:
		virtual ~Moveable() = default;

		virtual void MoveUp() = 0;
		virtual void MoveDown() = 0;
		virtual void MoveLeft() = 0;
		virtual void MoveRight() = 0;
};