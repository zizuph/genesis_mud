/*
 * Mortis 11.2005
 * 
 * Alleys?
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit MONKS_BASE;

string
query_to_jail()
{
	return "west";
}

void
reset_palan_room()
{
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
	+ "is to your south.  It is built from tan bricks with dirty gray "
	+ "mortar and an aging, wood shingled roof.  Above its door sways a "
	+ "dark, wooden sign with the picture of a leather shoe carved on it.\n");
	ITEM("sign", "It is a dark, wooden sign with the picture of a leather "
	+ "shoe carved on it.  It hangs above the doorway of the house to the "
	+ "south.\n");

	add_smell("vampire", "The smell of clay hovers in the air here despite "
	+ "the breeze from the bay.  From the doorway of the house to the south "
	+ "comes the smell of fresh leather, and the smell of blood is not far "
	+ "off.");
	add_smell("morgul", "The smell of clay hovers in the air here despite the "
	+ "breeze from the bay.  From the doorway of the house to the south "
	+ "comes the smell of fresh leather.");
	add_smell("human", "The smell of clay hovers in the air here despite "
	+ "the breeze from the bay.  From the doorway of the house to the south "
	+ "comes the smell of fresh leather.");
	add_smell("elf", "The smell of dirt, clay, and perhaps a hint of sewage "
	+ "hover in the air here despite the salty breeze from the bay.  From "
	+ "doorway of the house to the south comes the smell of fresh leather "
	+ "and cobblery.");
	add_smell("goblin", "Dirty clay, earthy smells hang in the air "
	+ "reminding you of places you've slept.  From the doorway of the house "
	+ "to the south comes the smell of fresh leather.");
	add_smell("dwarf", "The smell of clay hovers in the air here despite the "
	+ "breeze from the bay.  From the doorway of the house to the south "
	+ "comes the smell of fresh leather.");
	add_smell("hobbit", "The smell of clay hovers in the air here despite "
	+ "the breeze from the bay.  From the doorway of the house to the south "
	+ "comes the smell of fresh leather reminding you of new shoes.");
	add_smell("gnome", "The smell of dirt and clay from a lack of street "
	+ "cleaning hovers in the air here despite the salty breeze from the "
	+ "bay.  The smell of fresh leather commonly used in cobblery comes "
	+ "to you from the house to the south.");
	add_smell("minotaur", "The smell of clay hovers in the air here despite "
	+ "the breeze from the bay.  From the doorway of the house to the south "
	+ "comes the smell of fresh leather.");
	add_smell("halfhuman", "The smell of clay hovers in the air here despite "
	+ "the breeze from the bay.  From the doorway of the house to the south "
	+ "comes the smell of fresh leather.");
	add_smell("halfelf", "The smell of clay hovers in the air here despite "
	+ "the breeze from the bay.  From the doorway of the house to the south "
	+ "comes the smell of fresh leather.");
	add_smell("orc", "Dirty clay, earthy smells hang in the air reminding "
	+ "you of places you've slept and graves.  From the doorway of the house "
	+ "to the south comes the smell of fresh leather.");
	add_smell("hobgoblin", "Dirty clay, earthy smells hang in the air "
	+ "reminding you of places you've slept.  From the doorway of the house "
	+ "to the south comes the smell of fresh leather, the kind used by "
	+ "human shoemakers.");
	add_smell("kender", "The smell of clay hovers in the air here despite "
	+ "the breeze from the bay.  From the doorway of the house to the south "
	+ "comes the smell of fresh leather reminding you of new shoes.");
	add_smell("drow", "The smell of dirt, clay, and perhaps a hint of sewage "
	+ "hover in the air here despite the salty breeze from the bay.  From "
	+ "doorway of the house to the south comes the smell of fresh leather "
	+ "and cobblery.");
	add_smell("noldor", "The smell of dirt, clay, and perhaps a hint of sewage "
	+ "hover in the air here despite the salty breeze from the bay.  From "
	+ "doorway of the house to the south comes the smell of fresh leather "
	+ "and cobblery.");
	add_smell("uruk", "Dirty clay, earthy smells hang in the air reminding "
	+ "you of places you've slept and graves.  From the doorway of the house "
	+ "to the south comes the smell of fresh leather.");
	add_smell("presence", "You smell clay and leather, but you don't gather "
	+ "much in your present state.");
	add_smell("unknown", "The smell of clay hovers in the air here despite "
	+ "the breeze from the bay.  From the doorway of the house to the south "
	+ "comes the smell of fresh leather, but what the heck race are you?  "
	+ "Why not mail Krynn for fun?");

	clone_object(MONKS + "doors/cobbler_door_out")->move(TO);

	reset_palan_room();

	EXIT(MONKS + "a12", "east", 0, 0);
	EXIT(MONKS + "a10", "west", 0, 0);
}
