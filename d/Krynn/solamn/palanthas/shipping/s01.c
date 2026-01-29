/* Mortis 12.2005 
 * Alley north dir
 * Smells through shipping
 */

#include "../local.h"
#include CLOCKH

inherit SHIP_BASE;

string
query_to_jail()
{
  return "southeast";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  An alley cuts southeast between the buildings to  "
	+ "Scholar's Walk and another north through the warehouse district to "
	+ "the north and west.  The great white tower of the palace far to the "
	+ "southwest is still visible above the buildings from this distance.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The clean marble of Lotelis Avenue and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains.  The air is rich with the smells of wood, tar, and coffee "
	+ "borne on a cool, misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The well-worn marble of Lotelis Avenue and its buildings "
	+ "gleams in the midday sun as people travel to and from the piers "
	+ "filling the street with the noisy murmurings of their daily "
	+ "business.  A cool, salty breeze blows south off the bay." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Lotelis Avenue catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as travellers, sailors, and dockhands make their way about the "
	+ "street.  A misty, salty breeze blows south off the bay." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Lotelis Avenue amplifying the yellow glow of the street lamps.  "
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
    SHORT("On Lotelis Avenue northwest of Scholar's Walk");
    LONG("@@get_time_desc@@");

	add_alley("n", "north", SHIP + "alley200");

	EXIT(SHIP + "s10", "northeast", 0, 0);
	EXIT(NOBLE + "ner3", "southeast", 0, 0);
	EXIT(SHIP + "s02", "west", 0, 0);

}
