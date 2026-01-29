/* Mortis 12.2005 
 * Smells through shipping
 * npc idea: gravel raker
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
	string road = "  The warehouses of the professional warehouse district "
	+ "are all you can make out east along Palanthas Circle.  Bulwark Round "
	+ "curves northeast and southeast from this intersection.  A short, "
	+ "white marble tower rises to the northwest above the surrounding "
	+ "buildings, and Horizon road is to the southwest.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The clean marble of Palanthas Circle and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains.  The air is rich with the smells of wood, tar, and coffee "
	+ "borne on a cool, misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The well-worn marble of Palanthas Circle and its buildings "
	+ "gleams in the midday sun as people travel to and from the piers "
	+ "filling the street with the noisy murmurings of their daily "
	+ "business.  A cool, salty breeze blows south off the bay." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Palanthas Circle catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as travellers, sailors, and dockhands make their way about the "
	+ "street.  A misty, salty breeze blows south off the bay." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Palanthas Circle amplifying the yellow glow of the street lamps.  "
	+ "A few dock workers still make their way about at this hour.  "
	+ "A cool, salty breeze blows south off the bay." + road;
    break;

    default:
	break;
    }
    return desc;
}

void
create_palan_room()
{
    SHORT("On Bulwark Round south of the warehouses of Palanthas Circle");
    LONG("@@get_time_desc@@");

	ITEM(({"estate", "four-story estate", "marble estate", "great estate"}),
	  "One of the largest buildings in the shipping quarter, a great, four-"
	+ "story, marble estate is southeast.  Its ancient, copper roof has "
	+ "weathered green ages ago.\n");
	ITEM(({"roof", "ancient copper roof", "ancient roof", "copper roof"}),
	  "The roof of the great estate to the south has been done in copper "
	+ "that long ago weathered to green.  Its details are too small to "
	+ "make out at this distance..\n");
	ITEM(({"short tower", "short marble tower", "marble tower"}), "A tower "
	+ "of translucent, white marble rises at least forty feet into the air "
	+ "to the northwest, higher than all of the buildings in this section of "
	+ "the shipping quarter.  Chiseled into the marble above its entryway "
	+ "is, \"Palanthas Guard Tower\".\n");

	EXIT(SHIP + "s14", "northeast", 0, 0);
	EXIT(SHIP + "s06", "east", 0, 0);
	EXIT(SHIP + "s04", "southeast", 0, 0);
	EXIT(MERCH + "nwr5", "southwest", 0, 0);
	EXIT(SHIP + "shipping_tower1", "northwest", 0, 0);

}
