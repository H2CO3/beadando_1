//
// FlugiGfxSpn.h
// FlugiGfxSpn
// Sparkling bindings for Flugi's ITK graphics engine
//
// Created by Arpad Goretity on 13/03/2014
// No license, 'tis homework
//

#include "../libflugigfx/GfxContext.h"
#include "../Sparkling/src/ctx.h"

class FlugiGfxSpn {
private:
	SpnContext *spnCtx;
	GfxContext  gfxCtx;

	static void drawCallback(GfxContext &ctx, double dt);
	static void interactCallback(GfxContext &ctx, const genv::event &evt);

public:
	FlugiGfxSpn(SpnContext *ctx);
	GfxContext &getGfxContext();
	SpnContext *getSpnContext();
};


