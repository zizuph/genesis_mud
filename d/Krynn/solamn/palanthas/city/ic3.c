/* Mortis 07.2005 */

#include "../local.h"
#include CLOCKH

inherit CITY_BASE;

string
query_to_jail()
{
  return "northwest";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  To the northwest is Scholar's Walk.  The Solamnian "
	+ "Livery and its fenced corral can be seen just to your east, and "
	+ "south the street curves to Nobles' Way.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Inner Circle street and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "The air is rich with the smells of morning cooking and coffee borne "
	+ "on a cool, misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Inner Circle street and its buildings "
	+ "gleams in the midday sun as people travel to and from the plaza "
	+ "filling the street with the noisy murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Inner Circle street catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Inner Circle street amplifying the yellow glow of the street lamps.  "
	+ "A few people still make their way about at this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void create_palan_room()
{
    SHORT("On a curving stretch of Inner Circle street near the livery");
    LONG("@@get_time_desc@@");

	ITEM("livery", "The Solamnian Livery from what you can see is a very "
	+ "large and fair-looking estate to leave a mount.\n");

	ITEM("corral", "A high fence of large, squared wooden beams corrales "
	+ "several horses being walked it appears by handlers, but it's hard "
	+ "to get a good look from here.\n");

	add_alley("ne", "northeast", NOBLE + "alley002");
	add_alley("se", "southeast", NOBLE + "alley003");

	EXIT(ROOM + "er1", "south", 0, 0);
	EXIT(ROOM + "ner2", "northwest", 0, 0);

}