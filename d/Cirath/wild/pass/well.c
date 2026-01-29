 /* well.c: A well within the mountain pass. */

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void reset_room()
{
   bring_room_team(WILD_NPC+"raidlead.c",1,5,WILD_NPC+"stdraid.c",1);
}

void create_room()
{
    set_short("A well.");
    set_long ("A small stream makes it way along the rocky ground "+
              "here. The precious water looks very inviting. Why don't "+
              "you drink some....\n");
    ROCK;
    SUN;
    TRAIL;
    INSIDE
    add_exit(WILD_PASS+"pass09.c","east",0,2);
    reset_room();	 
}

void init()
{
	::init();
	add_action("my_drink","drink");
}

int my_drink(string str)
{
	
       if(str=="water" || str=="water from stream")
	{
	 	
	        if(TP->query_soaked() < TP->drink_max()-400)
				{
				write ("You drink some water from the well, and you feel refreshed.\n");
				say (QTNAME(TP) + " drinks some water.\n");
				TP->drink_soft(400);
				return 1;
				}
	NF("Nah, you are not thirsty anymore.\n");
        return 0;
	}

return 0;
}


