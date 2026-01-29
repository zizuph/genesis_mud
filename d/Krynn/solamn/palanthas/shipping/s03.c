/* Mortis 12.2005 
 * Smells through shipping
 * npc idea: gravel raker
 */

#include "../local.h"
#include <macros.h>
#include CLOCKH

inherit SHIP_BASE;

string
query_to_jail()
{
  return "northeast";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  The warehouses of the professional warehouse district "
	+ "are all you can make out northwards, and a great, four-story, marble "
	+ "estate is to the south.  Bulwark Round curves west towards another "
	+ "estate and northeast to the intersection of Trade road and Inner "
	+ "Circle street.  The great white tower of the palace far to the "
	+ "southeast is still visible above the buildings from this distance.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The clean marble of Bulwark Round and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains.  The air is rich with the smells of wood, tar, and coffee "
	+ "borne on a cool, misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The well-worn marble of Bulwark Round and its buildings "
	+ "gleams in the midday sun as people travel to and from the piers "
	+ "filling the street with the noisy murmurings of their daily "
	+ "business.  A cool, salty breeze blows south off the bay." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Bulwark Round catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as travellers, sailors, and dockhands make their way about the "
	+ "street.  A misty, salty breeze blows south off the bay." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Bulwark Round amplifying the yellow glow of the street lamps.  "
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
    SHORT("On Bulwark Round south of the warehouses of Palanthas Circle");
    LONG("@@get_time_desc@@");

	ITEM(({"estate", "four-story estate", "marble estate", "great estate"}),
	  "One of the largest buildings in the shipping quarter, a great, four-"
	+ "story, marble estate is south at the end of a wide, gravel street.\n");
	ITEM(({"gravel", "gravel street", "wide gravel street", "wide street"}),
	  "Small piece, crushed marble has been raked perfectly level on the "
	+ "wide street leading south from Bulwark Round to a great, four-story "
	+ "estate.\n");

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

	add_alley("se", "southeast", SHIP + "alley201");

	EXIT(SHIP + "tr3", "northeast", 0, 0);
	EXIT(SHIP + "trusq_foyer", "south", "@@merch_open", 0);
	EXIT(SHIP + "s04", "west", 0, 0);
}

int
merch_open()
{
	write("Crushed marble gravel crunches beneath your feet as you walk down "
	+ "the gravel street into the estate to the south.\n\n");
	say("Crushed marble gravel crunches beneath " + QTNAME(TP) + "'s feet as "
	+ HE(TP) + " walks down the gravel street into the estate to the "
	+ "south.\n");
	return 0;
}
