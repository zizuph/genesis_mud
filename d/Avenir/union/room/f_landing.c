/*
 * Hallway in the Union guildhall
 *  Cirion 032096
 */
#pragma strict_types
#include "../defs.h"

#include <filter_funs.h>
#include <composite.h>

inherit BASE;

#define SEE_WEST ({ "/d/Shire/smiths/rooms/shadow_forge" })
#define SEE_EAST ({ "/d/Avenir/union/room/forge" })

int busy;

void     set_busy(int i)       {    busy = i;        }
int      query_busy()          {    return busy;     }

void
reset_room()
{
    busy = 0;
}

int go_east()
{
    if (busy)
    {
	write("As your foot touches the first step down the east stair, "+
	  "you hear a human voice yell: "+
	  "Begone! Powerful, arcane magicks are at work down here. "+
	  "Try later.\n");
	return 1;
    }       
    write("The staircase turns from east to south, where you "+
      "follow it to the cavern's floor.\n");
    return 0;
}

int go_up()
{
    write("You step out of the heat and darkness.\n");
    return 0;
}

int go_west()
{
    write("The staircase curves from west to south, where you "+
      "follow it to the cavern's floor.\n");
    return 0;
}

string east_view()
{
    object *inv, *live, room;
    int i;

    inv = ({ });
    for(i = 0; i < sizeof(SEE_EAST); i++)
	if((room = find_object(SEE_EAST[i])))
	    inv += all_inventory(room);

    if(sizeof(inv)) 
    {
	live = FILTER_LIVE(inv);
	live = FILTER_CAN_SEE(live, TP);
	if(sizeof(live))
	    return " On the floor of the eastern side of the "+
	    "cavern you can see "+ COMPOSITE_LIVE(live) + 
	    " moving about.";
    }
    return "";
}

string west_view()
{
    object *inv, *live, room;
    int i;

    inv = ({ });
    for(i = 0; i < sizeof(SEE_WEST); i++)
	if((room = find_object(SEE_WEST[i])))
	    inv += all_inventory(room);

    if(sizeof(inv)) 
    {
	live = FILTER_LIVE(inv);
	live = FILTER_CAN_SEE(live, TP);
	if(sizeof(live))
	    return " Looking off to the west, you see that " + 
	    COMPOSITE_LIVE(live) + 
	    " is standing near a great forge.";
    }
    return "";
}

void union_room()
{
    set_short("landing overlooking the forges");

    set_long("This is a wide stone landing made from "
      +"white marble streaked with veins of adamantine, "
      +"about halfway down into a large cavern. "
      +"Here, the wide stairs that descend from the north "
      +"split into two, one set following the curve of the "
      +"east wall, the other down to the west."
      +"@@west_view@@@@east_view@@\n");

    add_item(({"hall","hallway","wall","walls","limestone"}),
      "The walls of the hallways are made from a powdery "
      +"smooth limestone, flawless and white.\n");
    add_item(({"floor","ground"}),"The floor is solid "
      +"marble, the same as the stairs.\n");
    add_item(({"stairs","stair","staircase"}),"The stairs "
      +"climb to the north where they seem to turn west, and "
      +"descend to the south into a thick gloom from which "
      +"hot air rises.\n");

    add_exit("landing", "up", "@@go_up@@");
    add_exit("forge", "east", "@@go_east@@");
    add_exit("/d/Shire/smiths/rooms/shadow_forge","west","@@go_west@@");
}

