/*Created by Stevenson*/
/* The beginning room for the White Dragon Quest */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

int trigger_set = 0;

init() 
{
    ADA("north");
    ::init();
}

create_icewall_room() 
{
    set_short("Warm Place");
    set_long("An amazing room, considering that all around is ice. You see "
	     + "grass and flowers growing lazily next to the path. To the north "
	     + "you see a large hole and to the west you can hear "
	     + "the soft clinking of the ice chunks floating in the lake.  East, "
	     + "however, you sense that something is waiting for you.\n"
	     + "@@show_door");
    
    add_cmd_item("hole","enter","Why not just go north?\n");
    add_item("ceiling","It is high above you.\n");
    add_item("path",
	     "It runs alonside the flowers giving you something else to trample on.\n");
    add_item("hole","It looks big enough to walk through.\n");
    add_item(({"grass","flowers"}),
	     "Looking closely at the grass and flowers you notice a small "
	     + "trickle of steaming water nourishing them.\n");
    add_item("water","The steaming water issues from a small fissure "
	     + "in the ground.\n");
    add_item("fissure","It is the source for the water.\n");
    add_item("ground","There is a small fissure in it.\n");
    add_item(({"block","ice"}),"@@item_door");
    add_exit(CAVERNS+"cavern4.c","west");
    add_exit(QUEST+"to_drag_1","east","@@is_closed");
    
    reset_icewall_room();
}

int 
north() 
{
    write("You climb through the hole.\n");
    say(QCTNAME(TP)+" climbs through the hole in the north wall.\n");
    tell_room(QUEST+"path1",QCTNAME(TP)+" climbs out of the hole "
	      + "in the south wall.\n");
    TP->move_living("M",QUEST+"path1",0,0);
    return 1;
}
int 
is_closed() 
{
    if (trigger_set) 
    {
	write("A massive block of ice bars your passage.\n");
	say(QCTNAME(TP)+" tries to go east but is stopped by a block of ice.\n");
	return 1;
    }
    return 0;
}

string 
show_door() 
{
    if (!trigger_set)
      return "";
    return "Block of ice.\n";
}

string 
item_door() 
{
    if (!trigger_set) 
      return "What?\n";
    return ("It is a large block of ice which is blocking the "
	    + "way east. Looking over its surface you see scratch "
	    + "marks which makes you think it fell from above in the "
	    + "near past.\n");
}

int 
set_trigger()
{
    trigger_set = !trigger_set;
    return trigger_set;
}

int 
query_trigger() 
{
    return trigger_set;
}

void 
reset_icewall_room()
{
    if (query_trigger())
    {
	tell_room(TO,"The block of ice slowly rises to the ceiling.\n");
	set_trigger();
    }
}
