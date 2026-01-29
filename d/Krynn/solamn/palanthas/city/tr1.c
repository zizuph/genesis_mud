/* Mortis 07.2005 
 * Alleys nw to vantage point atop building next to E. great merchant house.
 */

#include "../local.h"
#include CLOCKH

inherit CITY_BASE;

string
query_to_jail()
{
  return "east";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  To the north begins Trade road leading to the shipping "
	+ "district and the bay.  A grove of well cultivated trees grows just "
	+ "south of here the other side of which must be the palatial palace for "
	+ "its tall, white tower is visible even from here.  The street curves "
	+ "west and east from here, and to the northeast leads Lotelis avenue.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Inner Circle street and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "The air is rich with the smells of morning cooking and coffee borne "
	+ "on a cool, misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Inner Circle street and its buildings "
	+ "gleams in the midday sun as people travel to and from the plaza "
	+ "filling the street with the noisy murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Inner Circle street catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Inner Circle street amplifying the yellow glow of the street lamps.  "
	+ "A few people still make their way about at this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void
create_palan_room()
{
    SHORT("On a curving stretch of Inner Circle street near the livery");
    LONG("@@get_time_desc@@");

	ITEM(({"tree", "trees", "grove"}), "A great grove of well cultivated "
	+ "oaks, birches, poplars, and cedar grows to the south, their rich, "
	+ "green leaves rustle softly in the breeze off the bay.  It is "
	+ "forbidden by law to enter this palatial wood unbidden.\n");

	EXIT(SHIP + "tr2", "north", 0, 0);
	EXIT(SHIP + "s02", "northeast", 0, 0);
	EXIT(ROOM + "ic2", "east", 0, 0);
	EXIT(ROOM + "ic9", "west", 0, 0);

}