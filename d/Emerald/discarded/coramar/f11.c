/*
 * f11.c
 * Small Clearing off of a main artery in the coramar forest.
 * This room contains rune stone #2 for the cirdaan illusion quest.
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
    set_long("   The small clearing is almost completely surrounded by towering "+
	"bushes and plant life. Most of the thick, wide leaves are so high that "+
	"you cannot see over them. A cool breeze blows across the clearing, rustling "+
	"the tall leaves. The mist seems to swirl around the clearing instead of hovering "+
	"over it as it does throughout the rest of the forest. An eerie calm washes "+
	"over you as you stand in the clearing. The eerie sound and cold winds of the "+
	"forest don't seem able to penetrate the mist swirling about the clearing. A "+
	"single, narrow trail leads out of the clearing to the southeast.\n\n");  


    reset_euid();
    runestone=clone_object(CORAMAR_OBJ+"rstone2");
    runestone->move(this_object(), 1);

    add_fexit(CORAMAR+"f7", "southeast", 0);
}