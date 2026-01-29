/* Mortis 07.2005 */

#include "../local.h"
#include CLOCKH

inherit NOBLE_BASE;

object wguard;

string
query_to_jail()
{
	return "south";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  To the southwest can be seen a livery, and to the "
	+ "southeast are some of the noble estates.  The street runs northwest "
	+ "to Scholar's walk where it ends.  Itzus Street runs east ending "
	+ "in Palanthas Circle, and to your northeast is a three-story "
	+ "marble building.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Livery Street and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "A cool, misty breeze blows south from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Livery Street and its buildings "
	+ "gleams in the midday sun as people walk about the intersection "
	+ "filling the streets with the gentle murmurings of their daily "
	+ "business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Livery Street catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Livery Street amplifying the yellow glow of the street lamps.  "
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
	if (!wguard)
	{
		wguard = clone_object(LIV + "city_guard_wander");
		wguard->set_monster_home(NOBLE + "n03");
		wguard->set_restrain_path(NOBLE);
		wguard->set_random_move(55);
		wguard->move(TO);
	}
}

void
create_palan_room()
{
    SHORT("On Livery Street southeast of Scholar's Walk in the nobles "
	+ "district");
    LONG("@@get_time_desc@@");

	ITEM(({"livery", "solamnian livery", "stable", "stables"}), "The livery "
	+ "to your southwest is actually a large estate with a field, a corral, "
	+ "a long stable of wood, and a great, marble manor house in its midst.  "
	+ "The house is an old, translucent marble building whose grounds were "
	+ "converted ages ago to accomodate the field, wood-fenced corral, and "
	+ "stables.  The stables are a great longhouse of wood with a fenced in "
	+ "area for bringing horses to and from the stalls.\n");
	ITEM(({"estate", "estates", "noble estate", "noble estates"}), "There "
	+ "are a pair of estates to your southeast.  Their architecture is "
	+ "typical of the old buildings of marble rising several stories "
	+ "here in the noble district.\n");
	ITEM(({"building", "ne building", "northeast building", "three-story "
	+ "building", "marble building", "three-story marble building"}),
	  "To the northeast is a three-story building of clean, pristine "
	+ "marble and ornately trimmed windows facing Palanthas Circle to its "
	+ "southeast where you may enter it to your east.\n");
	ITEM(({"window", "windows", "ne window", "ne windows", "northeast window",
	"northeast windows"}), "The pristine, three-story, marble building to "
	+ "your northeast has windows on each floor trimmed in ornately "
	+ "chiseled marblework.  The one on the ground floor is open allowing "
	+ "in the fresh breeze.\n");

	CMD(({"window", "small window"}), "enter", "@@enter_window");

	EXIT(NOBLE + "ner3", "northwest", 0, 0);
	EXIT(NOBLE + "n04", "east", 0, 0);
	EXIT(NOBLE + "n01", "south", 0, 0);

	reset_palan_room();
}

string
enter_window()
{
	TP->move_living("climbing into the window on the ground floor of the "
	+ "three-story building to the northeast", NOBLE + "jeweler", 1, 0);
	return "";
}
