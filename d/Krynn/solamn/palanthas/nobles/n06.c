/* Mortis 11.2005
 */

#include "../local.h"
#include CLOCKH

inherit NOBLE_BASE;

object wguard;

string
query_to_jail()
{
	return "southwest";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Kosten Way curves through this portion of the nobles "
	+ "quarter from the northeast, where it begins on Old Circle, to the "
	+ "southeast where it also ends on Old Circle.  A side street leads "
	+ "southwest to Palanthas Circle.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Kosten Way and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "A cool, misty breeze blows south from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Kosten Way and its buildings "
	+ "gleams in the midday sun as people walk about the intersection "
	+ "filling the streets with the gentle murmurings of their daily "
	+ "business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Kosten Way catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Kosten Way amplifying the yellow glow of the street lamps.  "
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
		wguard->set_monster_home(NOBLE + "n06");
		wguard->set_restrain_path(NOBLE);
		wguard->set_random_move(55);
		wguard->move(TO);
	}
}

void
create_palan_room()
{
    SHORT("On Kosten Way northwest of Umberto's Cloth");
    LONG("@@get_time_desc@@");

	ITEM(({"umbertos", "umberto's", "umbertos cloth", "umberto's cloth"}),
	  "A large, two-story marble building with a great, purple banner "
	+ "hanging vertically from an upper level window can be seen through "
	+ "the buildings to your south.\n");

	EXIT(NOBLE + "w03", "northeast", 0, 0);
	EXIT(NOBLE + "n05", "southwest", 0, 0);
	EXIT(NOBLE + "n07", "southeast", 0, 0);

	reset_palan_room();
}
