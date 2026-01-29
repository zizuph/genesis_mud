#include "defs.h"
inherit THWIL_BASE_ROOM;

void create_thwil_room()
{
   set_short("Pier");
   set_long("You are on a strange pier. "+
	    "To the west a small alley leads into the prospering "+
	    "town of Thwil. Protected by the Roke wizards, the "+
	    "townsfolk " +
	    "have flourished even in times of famine elsewhere "+
	    "in Earthsea. "+
	    "The pier continues "+
	    "north and south. \n");
   
   
   add_item("pier",
	    "It is a smooth well tended pier, funny not "+
	    "any rubbish at all in sight... \n"); 
   
   add_item("alley", "The alley is well tended, though a bit " +
	    "nauseating from drying fish nets. \n");
   add_item(({"net", "nets"}), "You can't see any, but you " +
	    "can smell them!\n");
   add_exit(THWIL + "h5" , "north" , 0);
   add_exit(THWIL + "a1" , "west" , 0);
   add_exit(THWIL + "h1" , "south", 0);
   BEACH;
}

