/*
 * BASEGRAVES.c
 * This file sets up properties, items and other functions
 * that are common to the set of rooms which have headstones
 * in them.
 * Alaron - Feb 1998
 */

#include "/d/Emerald/defs.h"
#include "dirheader.h"
#include "coramar.h"
#include <stdproperties.h>

/* The graveyard is in the forest, so we inherit the forest baseroom to get
 * all of the items, properties and messages associated with the forest, including
 * the sleep-inducing exits of the forest.
 */

inherit BASEFOREST;

void create_graveyard();

void
create_graveyard()
{
// masked in inheriting object/room
}

void
create_forest()
{
    create_graveyard();

    add_prop(ROOM_I_LIGHT, -1);
    add_prop(ROOM_S_DARK_MSG, "The tree canopy just above blocks out "+
      "enough light so that it is impossible to");
    add_prop(ROOM_S_DARK_LONG, "   The tree canopy blocks out so much "+
     "light that you can see almost nothing. The only thing visible "+
     "is the strange, dark outline of a few of the trees above.\n\n");

    add_item( ({"fence", "iron fence", "black fence", "small fence", "small black fence",
	"small iron fence", "black iron fence"}),
	"The small, black iron fence is no more than a meter high. Thin, iron bars "+
	"just out of the ground and come to a spear-like point. Thicker horizontal bars "+
	"join the thin bars, creating an ominous, almost dangerous effect. It surrounds "+
	"the small graveyard on all sides. At either end of the graveyard there is a "+
	"break in the fence leading to paths that disappear back into the forest behind "+
	"the swirling veil of mist.\n");

    add_item( ({"graves", "grave"}),
	"The graves are extremely close together, all placed in very neat order and "+
	"rows. What strikes you as unusual is that the bodies are buried vertically. "+
	"Most of the graves in this section of the world are commonly buried "+
	"horizontally. At the top of each grave is a small, square marble headstone. "+
	"Perhaps the graves were placed vertically to save space, or it might have "+
	"been for religious purposes.\n");

    add_item( ({"headstone", "headstones", "marble headstones", "marble headstone",
	"square headstone", "square headstones", "marble square", "square marble"}),
	"The headstones resting deep in the grass above the graves are perfectly "+
	"square and still retain the smooth polish of the original marble. The "+
	"shiny, well-cared for marble disguises the fact that the stone must be "+
	"incredibly old. There is writing on the headstones.\n");

    add_item("writing",
	"Perhaps you should read it.\n");

    add_cmd_item("writing", "read",
	VBFC_ME("check_druid_read_writing") );
}

string
check_druid_read_writing()
{
    if (this_player()->query_cirdaan_druid())
      return "As you peer closely at the ancient writing, you notice that it is written "+
	"in the ancient language of the tohk'mai. Examining the headstones further, "+
	"you can tell that this is the gravesite of the First! You feel a sense of "+
	"awe overwhelm you as you realize that you are stepping among the graves of "+
	"the first true druids.\n";
    else
      return "The writing on the headstones is unintelligble. You try and can't "+
	"make out the writing. The language looks incredibly old, and could possibly "+
	"pre-date alphabets. The words appear to be more symbolic, almost rune-like "+
	"rather than composed of letters.\n";
}
