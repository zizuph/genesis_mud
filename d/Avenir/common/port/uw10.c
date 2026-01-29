// Underwater room   (/d/Avenir/common/port/uw10.c)
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
private int broken, drawer_state;
private int skeleton, made_eels;
private string other_window = (PORT + "uw5");


public void
reset_room(void)
{
    if (!skeleton && !present("bones"))
    {
	add_cmd_item(({"skeleton"}),({"get","take","pick","touch"}),
	    ({"get","take","pick","touch"}));
	add_item(({"skeleton","captain"}), "The skeletal remains of a human " +
	  "sits in a chair behind the desk. The grotesque grin of the " +
	  "skull seems to be directed at you watching your every move.\n");

	skeleton = 1;
    }

    drawer_state = 0;
    made_eels = 0;
}

public int
cmditem_action(string str)
{
    if (!skeleton || (str != "skeleton"))
	return 0;

    write("As you touch the skeleton it collapses into a pile of bones.\n");
    say("As " + QTNAME(TP) + " touches the skeleton it collapses into a " +
	"pile of bones.\n");

    object obj = clone_object(PORT + "obj/bones");
    obj->move(TO);

    remove_item("captain");
    remove_item("skeleton");
    remove_cmd_item("skeleton");

    skeleton = 0;
    return 1;
}

public int
do_open(string str)
{
    if (str != "drawer")
	return NF("Open what?\n");

    if (drawer_state)
    {
	write("The drawer is already open.\n");
	return 1;
    }

    write("You open the drawer.\n");
    say(QCTNAME(TP)+" opens the drawer in the desk.\n");

    drawer_state = 1;
    if (made_eels)
	return 1;

    tell_room(TO, "Two eels dart out of the drawer!\n");

    object eel = clone_object(PORT + "mon/eel");
    eel->move(TO);
    eel = clone_object(PORT + "mon/eel");
    eel->move(TO);
    made_eels = 1;

    return 1;
}

public int
do_close(string str)
{
    if (str != "drawer")
	return NF("Close what?\n");

    if (!drawer_state)
    {
	write("The drawer is already closed.\n");
	return 1;
    }

    write("You close the drawer.\n");
    say(QCTNAME(TP)+" closes the drawer in the desk.\n");

    drawer_state = 0;
    return 1;
}

public int
do_enter(string str)
{
    if (str != "window")
	return NF("Enter what?\n");

    if (!broken)
    {
	write("The window is closed and you see no way of opening it.\n");
	return 1;
    }

    string race = TP->query_race_name();
    if (race == "hobbit" || race == "gnome")
    {
	write("You crawl through the window.\n");
	if (!TP->move_living("through the window", PORT + "uw5", 1))
	    TP->add_fatigue(-10);
    }
    else
    {
	write("You are much too large to enter the window.\n");
    }
    return 1;
}

public void
set_broken()
{
    broken=1;
}

public int
do_break(string str)
{
    if (str != "window")
	return NF("Break what?\n");

    if (!broken)
    {
	write("You violently break the window. The glass shards float down " +
	  "into the silent darkness. You feel as if you have violated " +
	  "something sacred.\n");
	say(QCTNAME(TP) + " breaks the cabin window. The glass shards float " +
	  "down into the darkness. You feel as if you have witnessed " +
	  "the violation of something sacred.\n");
	broken =1;
	other_window->set_broken();
	return 1;
    }

    write("Sadly, it is broken already.\n");
    return 1;
}

public int
swim_exit(void)
{
    if (!door->query_open())
    {
	write("The cabin door is closed.\n");
	return 1;
    }

    write("You swim through the cabin door.\n");
    return 0;
}

public void
create_room(void)
{
    underwater_room();
    set_no_drift(1);

    set_short("In the cabin of a shipwreck");
    set_long("You have entered the cabin of an old shipwreck. " +
      "@@skeleton@@ Looking around the room, you see that it once must "+
      "have provided rather comfortable quarters for the captain. "+
      "Now, however, the sea has claimed it, slime and alga covering "+
      "most of the surfaces. The torn remains of a sailor's hammock seems "+
      "to wave almost sadly at you from two solid brass rings in the south "+
      "corner. A sturdy desk with a chair behind it is set against the "+
      "northwest wall. Some tracks are visible in the thin " +
      "layer of mud that covers the floor.\n");
    add_item(({"hammock","fabric","rings","corner","remains"}),
      "In the south corner of the cabin fabric remains of a hammock "+
      "flows with the current from the brass rings that the hammock "+
      "was one spanned between.\n");
    add_item(({"slime","alga","mud","surfaces","walls","wall"}),
	"A thin layer of mud and alga covers all suraces.\n");
    add_item(({"tracks","floor"}),
      "There are some wavy tracks in the mud on the floor, probably "+
      "made by some fish or eel.\n");
    add_item(({"desk"}),
      "A dark wooden desk with a large drawer. This must be where "+
      "the captain would sit planning his trips, looking at drafts, "+
      "staking out his positin and setting his cource. The desk has "+
      "been nailed to the cabin floor in to prevent it from moving "+
      "when the sea is rough.\n");
    add_item(({"chair"}),
      "A heavy wooden chair which has been nailed to the cabin "+
      "floor in a convenient distance from the desk in order to "+
      "keep it from moving when the sea is rough.\n");
    add_item(({"drawer"}),"@@drawer_desc@@");
    add_item(({"wreck","shipwreck","irregularity","hull","ship"}),
      "Amazing. This ship must have been swallowed by the currents "+
      "and somehow transported into this cave. You can tell it has "+
      "been here for a long time since the seaweed is growing "+
      "everywhere.\n");
    add_item(({"cabinhouse","cabin"}),
      "Except from the growth of seaweed the cabinhouse seems remarkably " +
      "intact, a tribute to old times craftmanship. A door leads out of the " +
      "cabinhouse to the ships deck.\n");
    add_item(({"water"}),
      "The dark water envelops you completely.\n");
    add_item(({"window"}),
      "A round window set in the wall of the cabinhouse. Its frame is "+
      "made from some kind of metal, but in the dim light it is "+
      "impossible to make out what. Bronze or lead would be a good "+
      "guess, seemingly inert to the water surrounding it. "+
      "@@window_state@@\n");

    add_exit(PORT + "uw8", "out");
    add_exit(PORT + "uw8", "northeast");

    remove_prop(ROOM_I_NO_EXTRA_DESC);

    door = clone_object("/std/door");
    door->set_door_id("uw_door");
    door->set_door_desc("A rather narrow door made from dark wood. " + 
      "It is set in the northeast wall.\n");
// Not used / necessary.
//    door->set_pass_command(
//	({"swim ne","swim northeast","ne","northeast"}));
    door->set_fail_pass("The cabin door is closed.\n");
    door->set_door_name(({"door","cabin door"}));
    door->set_other_room(PORT + "uw8");
    door->set_open_desc("The cabin door is open.\n");
    door->set_closed_desc("The cabin door is closed.\n");
    door->set_open(0);
    door->move(TO);
    broken = 0;

    reset_room();
}

public void
init(void)
{
    ::init();
    TP->add_prop("_has_been_in_shipwreck",1);

    add_action( do_enter, "enter" );
    add_action(  do_open, "open"  );
    add_action( do_close, "close" );
    add_action( do_break, "break" );
    add_action( do_break, "smash" );
}

string
window_state()
{
    if (!broken)
	return "";
    else
	return "The window has been broken.";
}

string
drawer_desc()
{
    if (drawer_state)
    {
	return "The drawer is open. Whatever might have been in there has " +
	"decayed into a layer of mud.\n";
    }
    return "The drawer is closed.\n";
}

string
skeleton()
{
    if (skeleton)
    {
	return "You eyes immediately land on the skeleton which sits behind " +
	"the desk.";
    }
    return "";
}
