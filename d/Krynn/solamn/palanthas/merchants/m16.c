/* 
 * Mortis 12.2005
 */

#include "../local.h"
#include CLOCKH

inherit MERCH_BASE;

string
query_to_jail()
{
  return "southeast";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Palanthas Circle curves northwest past the arms district "
	+ "and to the southeast intersects with Vingaard road.  A long, marble "
	+ "building stretches to the west.  A mint green banner flag flies atop "
	+ "its roof.\n";
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
    SHORT("On Palanthas Circle northwest of Vingaard road");
    LONG("@@get_time_desc@@");

	ITEM(({"banner", "flag", "mint green banner", "mint green flag",
		   "banner flag", "mint green banner flag"}), "A southerly "
	+ "breeze from the bay tousles this mint green banner flag atop the "
	+ "long, marble building stretching to your west.  Its acute triangle "
	+ "of mint green silk is emblazoned with the image of a longbow.\n");
	ITEM(({"long building", "marble building", "west building",
		   "long marble building"}), "Stretching to your west is a long, "
	+ "marble building flying from its roof a mint green banner flag.\n");

	EXIT(MERCH + "m13", "north", 0, 0);
	EXIT(MERCH + "bowyer", "west", 0, 0);
	EXIT(MONKS + "swr5", "southeast", 0, 0);

}
