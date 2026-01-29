#include "defs.h"
inherit THWIL_BASE_ROOM;

void create_thwil_room()
{
   set_short("Pier");
   set_long("You are at a strange pier. " +
	    "The distant noise of waves attacking the outer "+
	    "pier can be heard. Somehow you feel confident that this "+
	    "pier won't fall apart from a normal storm. "+
	    "Not that you have seen bad weather in Roke "+
	    "though, funny that...\n"+
	    "There is a pub to the west and the pier continues " +
	    "south and north.\n");
   
   add_item("pier","It is a smooth well tended pier, funny not "+
	    "any rubbish at all in sight... \n");
   
   add_exit(THWIL + "h9" , "north" , 0);
   add_exit(THWIL + "h5" , "south" , 0);
   add_exit(THWIL + "pub", "west", 0);
   BEACH;
}







