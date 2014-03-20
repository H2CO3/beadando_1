//
// GfxContext.h
// Wrapper around Flugi's graphics lib
//
// Created by Arpad Goretity on 06/03/2014
// What's a copyleft license?
//


#ifndef H2CO3_GFXCONTEXT_H
#define H2CO3_GFXCONTEXT_H

#include "graphics.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class GfxContext;

// If only there was something like std::function in C++03...

// I've never thought I will ever write an instantiable wrapper class...
// ...around a singleton!
// http://www.legalcheek.com/wp-content/uploads/2013/09/But-why-meme1.jpg
class GfxContext {
private:
	typedef void (*DrawCallback)(GfxContext &ctx, double dt); // dt is in seconds
	typedef void (*InteractionCallback)(GfxContext &ctx, const genv::event &evt);

	int w, h;
	DrawCallback draw;
	InteractionCallback interact;
	genv::color bgColor;
	void *uinfo;

	const double deltat;
	static const int millisecsPerSec;

	void clearScreen();

public:
	static const genv::color blackColor;
	static const genv::color whiteColor;
	static const genv::color redColor;
	static const genv::color greenColor;
	static const genv::color blueColor;
	static const genv::color yellowColor;
	static const genv::color magentaColor;
	static const genv::color cyanColor;

	GfxContext(
		int wp = 640,
		int hp = 480,
		DrawCallback drw = NULL,
		InteractionCallback act = NULL,
		void *ui = NULL
	);

	void loop();

	inline int width()  const { return w; }
	inline int height() const { return h; }
	inline void *userInfo() const { return uinfo; }

	// the 256 shades of grey
	static genv::color greyColor(double shade);
	void setColor(double r, double g, double b);
	void setColor(const genv::color &c);
	void setBgColor(double r, double g, double b);
	void setBgColor(const genv::color &c);

	// drawing primitives
	void line(int x, int y, int dx, int dy);
	void fillRect(int x, int y, int dx, int dy);
	void strokeRect(int x, int y, int dx, int dy);
	void strokeArc(int x, int y, int a, int b, double startAngle, double endAngle);
	void fillEllipse(int x, int y, int a, int b);
	void drawBezier(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3);

	// rendering text
	void drawText(int x, int y, const std::string &s);
	void setFont(const std::string &fname, double size, bool antialias = false);
	int charAsc() const;
	int charDesc() const;
	int lineHeight() const;
	static int textWidth(const std::string &s);

};

#endif // H2CO3_GFXCONTEXT_H

