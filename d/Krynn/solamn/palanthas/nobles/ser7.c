/* Mortis 11.2005
 * Gate operator/room, etc.
 */

#include "../local.h"
#include CLOCKH

inherit NOBLE_BASE;

string
query_to_jail()
{
  return "northwest";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  To the northwest is the inner city, its great white "
	+ "palatial tower still visible above the buildings from this distance.  "
	+ "The buildings north of here are grand and noble while on the south "
	+ "side there are fewer so large.  A side street leads southwest, "
	+ "and to the southeast the road leads to the main city gates.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Knight's High road, its buildings, and "
	+ "the city gates glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains.  The air is rich with the smells of morning cooking and "
	+ "coffee borne on a cool, misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Knight's High road, its buildings, and "
	+ "the city gates gleams in the midday sun as people travel to and from "
	+ "Palanthas filling the street with the noisy murmurings of their daily "
	+ "business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Knight's High road catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as travellers and citizens make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Knight's High road amplifying the yellow glow of the street lamps.  "
	+ "A few people still make their way about at this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void
create_palan_room()
{
	object gate;

    SHORT("On Knight's High road inside the main southeast gate of "
	+ "Palanthas");
    LONG("@@get_time_desc@@");

	ITEM(({"wall", "city wall", "great wall"}), "The city wall of "
	+ "Palanthas towers high above.  It is faced with "
	+ "large block panels of polished, translucent marble, but atop "
	+ "its crenallated defenses you spot dark grey rock which comprises "
	+ "its core.  The wall is in excellent repair.\n");

	EXIT(NOBLE + "ser6", "northwest", 0, 0);
	EXIT(NOBLE + "w10", "northeast", 0, 0);
	EXIT(MONKS + "w11", "southwest", 0, 0);

	gate = clone_object(NOBLE_DOOR + "city_segate1.c");
	gate->move(TO);

}