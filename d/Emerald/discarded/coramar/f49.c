/*
 * F49.c
 * small clearing at the end of a footpath in Coramar.
 * There is a rune-stone here, hidden by default.
 * Player's should notice an eerie calm in all places where there is a rune stone.
 * - Alaron Feb 1998
 */

#include "/d/Emerald/defs.h"
#include "coramar.h"
#include "dirheader.h"
#include <stdproperties.h>

inherit BASEFOREST;

object runestone;

void
create_forest()
{
    set_long("   The narrow footpath comes to an abrupt halt in a small clearing here. "+
	"The clearing is just large enough for two people to fit comfortably on the "+
	"small patch of exposed soil. A thick bank of fog seems to swirl slowly around "+
	"this spot. In the distance, the sound of wind gently rustling the greenery "+
	"on the forest floor can be heard. An eerie calm seems to descend upon the "+
	"clearing, washing away all of the hazardous sights and sounds of the rest "+
	"of the forest.\n\n");

    reset_euid();
    runestone=clone_object(CORAMAR_OBJ+"rstone1");
    runestone->move(this_object(), 1);

    add_fexit(CORAMAR+"f8", "west", 0);
}
