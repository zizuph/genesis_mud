/* Mortis 11.2005
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
    SHORT("On Knight's High road northwest of the main southeastern gates "
	+ "of Palanthas");
    LONG("@@get_time_desc@@");

	ITEM(({"gate", "gates", "southeastern gate", "southeastern gates",
		   "se gate", "se gates", "southeast gate", "southeast gates",
		   "main city gate", "main city gates", "city gate", "city gates",
		   "main gate", "main gates"}), "A large metal gate.\n");

	add_alley("ne", "northeast", NOBLE + "n13");

	EXIT(NOBLE + "ser5", "northwest", 0, 0);
	EXIT(MONKS + "a22", "southwest", 0, 0);
	EXIT(NOBLE + "ser7", "southeast", 0, 0);

}