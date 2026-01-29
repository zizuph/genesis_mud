/*Created by Stevenson*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

create_icewall_room() 
{
    set_short("Smooth Tunnel");
    set_long("The walls here are very smooth and icy.\n");
    
    add_item(({"stone","loose stone"}), "You search the room for " +
	     "the loose stone you seem to have stepped on, but " +
	     "you can't seem to find one.\n");
    add_item("walls",
	     "They were worn smooth over time. On one side you notice strange writing.\n");
    add_item("writing","It is readable.\n");
    add_cmd_item("writing","read",
		 "In their attempts to defeat the evil minions of Takhisis, "
		 + "the followers of Paladine would forge the Mighty Dragonlance. "
		 + "With it, they would pierce through the evil of the vilest "
		 + "dragons.\n");
    add_exit(QUEST+"to_drag_1","west","@@set_trigger");
    add_exit(QUEST+"to_drag_3","southeast","@@set_trigger");
}

int 
set_trigger() 
{
    write("You hear a soft click as you step on a loose stone.\n");
    if ((QUEST+"dryland")->set_trigger()) 
    {
	tell_room(QUEST+"dryland","A massive block of ice crashes down, blocking "
		  + "the east exit.\n");
	tell_room(QUEST+"to_drag_1","You hear a loud crashing sound "
		  + "immediately to the west.\n");
	say("You hear a loud crash in the distance.\n");
	write("In the distance is a loud crash.\n");
	return 0;
    }
    tell_room(QUEST+"dryland","The block of ice suddenly rises "
	      + "into the ceiling.\n");
    return 0;
}
