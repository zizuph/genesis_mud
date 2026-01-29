#pragma strict_types

#include "default.h"
#include "lift.h"

inherit PORT_ROOM;

void
create_port_room()
{
    set_short("Base of Lift");
    set_long("You find yourself at the base of a huge cliff that towers "+
      "far above you to the north, and stretches west and east into the "+
      "distance. Several thickly-braided ropes stretch up along the face "+
      "of the cliff and out of sight. This seems to be the northeastern "+
      "corner of a small square. The cobblestones beneath you are moist "+
      "and covered with greenish grime. To the southeast is a large "+
      "wooden building. From the cliff you see a rope hanging - just "+
      "within your reach.\n@@basket@@");

    add_item("rope", "To make the lift come, just pull it.\n");
    add_item(({"base","huge cliff","cliff"}), "The sheer rock walls of "+
      "the cliff look completely unclimbable.\n");
    add_item(({"small square","square"}),"The rest of it lies to the west, "+
      "southwest and south.\n");
    add_item(({"cobblestones","cobblestone"}),"The pavement looks a bit "+
      "weatherbeaten and seems to be perpetually covered in a thin film of "+
      "water, as a result a number of rootless plants have taken to fill "+
      "in the cracks among the cobbles.\n");
    add_item(({"greenish grime","grime","rootless plants","plants",
	"rootless plant","plant"}),
      "A number of moss and lichens grow among the cobbles of the square.\n");
    add_item(({"thickly-braided ropes","thickly-braided rope","ropes"}),
      "The large ropes seem to lead to a point far above you, apparently at "+
      "the top of the cliff. You surmise that they are probably part of some "+
      "elaborate system of pulleys and winches using baskets and/or platforms "+
      "that transport people and cargo from here to the cliff's top and "+
      "back.\n");
    add_item(({"large wooden building","large building",
	"wooden building","building"}),
      "A squat one-story structure built out of hardwood. Its most likely "+
      "some sort of warehouse.\n");

    add_exit(PORT + "s7", "west");
    add_exit(PORT + "s9", "east");
    add_exit(PORT + "s23", "southwest");
    add_exit(PORT + "s24", "south");
}

string
basket()
{
    switch (LIFT->query_lift_status())
    {
    case MOVING_DOWN:
	return "The lift seems to be lowering a basket towards you.\n";
	break;
    case MOVING_UP:
	return "The lift seems to move a basket upwards.\n";
	break;
    }

    switch (LIFT->query_lift_location())
    {
    case AT_BOTTOM:
	return "A basket stands quiet on the ground next to you.\n";
	break;
    case AT_TOP:
	return "A large basket hangs over the edge of the cliff far "+
	"above you.\n";
	break;
    }

}

public int
all_aboard(string str)
{
    int tmp;

    if (str != "basket" && str != "wooden basket")
    {
	notify_fail(capitalize(query_verb()) + " what?\n");
	return 0;
    }

    tmp = LIFT->query_lift_status();
    if (((tmp > LIFT_READY) && (tmp < LIFT_RESTING)) ||
      (LIFT->query_lift_location() != AT_BOTTOM))
    {
	write("The basket is not here to "+ query_verb() +".\n");
	return 1;
    }

    write("You climb aboard the basket.\n");
    tell_room(TO, QCTNAME(TP) + " boards the basket.\n", TP);
    tell_room(LIFT, QCTNAME(TP) + " enters the basket.\n", TP);
    set_dircmd("basket");
    TP->move_living("M", LIFT);
    return 1;
}

public int
pull_rope(string str)
{
    if (str != "rope")
    {
	notify_fail("Pull what?  The rope?\n");
	return 0;
    }

    write("You pull on the rope.\n");
    say(QCTNAME(TP) + " pulls on the rope.\n");

    str = "";

    switch (LIFT->query_lift_status())
    {
    case MOVING_DOWN:
	str = "However, the basket is already on its way to you.\n";
	break;
    case MOVING_UP:
	str = "The basket seems to be moving upwards. "+
	"Better try again in a while.\n";
	break;
    case LIFT_RESTING:
	str = "Nothing seems to happen, perhaps the operator is resting.\n";
	break;
    }

    if (strlen(str))
    {
	tell_room(TO, str);
	return 1;
    }

    switch(LIFT->query_lift_location())
    {
    case AT_BOTTOM:
	str = "Nothing happens since the basket is already here.\n";
	break;
    case AT_TOP:
	str = "The rope lurches a bit as the lift begins to move.\n";
	LIFT->move_lift();
	tell_room(LIFT, "The lift begins to move.\n");
	break;
    }

    tell_room(TO, str);
    return 1;
}

void
init()
{
    ::init();

    add_action(all_aboard, "board");
    add_action(all_aboard, "enter");
    add_action(pull_rope,  "pull");
}

