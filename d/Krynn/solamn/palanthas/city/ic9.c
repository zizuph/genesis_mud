/* Mortis 07.2005 */

#include "../local.h"
#include CLOCKH

inherit CITY_BASE;

string
query_to_jail()
{
  return "southwest";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  A grove of well cultivated trees grows behind the "
	+ "palatial palace to your southeast, and past a few buildings to your "
	+ "northwest are the great merchant shipping houses.  The street curves "
	+ "to Horizon road southwest and Trade road in the east.\n";
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
    SHORT("On a curving stretch of Inner Circle street near a tree grove");
    LONG("@@get_time_desc@@");

	ITEM(({"tree", "trees", "grove"}), "A great grove of well cultivated "
	+ "oaks, birches, poplars, and cedar grows to the southeast, their rich, "
	+ "green leaves softly rustling in the breeze off the bay.  It is "
	+ "forbidden by law to enter this palatial wood unbidden.  A tall, white "
	+ "tower of marble rises from the palace on the other side.\n");

	ITEM(({"houses", "merchant shipping houses", "merchant houses",
	"shipping houses", "trading houses", "merchant trading houses"}), 
	"A pair of four or perhaps five story marble houses rises high above the "
	+ "buildings to your northwest.  They are the two greatest merchant "
	+ "trading houses in Palanthas busy night and day with commerce from the "
	+ "Bay of Branchala and their warehouses.\n");

	EXIT(ROOM + "tr1", "east", 0, 0);
	EXIT(ROOM + "nwr2", "southwest", 0, 0);

}