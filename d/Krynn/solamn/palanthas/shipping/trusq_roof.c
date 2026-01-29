/* Mortis 02.2005 
 * 
 * Roof of merchant house Trusq in Palanthas
 *
 * Smells through shipping
 * CHECK move_living 1,0's to make party moves when appropriate.
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <ss_types.h>
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>

#define VIEWSTREET			(SHIP + "alley201")
#define VIEWENT				(SHIP + "s03")
#define VIEWWEST			(SHIP + "topofotherestate")
#define VIEWSOUTH			(SHIP + "alley202")
#define CHIMNEY				(SHIP + "trusq_chimney_roof")

inherit SHIP_BASE;

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "The roof of this great estate rises perhaps three score "
	+ "feet above the streets below with sloping curves and a gusting breeze "
	+ "constantly reminding you of your height.  It offers a sweeping view "
	+ "of the shipping quarter, the inner city, and the bay.  A large, wide "
	+ "chimney rises from the roof, and large-eyed, hunching gargoyles perch "
	+ "on the corners.  ";
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
}

void
create_palan_room()
{
    SHORT("On the roof of a great, marble estate with a sweeping view");
    LONG("@@get_time_desc@@");

	ITEM(({"view", "sweeping view"}), "You are on a thin ledge.  Have a "
	+ "<look> around or <view street> to look below at the east side "
	+ "street, <view entrance> to look down at the gravel path leading "
	+ "south into the estate, <view west> to see the estate west of here, "
	+ "or <view south> to look below at the south of the estate.\n");
	ITEM("roof", "The roof is covered in dark, tar sealed shingles with a "
	+ "large, wide chimney rising from it.  Its ornate, marblework overhangs "
	+ "are topped with stone gargoyles at the corners.  Over its edge, you "
	+ "can view the street below.  You also see a thin ledge below you "
	+ "might climb down to.\n");
	ITEM(({"ledge", "thin ledge"}), "Over the east edge of the roof, below a "
	+ "band of chiseled reliefs, is a thin ledge.  You could try climbing "
	+ "down to it if you don't mind risking falling onto the unforgiving "
	+ "marble blocks of the side street below\n");
	ITEM("chimney", "A large, wide, brick chimney rises from the roof.  It "
	+ "is covered with a dark shingled roof allowing for smoke to escape "
	+ "while keeping the rain out.  Be careful you don't fall in!\n");

	CMD(({"down", "street"}), "view", "@@view_street");
	CMD(({"north", "entrance"}), "view", "@@view_ent");
	CMD(({"west", "estate"}), "view", "@@view_west");
	CMD(({"south", "back"}), "view", "@@view_south");

	reset_palan_room();
	CHIMNEY->teleledningsanka();
}

int
view_street()
{
	/* This function returns an equivalent of 'look' from alley201
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
view_ent()
{
	/* This function returns an equivalent of 'look' from s03
	 * most importantly without any supporting code from the
	 * target room.
	 */

	object *inv, *obs, *ppl, target;
    string desc;

	write(VIEWENT->long());
	target = find_object(VIEWENT);
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
						+ desc + " on Bulwark Round.\n");
 
	return 1;
}

int
view_west()
{
	/* This function returns an equivalent of 'look' from neighbor_?
	 * most importantly without any supporting code from the
	 * target room.
	 

	object *inv, *obs, *ppl, target;
    string desc;

	write(VIEWWEST->long());
	target = find_object(VIEWWEST);
	inv = all_inventory(target);
	obs = FILTER_SHOWN(FILTER_DEAD(inv));
	ppl = FILTER_LIVE(inv);

	if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
	write(one_of_list(({"Across the side street you can make out ",
						"You believe you spot ",
						"Your eyes come across "}))
						+ desc + " on the roof.\n");

	if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
	write(one_of_list(({"To the west you see ",
						"You notice ",
						"High to the west you spy "}))
						+ desc + " on top of the great estate to your "
						+ "west.\n");
 
	return 1;*/
	write("You can't make out the other rooftop yet.\n");
	return 1;
}

int
view_south()
{
	/* This function returns an equivalent of 'look' from alley202
	 * most importantly without any supporting code from the
	 * target room.
	 */

	object *inv, *obs, *ppl, target;
    string desc;

	write(VIEWSOUTH->long());
	target = find_object(VIEWSOUTH);
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
						+ desc + " in the back side street.\n");
 
	return 1;
}

int
climb_down(string str)
{
	NF("Climb?  Where?\n");
	if (!str)
		return 0;

	NF("Climb?  Where?  Down to the ledge?\n");
	if (!parse_command(str, ({}), "'ledge' / 'down' [to] [the] [ledge]"))
		return 0;

	if (TP->query_skill(SS_CLIMB) < 31 + random(20))
	{
		int dmg = -120 - random(66);

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
			TP->do_die(TO);

		return 1;
	}

	write("Using the ledges and ornate marblework as handholds, you "
	+ "successfully climb down to the thin ledge below.\n"); 
	TP->move_living("climbing down to the thin ledge below",
	SHIP + "trusq_ledge", 1, 0);
	return 1;
}

int
fall(string str)
{
	NF("Oh, you would like to fall?  Ok, where?\n");
	if (!str)
		return 0;

	NF("Fall where?  Into the chimney???\n");
	if (!parse_command(str, ({}), "[in] [into] [the] 'chimney'"))
		return 0;

	write("What, are you mad?!?  Just crawl into it if you're so eager to "
	+ "get inside the chimney.\n");
	return 1;
}

int
crawl(string str)
{
	string vrb = query_verb();
	string race = QRACE(TP);
//	object ttools = "MAKE UP THIEVES TOOLS";
//	object cbar = "crowbar";

	NF("What?\n");
	if (!str)
		return 0;

	NF(C(vrb) + " into what?  The chimney?\n");
	if (!parse_command(str, ({}), "[in] [into] [the] 'chimney'"))
		return 0;

	if (parse_command(race, ({}), "'hobbit' / 'kender' / 'gnome'"))
	{
		write("You shimmy under the roof of the chimney and slip inside.\n");
		TP->move_living("shimmies under the roof of the chimney and slips "
		+ "inside", CHIMNEY, 1, 0);
		return 1;
	}

	NF("You're too big to fit under the roof of the chimney!  Maybe if you "
	+ "had a set of tools that included a crowbar, you could work your way "
	+ "in.\n");
	if (!present("ttools", TP) && !present("crowbar", TP))
		return 0;

	write("Using a crowbar, you pry the roof of the chimney up high enough "
	+ "to slip inside.\n");
	TP->move_living("uses a crowbar to pry the roof of the chimney up and "
	+ "slips inside", CHIMNEY, 1, 0);
	return 1;
}

void
init()
{
	::init();
	ADA("fall");
	ADA("crawl");
	ADD("crawl", "enter");
	ADD("climb_down", "climb");
}
