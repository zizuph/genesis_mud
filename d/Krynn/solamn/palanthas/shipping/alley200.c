/* Mortis 12.2005 
 * Alley dir south, ware dir north
 * Smells through shipping
 */

#include "../local.h"
#include CLOCKH

inherit SHIP_BASE;

string
query_to_jail()
{
  return "east";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  This is an alley between warehouses south of "
	+ "Palanthas Circle.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The clean marble of Palanthas Circle to the north "
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
    SHORT("South of Palanthas Circle in an alley in the east warehouse district");
    LONG("@@get_time_desc@@");

	EXIT(SHIP + "s09", "north", 0, 0);
	EXIT(SHIP + "s01", "south", 0, 0);

}
