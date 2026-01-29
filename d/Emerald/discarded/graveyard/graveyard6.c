/*
 * GRAVEYARD6.c
 * 
 * Room in the Emerald graveyard.
 * by Alaron July 29, 1996
 */

#include "default.h"

inherit "/std/room";

void
create_room()
{
    set_short("Graveyard");
    set_long("  A heavy overcast of dreary, lonely fog rests heavily "+
	     "upon the damp ground of the grave sites. A chill breeze "+
	     "blows across the tops of the headstones, howling "+
	     "maliciously as it presses its icy chill against your "+
	     "face. Despite the strength of the breeze, the dense, "+
	     "dark gray fog seems to remain motionless; unaffected "+
	     "by the air currents. The damp field is littered with "+
	     "grave sites in what appears to be a random pattern. Looking "+
	     "out across the eerie graveyard in all directions you "+
	     "see an endless gray-and-green sea of death and despair.\n\n");

    add_item( ({"fog", "mist", "dense fog", "thick fog", "heavy fog",
		"lonely fog", "dreary fog"}),
	     "The dark, gray fog hangs ominously over the graves, "+
	     "smothering in its dark gray blanket any sign of hope "+
	     "or light in this despair-filled graveyard. You feel "+
	     "as though there is something more than meets the eye "+
	     "to the fog when you notice that despite the strong, chill "+
	     "breeze blowing against the headstones, the looming "+
	     "mist remains motionless.\n");

    add_item(({"headstones", "head stones", "graves", "gravestones",
	       "grave stones", "grave", "headstone", "grave sites",
	       "sites"}),
	     "Time has not been kind to these ancient, stone grave "+
	     "markers. Most of them are cracked straight through "+
	     "in several places. Some of the headstones are even "+
	     "in several pieces. All of the markers, however, show "+
	     "obvious signs of age and water-decay, leaving the entire "+
	     "graveyards with an old, worn-out appearance. As if the "+
	     "gravestones themselves had died with those in the ground.\n");

    add_item( ({"field", "graveyard", "ground", "down", "damp field"}),
	     "The dark green, damp graveyard is littered in random "+
	     "patterns with hundreds upon hundreds of broken, ancient "+
	     "and decaying gravestones, tombs and grave markings.\n");
    
    add_exit(GRAVEYARD_DIR + "graveyard7", "east");
    add_exit(GRAVEYARD_DIR + "graveyard2", "north");
}

