/* Mortis 12.2005
 * Alleys?  Jems smells?
 */

#include "../local.h"
#include CLOCKH

inherit MONKS_BASE;

string
query_to_jail()
{
  return "east";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  The circle curves east into its intersection with "
	+ "Aesthetics Row and west towards more shops and homes.  A side street "
	+ "winds south through tightly packed buildings and houses to Jem "
	+ "court.  To the northwest can be seen a group of shops and "
	+ "buildings.\n";
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
    SHORT("On Palanthas Circle west of Aesthetics Row");
    LONG("@@get_time_desc@@");

	ITEM(({"court", "jems court", "jems", "housing district", "houses"}),
		"A large housing district unfolds before you to the southwest.  "
	+ "They are densely arranged around Jems court, a long oval of a "
	+ "street between Aesthetics Row and Vingaard road.  Though almost "
	+ "entirely well-worn marble, portions of the street have been "
	+ "replaced with beige, clay bricks.  The houses are smaller than "
	+ "most in the city.  Several are two-stories, but a good deal are "
	+ "only one.  Marble isn't uncommon here, but it's as prevalent as "
	+ "brick and wood.  Street lamps are not arranged so orderly in this "
	+ "part of the city either.\n");

	EXIT(MONKS + "sr3", "east", 0, 0);
	EXIT(MONKS + "a15", "south", 0, 0);
	EXIT(MONKS + "a08", "west", 0, 0);

}