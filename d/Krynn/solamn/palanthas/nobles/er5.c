/* Mortis 07.2005
 * Make this a gate room with appropriate desc.
 */

#include "../local.h"
#include CLOCKH

inherit NOBLE_BASE;

string
query_to_jail()
{
  return "west";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  To the west is the inner city, its "
	+ "great white tower still visible above the buildings from this "
	+ "distance.  Through the buildings to your north you can just catch "
	+ "a glimpse of the Plaisir district.  The road leads east to the "
	+ "eastern gates.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Nobles' Way "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "A cool, misty breeze blows south from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Nobles' Way "
	+ "gleams in the midday sun as people walk about the intersection "
	+ "filling the streets with the gentle murmurings of their daily "
	+ "business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Nobles' Way "
	+ "catches the last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Nobles' Way amplifying the yellow glow of the "
	+ "street lamps.  A few people still make their way about at this hour."
	+ road;
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


void create_palan_room()
{
	object gate;

    SHORT("On Nobles' Way in the nobles district");
    LONG("@@get_time_desc@@");

	EXIT(NOBLE + "er4", "west", 0, 0);
	EXIT(NOBLE + "w06", "north", 0, 0);
	EXIT(NOBLE + "w07", "south", 0, 0);

    gate = clone_object(NOBLE_DOOR + "city_egate1.c");
	gate->move(TO);

	reset_palan_room();

}

