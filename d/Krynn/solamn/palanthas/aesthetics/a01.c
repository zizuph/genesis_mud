/*
 * Jems smells?
 *
 * Mortis 12.2005
 *
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
	string road = "  The court unfolds into an oval here between Vingaard "
	+ "road in the northwest and Palanthas Circle to the south.  An "
	+ "estate is situated to the north, and to the southwest is a two-story, "
	+ "round, marble building above the doorway of which have been chiseled "
	+ "the words \"Scholar's Den\".  A small, beige brick, government "
	+ "office building is to the southeast and south through tightly packed "
	+ "buildings and houses you can just make out Jem court.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The worn marble of Scholis court and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and " + one_of_list(({"tea", "coffee"})) + " borne on a cool, "
	+ "misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The worn marble of Scholis court and its buildings "
	+ "appears mostly white in the midday sun as people travel along the way "
	+ "filling the street with the murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Scholis court catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as citizens make their way about the street, and maroon robed "
	+ "aesthetics make their way about Scholis court." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Scholis court amplifying the yellow glow of the street lamps.  "
	+ "Maroon robed aesthetics can still be seen making their way about "
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
    SHORT("In Scholis court southeast of Vingaard road");
    LONG("@@get_time_desc@@");

	ITEM(({"south court", "jems court", "jems", "housing district", "houses"}),
		"A large housing district unfolds down the street to the south.  "
	+ "They are densely arranged arround Jems court, a long oval of a "
	+ "street between Aesthetics Row and Vingaard road.  Though almost "
	+ "entirely well-worn marble, portions of the street have been "
	+ "replaced with beige, clay bricks.  The houses are smaller than "
	+ "most in the city.  Several are two-stories, but a good deal are "
	+ "only one.  Marble isn't uncommon here, but it's as prevalent as "
	+ "brick and wood.  Street lamps are not arranged so orderly in this "
	+ "part of the city either.\n");
	ITEM("court", "Which court?  Scholis court here?  Or Jems "
	+ "court to the south?\n");
	ITEM(({"scholis court", "north court"}), "The worn marble of Scholis "
	+ "court widens here into an oval around which several buildings "
	+ "are situated.\n");
	ITEM("estate", "A good sized, two-story estate of marble is right off "
	+ "the court to the north.  A shield shaped, red banner hangs below its "
	+ "roof from a polished brass rod.\n");
	ITEM(({"banner", "red banner", "shield shaped banner",
		   "shield shaped red banner"}), "The shield shaped, red banner "
	+ "hangs from a shiny, brass rod below the roof of the estate to the "
	+ "north.  It bears a crest of three equally spaced golden balls above "
	+ "two rampant lions facing each other.\n");
	ITEM(({"rod", "brass rod", "shiny rod", "polished rod"}), "Bolted "
	+ "parallel to the wall of the north estate below its roof, the rod "
	+ "protrudes a few inches.  From it hangs a shield shaped, red "
	+ "banner.\n");
	ITEM(({"den", "scholar's den", "scholars den"}), "A round, marble "
	+ "building is set a ways off Scholis court to the southwest.  From "
	+ "its open doorway maroon-robed aesthetics come and go as well as the "
	+ "occasional merchant or traveller.\n");
	ITEM(({"office", "brick office", "government office", "office building"}),
	  "The beige bricks of this small office building have accumulated dirt "
	+ "and soot in the mortar cracks between them as well as occasional "
	+ "dots of grout.  Official government buildings of Palanthas are "
	+ "usually kept in excellent repair.  The building's backdoor is to "
	+ "your southeast.\n");

	EXIT(MONKS + "hausx", "north", "@@place_closed", 0);
	EXIT(MONKS + "pages", "southeast", 0, 0);
	EXIT(MONKS + "a08", "south", 0, 0);
	EXIT(MONKS + "den", "southwest", "@@place_closed", 0);
	EXIT(MONKS + "swr3", "northwest", 0, 0);

}

int
place_closed()
{
	write("This will open in the future.\n");
	return 1;
}