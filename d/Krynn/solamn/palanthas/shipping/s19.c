/* Mortis 12.2005 
 *
 */

#include "../local.h"
#include CLOCKH

#define GULLY "/d/Krynn/solamn/pal_gully/rooms/"

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
	string road = "\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The clean marble of Landing street and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "The air is rich with the smells of wood, tar, and coffee borne "
	+ "on a cool, misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The well-worn marble of Landing street and its buildings "
	+ "gleams in the midday sun as people travel to and from the piers "
	+ "filling the street with the noisy murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Landing street catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as merchants, sailors, and dockhands make their way about the street."
	+ road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Landing street amplifying the yellow glow of the street lamps.  "
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
    SHORT("On Landing street");
    LONG("@@get_time_desc@@");

	EXIT(SHIP + "p03", "northeast", "@@pier_closed", 0);
	EXIT(SHIP + "s18", "east", 0, 0);
	EXIT(SHIP + "s20", "northwest", 0, 0);
	add_exit("xx", "west", "@@moor_closed", 0, 1);

}

int
moor_closed()
{
	write("The path from the dock to the moors has flooded. You'll " +
            "need to access that area from the western or northwestern " +
            "gate of the city of Palanthas.\n");
	return 1;
}

int
pier_closed()
{
	write("Pier available.\n");
	return 1;
}