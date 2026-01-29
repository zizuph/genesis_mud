/* Mortis 12.2005 
 * Housing smells?
 */

#include "../local.h"
#include CLOCKH

inherit MONKS_BASE;

string
query_to_jail()
{
  return "northeast";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Palanthas circle intersects the road here curving "
	+ "northwest into the merchant quarter and southeast towards the "
	+ "dense housing district of the aesthetics quarter.  Southwest the "
	+ "road leads to the city gates.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Vingaard road and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and " + one_of_list(({"tea", "coffee"})) + " borne on a cool, "
	+ "misty breeze." + road;
	break;

    case TOD_DAY:
	desc += "The dusty marble of Vingaard road and its buildings "
	+ "gleams somewhat in the midday sun as people travel to and from the "
	+ "plaza filling the street with the noisy murmurings of their daily "
	+ "business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The dusty, translucent marble of Vingaard road catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the dusty, "
	+ "translucent marble of Vingaard road amplifying the yellow glow of "
	+ "the street lamps.  A few people still make their way about at this "
	+ "hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void
create_palan_room()
{
    SHORT("On Vingaard road at the intersection of Palanthas Circle");
    LONG("@@get_time_desc@@");

	ITEM(({"oak", "oaks", "tree", "trees", "grove", "shoikan grove"}),
	  "Before you is a grove of oaks, much larger than most you've seen, "
	+ "moving unnaturally on chill surges in the breeze.  As you peer into "
	+ "their midst your eyes are drawn deeper in and for a moment you almost "
	+ "feel as if you're falling before the feeling passes.  No buildings "
	+ "border closely with the trees.\n");
	ITEM(({"dark tower", "grey tower", "tower of high sorcery"}),
	  "Set deep in the center of the grove of oaks before you rises a tower "
	+ "of great and dark grey blocks of stone.  At its top are several "
	+ "pinnacles from which no banners fly.  Its shadow somehow spreads "
	+ "across the entire darkened grove.\n");

	EXIT(MONKS + "swr4", "northeast", 0, 0);
	EXIT(MONKS + "a09", "southeast", 0, 0);
	EXIT(MONKS + "swr6", "southwest", 0, 0);
	EXIT(MERCH + "m16", "northwest", 0, 0);

}