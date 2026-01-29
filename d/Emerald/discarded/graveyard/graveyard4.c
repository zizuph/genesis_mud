/*
 * GRAVEYARD4.C
 * by Alaron July 26, 1996
 */

#include "default.h"

inherit "/std/room";

void
create_room()
{
    set_short("Graveyard");
    set_long("   You stand in the middle of a three-quarter circle of "+
	     "enormous tomb stones. They stand as tall as you and are "+
	     "made of thick, gray slabs of moss-covered, eroding stone. "+
	     "A chill breeze blows through the circle of tombs, whistling "+
	     "a high-pitched howl as it blasts against the ancient "+
	     "stone houses of the long dead. A dark, eerie mist drifts "+
	     "slowly in and out of the narrow, damp, grass alleys between "+
	     "the tombs, snaking its way along the edges of the stone "+
	     "buildings, filling the entire area with a sense of "+
	     "dread and forboding. The graveyard fields extend in all "+
	     "directions out into the dark shadows of the fog.\n\n");

    add_item( ({"tombs", "houses", "buildings", "structures", "stone",
		"rotting stone", "tomb stones", "circle", "tomb circle"}),
	     "The tombs are tall, square stone buildings with completely "+
	     "stone, angled roofs. They are ancient and the stone has "+
	     "long since begun to crack and erode. Obvious signs of "+
	     "water erosion mar the face of the tombs. The eerie mist "+
	     "drifts between them, looming ominously.\n");

    add_item( ({"mist", "fog", "eerie fog", "dark fog", "dark mist",
		"eerie mist", "dark eerie mist"}),
	     "The dark, eerie fog drifts slowly throughout the area, "+
	     "blanketing the entire scene with a dark cover of "+
	     "loneliness and despair.\n");

    add_item( "grass",
	     "The grass is long, uncut and very wet.\n");

    add_item( ({"alleys", "grass alleys"}),
	     "The tombs are all arranged in a a three-quarter circle, all "+
	     "of them facing generally south. The spaces between the tombs "+
	     "form alleys made of long, wet, uncut grass.\n");

    add_exit( GRAVEYARD_DIR + "graveyard1", "south", 0);

}

