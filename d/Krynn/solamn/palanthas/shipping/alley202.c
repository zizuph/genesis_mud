/* Mortis 12.2005 
 * 
 * Alley wrapping behind merchant house Trusq.
 * The backdoor alley.
 *
 * Smells through shipping
 */

#include "../local.h"
#include CLOCKH

inherit SHIP_BASE;

string
query_to_jail()
{
  return "northeast";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "A grand, four-story, marble estate sits off this side "
	+ "street to your north amidst long warehouses.  ";
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
	object backdoor;

    SHORT("In an alley between a four-story, marble estate and warehouses");
    LONG("@@get_time_desc@@");
	ITEM(({"estate", "four-story estate", "marble estate", "great estate"}),
	  "One of the largest buildings in the shipping quarter, a great, four-"
	+ "story, marble estate is to your west off this side street.  Each "
	+ "level has an ornate thin ledge, and across the top of the fourth "
	+ "floor is a band of chiseled reliefs.  Small, hunched gargoyles "
	+ "sit at the top corners of the estate along the roof.  A servants "
	+ "door leads into the estate from here.\n");
	ITEM(({"ledge", "ledges"}), "Thin, ornate marble ledges separate each of "
	+ "the four stories of the marble estate to your west.\n");

	EXIT(SHIP + "alley201", "northeast", 0, 0);

	backdoor = clone_object(SHIP + "doors/trusq_backdoor1");
	backdoor->move(TO);
}
