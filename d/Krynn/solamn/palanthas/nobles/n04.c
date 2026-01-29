/* Mortis 11.2005
 * Add command to look in window of Harnoncourt's and
 * see who's inside plus displays, etc.
 *
 * Added jeweler guard to block kender from entering
 * conventionally in 11.2005.  Finally had time to
 * implement now.
 *
 * Mortis 10.2006
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit NOBLE_BASE;

object jguard;

string
query_to_jail()
{
	return "south";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  To the northwest is the Harnoncourt Jewelers.  "
	+ "Itzus Street runs west to Livery Street, and Palanthas Circle "
	+ "curves north towards Scholar's Walk and south to Nobles' Way.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Palanthas Circle and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "A cool, misty breeze blows south from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Palanthas Circle and its buildings "
	+ "gleams in the midday sun as people walk about the intersection "
	+ "filling the streets with the gentle murmurings of their daily "
	+ "business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Palanthas Circle catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Palanthas Circle amplifying the yellow glow of the street lamps.  "
	+ "A few people still make their way about at this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void
reset_palan_room()
{
	if (!jguard)
	{
		jguard = clone_object(NOBLE + "living/jguard");
		jguard->move(TO);
		jguard->command("emote stands guard by the door of the jeweler's "
		+ "shop to the northwest.");
	}
}

void
create_palan_room()
{
    SHORT("On Palanthas Circle southeast of the Harnoncourt Jewelers");
    LONG("@@get_time_desc@@");

	ITEM(({"harnoncourt", "jeweler", "jewelers", "harnoncourt jewelers"}),
	  "The Harnoncourt Jewelers is a three-story marble building facing "
	+ "you to your northwest.  Its marble is pristine and clean.  A "
	+ "great window allows you to look in and see some of the displays "
	+ "within.  Painted across it in calligraphied letters is, "
	+ "\"Harnoncourt Jewelers\", above a four-pointed white jewel.\n");
	ITEM(({"estate", "estates", "noble estate", "noble estates"}), "There "
	+ "are a pair of estates to your southwest.  Their architecture is "
	+ "typical of the old buildings of marble rising several stories "
	+ "here in the noble district.\n");
	ITEM("window", "Bright sparkles gleam from just the other side of the "
	+ "window.\n");

	EXIT(NOBLE + "jeweler", "northwest", "@@no_kender", 0);
	EXIT(NOBLE + "n05", "north", 0, 0);
	EXIT(NOBLE + "n03", "west", 0, 0);
	EXIT(NOBLE + "n08", "south", 0, 0);

	reset_palan_room();
}

int
no_kender()
{
	if (TP->query_race_name() == "hobbit" || TP->query_race_name() == "kender")
	{
		if (jguard)
		{
			write("The towering guard peers down at you and says:  Not so fast "
			+ "kenderling!  The Harnoncourts bear you no ill will, but your kind "
			+ "is not tolerated inside.  Don't even look in the window.\n");
			say(QCTNAME(TP) + " tries to stroll northwest into Harnoncourt "
			+ "Jewelers but is barred entry by the door guard with whom "
			+ HE(TP) + " exchanges words.\n");
			return 1;
		}
		
		write("You stroll happily into the jewel shop.\n");
		return 0;
	}

	else if (jguard)
	{
		write("The guard by the door nods her head respectfully as you walk "
		+ "inside.\n");
		say(QCTNAME(TP) + " walks northwest into Harnoncourt Jewelers as the "
		+ "guard by the door nods her head respectfully.\n");
		return 0;
	}
	
	return 0;
}