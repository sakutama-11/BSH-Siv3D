# pragma once
# include <Siv3D.hpp>
# include "Boundary.hpp"

class SamplePoint
{
	private:
		Boundary* m_boundary;
		Circle m_point;
		Line m_handle;
		Color m_color;
		// 算出可能なので消してもよい
		float m_direction;
		float m_t;

	public:
		SamplePoint( Vec2 pos, Boundary* boundary );
		Vec2 getPos();
		Circle getCircle();
		float getDirection();
		Boundary getBoundary() const;
		void setDirection(float direction);
		void setHandle();
		void draw();
		void setPos(Vec2 pos);
		void setDirectionByPos(Vec2 pos);
};
