# include "stdafx.h"

# ifndef   SAMPLE_POINT_HPP
# define   SAMPLE_POINT_HPP

class Boundary;

class SamplePoint
{
	// variable
	private:
		Boundary m_boundary;
		s3d::Circle m_point;
		s3d::Line m_handle;
		// 算出可能なので消してもよい
		int m_direction;
		float m_t;

	// acsessor
	public:
		SamplePoint( Boundary boundary, Vec2 pos );
		void setDirection(int direction);
		void draw();
};

# endif // SAMPLE_POINT_HPP
