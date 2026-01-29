/* Mortis 11.2005
 * Exits to ne/sw that circle city.  Hidden?
 * Road2 needs serious work, too.
 * Gate, portcullis, guard descs, the works.  npc guards
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
	string road = "  To the northwest are the main gates of the city of "
	+ "Palanthas, its great white palatial tower still visible above the "
	+ "buildings from this distance.  High marble walls curve to your "
	+ "southwest and northeast around the city.  A road follows the outside "
	+ "of the wall in each direction and to the southeast the road begins "
	+ "its trek through the mountains to the High Clerist's tower.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Knight's High road and "
	+ "the city gates glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains.  The air is rich with the smells of morning cooking and "
	+ "coffee borne on a cool, misty breeze from the city." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Knight's High road and "
	+ "the city gates gleams in the midday sun as people travel to and from "
	+ "Palanthas filling the street with the noisy murmurings of their daily "
	+ "business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Knight's High road catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as travellers make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Knight's High road amplifying the yellow glow of the street lamps.  "
	+ "A few travellers still make their way about at this hour." + road;
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

    SHORT("On Knight's High road southeast outside the gates of Palanthas");
    LONG("@@get_time_desc@@");

	ITEM(({"wall", "city wall", "great wall"}), "The city wall of "
	+ "Palanthas towers high above to your northwest.  Its massive width "
	+ "of large block panels of polished, translucent marble extends far to "
	+ "your southwest and northeast as it curves around the city in a "
	+ "perfect arc.  The wall is in excellent repair.\n");

//	EXIT(ROOM + "outx", "northeast", 0, 0);
//	EXIT(ROOM + "outy", "southwest", 0, 0);
	EXIT(PARENT2 + "vin_mount/room/road2", "southeast", 0, 0);

	gate = clone_object(NOBLE_DOOR + "city_segate2.c");
	gate->move(TO);

}