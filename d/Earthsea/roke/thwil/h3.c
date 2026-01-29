#include "defs.h"
inherit THWIL_BASE_ROOM;

void create_thwil_room()
{
   set_short("pier");
   set_long("You are at the south-eastern end of Thwil's pier. "+
	    "Westwards the pier leads back to the town. "+
	    "To the east only the open sea can be seen, the waves "+
	    "whipping forth white scum in their pursuit for land. "+
	    "Their ferocity makes you feel happy "+
	    "that you have solid earth under your feet. Strange "+
	    "though, the height and aggressiveness of the sea falls "+
	    "considerably as the waves approach Roke. It looks as though " +
	    "they pass through an invisible boundary... \n");
   add_item(({"wave","waves","sea"}),"It seems like that the waves "+
	    "call out for you, mocking you to swim east...\n");
   
   add_item("pier","It is a smooth well tended pier, funny not "+
	    "any rubbish at all in sight... \n");
   
   
   add_exit(THWIL + "h2" , "west",0);
   
   BEACH;
}

