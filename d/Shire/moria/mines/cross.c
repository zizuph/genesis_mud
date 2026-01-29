#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("The Crossing");
    set_long(
	"This is the Crossing. A dark passage from the west continues east here, "+
	"and in the north a wide passage climbs upwards. The walls are covered "+
	"with a bad-smelling moss, while the floor is made of pure rock. There "+
	"is an interesting opening in the south wall.\n");
    add_item(({"exit","exits"}),
	"Which exit do you mean? North, south, east or west?");
    add_item("passage", "Which passage? The dark or the wide passage?");
    add_item(({"dark passage","west exit", "east exit"}),
	"You could follow the dark passage to the west and the east.");
    add_item(({"opening", "south exit"}),
	"Why is it interesting? Well, let's go there and find out!! :-)");
    add_item(({"wide passage", "north exit"}),
	"It slopes slowly upwards to the north.");
    add_item(({"walls","moss"}),
	"The walls are covered with a bad-smelling moss of some kind. "+
	"It does not look very appealing.");
    add_item("floor", "It seems to be made of the surrounding rock, which "+
	"is granite.");
    NORTH("widepas2");
    SOUTH("private_closet");
    EAST("roundchb");
    WEST("bedroom");
    reset();
}

int amount;

RESET_ROOM
{
    amount = 2;
}

init()
{
    ::init();
    add_action("pick","pick");
    add_action("pick","grab");
    add_action("pick","get");
}

int pick(string what)
{
    if (what!="moss")
	return notify_fail(CAP(query_verb())+" what?\n");
    if (amount==0)
	return notify_fail(
	    "Sorry, but you can't "+query_verb()+" anymore moss now.\n");
    write("You "+query_verb()+" a handfull grey moss.\n");
    clone_object(MORIA_HERB + "pindan")->move(TP);
    amount --;
    return 1;
}
