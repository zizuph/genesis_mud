#include "defs.h"
inherit THWIL_BASE_ROOM;

void create_thwil_room()
{
   set_short("Pier");
   set_long("You are on a solid stone pier, feeling slightly "+
	    "uncomfortable. Something with the pier feels wrong. "+
	    "To the west you see glimpses of Thwil, "+
	    "the only town at Roke, though "+
	    "the inhabitants themselves think about it as a city. "+
	    "Still further west you see the characteristic lush, green "+
	    "meadows of the island. "+
	    "The pier continues east and west.\n");
   
   add_item("pier","It is a smooth well tended pier, funny not "+
	    "any rubbish at all in sight... \n");
   add_item("bay", "Some fishingboats are just setting sail "+
	    "to try their luck for food. \n");
   
   
   add_exit(THWIL + "h9" , "west" , 0);
   add_exit(THWIL + "h7" , "east" , 0);
   BEACH;
}



