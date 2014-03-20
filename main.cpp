// main.cpp
//
// "Prog I Beadando 1"
//
// Created by Arpad Goretity on 06/03/2014
// Still no license here because this is homework o.O
//

#include "libflugigfx-spn/FlugiGfxSpn.h"

#include <iostream>

#ifdef WORKAROUND_TO_COMPENSATE_THE_SDL_DEVELOPERS_BEING_STUPID
#include <SDL/SDL.h>
#endif


static void run_script_file(SpnContext *spnCtx, const std::string &fname)
{
	if (spn_ctx_execsrcfile(spnCtx, fname.c_str(), NULL) != 0) {
		std::cerr << spn_ctx_geterrmsg(spnCtx) << std::endl;
		std::size_t n, i;
		const char **bt = spn_ctx_stacktrace(spnCtx, &n);
		for (i = 0; i < n; i++) {
			std::cerr << bt[i] << std::endl;
		}
		
		std::free(bt);
		std::exit(-1);
	}
}

int main(int argc, char *argv[])
{
	SpnContext *spnCtx = spn_ctx_new();

	// attach graphics lib, create graphics context
	FlugiGfxSpn gfx(spnCtx);

	run_script_file(spnCtx, "libspnphysx/physx.spn");
	run_script_file(spnCtx, "main.spn");

	gfx.getGfxContext().loop();

	return 0;
}

