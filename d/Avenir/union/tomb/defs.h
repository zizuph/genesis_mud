#ifndef _AKRAMS_TOMB_
#define _AKRAMS_TOMB_

#include "../defs.h"

//#define DEBUG(x)	find_living("lucius")->catch_tell("#TOMB# " + x + "\n")
#define DEBUG(x)

#define PUZZLE		(UNION + "tomb/")
#define MAZE		(PUZZLE + "maze/")
#define TOBJ		(PUZZLE + "obj/")

#define AKRAM		(PUZZLE + "akram")
#define THALLE		(PUZZLE + "tilt_hall_e")
#define THALLW		(PUZZLE + "tilt_hall_w")
#define HOLE		(PUZZLE + "tilt_hole")
#define PANEL		(PUZZLE + "panel_room")
#define PASSAGE		(PUZZLE + "passage_east")
#define RESTING		(PUZZLE + "resting")
#define FALSE_TOMB	(PUZZLE + "false_tomb")

#define WORD_PROP	"_tomb_maze_words"
#define WORDS ({ "amek", "soru", "tins", "fer", "oli", \
                 "nastu", "tess", "aliy", "fras", "tene", "tor", \
                 "xas", "epher", "nas", "qou", "estri", "parim" })
#endif
