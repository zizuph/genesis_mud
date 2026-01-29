/* Mortis 12.2005 
 * Failure msg for trying to enter Shoikan or entrance?
 * Smells?
 */

#include "../local.h"
#include CLOCKH

inherit MERCH_BASE;

string
query_to_jail()
{
  return "east";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  From this intersection with Palanthas Circle, the "
	+ "great, white, palatial tower is still visible above the buildings in "
	+ "the east from this distance.  To the west the road leads through a "
	+ "shopping district, and southeast is a grove of great oaks out of the "
	+ "center of which looms a tower of dark, grey stone.  A grove of thick "
	+ "woods is to the northeast.  From it rises a squat, square tower of "
	+ "great marble blocks.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Merchants' Way and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and coffee borne on a cool, misty breeze from the bay." + road;
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
	+ "as merchants and shoppers make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent "
	+ "marble of Merchants' Way amplifying the yellow glow of the street "
	+ "lamps.  A few people still make their way about at this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void
create_palan_room()
{
    SHORT("On Merchants' Way at the intersection of Palanthas Circle");
    LONG("@@get_time_desc@@");

	ITEM(({"oak", "oaks", "tree", "trees", "grove", "shoikan grove"}),
	  "Southeast is a grove of oaks, much larger than most you've seen, "
	+ "moving unnaturally on chill surges in the breeze.  As you peer into "
	+ "their midst your eyes are drawn deeper in and for a moment you almost "
	+ "feel as if you're falling before the feeling passes.  No buildings "
	+ "border closely with the trees.\n");
	ITEM(({"wood", "woods", "north wood", "north woods", "thick wood",
		   "thick woods"}), "A thick wood of trees stands to your northeast.  "
	+ "They are the Gallant Field Woods and home to the constabulary of "
	+ "Palanthas, the Palanthian Guard.  Their Tower of Arms rises from "
	+ "the vast field at its center.\n");

	add_alley("ne", "northeast", MERCH + "leiden_garden");

	EXIT(MERCH + "m06", "north", 0, 0);
	EXIT(MERCH + "wr2", "east", 0, 0);
	EXIT(MERCH + "m10", "south", 0, 0);
	EXIT(MERCH + "wr4", "west", 0, 0);

        CMD("alley", ({"enter","go","walk"}), "Use the command 'alley <direction>' " +
        "to enter an alley.\n");

}
