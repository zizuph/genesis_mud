/* 
 * Mortis 02.2005 
 * 
 * Ledge outside fourth floor window of master suite.
 *
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <ss_types.h>
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>

#define PEEKIN				(SHIP + "trusq_master")
#define VIEWSTREET			(SHIP + "alley201")

inherit SHIP_BASE;

// Prototypes
string window_status();

int winopen, winlock, gargoyle;
object garg;

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "This ornately worked, thin ledge is barely enough for you "
	+ "to perch on.  It offers a wide view of the shipping quarter, but at "
	+ "almost two score feet high with gusty breezes, it comes at a price.  "
	+ "There is a window here, and large-eyed, hunching gargoyles peer down "
	+ "at you from the corners of the roof.  ";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += road + "The estate's pristine marble glows in "
	+ one_of_list(({"pale purple ", "soft pink ", "pale orange ",
	  "grey and pink "})) + "hues as the sun peeks above the mountains.  The "
	+ "air is rich with the smells of wood, tar, and coffee borne on a cool, "
	+ "misty breeze from the bay.\n";
	break;

    case TOD_DAY:
	desc += road + "The estate's pristine marble gleams in the midday sun as "
	+ "servants and dock hands pass by filling the side street with the "
	+ "noisy murmurings of their daily business.  A cool, salty breeze "
	+ "blows south off the bay.\n";
	break;

    case TOD_TWILIGHT:
	desc += road + "The estate's pristine marble catches the last rays of "
	+ "the sun appearing to glow of its own accord as servants, sailors, and "
	+ "dockhands make their way about the street.  A misty, salty breeze "
	+ "blows south off the bay.\n";
    break;

    case TOD_NIGHT:
	desc += road + "The moon and stars shed pale light across the pristine "
	+ "marble of the estate amplifying the yellow glow of the street lamps.  "
	+ "A few dock workers still make their way about at this hour.  "
	+ "A cool, salty breeze blows south off the bay.\n";
    break;

    default:
	break;
    }
    return desc;
}

void
reset_palan_room()
{
	winopen = 1;
	winlock = 1;
	gargoyle = 0;

	if (garg)
		garg->remove_object();
}

void
create_palan_room()
{
    SHORT("On a thin ledge off the fourth story of a great, marble estate");
    LONG("@@get_time_desc@@");

	ITEM("window", "An iron-rimmed window looks in on the fourth floor.  "
	+ "You can <peek window> to have a look.  " + "@@window_status@@" + "\n");
	ITEM("lock", "There is a small, iron keyhole in the center of the window "
	+ "that locks from the inside.\n");
	ITEM(({"view", "ledge"}), "You are on a thin ledge.  Have a <look> "
	+ "around or <view street> to look below.\n");
	ITEM("roof", "The roof is a dozen feet higher past a chiseled band of "
	+ "reliefs and ornate overhangs topped with stone gargoyles at the "
	+ "corners.\n");

	CMD(({"window", "in window"}), "peek", "@@peek_in");
	CMD(({"down", "street"}), "view", "@@view_street");
	CMD(({"wall", "down"}), "climb", "@@climb_down");
	CMD(({"roof", "up"}), "climb", "@@climb_up");
	CMD("window", "open", "@@open_window");
	CMD("window", "enter", "@@enter_window");

	reset_palan_room();
}

string
window_status()
{
	if (winopen == 1 && winlock == 1)
		return "The window is closed and locked from the inside.";

	if (winopen == 1)
		return "The window is closed but unlocked.";

	return "The window is open.";
}

int
peek_in()
{
	/* This function returns an equivalent of 'look' from trusq_master
	 * most importantly without any supporting code from the
	 * target room.
	 */

	object *inv, *obs, *ppl, target;
    string desc;

	write(PEEKIN->long());
	target = find_object(PEEKIN);
	inv = all_inventory(target);
	obs = FILTER_SHOWN(FILTER_DEAD(inv));
	ppl = FILTER_LIVE(inv);

	if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
	write(one_of_list(({"Peeking in the window you see ",
						"Peeking within you see ",
						"Inside you see "}))
						+ desc + " on the floor.\n");

	if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
	write(one_of_list(({"Inside you spy ",
						"You make out ",
						"From within you spy "}))
						+ desc + " inside the suite.\n");
 
	return 1;
}

int
view_street()
{
	/* This function returns an equivalent of 'look' from trusq_master
	 * most importantly without any supporting code from the
	 * target room.
	 */

	object *inv, *obs, *ppl, target;
    string desc;

	write(VIEWSTREET->long());
	target = find_object(VIEWSTREET);
	inv = all_inventory(target);
	obs = FILTER_SHOWN(FILTER_DEAD(inv));
	ppl = FILTER_LIVE(inv);

	if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
	write(one_of_list(({"From above you can make out ",
						"You believe you spot ",
						"Your eyes come across "}))
						+ desc + " on the ground.\n");

	if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
	write(one_of_list(({"Down below you see ",
						"You notice below ",
						"Down below you spy "}))
						+ desc + " in the side street.\n");
 
	return 1;
}

int
climb_down()
{
	if (TP->query_skill(SS_CLIMB) < 31 + random(20))
	{
		int dmg = -100 - random(60);

		write("You try to climb down to the side street below but slip "
		+ "and fall!\nYou land with a \"Smack\" on the marble blocks "
		+ "below.\n");
		say(QCTNAME(TP) + " tries to climb down but slips and falls!  "
		+ QCTNAME(TP) + " lands with a \"Smack\" on the side street "
		+ "below.\n");
		TP->move_living("falling onto the street", SHIP + "alley201",
		1, 0);
		TP->heal_hp(dmg);

		if (TP->query_hp() <= 0)
			TP->do_die(E(TO));

		return 1;
	}

	write("Using the ledges and ornate marblework as handholds, you "
	+ "successfully climb down to the side street below.\n"); 
	TP->move_living("climbing down to the side street below",
	SHIP + "alley201", 1, 0);
	return 1;
}

int
climb_up()
{
	if (TP->query_skill(SS_CLIMB) < 28 + random(20))
	{
		int dmg = -110 - random(65);

		write("You try to climb up to the roof above but slip "
		+ "and fall!\nYou land with a \"Smack\" on the marble blocks "
		+ "below.\n");
		say(QCTNAME(TP) + " tries to climb further up but slips and falls!  "
		+ QCTNAME(TP) + " lands with a \"Smack\" on the side street "
		+ "below.\n");
		TP->move_living("falling onto the street", SHIP + "alley201",
		1, 0);
		TP->heal_hp(dmg);

		if (TP->query_hp() <= 0)
			TP->do_die(TO);

		return 1;
	}

	write("Using the band of chiseled reliefs and ornate marblework as "
	+ "handholds, you successfully climb up to the roof above.\n"); 
	TP->move_living("climbing up to the roof above", SHIP + "trusq_roof",
	1, 0);
	return 1;
}

int query_open()
{
	return winopen;
}

int query_lock()
{
	return winlock;
}

void win_open()
{
	say("The window is opened from inside.\n");
	winopen = 0;
}

void win_close()
{
	say("The window is closed from inside.\n");
	winopen = 1;
}

void win_unlock()
{
	say("The window is unlocked from inside.\n");
	winlock = 0;
}

void win_lock()
{
	say("The window is locked from inside.\n");
	winlock = 1;
}

int
open_window()
{
	NF("The window is already open.\n");
	if (winopen == 0)
		return 0;

	NF("The window is locked.\n");
	if (winlock == 1)
		return 0;

	if (winlock == 0)
	{
		write("You pull the iron-rimmed window open.\n");
		say(QCTNAME(TP) + " pulls the iron-rimmed window open.\n");
		tell_room(SHIP + "trusq_master", "Someone opens the east window "
		+ "from the outside.\n");
		winopen = 0;
		return 1;
	}
}

int
enter_window()
{
	NF("You must first open the window before you attempt to enter it.\n");
	if (winopen == 1)
		return 0;

	write("You slip in the window.\n");
	say(QCTNAME(TP) + " slips in the window.\n");
	TP->move_living("entering the window", SHIP + "trusq_master", 0, 0);
	return 1;
}

void
init()
{
  ::init();
  ADD("pick_winlock", "pick");
}

int
pick_winlock(string str)
{
	if (!str)
		return 0;

	if (!parse_command(str, ({}), "[the] 'lock' / 'window' [on] [the] [window]"))
		return 0;

	NF("The window is already unlocked.\n");
	if (winlock == 0)
		return 0;

	NF("You try to pick the lock on the window, but fail.\n");
	if (TP->query_skill(SS_OPEN_LOCK) <= 70 + random(15))
		return 0;

	write("You hear a tiny \"Click\" as your picks hit the right spot in the "
	+ "lock on the window.\n");
	say(QCTNAME(TP) + " fiddles with the lock on the window.\n");
	winlock = 0;
	return 1;
}

void
activate_gargoyle(object ob)
{
	if (present(ob) && !garg && gargoyle == 0)
	{
		garg = clone_object(SHIP + "living/trusq_gargoyle");
		garg->move_living("standing up from its hunched crouch atop the roof",
		(TO), 0, 0);
		gargoyle = 1;
	}
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        set_alarm(9.0, 0.0, "activate_gargoyle", ob);
}
