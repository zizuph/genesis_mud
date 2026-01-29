#include "defs.h"

int door_status = 0;
void close_it();

CONSTRUCT_ROOM
{
    set_short("Bottom of the Trolls dungeon");
    set_long(
	"This is the bottom of the Trolls dungeon.\n"+
	"This is a small room which is built into the mountain. The room is " +
    "dark and the floor dirty from all the prisoners thrown in here. The " +
    "only exit here is up.\n");
    UP("prison");
    add_item(({"hole","ceiling"}),
	"There is a hole in the ceiling here, leading to another room.");
    add_item(({"wall","walls","dungeon"}),
	"It seems like the dwarves made this dungeon quite safe for "+
	"their prisoners. The walls look very solid.");
    add_item(({"floor", "ground"}),
	"It is very dirty from all the prisoners kept here. Scratched on the floor is an inscription.");
    add_item("inscription",
	"You might want to read it.\n");
}

init()
{
    ::init();
    add_action("read", "read");
    add_action("my_say", "'",1);
    add_action("my_say", "say");
    add_action("my_say", "rsay");
    add_action("my_say", "shout");
}

int
read(string str)
{
    if (str!="inscription")
	return notify_fail("Read what?\n");
    TP->catch_msg(
	"The inscription reads:\n"+ 
    "I, Gloin of the Dwarves, was here. There is a secret exit, made " +
    "by us dwarves to get out of here that the Trolls do not know. The " +
    "password, friend, we dare not reveal here. The orcs have been " +
    "known to torture their prisoners to learn how we escape here. " +
    "But when you get out watch out for the trolls and orc!\n");
    tell_room(TO,
	QCTNAME(TP)+" reads a hidden inscription.\n", TP);
    return 1;
}

int
my_say(string what)
{
    what = lower_case(what);
    if (what != "friend")
	return 0;
    if(door_status == 0) // door closed
    {
        tell_room(TO,
	    "A hidden exit to the south reveals in the wall!!\n");
        add_exit(THIS_DIR+"shnarhol", "south", "@@goes_south");
        (THIS_DIR+"shnarhol")->EXIT("prison2", "north");
        door_status = 1;
        set_alarm(4.0, 0.0, &close_it());
    }

}

int
goes_south()
{
    if(door_status == 1) // door open
    {
        set_alarm(4.0, 0.0, &close_it());
        return 0;
    }
    return 1;
}

close_it()
{
    if (door_status == 1) // door open
    {
        tell_room(TO,
	    "The southern exit suddenly slams shut!\n");
        tell_room(THIS_DIR+"shnarhol",
    	"The northern exit suddenly slams shut!\n");
        remove_exit("south");
        (THIS_DIR+"shnarhol")->remove_exit("north");
        door_status = 0; // door closed
    }
}
