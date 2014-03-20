//
// FlugiGfxSpn.cpp
// FlugiGfxSpn
// Sparkling bindings for Flugi's ITK graphics engine
//
// Created by Arpad Goretity on 13/03/2014
// No license, 'tis homework
//

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cassert>

#include <SDL/SDL.h>

#include "FlugiGfxSpn.h"


// The actual wrappers

static double val2double(SpnValue *val)
{
	return spn_isfloat(val) ? spn_floatvalue(val) : spn_intvalue(val);
}

static GfxContext &spnToGfxCtx(void *ctx)
{
	SpnContext *spnCtx = static_cast<SpnContext *>(ctx);
	return *static_cast<GfxContext *>(spn_ctx_getuserinfo(spnCtx));
}

#define floatarg(n) val2double(argv + (n))

static int flugigfx_setColor(SpnValue *ret, int argc, SpnValue *argv, void *ctx)
{
	GfxContext &gfxCtx = spnToGfxCtx(ctx);

	assert(argc == 3);
	assert(spn_isnumber(argv + 0) && spn_isnumber(argv + 1) && spn_isnumber(argv + 2));

	double r = floatarg(0);
	double g = floatarg(1);
	double b = floatarg(2);

	gfxCtx.setColor(r, g, b);

	return 0;
}

static int flugigfx_setBgColor(SpnValue *ret, int argc, SpnValue *argv, void *ctx)
{
	GfxContext &gfxCtx = spnToGfxCtx(ctx);

	assert(argc == 3);
	assert(spn_isnumber(argv + 0) && spn_isnumber(argv + 1) && spn_isnumber(argv + 2));

	double r = floatarg(0);
	double g = floatarg(1);
	double b = floatarg(2);

	gfxCtx.setBgColor(r, g, b);

	return 0;
}

static int flugigfx_line(SpnValue *ret, int argc, SpnValue *argv, void *ctx)
{
	GfxContext &gfxCtx = spnToGfxCtx(ctx);

	double x0 = floatarg(0);
	double y0 = floatarg(1);
	double dx = floatarg(2);
	double dy = floatarg(3);

	gfxCtx.line(x0, y0, dx, dy);
	return 0;
}

static int flugigfx_bezier(SpnValue *ret, int argc, SpnValue *argv, void *ctx)
{
	GfxContext &gfxCtx = spnToGfxCtx(ctx);

	double x0 = floatarg(0);
	double y0 = floatarg(1);
	double x1 = floatarg(2);
	double y1 = floatarg(3);
	double x2 = floatarg(4);
	double y2 = floatarg(5);
	double x3 = floatarg(6);
	double y3 = floatarg(7);

	gfxCtx.drawBezier(x0, y0, x1, y1, x2, y2, x3, y3);

	return 0;
}

static int flugigfx_strokeRect(SpnValue *ret, int argc, SpnValue *argv, void *ctx)
{
	GfxContext &gfxCtx = spnToGfxCtx(ctx);

	double x0 = floatarg(0);
	double y0 = floatarg(1);
	double dx = floatarg(2);
	double dy = floatarg(3);

	gfxCtx.strokeRect(x0, y0, dx, dy);
	return 0;
}

static int flugigfx_fillRect(SpnValue *ret, int argc, SpnValue *argv, void *ctx)
{
	GfxContext &gfxCtx = spnToGfxCtx(ctx);

	double x0 = floatarg(0);
	double y0 = floatarg(1);
	double dx = floatarg(2);
	double dy = floatarg(3);

	gfxCtx.fillRect(x0, y0, dx, dy);
	return 0;
}

static int flugigfx_strokeArc(SpnValue *ret, int argc, SpnValue *argv, void *ctx)
{
	GfxContext &gfxCtx = spnToGfxCtx(ctx);

	double x = floatarg(0);
	double y = floatarg(1);
	double a = floatarg(2);
	double b = floatarg(3);
	double start = floatarg(4);
	double stop  = floatarg(5);

	gfxCtx.strokeArc(x, y, a, b, start, stop);
	return 0;
}

static int flugigfx_fillEllipse(SpnValue *ret, int argc, SpnValue *argv, void *ctx)
{
	GfxContext &gfxCtx = spnToGfxCtx(ctx);

	double x = floatarg(0);
	double y = floatarg(1);
	double a = floatarg(2);
	double b = floatarg(3);

	gfxCtx.fillEllipse(x, y, a, b);
	return 0;
}

static int flugigfx_drawText(SpnValue *ret, int argc, SpnValue *argv, void *ctx)
{
	// GfxContext &gfxCtx = spnToGfxCtx(ctx);
	GfxContext &gfxCtx = spnToGfxCtx(ctx);

	double x = floatarg(0);
	double y = floatarg(1);

	SpnString *str = spn_stringvalue(argv + 2);

	gfxCtx.drawText(x, y, str->cstr);
	return 0;
}

static int flugigfx_setFont(SpnValue *ret, int argc, SpnValue *argv, void *ctx)
{
	// GfxContext &gfxCtx = spnToGfxCtx(ctx);
	// TODO: implement
	return 0;
}


// Implementation of the class
FlugiGfxSpn::FlugiGfxSpn(SpnContext *ctx):
	spnCtx(ctx),
	gfxCtx(960, 720, drawCallback, interactCallback, spnCtx)
{
	spn_ctx_setuserinfo(spnCtx, &gfxCtx);
	static const SpnExtFunc lib[] = {
		{ "setColor",		flugigfx_setColor	},
		{ "setBgColor",		flugigfx_setBgColor	},
		{ "line",		flugigfx_line		},
		{ "bezier",		flugigfx_bezier		},
		{ "strokeRect",		flugigfx_strokeRect	},
		{ "fillRect",		flugigfx_fillRect	},
		{ "strokeArc",		flugigfx_strokeArc	},
		{ "fillEllipse",	flugigfx_fillEllipse	},
		{ "setFont",		flugigfx_setFont	},
		{ "drawText",		flugigfx_drawText	}
	};
	spn_ctx_addlib_cfuncs(spnCtx, "FGFX", lib, sizeof lib / sizeof lib[0]);

	// excuse me for this. I am really sorry. I mean it.
	// I *promise* I will refactor this later.
	std::stringstream ss;
	ss << "FGFX.width  = " << gfxCtx.width()  << ";" << std::endl;
	ss << "FGFX.height = " << gfxCtx.height() << ";" << std::endl;
	ss << "FGFX.mouseLeft  = " << SDL_BUTTON_LEFT  << ";" << std::endl;
	ss << "FGFX.mouseMid = " << SDL_BUTTON_MIDDLE << ";" << std::endl;
	ss << "FGFX.mouseRight  = " << SDL_BUTTON_RIGHT  << ";" << std::endl;

	assert(spn_ctx_execstring(spnCtx, ss.str().c_str(), NULL) == 0);
}

GfxContext &FlugiGfxSpn::getGfxContext()
{
	return gfxCtx;
}

SpnContext *FlugiGfxSpn::getSpnContext()
{
	return spnCtx;
}

void FlugiGfxSpn::drawCallback(GfxContext &ctx, double dt)
{
	// this calls the FGFX.renderFrame() function
	SpnContext *spnCtx = static_cast<SpnContext *>(ctx.userInfo());
	SpnArray *globs = spn_ctx_getglobals(spnCtx);

	SpnValue FGFX;
	spn_array_get_strkey(globs, "FGFX", &FGFX);

	SpnValue renderFrame;
	spn_array_get_strkey(spn_arrayvalue(&FGFX), "renderFrame", &renderFrame);

	SpnValue dtv = spn_makefloat(dt);

	if (spn_ctx_callfunc(spnCtx, &renderFrame, NULL, 1, &dtv) != 0) {
		std::cerr << spn_ctx_geterrmsg(spnCtx) << std::endl;

		std::size_t n, i;
		const char **bt = spn_ctx_stacktrace(spnCtx, &n);
		for (i = 0; i < n; i++) {
			std::cerr << bt[i] << std::endl;
		}

		std::exit(-1);
	}
}

void FlugiGfxSpn::interactCallback(GfxContext &ctx, const genv::event &evt)
{
	// this calls the one almighty handleEvent function
	SpnContext *spnCtx = static_cast<SpnContext *>(ctx.userInfo());
	SpnArray *globs = spn_ctx_getglobals(spnCtx);

	SpnValue FGFX;
	spn_array_get_strkey(globs, "FGFX", &FGFX);

	SpnValue handleEvent;
	spn_array_get_strkey(spn_arrayvalue(&FGFX), "handleEvent", &handleEvent);

	SpnArray *evtObj = spn_array_new();
	SpnValue type = spn_makestring(evt.type == genv::ev_key ? "key" : "mouse");
	spn_array_set_strkey(evtObj, "type", &type);
	spn_value_release(&type);

	if (evt.type == genv::ev_key) {
		SpnValue code = spn_makeint(evt.keycode);
		spn_array_set_strkey(evtObj, "code", &code);
	} else {
		SpnValue x = spn_makefloat(evt.pos_x);
		SpnValue y = spn_makefloat(evt.pos_y);
		SpnValue button = spn_makefloat(evt.button);
		spn_array_set_strkey(evtObj, "x", &x);
		spn_array_set_strkey(evtObj, "y", &y);
		spn_array_set_strkey(evtObj, "button", &button);
	}

	SpnValue evtVal;
	evtVal.type = SPN_TYPE_ARRAY;
	evtVal.v.o = evtObj;

	if (spn_ctx_callfunc(spnCtx, &handleEvent, NULL, 1, &evtVal) != 0) {
		std::cerr << spn_ctx_geterrmsg(spnCtx) << std::endl;

		std::size_t n, i;
		const char **bt = spn_ctx_stacktrace(spnCtx, &n);
		for (i = 0; i < n; i++) {
			std::cerr << bt[i] << std::endl;
		}

		std::exit(-1);
	}

	spn_object_release(evtObj);
}


