/* Mortis 11.2005
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
	string road = "  To the southwest is the inner city and palatial plaza, "
	+ "its great white tower still visible above the buildings from this "
	+ "distance.  To the northeast the road continues on between the noble "
	+ "and shipping districts towards Scholar's Gate.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Scholar's Walk and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "The air is rich with the smells of morning cooking and coffee borne "
	+ "on a cool, misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Scholar's Walk and its buildings "
	+ "gleams in the midday sun as people travel to and from the plaza "
	+ "filling the street with the noisy murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Scholar's Walk catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the street." + road;
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

void create_palan_room()
{
    SHORT("On Scholar's Walk northeast of the inner city");
    LONG("@@get_time_desc@@");

	ITEM(({"gate", "northeast gate", "ne gate", "scholars gate",
		   "scholar's gate"}), "A large metal gate.\n");

	EXIT(NOBLE + "ner4", "southwest", 0, 0);
	EXIT(SHIP + "s10", "northwest", 0, 0);
	EXIT(NOBLE + "ner6", "northeast", 0, 0);
	EXIT(NOBLE + "n05", "southeast", 0, 0);

}
