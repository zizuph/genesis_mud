/* Mortis 11.2005 */

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
	string road = "  To the northwest is the palatial plaza, its great white "
	+ "tower still visible above the buildings from this distance.  To the "
	+ "southwest is a large two-story building from which hangs a sign, "
	+ "\"The Wayside\".  To the northeast is a short, marble tower two "
	+ "dozen feet in height, and to the southeast the road continues on "
	+ "between the noble and aesthetics districts on its way out of the "
	+ "city.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Knight's High road and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "The air is rich with the smells of morning cooking and coffee borne "
	+ "on a cool, misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Knight's High road and its buildings "
	+ "gleams in the midday sun as people travel to and from the plaza "
	+ "filling the street with the noisy murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Knight's High road catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the street." + road;
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
    SHORT("On Knight's High road northwest of Palanthas Circle");
    LONG("@@get_time_desc@@");

	ITEM(({"short tower", "ne tower", "northeast tower", "marble tower",
		   "short marble tower"}), "To the northeast between tall, marble "
	+ "buildings is a two-story, marble tower with an open doorway.  Above "
	+ "the doorway is hung a banner reading, \"Adventurer's Guild of "
	+ "Palanthas\".\n");

	EXIT(NOBLE + "ser3", "northwest", 0, 0);
	EXIT(MONKS + "adv_guild", "northeast", "@@place_closed", 0);
	EXIT(MONKS + "wayside", "southwest", "@@place_closed", 0);
	EXIT(NOBLE + "ser5", "southeast", 0, 0);

}

int
place_closed()
{
	write("To be opened in the future.\n");
	return 1;
}