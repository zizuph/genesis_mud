/* Mortis 11.2005
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit NOBLE_BASE;

object wguard;

string
query_to_jail()
{
	return "southeast";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  A side street curves southeast to Old Circle which "
	+ "runs along the city wall to the east.  A short, white marble tower "
	+ "rises at least two score feet into the air to your south.  The city "
	+ "wall towers above you to the southeast.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of the streets and buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above "
	+ "the mountains.  The air is rich with the salty smells from the bay "
	+ "borne on a cool, misty breeze." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of the streets and buildings "
	+ "gleams in the midday sun as people travel about the "
	+ "noble district filling the street with the noisy murmurings "
	+ "of their daily business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of the streets and buildings catches "
	+ "the last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the street."
	+ road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of the streets amplifying the yellow glow of the street lamps.  "
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
		wguard->set_monster_home(NOBLE + "n17");
		wguard->set_restrain_path(NOBLE);
		wguard->set_random_move(55);
		wguard->move(TO);
	}
}

void
create_palan_room()
{
	object gate;

    SHORT("North of a short, marble tower in the heart of the nobles "
	+ "quarter");
    LONG("@@get_time_desc@@");

	ITEM(({"short tower", "short marble tower", "marble tower"}), "A tower "
	+ "of translucent, white marble rises at least forty feet into the air "
	+ "to the south, higher than nearly all of the buildings in this section "
	+ "of the noble quarter.  Chiseled into the marble above its entryway "
	+ "is, \"Palanthas Guard Tower\".\n");
	ITEM(({"wall", "city wall", "great wall"}), "The city wall of "
	+ "Palanthas towers high above to your southeast..\n");

	EXIT(NOBLE + "w07", "southeast", 0, 0);
	EXIT(NOBLE + "noble_tower1", "south", 0, 0);

	reset_palan_room();
}
