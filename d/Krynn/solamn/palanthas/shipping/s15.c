/* Mortis 12.2005 
 *
 */

#include "../local.h"
#include CLOCKH

inherit SHIP_BASE;

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
	string road = "\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The clean marble of Landing street and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "The air is rich with the smells of wood, tar, and coffee borne "
	+ "on a cool, misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The well-worn marble of Landing street and its buildings "
	+ "gleams in the midday sun as people travel to and from the piers "
	+ "filling the street with the noisy murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Landing street catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as merchants, sailors, and dockhands make their way about the street."
	+ road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Landing street amplifying the yellow glow of the street lamps.  "
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
		wguard->set_monster_home(SHIP + "s15");
		wguard->set_restrain_path(SHIP);
		wguard->set_random_move(55);
		wguard->move(TO);
	}
}

void
create_palan_room()
{
    SHORT("On Landing street");
    LONG("@@get_time_desc@@");

//	EXIT(SHIP + "po4", "northeast", 0, 0);
	EXIT(PARENT2 + "palan/ship2/pier", "north", 0, 0);
	EXIT(SHIP + "tr4", "southeast", 0, 0);
	EXIT(SHIP + "s16", "northwest", 0, 0);

	reset_palan_room();
}