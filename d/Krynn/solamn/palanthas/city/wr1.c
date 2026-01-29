/* Mortis 07.2005 */

#include "../local.h"
#include CLOCKH

inherit CITY_BASE;

string
query_to_jail()
{
  return "east";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  To the east is the palatial plaza, its great white "
	+ "tower still visible above the buildings from this distance.  To the "
	+ "west the road leads to the merchants district, and southwest of you "
	+ "is a grove of great oaks out of the center of which looms a tower "
	+ "of dark, grey stone.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Merchants' Way and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "The air is rich with the smells of morning cooking and coffee borne "
	+ "on a cool, misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Merchants' Way and its buildings "
	+ "gleams in the midday sun as people travel to and from the plaza "
	+ "filling the street with the noisy murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Merchants' Way catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Merchants' Way amplifying the yellow glow of the street lamps.  "
	+ "A few people still make their way about at this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void create_palan_room()
{
    SHORT("On Merchants' Way west of the palatial plaza");
    LONG("@@get_time_desc@@");

	ITEM(({"oak", "oaks", "tree", "trees", "grove", "shoikan grove"}),
	"Before you is a grove of oaks, much larger than most you've seen, moving "
	+ "unnaturally on chill surges in the breeze.  As you peer into their "
	+ "midst your eyes are drawn deeper in and for a moment you almost "
	+ "feel as if you're falling before the feeling passes.  No buildings "
	+ "border closely with the trees.\n");

	ITEM(({"dark tower", "grey tower", "tower of high sorcery"}),
	"Set deep in the center of the grove of oaks before you rises a tower of "
	+ "great and dark grey blocks of stone.  At its top are several pinnacles "
	+ "from which no banners fly.  Its shadow somehow spreads across the "
	+ "entire darkened grove.\n");

    EXIT(ROOM + "ic8", "north", 0, 0);
	EXIT(ROOM + "plaza", "east", 0, 0);
	EXIT(ROOM + "ic7", "south", 0, 0);
	EXIT(MERCH + "wr2", "west", 0, 0);

}