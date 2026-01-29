/*Created by Stevenson*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

create_icewall_room() 
{
    set_short("Smooth Walled Tunnel");
    set_long("The walls here are very smooth and icy.\n");
    
    add_item("walls","They were worn smooth over time. On one side "
	     + "you notice some strange writing.\n");
    add_item("writing","It is readable.\n");
    add_cmd_item("writing","read",
		 "In ancient times, men flew upon dragons. Great battles "
		 + "were waged in the air. Good would overcome evil but not "
		 + "without a price. Thus the Gods would wage warfare via "
		 + "mortal participants.\n");
    add_exit(QUEST+"dryland","west","@@check_blocked");
    add_exit(QUEST+"to_drag_2","east");
}

int 
check_blocked() 
{
    if ((QUEST+"dryland")->query_trigger()) 
    {
	write("For some bizarre reason that way seems to be blocked.\n");
	return 1;
    }
    return 0;
}
