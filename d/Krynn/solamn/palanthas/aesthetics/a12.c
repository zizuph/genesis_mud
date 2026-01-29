/* 
 * Mortis 11.2005
 * 
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
	string road = "  Jems court curves in an oval east and west from "
	+ "here.  Row upon row of tightly packed houses are all you can see in "
	+ "this housing district.  The street is dusty.  The street cleaners "
	+ "must not come here.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The worn marble of Jems court and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and " + one_of_list(({"tea", "coffee"})) + " borne on a cool, "
	+ "misty breeze." + road;
	break;

    case TOD_DAY:
	desc += "The worn, dusty marble of Jems court and its buildings lights "
	+ "up in the midday sun as people and maroon robed aesthetics travel "
	+ "throughout the Aesthetics quarter filling the street with the "
	+ "murmurings of their daily business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The worn, dusty marble of Jems court catches the "
	+ "last rays of the sun appearing to glow in a dull fashion "
	+ "as travellers and the occasional maroon robed aesthetics make their "
	+ "way about the court." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Jems court amplifying the yellow glow of the street lamps.  "
	+ "A few poorly dressed people still make their way about at "
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
    SHORT("On Jems court in the southwest housing district of the "
	+ "aesthetics quarter");
    LONG("@@get_time_desc@@");

	ITEM(({"court", "jems court", "jems", "housing district", "houses"}),
		"A large housing district unfolds before you to the east and "
	+ "west.  The houses are densely arranged around Jems court, a long "
	+ "oval of a street.  Though mostly well-worn marble, portions of the "
	+ "street have been replaced with beige, clay bricks while some blocks "
	+ "are missing entirely and are potholes of dirt and muck.  The houses "
	+ "are smaller than most in the city.  Several are two-stories, but a "
	+ "good deal are only one.  Marble isn't uncommon here, but it's no "
	+ "more prevalent than brick and wood.  Street lamps are not arranged "
	+ "so orderly in this part of the city either.\n");
	ITEM("house", "Any house in particular?\n");
	ITEM(({"south house", "southern house"}), "A small, two-story house "
	+ "is to your south.  It is built from tan bricks with old, gray "
	+ "mortar and an aging, wood shingled roof.  Above its door sways a "
	+ "dark, wooden sign with the picture of a lantern in a coil of rope "
	+ "carved on it.\n");
	ITEM("sign", "It is a dark, wooden sign with the picture of a lantern "
	+ "in a coil of rope carved on it.  It hangs above the doorway of the "
	+ "house to the south.\n");
	ITEM(({"s alley", "south alley"}), "An alley leads south around the "
	+ "right of the house to your south towards the center of Jems court.\n");

	add_smell("vampire", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and the uniquely pungent smell of a flammable "
	+ "fungus from the house to the south.  The scent of blood is weak here.");
	add_smell("morgul", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and the uniquely pungent smell of a flammable "
	+ "fungus from the house to the south.");
	add_smell("human", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and a unique, pungent smell from the house to "
	+ "the south.");
	add_smell("elf", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and the uniquely pungent smell of a flammable "
	+ "fungus from the house to the south.");
	add_smell("goblin", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and a uniquely pungent fiery smell that your "
	+ "goblin nostrils can't get enough of from the house to the south.");
	add_smell("dwarf", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and the uniquely pungent smell of a flammable "
	+ "fungus from the house to the south.");
	add_smell("hobbit", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and a pungent smell that makes your nose "
	+ "itch coming from the house to the south.");
	add_smell("gnome", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and the distinct, pungent smell of a flammable "
	+ "fungus that sets off alarm bells in your head coming from the house "
	+ "to the south.");
	add_smell("minotaur", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and a unique, pungent smell from the house to "
	+ "the south.");
	add_smell("halfhuman", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and a unique, pungent smell from the house to "
	+ "the south.");
	add_smell("halfelf", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and a unique, pungent smell from the house to "
	+ "the south.");
	add_smell("orc", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and a uniquely pungent fiery smell that your "
	+ "orcish nostrils can't get enough of from the house to the south.");
	add_smell("hobgoblin", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and the uniquely pungent smell of a flammable "
	+ "fungus from the house to the south.");
	add_smell("kender", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and a pungent smell that makes your nose "
	+ "itch coming from the house to the south.");
	add_smell("drow", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and the distinct, pungent smell of a flammable "
	+ "fungus called Phosphentus coming from the house to the south.  How did "
	+ "these humans acquire this deep cave grown growth?  It's dangerously "
	+ "flammable, explosive in alcohol, and grows like the plague.");
	add_smell("noldor", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and the uniquely pungent smell of a flammable "
	+ "fungus coming from the house to the south.");
	add_smell("uruk", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and a uniquely pungent fiery smell that your "
	+ "uruk nostrils can't get enough of from the house to the south.");
	add_smell("presence", "This isn't the best form to appreciate the "
	+ "air thick with the rich smells of new equipment coming from the "
	+ "house to the south.");
	add_smell("unknown", "You smell the air rich with the smells of new "
	+ "equipment coming from the house to the south, but what the heck race "
	+ "are you?  Why not mail Krynn for fun?");

	clone_object(MONKS + "doors/generaleq_door_out")->move(TO);

	add_alley("s", "south", MONKS + "alley053");

	EXIT(MONKS + "a13", "east", 0, 0);
	EXIT(MONKS + "a11", "west", 0, 0);
}
