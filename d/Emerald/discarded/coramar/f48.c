/*
 * F48.c
 * Small clearing off of a main artery in the coramar forest.
 * This room contains rune stone #3 for the cirdaan illusion quest.
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
    set_long("   The small clearing is surrounded on all sides by slowly swirling "+
	"mist, distorting your view of the forest around you. All of the trees and "+
	"vines more than a meter away appear to be nothing more than dark gray "+
	"shadows. The sounds of the forest and the chill wind don't seem able "+
	"to penetrate the small clearing. The bushes and leaves surrounding the clearing "+
	"are so high that only a giant could see over them. An eerie, unexplainable "+
	"sense of calm washes over the clearing, drowning out the harsh, mysterious "+
	"forest surroundings.\n\n");


    reset_euid();
    runestone=clone_object(CORAMAR_OBJ+"rstone3");
    runestone->move(this_object(), 1);

    add_fexit(CORAMAR+"f47", "north" ,0);
}