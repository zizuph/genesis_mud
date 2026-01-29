#include "defs.h"

//object ring;

CONSTRUCT_ROOM
{
    set_short("The Troll's Treasure Chamber!!!");
    set_long(
	"You have entered the trolls treasure chamber!!!\n"+
	"A large flat slab of stone covers almost the whole floor, and in "+
	"a corner there is a shaft from where there comes a rotten smell. "+
	//"If you go down there, you will not be able to come back up. "+
	"A huge boulder blocks the passage down the shaft. In the "+
	"ceiling there is a hole, but you would not be able to climb up. "+
	"In the south however, there is a door, but wait! Is that not trolls "+
	"which are guarding the door there?\n");
    add_item(({"slab","stone","floor"}),
	"The flat slab of stone covers almost all the floor, except from "+
	"in the corner, where it leads down a steep shaft.");
	ITEM(({"boulder", "rock"}),"A huge boulder is set upon the hole "+
	"that leads down the shaft. It looks impossible to move.\n");
    add_item(({"hole","ceiling"}),
	"The ceiling is just a couple of meters above you, but since you "+
	"couldn't climb up there anyhow, it doesn't make any sense to "+
	"investigate that exit further.");
    add_item(({"door","trolls"}),
	"Yes! Scream and terror! Two great Uruk trolls are standing just "+
	"outside the room! If they see you, you'll meet certain death!");
    add_item(({"corner","shaft"}),
	"It is too dark too see down the shaft, but you would guess that "+
	"you would not be able to climb up again.");
    add_item(({"smell","stench"}),
	"Phh. That smells almost like rotten bodies.");
    SOUTH("urukfore");
    //DOWN("sholdpr");
    //reset();
}
/*
RESET_ROOM
{
    if(!ring || !present(ring, TO)) {
	ring = clone_object(MORIA_ARM + "dwarven_ring");
	ring -> move(TO);
    }
}
*/

init()
{
	::init();
	add_action("do_move", "move");
}

int
do_move(string str)
{
	notify_fail("Move what?\n");
	if(!strlen(str))
		return 0;

	if(str == "boulder" || str == "rock")
	{
		write("You try with all your cunning might to move the boulder, "+
		"but it is far to heavy to push in any direction.\n");
		say(QCTNAME(TP)+" tries with all "+HIS_HER(TP)+" cunning might to "+
		"move the boulder, but it is impossible.\n");
		return 1;
	}
	else
	{
		notify_fail("You can't move that!\n");
		return 0;
	}
}
