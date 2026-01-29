/*
 * F25
 * Forest of Coramar
 * Alaron March 1998
 */

#include "/d/Emerald/defs.h"
#include "dirheader.h"
#include "coramar.h"

inherit BASEFOREST;

void
create_forest()
{
    set_long("   You are on a misty, narrow forest path that seems to be under "+
	"attack by its surroundings. Huge bushes, ferns and giant leaves from trees "+
	"all seem to be creeping out of the forest and trying to smother the trail. A "+
	"high wall of green foliage springs forth out of the ground and comes to a "+
	"point high above your head, preventing you from seeing anything but the "+
	"path in front of and behind you. A thick cloud of mist hovers low above "+
	"the forest floor, fading the rest of the forest into dark, blue-gray "+
	"shadows. The path continues in an east/west direction.\n\n");

  
    add_fexit(CORAMAR+"f26", "east", 0);
    add_fexit(CORAMAR+"f24", "west", 0);
}