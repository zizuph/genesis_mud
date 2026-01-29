/* Mortis 12.2005
 * Jems smells?
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
	string road = "  The circle curves west towards an intersection with "
	+ "Vingaard road and east towards Aesthetics Row.  An alley winds "
	+ "south through tightly packed buildings and houses to Jem court  "
	+ "To the northwest can be seen a group of shops and buildings while "
	+ "to the north is Scholis Court.\n";
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
	+ "as citizens make their way about the street, and maroon robed "
	+ "aesthetics head toward Scholis court." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Palanthas Circle amplifying the yellow glow of the street lamps.  "
	+ "Maroon robed aesthetics can still be seen making their way towards "
	+ "Scholis court at this hour." + road;
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
	+ "part of the city either.  In Scholis Court to the north can be "
	+ "seen a large estate.\n");
	ITEM("court", "Which court?  Scholis court in the north?  Or Jems "
	+ "court to the south?\n");
	ITEM(({"scholis court", "north court"}), "The worn marble of Scholis "
	+ "court unfolds before you to the north around which several buildings "
	+ "are situated.\n");

	EXIT(MONKS + "a01", "north", 0, 0);
	EXIT(MONKS + "a07", "east", 0, 0);
	EXIT(MONKS + "a13", "south", 0, 0);
	EXIT(MONKS + "a09", "west", 0, 0);

}