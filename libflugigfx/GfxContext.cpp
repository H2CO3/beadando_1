//
// GfxContext.cpp
// Wrapper around Flugi's graphics lib
//
// Created by Arpad Goretity on 06/03/2014
// What's a copyleft license?
//


#include <cstdlib>
#include <cmath>
#include <cassert>
#include <iostream>

#include "GfxContext.h"

// I've never thought I will ever write an instantiable wrapper class...
// ...around a singleton!
// http://www.legalcheek.com/wp-content/uploads/2013/09/But-why-meme1.jpg
void GfxContext::clearScreen()
{
	// clear screen, move cursor to (0, 0)
	genv::gout << genv::move_to(0, 0);
	genv::gout << bgColor;
	genv::gout << genv::box(w, h);
	genv::gout << genv::move_to(0, 0);
}

GfxContext::GfxContext(
	int wp,
	int hp,
	DrawCallback drw,
	InteractionCallback act,
	void *ui
):
	w(wp),
	h(hp),
	draw(drw),
	interact(act),
	bgColor(0, 0, 0), // black background by default
	uinfo(ui),
	deltat(0.04) // 25 FPS (TODO: make constructor argument)
{
	// init SDL
	genv::gout.open(wp, hp);
	genv::gin.timer(deltat * millisecsPerSec);
	clearScreen();
}

// guess what this does
void GfxContext::loop()
{
	genv::event evt;
	while (genv::gin >> evt) {
		switch (evt.type) {
		case genv::ev_timer:
			if (draw != NULL) {
				clearScreen();
				draw(*this, deltat);
				genv::gout << genv::refresh;
			}
			break;
		case genv::ev_key:	// fallthru
		case genv::ev_mouse:
			if (interact != NULL) {
				interact(*this, evt);
			}
			break;
		default:
			std::cerr << "Unicorns!" << std::endl;
			std::abort();
			break;
		}
	}
}	


genv::color GfxContext::greyColor(double shade)
{
	return genv::color(shade * 255, shade * 255, shade * 255);
}

void GfxContext::setColor(double r, double g, double b)
{
	genv::gout << genv::color(r * 255, g * 255, b * 255);
}

void GfxContext::setColor(const genv::color &c)
{
	genv::gout << c;
}

void GfxContext::setBgColor(double r, double g, double b)
{
	bgColor = genv::color(r * 255, g * 255, b * 255);
}

void GfxContext::setBgColor(const genv::color &c)
{
	bgColor = c;
}

void GfxContext::line(int x, int y, int dx, int dy)
{
	genv::gout << genv::move_to(x, y);
	genv::gout << genv::line(dx, dy);
}

void GfxContext::fillRect(int x, int y, int dx, int dy)
{
	genv::gout << genv::move_to(x, y);
	genv::gout << genv::box(dx, dy);
}

void GfxContext::strokeRect(int x, int y, int dx, int dy)
{
	genv::gout << genv::move_to(x, y);
	genv::gout << genv::line(dx, 0);
	genv::gout << genv::line(0, dy);
	genv::gout << genv::line(-dx, 0);
	genv::gout << genv::line(0, -dy);
}

void GfxContext::strokeArc(int x, int y, int a, int b, double startAngle, double endAngle)
{
	assert(a >= 0 && b >= 0);
	
	const double delta = endAngle - startAngle;

	genv::gout << genv::move_to(
		x + a * std::cos(startAngle),
		y + b * std::sin(startAngle)
	);

	// guesstimation: 1024 steps will be good enough
	// 1024, because 1 / 1024 is exactly representable
	// as a `double`. Yay!

	for (double t = 0.0; t <= 1.0; t += 1.0 / 1024) {
		double phi = startAngle + t * delta;
		int xt = x + a * std::cos(phi);
		int yt = y + b * std::sin(phi);

		genv::gout << genv::line_to(xt, yt);
	}
}

void GfxContext::fillEllipse(int x, int y, int a, int b)
{
	assert(a >= 0 && b >= 0);

	// I hate my job
	for (int i = x - a; i <= x + a; i++) {
		for (int j = y - b; j <= y + b; j++) {
			double dx = (i - x) / static_cast<double>(a);
			double dy = (j - y) / static_cast<double>(b);
			if (std::hypot(dx, dy) <= 1) {
				genv::gout << genv::move_to(i, j);
				genv::gout << genv::dot;
			}
		}
	}
}

// Cubic Bézier curve. Who knows if/when we will need it?
// Formula adapted and shamelessly stolen from:
// https://en.wikipedia.org/wiki/B%C3%A9zier_curve#Cubic_B.C3.A9zier_curves
void GfxContext::drawBezier(
	int x0, int y0,
	int x1, int y1,
	int x2, int y2,
	int x3, int y3
)
{
	genv::gout << genv::move_to(x0, y0);

	for (double t = 0; t <= 1; t += 1.0 / 1024) {
		int x = std::pow(1 - t, 3) * x0
		      + 3 * std::pow(1 - t, 2) * t * x1
		      + 3 * (1 - t) * t * t * x2
		      + std::pow(t, 3) * x3;
		int y = std::pow(1 - t, 3) * y0
		      + 3 * std::pow(1 - t, 2) * t * y1
		      + 3 * (1 - t) * t * t * y2
		      + std::pow(t, 3) * y3;

		genv::gout << genv::line_to(x, y);
	}
}

void GfxContext::drawText(int x, int y, const std::string &s)
{
	genv::gout << genv::move_to(x, y);
	genv::gout << genv::text(s);
}

void GfxContext::setFont(const std::string &fname, double size, bool antialias)
{
	genv::gout.load_font(fname, size, antialias);
}

int GfxContext::charAsc() const
{
	return genv::gout.cascent();
}

int GfxContext::charDesc() const
{
	return genv::gout.cdescent();
}

int GfxContext::lineHeight() const
{
	return charAsc() + charDesc();
}

int GfxContext::textWidth(const std::string &s)
{
	return genv::gout.twidth(s);
}

const int GfxContext::millisecsPerSec = 1000;

const genv::color GfxContext::blackColor(0, 0, 0);
const genv::color GfxContext::whiteColor(255, 255, 255);
const genv::color GfxContext::redColor(255, 0, 0);
const genv::color GfxContext::greenColor(0, 255, 0);
const genv::color GfxContext::blueColor(0, 0, 255);
const genv::color GfxContext::yellowColor(255, 255, 0);
const genv::color GfxContext::magentaColor(255, 0, 255);
const genv::color GfxContext::cyanColor(0, 255, 255);


