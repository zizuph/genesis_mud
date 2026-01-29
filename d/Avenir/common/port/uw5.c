// Underwater cave   (/d/Avenir/common/port/uw5.c)
// creator(s):       Glinda may -95
// last update:      Lilith May 97: fixed add_action error, typed functions
// 		Lucius, Jan 2009: Re-written for new water code.
// purpose:
//
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/water";
#include "/d/Avenir/common/common.h"

private int broken, polished;
private string other_window = (PORT + "uw10");


public string
hook_no_swim(string str)
{
    if ((str == "west") || (str == "northwest") || (str == "southwest"))
    {
	return "You swim into the cave wall.\n"+
	    "You had no idea it was so close.\n";
    }
    return "";
}

public int
swim_exit(void)
{
    if ((swim_dir == "north") || (swim_dir == "northeast"))
	write("You swim around the cabinhouse.\n");

    return 0;
}

int
do_enter(string str)
{
    if (str!="window")
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
	if (TP->move_living("through the window", PORT + "uw10",1))
	    TP->add_fatigue(-10);
    }
    else
    {
	write("You are much too large to enter the window.\n");
    }
    return 1;
}

int
do_polish(string str)
{
    if (!strlen(str) || !parse_command(str, ({ }), "[a] / [the] 'window'"))
	return NF("Polish what, the window?\n");

    if (broken)
    {
	write("There is not enough window left to polish, it's broken!\n");
    }
    else if (!broken && !polished)
    {
	polished=1;
	write("You gently wipe away the slime from the window.\n");
	say(QCTNAME(TP) + " wipes away slime from the window.\n");
    }
    else if (!broken && polished)
    {
	write("You try to wipe away more slime from the window.\n");
	say(QCTNAME(TP) + " polishes the window, even though it looks " +
	  "like it has already been cleaned.\n");
    }
    return 1;
}

public void
set_broken()
{
    broken=1;
}

int
do_break(string str)
{
    if (!strlen(str) || !parse_command(str, ({ }), "[a] / [the] 'window'"))
	return NF("Break what, the window?\n");

    if (!broken)
    {
	write("You violently break the window. The glass shards float down " +
	  "into the silent darkness. You feel as if you have violated " +
	  "something sacred.\n");
	say(QCTNAME(TP) + " breaks the cabin window. The glass shards float " +
	  "down into the darkness. You feel as if you have witnessed " +
	  "the violation of something sacred.\n");

	broken = 1;
	other_window->set_broken();
    }
    else
    {
	write("Sadly, it is broken already.\n");
    }
    return 1;
}

public void
create_room(void)
{
    underwater_room();
    set_no_drift(1);

    set_short("Underwater in a cave");
    set_long("This is the aft end of the shipwreck. You are right " +
      "the long time the ship has been left at the mercy of the sea. " +
      "A round window is set into the wall of the cabinhouse. The hull of " +
      "the ship is covered with seaweed in which tiny fish swim around " +
      "like small darting shadows. The impenetrable darkness and silence of " +
      "the cave enshrine the ship like a giant crypt.\n");
    add_item(({"wreck","shipwreck","irregularity","hull","ship"}),
      "Amazing. This ship must have been swallowed by the currents and somehow " +
      "transported into this cave. You can tell it has been here for a long " +
      "time since the seaweed is growing richly along the hull.\n");
    add_item(({"cabinhouse","cabin"}),
      "Except from the growth of seaweed the cabinhouse seems remarkably " +
      "intact, a tribute to old times craftmanship. @@cabin_window");
    add_item(({"window"}),"@@window_state");
    add_item(({"water"}),
      "The dark water envelops you completely.\n");
    add_item(({"cliff","rock","wall","floor","ceiling","walls"}),
      "You cannot really see it, despite knowing that it exists, for there is "+
      "only blackness.\n");
    add_item(({"opening"}),
      "The exit from the cave is visible to your southwest as a lighter shade " +
      "of grey in the darkness.\n");

    add_exit(PORT + "uw8", "north");
    add_exit(PORT + "uw8", "northeast");
    add_exit(PORT + "uw6", "east");
    add_exit(PORT + "uw4", "southeast");
    add_exit(PORT + "uw4", "south");
}

string
window_state()
{
    if (broken)
    {
	return "The cabin window has been broken, possibly " +
	"in an attempt to look within. However it is impossible " +
	"to make out anything about the cabinroom because of the " +
	"darkness inside.\n";
    }
    if (polished)
    {
	return "The window seems to have recently been polished " +
	"in an attempt to see within. However it is impossible " +
	"to make out anything about the cabinroom because of the " +
	"darkness inside.\n";
    }
    return "A round window set in the wall of the cabinhouse. Its frame is " +
    "made from some kind of metal, but in the dim light it is " +
    "impossible to make out what. Bronze or lead would be a good " +
    "guess, seemingly inert to the water surrounding it. The window " +
    "is covered with slime disallowing you to look within.\n";
}

string
cabin_window()
{
    if (broken)
    {
	return "The cabin window seems to have been broken " +
	"recently by some other force than fish and sea.\n";
    }
    if (polished)
    {
	return "Even the cabin window has survived the gnaw of time.\n";
    }
    return "Even the cabin window has survived the gnaw of time, " +
	"though it is covered with slime.\n";
}

public void
init(void)
{
    ::init();

    add_action(  do_enter, "enter"  );
    add_action(  do_break, "break"  );
    add_action(  do_break, "smash"  );
    add_action( do_polish, "clean"  );
    add_action( do_polish, "polish" );
}
