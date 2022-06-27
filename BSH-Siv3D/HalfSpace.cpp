#include "stdafx.h"
#include "HalfSpace.hpp"

void HalfSpace::sort()
{
	// 重心を計算
	Vec2 g = m_vertices.sum() / m_vertices.size();
	// 交点が時計回りに並ぶように極座標で整列
	std::sort(m_vertices.begin(), m_vertices.end(), [g](auto const& left, auto const& right) {
		return std::atan2((left - g).y, (left - g).x) < std::atan2((right - g).y, (right - g).x);
	});
}

Array<HalfSpace> HalfSpace::divideBySample(HalfSpace parent, SamplePoint sample)
{
	Array<HalfSpace> halfSpaces = Array<HalfSpace>();
	Line l = sample.getBoundary().getLine();
	Polygon parentPolygon = parent.getPolygon();
	auto intersections = l.intersectsAt(parentPolygon);
	Array<Vec2> upperSide = intersections.value();
	Array<Vec2> lowerSide = intersections.value();
	for (auto& v : parent.getVertices()) {
		Line toPoint = Line(0, 0, v.x, v.y);
		if (toPoint.hasLength() && toPoint.intersects(l)) {
			lowerSide << v;
		}
		else {
			upperSide << v;
		}
	}
	Array<SamplePoint> upperSamples = Array<SamplePoint>();
	upperSamples << sample;
	Array<SamplePoint> lowerSamples = Array<SamplePoint>();
	lowerSamples << sample;

	for (auto& s : parent.getSamples()) {
		Line toPoint = Line(0, 0, s.getPos().x, s.getPos().y);
		if (toPoint.intersects(l)) {
			lowerSamples << s;
		}
		else {
			upperSamples << s;
		}
	}
	Vec2 samplePos = Vec2(sample.getPos().x + Math::Cos(sample.getDirection()), sample.getPos().y + Math::Sin(sample.getDirection()));
	Line toSample = Line(0, 0, samplePos.x, samplePos.y);
	Array<SamplePoint> samples = parent.getSamples();
	samples << sample;
	if (toSample.intersects(l)) {
		halfSpaces << HalfSpace(lowerSamples, lowerSide, false);
		halfSpaces << HalfSpace(upperSamples, upperSide, true);
	}
	else {
		halfSpaces << HalfSpace(lowerSamples, lowerSide, true);
		halfSpaces << HalfSpace(upperSamples, upperSide, false);
	}
	return halfSpaces;
}

HalfSpace::HalfSpace(Array<SamplePoint> samplePoints, Array<Vec2> vertices, bool inside)
{
	m_samples = samplePoints;
	m_vertices = vertices;
	is_inside = inside;
	sort();
}

Polygon HalfSpace::getPolygon() const
{
	return Polygon(m_vertices);
}

Array<Vec2> HalfSpace::getVertices() const
{
	return m_vertices;
}

Array<SamplePoint> HalfSpace::getSamples() const
{
	return m_samples;
}

void HalfSpace::draw() const
{
	Print << m_vertices << is_inside;

	if (is_inside)
	{
		// ポリゴンを描画
		Polygon(m_vertices).draw(Palette::Red);
	}
}
