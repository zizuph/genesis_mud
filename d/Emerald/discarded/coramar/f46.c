/*
 * F46.c
 * This is another section/clearing in the coramar forest, at the end of a trail
 * You can look across a brook to see that there is another section of the path
 * visible north.
 * Alaron - Feb 1998
 */

#include "/d/Emerald/defs.h"
#include "dirheader.h"
#include "coramar.h"
#include <stdproperties.h>

inherit BASEFOREST;

int fake_north(string str);

void
init()
{
    ::init();
    add_action(fake_north, "north");
    add_action(fake_north, "n");
}

void
create_forest()
{
    set_long("   This small clearing at the edge of the path is an unexpected "+
	"change of terrain. The tall bushes and vegetation that normally border the "+
	"path and prevent seeing in either direction taper down to ankle-height here. "+
	"A small brook runs along the edge of the path here, it trickles down from the "+
	"northwest over small rocks and dirt formations, filling the small peninsula "+
	"with the soothing sound of gently trickling water. The everpresent, cool wind "+
	"blows from the south to the north, whistling through trees and bushes on "+
	"the north bank of the brook. It looks as though there may be another section "+
	"of the path on the north side of the brook.\n\n");

    add_item( ({"brook", "water", "rocks", "dirt formations"}),
	"The gently running brook adds a soft, soothing noise to the otherwise "+
	"intimidating and confining feeling of the forest and smothering mist. The "+
	"soil beneath the brook, however, is extremely dark and moist and looks fairly "+
	"unstable. If you attempted to cross the brook, you might end up stuck.\n");


    add_fexit(CORAMAR+"f47", "southwest", 0);
}

int
fake_north(string str)
{
    notify_fail("You think about heading north across the brook, but decide against "+
	"it when you see how soft and unstable the soil looks. You decide not to risk "+
	"sinking or getting stuck in the water.\n");
    return 0;
}