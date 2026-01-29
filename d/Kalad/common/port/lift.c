#pragma strict_types
#pragma no_clone

#include "default.h"
#include "lift.h"

inherit PORT_ROOM;

/*
 * Location:  0 = bottom room, 1 = top room
 * Status  :  0 = ready, 1 = moving up, 2 = moving down, 3 = resting
 */
static private int    Status, location, alarm;
static private string top_room, bot_room;

private void
set_top_room(string file)	{ top_room = file; }

private void
set_bot_room(string file)	{ bot_room = file; }

public string
query_top_room()		{ return top_room; }

public string
query_bot_room()		{ return bot_room; }

private void
set_lift_status(int i)		{ Status = i; }

public int
query_lift_status()		{ return Status; }

private void
set_lift_location(int i)	{ location = i; }

public int
query_lift_location()		{ return location; }

public varargs void
move_lift(int count)
{
    if (!count)
    {
	if (query_lift_status() != LIFT_READY)
	{
	    return;
	}
	else if (query_lift_location() == AT_BOTTOM)
	{
	    set_lift_status(MOVING_UP);
	}
	else
	{
	    set_lift_status(MOVING_DOWN);
	}
    }

    switch(count)
    {
    case 0:
	if (query_lift_location() == AT_BOTTOM)
	{
	    tell_room(query_bot_room(),
	      "The basket leaves for the city above.\n");
	    tell_room(query_top_room(),
	      "The basket seems to ascend towards you.\n");
	}
	else
	{
	    tell_room(query_bot_room(),
	      "The basket seems to descend towards you.\n");
	    tell_room(query_top_room(),
	      "The basket descends towards the port dictrict.\n");
	}
	alarm = set_alarm(nrnd(5.0), 0.0, &move_lift(++count));
	break;
    case 1..4:
	tell_room(TO, one_of_list(LIFT_MSGS));
	alarm = set_alarm(nrnd(5.0), 0.0, &move_lift(++count));
	break;
    case 5:
	if (query_lift_location() == AT_BOTTOM)
	{
	    tell_room(query_bot_room(),
	      "The basket seems to have stopped at the top.\n");
	    tell_room(query_top_room(),
	      "The basket arrives from below.  Now you may board it.\n");
	    tell_room(TO, "The platform shudders to a complete stop " +
	      "at its destination.\nNow is the time to go out.\n");
	}
	else
	{
	    tell_room(query_bot_room(),
	      "The basket arrives from above.  Now you may board it.\n");
	    tell_room(query_top_room(),
	      "The basket seems to have stopped at the bottom.\n");
	    tell_room(TO, "The platform shudders to a complete stop "+
	      "at its destination.\nNow is the time to go out.\n");
	}
	set_lift_status(LIFT_RESTING);
	set_lift_location(!query_lift_location());
	alarm = set_alarm(nrnd(10.0), 0.0, &move_lift(++count));
	break;
    default:
	set_lift_status(LIFT_READY);
	break;
    }
}

void
create_port_room()
{
    set_top_room(TOP_ROOM);
    set_bot_room(BOTTOM_ROOM);

    set_short("In the Lift");
    set_long(
      "The wooden platform is made from strong hardwood logs " +
      "reinforced with blackened steel. " +
      "Discoloration from spills of shipped goods depicts " +
      "a mystical and eerie pattern of horrid color and form. " +
      "Three thick hemp ropes hold the cart aloft and " +
      "transport you to your destination. "+
      "A rope hangs at the side of the lift.\n");

    add_item(({"hardwood logs","hardwood log","logs","log"}),
      "Thick and sturdy, you have no fear that they may snap at any moment "+
      "and cause your untimely death should you be at the top of the cliff.\n");
    add_item(({"blackened steel","steel"}),"Unusually dark steel. Otherwise "+
      "it looks normal.\n");
    add_item(({"thick hemp ropes","thick ropes","hemp ropes","ropes","rope"}),
      "Large ropes that are as thick as your arm. To make the lift move, "+
      "just pull it.\n");

    add_prop(ROOM_I_INSIDE, 1);
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

    if (query_lift_status() == LIFT_RESTING)
    {
	write("Nothing happens, perhaps the operator is resting.\n");
    }
    else if (query_lift_status() > LIFT_READY)
    {
	write("The lift is already in-transit, however.\n");
    }
    else
    {
	if (query_lift_location() == AT_BOTTOM)
	{
	    tell_room(TO, "You feel a lurch as the basket begins "+
	      "to rise.\n");
	}
	else
	{
	    tell_room(TO, "The basket sways a bit as it begins "+
	      "to descend.\n");
	}
	move_lift();
    }
    return 1;
}

public int
exit_lift()
{
    if ((query_lift_status() > LIFT_READY) &&
      (query_lift_status() < LIFT_RESTING))
    {
	write("The lift is in-transit.. leaving now would be "+
	  "rather detrimental to your health.\n");
	return 1;
    }

    write("You leap out of the basket.\n");
    tell_room(TO, QCTNAME(TP) + " leaps out of the basket.\n", TP);

    if (query_lift_location() == AT_TOP)
    {
	tell_room(query_top_room(), QCTNAME(TP) +
	  " leaps out of the basket.\n");
	TP->move_living("M", query_top_room());
    }
    else
    {
	tell_room(query_bot_room(), QCTNAME(TP) +
	  " leaps out of the basket.\n");
	TP->move_living("M", query_bot_room());
    }
    return 1;
}

void
init()
{
    ::init();

    add_action(pull_rope, "pull");
    add_action(exit_lift, "out");
}
