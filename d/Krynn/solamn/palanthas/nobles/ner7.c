/* Mortis 11.2005
 * Add_smells for crab shack to nw.
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit NOBLE_BASE;

string
query_to_jail()
{
  return "southwest";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  The road runs southwest to the inner city and palatial "
	+ "plaza, its great white tower visible above the buildings from even "
	+ "this distance.  Old Circle leads off to your northwest and "
	+ "southeast following the inside of the city wall.  Scholar's Gate "
	+ "exits the city to your northeast.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Scholar's Walk and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "The air is rich with the salty smells from the bay borne on a cool, "
	+ "misty breeze." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Scholar's Walk and its buildings "
	+ "gleams in the midday sun as people travel to and from the plaza "
	+ "and noble district filling the street with the noisy murmurings "
	+ " of their daily business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Scholar's Walk catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed travellers make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Scholar's Walk amplifying the yellow glow of the street lamps.  "
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

    SHORT("On Scholar's Walk inside the Scholar's Gate");
    LONG("@@get_time_desc@@");

	EXIT(NOBLE + "ner6", "southwest", 0, 0);
	EXIT(SHIP + "w02", "northwest", 0, 0);
	EXIT(NOBLE + "w03", "southeast", 0, 0);

	gate = clone_object(NOBLE_DOOR + "city_negate1.c");
	gate->move(TO);

}
