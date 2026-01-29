/* 
 * Mortis 12.2005
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit SHIP_BASE;

string
query_to_jail()
{
  return "west";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Palanthas Circle curves west through side streets "
	+ "and alleys filled with warehouses and east to its intersection "
	+ "with Trade road and Bulwark Round.  Large warehouses are located "
	+ "to the north and south each with a sign hanging above their doors, "
	+ "and through the buildings to the northeast you can make out the "
	+ "piers and the bay.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The clean marble of Palanthas Circle and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains.  The air is rich with the smells of wood, tar, and coffee "
	+ "borne on a cool, misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The well-worn marble of Palanthas Circle and its buildings "
	+ "gleams in the midday sun as people travel to and from the piers "
	+ "filling the street with the noisy murmurings of their daily "
	+ "business.  A cool, salty breeze blows south off the bay." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Palanthas Circle catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as travellers, sailors, and dockhands make their way about the "
	+ "street.  A misty, salty breeze blows south off the bay." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Palanthas Circle amplifying the yellow glow of the street lamps.  "
	+ "A few dock workers still make their way about at this hour.  "
	+ "A cool, salty breeze blows south off the bay." + road;
    break;

    default:
	break;
    }
    return desc;
}

void
create_palan_room()
{
    SHORT("On Palanthas Circle west of Trade road in a warehouse district");
    LONG("@@get_time_desc@@");

	ITEM(({"warehouse", "warehouses"}), "A pair of the largest warehouses "
	+ "on Palanthas Circle are located to the north and south.  From them "
	+ "dock workers come and go at all hours.  Above the great doors on "
	+ "each hangs a sign on chains hanging from an iron rod.  You can read "
	+ "the north or south one.\n");
	ITEM(({"chain", "chains", "rod", "rods"}), "Above the great doors of "
	+ "the large warehouses to the north and south is planted an iron rod "
	+ "from which the warehouse's sign hangs.\n");
	ITEM(({"sign", "signs"}), "Which sign do you want to examine?  The north "
	+ "or south sign?\n");
	ITEM("north sign", "It is a sturdy wooden sign hanging from chains above "
	+ "the great doors of the warehouse to your north.  Try <read north>.\n");
	ITEM("south sign", "It is a sturdy wooden sign hanging from chains above "
	+ "the great doors of the warehouse to your south.  Try <read south>.\n");

	add_smell("vampire", "The air is rich with the smells of wood, tar, and "
	+ "leather borne on a salty breeze from the bay.  You are not far from "
	+ "blood.");
	add_smell("morgul", "The air is thick with the smells of wood, tar, and "
	+ "leather borne on a salty breeze from the bay.");
	add_smell("human", "The air is rich with the smells of wood, tar, and "
	+ "leather borne on a salty breeze from the bay.");
	add_smell("elf", "A salty breeze off the bay brings with it the smells "
	+ "of wood, tar, leather, and other materials common on the piers of "
	+ "human cities.");
	add_smell("goblin", "The air is thick with the smells of wood, tar, and "
	+ "leather borne on a salty breeze from the bay.");
	add_smell("dwarf", "The air is rich with the smells of wood, tar, and "
	+ "leather borne on a salty breeze from the bay.");
	add_smell("hobbit", "A salty breeze off the bay brings with it the smells "
	+ "of wood, tar, leather, and other materials common on the piers of "
	+ "human cities.");
	add_smell("gnome", "The salty air from the bay brings with it the smells "
	+ "of common ship maintenance components such as tar, wood, and leather "
	+ "as well as common trade goods and spices typical in a human port.");
	add_smell("minotaur", "The air is thick with the smells of wood, tar, and "
	+ "leather borne on a salty breeze from the bay.");
	add_smell("halfhuman", "The air is rich with the smells of wood, tar, and "
	+ "leather borne on a salty breeze from the bay.");
	add_smell("halfelf", "A salty breeze off the bay brings with it the "
	+ "smells of wood, tar, leather, and other materials common on the piers "
	+ "of human cities.");
	add_smell("orc", "The air is thick with the smells of wood, tar, and "
	+ "leather borne on a salty breeze from the bay.  The scent of manflesh "
	+ "is strong nearby.");
	add_smell("hobgoblin", "The air is thick with the smells of wood, tar, and "
	+ "leather borne on a salty breeze from the bay.");
	add_smell("kender", "A salty breeze off the bay brings with it the smells "
	+ "of wood, tar, leather, and other materials common on the piers of "
	+ "human cities.");
	add_smell("drow", "A salty breeze off the bay brings with it the smells "
	+ "of wood, tar, leather, and other materials common on the piers of "
	+ "human cities.");
	add_smell("noldor", "A salty breeze off the bay brings with it the smells "
	+ "of wood, tar, leather, and other materials common on the piers of "
	+ "human cities.");
	add_smell("uruk", "The air is thick with the smells of wood, tar, and "
	+ "leather borne on a salty breeze from the bay.  The scent of manflesh "
	+ "is strong nearby.");
	add_smell("presence", "The air smells like it is near the bay, but you "
	+ "fail to appreciate it fully in your current form.");
	add_smell("unknown", "The salty air is rich with wood, tar, and the like, "
	+ "but what the heck race are you?  Why not mail Krynn for fun?");

	CMD(({"sign", "signs"}), "read", "@@read_sign");
	CMD(({"north", "n", "north sign", "n sign"}), "read", "@@read_north");
	CMD(({"south", "s", "south sign", "s sign"}), "read", "@@read_south");

	EXIT(SHIP + "ware_5", "north", "@@place_closed", 0);
	EXIT(SHIP + "tr3", "east", 0, 0);
	EXIT(SHIP + "ware_trusq", "south", 0, 0);
	EXIT(SHIP + "s06", "west", 0, 0);

}

int
place_closed()
{
	write("Warehouse Five (5) is not open yet.\n");
	return 1;
}

int
read_sign()
{
	write("Which sign would you like to read?  The north or south one?\n");
	say(QCTNAME(TP) + " ponder which sign " + HE(TP) + " would like to "
	+ "read.\n");
	return 1;
}

int
read_north()
{
	write("The north sign reads, \"Warehouse Five (5)\".\n");
	say(QCTNAME(TP) + " reads the sign above the north warehouse.\n");
	return 1;
}

int
read_south()
{
	write("The south sign reads, \"Warehouse Trusq\".\n");
	say(QCTNAME(TP) + " reads the sign above the south warehouse.\n");
	return 1;
}
