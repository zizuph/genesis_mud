// Underwater cave   (/d/Avenir/common/port/uw8.c)
// creator(s):       Glinda may -95
// last update:
// 		Lucius, Jan 2009: Re-written for new water code.
// purpose:
//
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/water";
#include "/d/Avenir/common/common.h"

private object door;

public int
swim_exit(void)
{
    if ((swim_dir == "cabin") || (swim_dir == "southwest"))
    {
	if (door->query_open())
	{
	    write("You swim through the cabin door.\n");
	    return 0;
	}

	write("The cabin door is closed.\n");
	return 1;
    }
    else if ((swim_dir == "hatch") || (swim_dir == "down"))
    {
	write("You dive into the hatch.\n");
    }
    else if (swim_dir == "west")
    {
	write("You swim around the cabinhouse.\n");
    }
    return 0;
}

public int
swim_hatch(void)
{
    if (room_dircmd != "hatch")
    {
	write("Enter what?\n");
	return 1;
    }

    write("You dive into the hatch.\n");
    swim_dir = "hatch";
    swim = 1;

    return 0;
}

public string
hook_no_swim(string str)
{
    if ((str == "north") || (str == "northwest"))
    {
	return "You swim into the cave wall.\n"+
	    "You had no idea it was so close.\n";
    }
}

public string
hook_swim_from(void)
{
    if ((swim_dir == "hatch") || (swim_dir == "down"))
	return "swimming through the hatch.";

    return "";
}

public void
create_room(void)
{
    underwater_room();
    set_no_drift(0);

    set_short("On the deck of a shipwreck");
    set_long("You are on the deck of an old shipwreck. The ship tilts "+
      "to starboard and aft, making the deck slope slightly southwest "+
      "toward the cabinhouse door. The deck is covered with a thick "+
      "layer of mud and algae in which some larger seaplants have found "+
      "enough foundation for growing, their large leaves floating with "+
      "the currents. The outline of a hatch protrudes from the deck, "+
      "leading to the storage room below. The mast is broken midway, "+
      "its upper portion falling back down to the deck, like a gesture "+
      "of surrender.\n");
    add_item(({"slime","alga","mud","surfaces","walls","wall"}),
      "A thin layer of mud and algae covers all surfaces.\n");
    add_item(({"leaves","seaplants","plants","seaweed"}),
      "A few larger species of seaweed grow here, larger than the ones "+
      "that grow on the hull.\n");
    add_item(({"hatch"}),
      "You stare into the darkness of the storage room. You cannot make "+
      "out much in the darkness, but you think you see some motion down "+
      "there... Or is it just your imagination playing tricks on you?\n");
    add_item(({"wreck","shipwreck","irregularity","hull","ship"}),
      "Amazing. This ship must have been swallowed by the currents and "+
      "somehow transported into this cave. You can tell it has been here "+
      "for a long time since the seaweed is growing everywhere.\n");
    add_item(({"cabinhouse","cabin"}),
      "Except from the growth of seaweed, the cabinhouse seems remarkably " +
      "intact, a tribute to its excellent craftmanship. A door leads "+
      "from the deck into the cabinhouse.\n");
    add_item(({"water"}),
      "The dark water envelops you completely.\n");
    add_item(({"cliff","rock","wall","floor","ceiling","walls"}),
      "You cannot really see it, there is only blackness.\n");

    add_exit(PORT + "uw10", "cabin");
    add_exit(PORT + "uw11", "hatch");
    add_exit(PORT + "uw11", "enter", swim_hatch);
    add_exit(PORT + "uw11", "down");
    add_exit(PORT + "uw9",  "northeast");
    add_exit(PORT + "uw9",  "east");
    add_exit(PORT + "uw6",  "southeast");
    add_exit(PORT + "uw6",  "south");
    add_exit(PORT + "uw10", "southwest");

    remove_prop(ROOM_I_NO_EXTRA_DESC);

    door = clone_object("/std/door");
    door->set_door_id("uw_door");
    door->set_door_desc("A rather narrow door made from dark wood.\n");
// Not used / necessary.
//    door->set_pass_command(({"swim sw","swim southwest","sw","southwest"}));
    door->set_fail_pass("The cabin door is closed.\n");
    door->set_door_name(({"door","cabin door"}));
    door->set_other_room(PORT + "uw10");
    door->set_open_desc("The cabin door is open.\n");
    door->set_closed_desc("The cabin door is closed.\n");
    door->set_open(0);
    door->move(TO);
}

public void
reset_room(void)
{
    if (door->query_open())
    {
	string mess = "The water currents swing the "+
	    door->short() +" shut.\n";

	door->do_close_door(mess);
	door->query_other_door()->do_close_door(mess);
    }
}
