/*
 * 2k8.c
 * Telberin Castle Second Floor.
 * - Alaron November 1996
 */

#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
    ::create_room();
   set_short("Stone hallway");
   set_long("   Standing in a large corner section of the hall, you are brushed "+
	"aside without so much as a second glance as people scurry in and out of "+
	"the hallway leading to the courtroom. The people are outfitted in fine "+
	"court clothes and shining, silky dresses with frills and sparkling "+
	"jewelry to accent their decadence. The emerald green walls glow softly "+
	"and seem to cast a dim green shade against the stone floor. The hallway "+
	"turns the corner to the west and south. The sound of people arguing, debating, "+
	"shouting and discussing melts into one loud din echoing through the hall "+
	"from the courtroom.\n\n");

   
   add_item( ({"people", "clothes", "dresses", "jewelry"}),
	    "The people brushing past you through the hall are all outfitted in "+
	    "fine clothing accented in expensive jewelry. They charge through the "+
            "hall and brush you aside without much thought as they hurry to and "+
            "from their court appointments.\n");

   add_item( ({"court", "courtroom"}),
            "You can't see the courtroom from here, but from all of the commotion "+
	    "and noise coming from the west hallway, you can guess that it is somewhere "+
            "in that direction.\n");
   
   add_exit(CASTLE_DIR + "2k6","south",0);
   add_exit(CASTLE_DIR + "2k9","west",0);
}

