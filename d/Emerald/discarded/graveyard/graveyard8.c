/*
 * GRAVEYARD8.c
 * This is the dead-end in the graveyard.
 * by Alaron August 14, 1996
 */

#include "default.h"
#include "/d/Emerald/defs.h"

inherit "/std/room";

void
create_room()
{
    set_short("Graveyard");
    set_long("   You stand in a mirky abyss of mist and fog. Surrounding "+
	     "you on all sides is a thick gray blanket of despair and "+
	     "forboding. The ground beneath your feet compresses and "+
	     "releases stored moisture as you step carefully across "+
	     "the overgrowth of the graveyard. The field sprawls out in "+
	     "all directions, its damp green surface littered with old "+
	     "and broken gravestones, markers and rubble. It is a sad "+
	     "scene that the graves of all of these people have fallen "+
	     "into such disrepair.\n\n");

    add_item( ({"abyss", "mist", "fog", "mirky abyss"}),
	     "The mist and fog surrounds you on all sides, blanketing "+
	     "the area in a gray cover of loneliness and despair.\n");

    add_item( ({"ground", "moisture", "down", "grass", "overgrowth",
		"field", "sprawling field", "green surface"}),
	     "The field sprawls out in all directions. The damp overgrowth "+
	     "is almost tall enough to hide all but the tops of the "+
	     "ancient, decaying gravestones.\n");

    add_item ( ({"gravestones", "stones", "markers", "grave markers",
		 "ancient gravestones", "decaying gravestones"}),
	      "The ancient and decaying gravestones litter the entire "+
	      "green countryside. Most of them, however, are either "+
	      "broken or decaying so badly that they will eventually "+
	      "crumble into dust.\n");

    add_exit (GRAVEYARD_DIR + "graveyard7", "north");

}
