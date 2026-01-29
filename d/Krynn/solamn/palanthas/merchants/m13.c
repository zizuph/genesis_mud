/* Mortis 12.2005
 * Double-check mXX's
 */

#include "../local.h"
#include CLOCKH

inherit MERCH_BASE;

string
query_to_jail()
{
  return "north";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Palanthas Circle curves north past the arms district to "
	+ "the west and south towards Vingaard road.  Scholis court curves away "
	+ "to the east, and to the northeast is a grove of great oaks out of the "
	+ "center of which looms a tower of dark, grey stone.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The worn marble of Palanthas Circle and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and coffee borne on a cool, misty breeze." + road;
	break;

    case TOD_DAY:
	desc += "The worn marble of Palanthas Circle and its buildings lights up "
	+ "in the midday sun as travellers, merchants, and shoppers travel "
	+ "throughout the Merchant quarter filling the street with the noisy "
	+ "murmurings of their daily business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Palanthas Circle catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as travellers and merchants make their way about the "
	+ "street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Palanthas Circle amplifying the yellow glow of the street lamps.  "
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
    SHORT("On Palanthas Circle between the Arms district and a grove of "
	+ "large oaks");
    LONG("@@get_time_desc@@");

	ITEM(({"oak", "oaks", "tree", "trees", "grove", "shoikan grove"}),
	  "Northeast is a grove of oaks, much larger than most you've seen, "
	+ "moving unnaturally on chill surges in the breeze.  As you peer into "
	+ "their midst your eyes are drawn deeper in and for a moment you almost "
	+ "feel as if you're falling before the feeling passes.  No buildings "
	+ "border closely with the trees.\n");

	EXIT(MERCH + "m10", "north", 0, 0);
	EXIT(MERCH + "m14", "east", 0, 0);
	EXIT(MERCH + "m16", "south", 0, 0);

}
