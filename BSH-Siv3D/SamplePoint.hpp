# pragma once
# include <Siv3D.hpp>

class SamplePoint
{
	private:
		Circle m_point;
		Line m_handle;
		// 算出可能なので消してもよい
		float m_direction;
		float m_t;

	public:
		SamplePoint( Vec2 pos );
		Vec2 getPos();
		Circle getCircle();
		float getDirection();
		void setDirection(float direction);
		void setHandle();
		void draw(Color color);
		void setPos(Vec2 pos);
		void setDirectionByPos(Vec2 pos);
};
