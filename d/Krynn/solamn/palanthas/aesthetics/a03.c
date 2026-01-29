/* Mortis 11.2005
 * Alleys?  Park smells?~
 */

#include "../local.h"
#include CLOCKH

inherit MONKS_BASE;

string
query_to_jail()
{
  return "south";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  A side street leads west to a three-story, marble "
	+ "estate in this housing district.  Through a few buildings and "
	+ "homes to the northeast you can see Knight's High Road.  Naerth "
	+ "street leads south where it T's into Palanthas Circle.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The worn marble of Naerth street and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and " + one_of_list(({"tea", "coffee"})) + " borne on a cool, "
	+ "misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The worn marble of Naerth street and its buildings "
	+ "appears mostly white in the midday sun as people travel along the way "
	+ "filling the street with the murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The worn marble of Naerth street catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as citizens and maroon robed aesthetics make their way about the "
	+ "street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Naerth street amplifying the yellow glow of the street lamps.  "
	+ "A few people  still make their way about at this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void
create_palan_room()
{
    SHORT("On Naerth street southwest of Knight's High Road");
    LONG("@@get_time_desc@@");

	ITEM("estate", "A three-story, marble estate sits at the end of a side "
	+ "street to the west.  It is not adorned with fancy marble or "
	+ "architectural features nor does it boast a great deal of "
	+ "gargoyles.\n");
	ITEM("housing district", "This is a fair looking housing section of the "
	+ "Aesthetics quarter not far from the Nobles quarter.\n");

	EXIT(MONKS + "a05", "south", 0, 0);
	EXIT(MONKS + "hausx", "west", "@@place_closed", 0);

}

int
place_closed()
{
	write("This will open in the future.\n");
	return 1;
}