/* Mortis 11.2005
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
	string road = "  Old Circle curves northwest into the Merchant quarter "
	+ "and southeast along the curve of the city wall to the "
	+ "city gates.  A side street leads to the northeast where Emptoris "
	+ "Row begins.  The city wall towers above you to the southwest.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The worn marble of Old Circle and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and coffee borne on a cool, misty breeze." + road;
	break;

    case TOD_DAY:
	desc += "The worn marble of Old Circle and its buildings lights up "
	+ "in the midday sun as travellers, merchants, and shoppers travel "
	+ "throughout the Merchant quarter filling the street with the noisy "
	+ "murmurings of their daily business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Old Circle catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as travellers and merchants make their way about the "
	+ "street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Old Circle amplifying the yellow glow of the street lamps.  "
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
    SHORT("On Old Circle northeast of the southwestern city gates");
    LONG("@@get_time_desc@@");

	ITEM(({"gate", "gates", "southwestern gate", "southwest gates",
		   "sw gate", "sw gates", "southwest gate", "southwest gates"}),
	  "A large metal gate.\n");
	ITEM(({"wall", "city wall", "great wall"}), "The city wall of "
	+ "Palanthas towers high above to the southwest.  It is faced with "
	+ "large block panels of polished, translucent marble, but atop "
	+ "its crenallated defenses you spot the dark grey rock "
	+ "which comprises its core.  The wall is in fair shape.\n");

	EXIT(MERCH + "m17", "northeast", 0, 0);
	EXIT(MONKS + "swr7", "southeast", 0, 0);
	EXIT(MERCH + "w21", "northwest", 0, 0);

}
