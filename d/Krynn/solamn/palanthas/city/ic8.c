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
	string road = "  To the west is a cultivated grove of trees, and "
	+ "east at the city center is the palatial plaza, its white tower rising "
	+ "high above the buildings still visible from here.  The street curves "
	+ "to Merchants Way in the south and Horizon road northwest.\n";
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
    SHORT("On a curving stretch of Inner Circle street near a park");
    LONG("@@get_time_desc@@");

	ITEM(({"tree", "trees", "grove"}), "A great grove of cultivated oaks, "
	+ "birches, poplars, and cedar grows to your west their rich, green "
	+ "leaves softly rustling in the breeze off the bay.  A short, wide "
	+ "tower of great marble blocks sits in a clearing at the grove's "
	+ "center.\n");

	ITEM(({"short tower", "wide tower", "tower of arms"}), "Topped with "
	+ "fortified crenellations and the glint of armored knights, this stocky "
	+ "tower rises from a clearing in the midst of a grove of cultivated trees "
	+ "to your west.\n");

	EXIT(ROOM + "wr1", "south", 0, 0);
	EXIT(ROOM + "nwr2", "northeast", 0, 0);

}