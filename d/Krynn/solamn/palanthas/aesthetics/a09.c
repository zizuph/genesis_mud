/* Mortis 12.2005
 * Jems smells?
 */

#include "../local.h"
#include CLOCKH

inherit MONKS_BASE;

string
query_to_jail()
{
  return "northwest";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  The circle curves northwest towards its intersection "
	+ "with Vingaard road and east along Jems court to the south.  To "
	+ "the northeast can be seen a group of shops and buildings.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The worn marble of Palanthas Circle and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and " + one_of_list(({"tea", "coffee"})) + " borne on a cool, "
	+ "misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The worn marble of Palanthas Circle and its buildings "
	+ "appears mostly white in the midday sun as people travel along the way "
	+ "filling the street with the murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The worn marble of Palanthas Circle catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as citizens and maroon robed aesthetics make their way about the "
	+ "street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Palanthas Circle amplifying the yellow glow of the street lamps.  "
	+ "Maroon robed aesthetics can still be seen making their way towards the "
	+ "east at this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void
create_palan_room()
{
    SHORT("On Palanthas Circle between Scholis and Jems courts");
    LONG("@@get_time_desc@@");

	ITEM(({"south court", "jems court", "jems", "housing district", "houses"}),
		"A large housing district unfolds before you to the southwest.  "
	+ "They are densely arranged around Jems court, a long oval of a "
	+ "street between Aesthetics Row and Vingaard road.  Though almost "
	+ "entirely well-worn marble, portions of the street have been "
	+ "replaced with beige, clay bricks.  The houses are smaller than "
	+ "most in the city.  Several are two-stories, but a good deal are "
	+ "only one.  Marble isn't uncommon here, but it's as prevalent as "
	+ "brick and wood.  Street lamps are not arranged so orderly in this "
	+ "part of the city either.  In Scholis Court to the northeast can be "
	+ "seen a large estate.\n");
	ITEM("court", "Which court?  Scholis court in the northeast?  Or Jems "
	+ "court to the south?\n");
	ITEM(({"scholis court", "northeast court"}), "The worn marble of Scholis "
	+ "court unfolds before you to the north around which several buildings "
	+ "are situated.\n");

	EXIT(MONKS + "swr5", "northwest", 0, 0);
	EXIT(MONKS + "a08", "east", 0, 0);

}