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
	string road = "  Far to the northeast is the great white palatial tower "
	+ "still visible above the buildings from this distance.  A mottled "
	+ "marble and brick shop is just off the road to the northwest, and an "
	+ "old, round marble building is southeast.  Southwest the road "
	+ "leads between the merchant and aesthetics quarters.\n";
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
    SHORT("On Vingaard road between an old shop and rounded marble building");
    LONG("@@get_time_desc@@");

	ITEM(({"oak", "oaks", "tree", "trees", "grove", "shoikan grove"}),
	  "To the north is a grove of oaks, much larger than most you've seen, "
	+ "moving unnaturally on chill surges in the breeze.  As you peer into "
	+ "their midst your eyes are drawn deeper in and for a moment you almost "
	+ "feel as if you're falling before the feeling passes.  No buildings "
	+ "border closely with the trees.\n");
	ITEM(({"dark tower", "grey tower", "tower of high sorcery"}),
	  "Set deep in the center of the grove of oaks to the north rises a "
	+ "tower of great and dark grey blocks of stone.  At its top are several "
	+ "pinnacles from which no banners fly.  Its shadow somehow spreads "
	+ "across the entire darkened grove.\n");
	ITEM(({"round building", "den", "scholar's den", "scholars den"}),
	  "A round, marble building is set off the road to the southeast.  "
	+ "From its open doorway maroon-robed aesthetics come and go as well "
	+ "as the occasional merchant or traveller.  Above the doorway are "
	+ "chiseled the words, \"Scholar's Den\".\n");
	ITEM(({"mottled shop", "brick shop", "marble shop"}), "Northwest is "
	+ "the dark doorway of a very old looking shop.  Its base is mostly "
	+ "marble, but repairs over the year appear to have substituted beige "
	+ "brick as you look higher up its walls.  Its shutters hang askew, "
	+ "and some of the window panes are cracked.  Painted an the doorsill "
	+ "in crude white letters are the words, \"Warlok's Fleshmods\".\n");

	EXIT(MONKS + "swr3", "northeast", 0, 0);
	EXIT(MONKS + "den", "southeast", "@@place_closed", 0);
	EXIT(MONKS + "swr5", "southwest", 0, 0);
	EXIT(MERCH + "piercer", "northwest", "@@place_closed", 0);

}

int
place_closed()
{
	write("This will open in the future.\n");
	return 1;
}