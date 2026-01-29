/* Mortis 11.2005
 * Alleys?  Park smells?~
 */

#include "../local.h"
#include CLOCKH

inherit MONKS_BASE;

string
query_to_jail()
{
  return "west";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Large two and three-story homes line this court in "
	+ "the northern housing district of the quarter.  A side street leads "
	+ "west to an intersection with Aesthetics Row.  Through a few buildings "
	+ "and homes to the east you can see a three-story, marble estate.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The translucent marble of the court and its homes and buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and " + one_of_list(({"tea", "coffee"})) + " borne on a cool, "
	+ "misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The translucent marble of the court and its homes and buildings "
	+ "appears mostly white in the midday sun as people travel along the way "
	+ "filling the street with the murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of the court catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as citizens and maroon robed aesthetics make their way about the "
	+ "street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of the court amplifying the yellow glow of the street lamps.  "
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

	ITEM("estate", "A three-story, marble estate can be seen through a few "
	+ "buildings to the east.  It is not adorned with fancy marble or "
	+ "architectural features nor does it boast a great deal of "
	+ "gargoyles.\n");
	ITEM("housing district", "This is a fair looking housing section of the "
	+ "Aesthetics quarter not far from the Nobles quarter.\n");
	ITEM(({"home", "homes"}), "Two and three-story, marble homes of fair "
	+ "size for this quarter line the cul-de-sac here somewhat spaced "
	+ "apart.\n");

	EXIT(MONKS + "sr2", "west", 0, 0);

}