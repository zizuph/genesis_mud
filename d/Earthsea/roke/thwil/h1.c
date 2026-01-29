#include "defs.h"
inherit THWIL_BASE_ROOM;

void create_thwil_room()
{
   set_short("pier");
   set_long("You are at the farthest southeast corner "+
	    "of a strange pier. To the north the pier continues "+
	    "for a good 100 meters where it makes a dramatic twist "+
	    "to the east. Directly east from here however, the pier "+
	    "continues for about half that distance. \n");
   
   add_item("pier",
	    "It is a smooth well tended pier, funny not "+
	    "any rubbish at all in sight... \n");
   
   add_exit(THWIL + "h4" , "north" , 0);
   add_exit(THWIL + "h2" , "east" , 0);
   BEACH;
}

