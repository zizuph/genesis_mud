/*
 * /d/Genesis/guilds/merc/west_hall, by Morrigan 11/2001
 *
 */
inherit "/std/room";

#include "../merc.h"
#include "room.h"

object guard1;

void
reset_room()
{
    /* They have all left. (Gorboth)
    if (!guard1)
	(guard1 = clone_object(MNPC + "merc_base"))->move(this_object());
    */
}


int enter_west_hall()
{
    write("As you approach, the guards open the door and allow you to pass.\n");
    return 0;
}

int enter_unopen_area()
{
    if(MERC_DISALLOW_DOGS)
    {
	write("That way is not open yet.\n");
	return 1;
    }

    return 0;
}

public void
create_room()
{
    set_short("A hallway");
    set_long(BUILDING_DESC+
        "This is a hallway leading north away from the main guild halls. "+
	"To the west you notice a counter of some sort, while the hall "+
	"continues north. To the east you can hear the sounds of dogs, and "+
	"you notice the scent of outdoors. To the south is a door leading "+
	"back to the "+
	"common area of the halls.\n");

    add_item("door", "The door is in the south wall.\n");
    add_cmd_item("door", "open", "The door is locked.\n");
    add_cmd_item(({"door", "lock"}), "pick", "You start to try to "+
	"pick the lock, but stop at the glance of several unhappy "+
	"guards.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit(MROOM + "armoury.c", "west", 0, 1, 0);
    add_exit(MROOM + "kennel.c", "east", "@@enter_unopen_area", 1, 0);
    add_exit(MROOM + "west_hall.c", "south", "@@enter_west_hall", 1, 0);
    add_exit(MROOM + "lord_boardroom.c", "north", 0, 1, 0);
    reset_room();
}
