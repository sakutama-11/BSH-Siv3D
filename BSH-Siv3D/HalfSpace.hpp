#pragma once
#include "SamplePoint.hpp"
class HalfSpace
{
	private:
		Array<SamplePoint> m_samples;
		Array<Vec2> m_vertices;
		bool is_inside;

		void sort();

	public:
		static Array<HalfSpace> divideBySample(HalfSpace parent, SamplePoint sample);
		HalfSpace(Array<SamplePoint> samplePoints, Array<Vec2> vertices, bool inside);
		void setInside(bool inside);
		Polygon getPolygon() const;
		Array<Vec2> getVertices() const;
		Array<SamplePoint> getSamples() const;
		void draw() const;
};

