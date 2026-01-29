/* Mortis 11.2005
 * Housing smells.
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

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
	string road = "  Old Circle runs east to the southern city gates "
	+ "on Aesthetics row and west along the curve of the city wall "
	+ "into along Jems court which opens up before you down an alley "
	+ "to the north.  Many buildings and homes stretch out to the north "
	+ "on Jems court, a densely packed housing district.  The city wall "
	+ "towers above you to the south.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The worn marble of Old Circle and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and " + one_of_list(({"tea", "coffee"})) + " borne on a cool, "
	+ "misty breeze." + road;
	break;

    case TOD_DAY:
	desc += "The worn marble of Old Circle and its buildings lights up "
	+ "in the midday sun as people and maroon robed aesthetics travel "
	+ "throughout the Aesthetics quarter filling the street with the "
	+ "murmurings of their daily business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The worn marble of Old Circle catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as travellers and maroon robed aesthetics make their way about the "
	+ "street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Old Circle amplifying the yellow glow of the street lamps.  "
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
    SHORT("On Old Circle south of Jems court in the aesthetics quarter");
    LONG("@@get_time_desc@@");

	ITEM(({"gate", "gates", "southern gate", "south gates",
		   "s gate", "s gates", "south gate", "south gates"}),
	  "A large metal gate.\n");
	ITEM(({"wall", "city wall", "great wall"}), "The city wall of "
	+ "Palanthas towers high above to the south.  It is faced with "
	+ "large block panels of polished, translucent marble, but atop "
	+ "its crenallated defenses you spot cracks in the dark grey rock "
	+ "which comprises its core.  The wall is in poor shape.\n");
	ITEM(({"court", "jems court", "jems", "housing district", "houses"}),
		"A large housing district unfolds before you to the north.  "
	+ "They are densely arranged around Jems court, a long oval of a "
	+ "street between Aesthetics Row and Vingaard road.  Though almost "
	+ "entirely well-worn marble, portions of the street have been "
	+ "replaced with beige, clay bricks.  The houses are smaller than "
	+ "most in the city.  Several are two-stories, but a good deal are "
	+ "only one.  Marble isn't uncommon here, but it's as prevalent as "
	+ "brick and wood.  Street lamps are not arranged so orderly in this "
	+ "part of the city either.\n");

	EXIT(MONKS + "a19", "north", 0, 0);
	EXIT(MONKS + "w16", "east", 0, 0);
	EXIT(MONKS + "w18", "west", 0, 0);

}
