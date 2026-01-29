/*
 * 1k9.c
 * This is the courtyard in the Telberin Castle.
 * Originally by Jasmine, Re-Described by Xarguul July 25, 1996
 * Added items - Alaron August 16, 1996
 */

#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
    ::create_room();
   set_short("Courtyard");
   set_long("\n"+
	    "   You stand near the outer wall of an enormous open courtyard, "+
	    "dwarfed in the shadow of a huge decorative fountain in the "+
	    "center. A fresh breeze blows through the courtyard, lapping "+
	    "gently at the hanging tapestries in the northwest corner. Looking "+
	    "up, a sight of clear sky and the top walls of the castle are "+
	    "revealed to you. The second and third floors of the castle "+
	    "maneuver around the courtyard, small fenced balconies overlook "+
	    "the peaceful scene from above. Arched, stone hallways lead out of the courtyard "+
	    "in all four directions. The warm, tantalizing smell of something "+
	    "being freshly baked drifts temptingly into the open air of the "+
	    "courtyard.\n\n");
  
    add_item( ({"tapestries", "tapestry", "northwest corner"}),
             "Beautiful, hanging tapestries adorn the northwest "+
             "corner of the courtyard. They lie underneath large "+
             "awnings and the undersides of the surrounding balconies "+
             "to protect them from the harsh weather. They depict "+
             "scenes of calm, beautiful serenity and invoke a feeling "+
             "of peace.\n");

    add_item( ({"fountain", "huge fountain", "decorative fountain",
		"huge decorative fountain"}),
	     "The fountain is a breathtaking sight. It is constructed out "+
	     "of stone and marble, its base being a lavish stone circle "+
	     "filled with several planted gardens. The base gardens display "+
	     "hundreds of beautiful and rare plants. In the center of the "+
	     "garden stands a beautiful statue of a tall, robed female "+
	     "elf. She is playing the flute as streams of clear, blue "+
	     "water trickle out of the holes in the instrument. It reaches "+
	     "almost to the height of the balcony surrounding the courtyard "+
	     "on the second floor of the castle.\n");

    add_item( ({"garden", "gardens", "dirt", "base gardens", "plants",
		"flowers", "rare plants", "beautiful plants"}),
	     "The base of the fountain is a beautiful garden filled "+
	     "with rare, exotic and beautiful plants.\n");

    add_item("flute",
	     "It is the statue of the elf maiden's flute. It is sending "+
	     "trickles of clear, blue water to the base of the fountain.\n");

    add_item(({"robed elf", "statue"}),
	     "The statue is breathtaking. It is the angelic image of "+
	     "a lightly robed female elf playing the flute.\n");

    add_item( ({"balconies", "fenced balconies"}),
	     "Small, fenced balconies overlook the courtyard from the "+
	     "second and third floors of Castle Telberin. It looks like "+
	     "they might be nice places to sit and relax and enjoy "+
	     "the view.\n");


   add_exit(CASTLE_DIR + "1k10","north",0);
   add_exit(CASTLE_DIR + "1k2","west",0);
   add_exit(CASTLE_DIR + "1k5","south",0);
   add_exit(CASTLE_DIR + "1k7","east",0);
}

