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
	return "south";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Trade road leads north through the city gates to "
	+ "the docks and south to Inner Circle street past which a grove "
	+ "of well cultivated trees grows.  Palanthas Circle intersects "
	+ "here leading east and west through rows of warehouses.  Bulwark "
	+ "Round curves northwest past the warehouses and southwest past "
	+ "great estates.  The white tower of the palatial plaza at city "
	+ "center is visible even from here.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The clean marble of Trade road and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "The air is rich with the smells of wood, tar, and coffee borne "
	+ "on a cool, misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The well-worn marble of Trade road and its buildings "
	+ "gleams in the midday sun as people travel to and from the piers "
	+ "filling the street with the noisy murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Trade road catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as merchants, sailors, and dockhands make their way about the street."
	+ road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Trade road amplifying the yellow glow of the street lamps.  "
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
		wguard->set_monster_home(SHIP + "tr3");
		wguard->set_restrain_path(SHIP);
		wguard->set_random_move(55);
		wguard->move(TO);
	}
}

void
create_palan_room()
{
	object gate;

    SHORT("On Trade road at the intersection of Palanthas Circle");
    LONG("@@get_time_desc@@");

	ITEM(({"tree", "trees", "grove"}), "A great grove of well cultivated "
	+ "oaks, birches, poplars, and cedar grows to the south, their rich, "
	+ "green leaves rustle softly in the breeze off the bay.\n");

	EXIT(SHIP + "s08", "east", 0, 0);
	EXIT(SHIP + "tr2", "south", 0, 0);
	EXIT(SHIP + "s03", "southwest", 0, 0);
	EXIT(SHIP + "s07", "west", 0, 0);
	EXIT(SHIP + "s13", "northwest", 0, 0);

	gate = clone_object(SHIP + "doors/city_ngate1.c");
	gate->move(TO);

	reset_palan_room();
}