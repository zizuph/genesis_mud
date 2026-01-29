/* Mortis 12.2005 
 * Smells through shipping
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
	string road = "  Palanthas Circle curves west through a district "
	+ "filled almost entirely with warehouses and southeast to its "
	+ "intersection with Scholar's Walk.  Lotelis Avenue winds its way "
	+ "southwest towards the inner city.\n";
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
reset_palan_room()
{
	if (!wguard)
	{
		wguard = clone_object(LIV + "city_guard_wander");
		wguard->set_monster_home(SHIP + "s10");
		wguard->set_restrain_path(SHIP);
		wguard->set_random_move(55);
		wguard->move(TO);
	}
}

void
create_palan_room()
{
    SHORT("On Palanthas Circle northwest of Scholar's Walk");
    LONG("@@get_time_desc@@");

	EXIT(NOBLE + "ner5", "southeast", 0, 0);
	EXIT(SHIP + "s01", "southwest", 0, 0);
	EXIT(SHIP + "s09", "west", 0, 0);
        EXIT(SHIP + "fishmonger", "north", "@@check_open", 0);

	reset_palan_room();
}

int
check_open()
{
    return 0;
/*
    if (this_player()->query_wiz_level())
          return 0;
    write("The fish markets are closed at this time.\n");
    return 1;
*/
}