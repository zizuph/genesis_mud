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
	string road = "  The road leads west into the heart of the Aesthetics "
	+ "quarter and curves east towards its intersection with Knight's "
	+ "High road.  Naerth street leads north towards an estate, and "
	+ "through a few buildings to your southeast you can see the "
	+ "top of a fountain spraying water above the tops of bushes.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The translucent marble of Palanthas Circle and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and " + one_of_list(({"tea", "coffee"})) + " borne on a cool, "
	+ "misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The translucent marble of Palanthas Circle and its buildings "
	+ "appears mostly white in the midday sun as people travel along the way "
	+ "filling the street with the murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Palanthas Circle catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as citizens and maroon robed aesthetics make their way about the "
	+ "street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Palanthas Circle amplifying the yellow glow of the street lamps.  "
	+ "A few people and maroon robed aesthetics still make their way about at "
	+ "this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void
create_palan_room()
{
    SHORT("On Palanthas Circle southwest of Knight's High Road");
    LONG("@@get_time_desc@@");

	ITEM("fountain", "To the southeast through a few buildings you see the "
	+ "top of a water spraying fountain above low, green bushes.\n");
	ITEM(({"bush", "bushes"}), "Low, green bushes surround a grassy area "
	+ "with a fountain to your southeast.\n");

	EXIT(MONKS + "a03", "north", 0, 0);
	EXIT(MONKS + "a04", "east", 0, 0);
	EXIT(MONKS + "a06", "west", 0, 0);

}