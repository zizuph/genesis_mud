/* goblin caves */

#include <ss_types.h>
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);

    set_short("goblin prison");
    set_long("This room is dark and smells bad. It seems this " +
        "is where goblins keep their prisoners. To the west is " +
        "a door that leads back to the tunnels. Loud noises " +
        "echo in from the north. The prison continues to the east.\n");

    add_item("door", "This is the other side of the secret " +
        "door. Goblins haven't even tried to hide it from this " +
        "side. You can probably push it to get through.\n");
    add_item(({"wall","walls"}),
    "The walls are dark and foreboding, and reek of evil deeds.\n");

    add_exit(ROOMS_DIR+"c94", "southwest");
    add_exit(ROOMS_DIR+"c97", "south");
}

void
init()
{
    ::init();
    add_action("push_something", "push");
}

int
push_something(string something)
{
    if(something=="door")
    {
	TP->catch_msg("You open the door and pass through it quickly. The wall swings "+
	  "back, closing the small opening.\n");
	say(QCTNAME(TP)+" opens the door and passes through it quickly. The wall " +
        "swings back, closing the small opening.\n");
	tell_room(ROOMS_DIR+"c92",QCTNAME(TP)+" enters the room through a "+
	  "secret door.\n");
	TP->move_living("M",ROOMS_DIR+"c92");
	return 1;
    }
    return 0;
}
