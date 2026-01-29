/* Mortis 12.2005 
 * 
 * Alley wrapping behind merchant house Trusq.
 * The climb alley.
 *
 * Smells through shipping
 */

#include "../local.h"
#include CLOCKH
#include <ss_types.h>
#include <macros.h>

#define FOUND_TRUSQ_LEDGE_INFO		"_found_trusq_ledge_info"

inherit SHIP_BASE;

string
query_to_jail()
{
  return "northwest";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "A grand, four-story, marble estate sits off this side "
	+ "street to your west amidst long warehouses.  ";
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
create_palan_room()
{
    SHORT("In an alley between a four-story, marble estate and warehouses");
    LONG("@@get_time_desc@@");

	ITEM(({"estate", "four-story estate", "marble estate", "great estate"}),
	  "One of the largest buildings in the shipping quarter, a great, four-"
	+ "story, marble estate is to your west off this side street.  Each "
	+ "level has an ornate thin ledge, and across the top of the fourth "
	+ "floor is a band of chiseled reliefs.  Small, hunched gargoyles "
	+ "sit at the top corners of the estate along the roof.\n");
	ITEM(({"ledge", "ledges"}), "Thin, ornate marble ledges separate each of "
	+ "the four stories of the marble estate to your west."	+ "@@ledge_aware@@"
	+ "\n");

	EXIT(SHIP + "s03", "northwest", 0, 0);
	EXIT(SHIP + "alley202", "southwest", 0, 0);
}

string
ledge_aware()
{
	string seeledge;

	if (TP->query_skill(SS_AWARENESS) > 30 + random(6)) // Skill 110
	{	
		TP->add_prop(FOUND_TRUSQ_LEDGE_INFO, 1);
		seeledge = "  You notice the ledge below the fourth story is a "
		+ "little wider than the others.  Perhaps enough to perch on if "
		+ "you were able to climb up to it somehow.";
	}
	else
	{   seeledge = ""; }

	return seeledge;
}

void
init()
{
  ::init();
  ADD("climb_ledge", "climb");
}

int
climb_ledge(string str)
{
	if (TP->query_prop(FOUND_TRUSQ_LEDGE_INFO) == 1 )
	{
		NF("Climb up to what?\n");
		if (!str)
			return 0;

		if (!parse_command(str, ({}), "[up] [to] 'ledge' / 'wall'"))
			return 0;

		if (TP->query_skill(SS_CLIMB) < 30 + random(20))
		{
			write("You try to climb up to the ledge but slip and fall!\n"
			+ "You just can't seem to make it.\n");
			say(QCTNAME(TP) + " " + one_of_list(({"tries to climb up the "
			+ "wall of the great estate to the west but slips, falls, and "
			+ "lands on " + HIS(TP) + " butt in a heap on the street.",
			  "lays flat against the wall of the great estate to the west "
			+ "and humps it impotently in a failed attempt to scale it, "
			+ "or so you guess.",
			  "pounds " + HIS(TP) + " fists against the marble wall of the "
			+ "great estate to the west in a feeble attempt to climb it.",
			  "sighs as " + HE(TP) + " wishes " + HE(TP) + " were a better "
			+ "climber."})) + "\n");
			return 1;
		}

		write("Using the ledges and ornate marblework as handholds, you "
		+ "successfully climb to the slightly wider fourth story ledge "
		+ "of the great estate.\n"); 
		TP->move_living("climbing up to the fourth story ledge of the "
		+ "great estate to the west", SHIP + "trusq_ledge", 1, 0);
		return 1;
	}
	
	NF("What?\n");
	return 0;
}
