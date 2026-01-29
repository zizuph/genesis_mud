/* Mortis 07.2005 */

#include "../local.h"
#include CLOCKH

inherit CITY_BASE;

string
query_to_jail()
{
  return "northeast";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  To the northeast is the palatial plaza, its great white "
	+ "tower still visible above the buildings from this distance.  Inner "
	+ "Circle street curves to the northwest and southeast, and to the "
	+ "southwest the road continues on between the merchant and aesthetics "
	+ "districts.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Vingaard road and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "The air is rich with the smells of morning cooking and coffee borne "
	+ "on a cool, misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Vingaard road and its buildings "
	+ "gleams in the midday sun as people travel to and from the plaza "
	+ "filling the street with the noisy murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Vingaard road catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Vingaard road amplifying the yellow glow of the street lamps.  "
	+ "A few people still make their way about at this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void create_palan_room()
{
    SHORT("On Vingaard road southwest of the palatial plaza");
    LONG("@@get_time_desc@@");

	EXIT(ROOM + "swr1", "northeast", 0, 0);
	EXIT(ROOM + "ic7", "northwest", 0, 0);
	EXIT(MONKS + "swr3", "southwest", 0, 0);
	EXIT(ROOM + "ic6", "southeast", 0, 0);

}