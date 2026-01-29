/* Mortis 12.2005
 * Smells
 */

#include "../local.h"
#include CLOCKH

inherit MERCH_BASE;

string
query_to_jail()
{
  return "south";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Palanthas Circle curves northeast towards Horizon road "
	+ "and south through the shopping district west.  To the southeast is a "
	+ "thick wood from which rises a squat, square tower of marble.  A "
	+ "short, white marble tower at least two score feet high is due "
	+ "northwest, and a side street cuts through the buildings along the "
	+ "wood to Horizon road.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The clean marble of Palanthas Circle and its buildings "
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
    SHORT("On Palanthas Circle southwest of Horizon road");
    LONG("@@get_time_desc@@");

	ITEM(({"wood", "woods", "north wood", "north woods", "thick wood",
		   "thick woods"}), "A thick wood of trees stands to your "
	+ "southeast.  They are the Gallant Field Woods and home to the "
	+ "constabulary of Palanthas, the Palanthian Guard.  Their Tower of "
	+ "Arms rises from the vast field at its center.\n");
	ITEM(({"short tower", "short marble tower", "marble tower"}), "A tower "
	+ "of translucent, white marble rises at least forty feet into the air "
	+ "to the northwest, higher than nearly all of the buildings in this "
	+ "section of the merchant quarter.  Chiseled into the marble above its "
	+ "entryway is, \"Palanthas Guard Tower\".\n");

	EXIT(MERCH + "nwr5", "northeast", 0, 0);
	EXIT(MERCH + "nwr4", "east", 0, 0);
	EXIT(MERCH + "m03", "south", 0, 0);
	EXIT(MERCH + "merchant_tower1", "northwest", 0, 0);

}
