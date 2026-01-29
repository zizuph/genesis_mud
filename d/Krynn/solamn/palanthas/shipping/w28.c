/* Mortis 12.2005
 * Alley.
 * Smells, bay is close.
 */

#include "../local.h"
#include CLOCKH

inherit SHIP_BASE;

string
query_to_jail()
{
  return "southwest";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Old Circle curves southwest to the city gates on "
	+ "Horizon road and north along the curve of the city wall.  Above "
	+ "the shops to the southeast rises a short, white marble tower.  The "
	+ "city wall towers high above to the northwest.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The clean marble of Old Circle and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and coffee borne on a cool, misty breeze." + road;
	break;

    case TOD_DAY:
	desc += "The clean marble of Old Circle and its buildings lights up "
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
    SHORT("On Old Circle northeast of the city gates on Horizon road");
    LONG("@@get_time_desc@@");

	ITEM(({"gate", "gates", "northwestern gate", "northwest gates",
		   "nw gate", "nw gates", "northwest gate", "northwest gates"}),
	  "A large metal gate.\n");
	ITEM(({"short tower", "short marble tower", "marble tower"}), "A tower "
	+ "of translucent, white marble rises at least forty feet into the air "
	+ "to the southeast, higher than all of the buildings in this section "
	+ "of the merchant quarter.\n");
	ITEM(({"wall", "city wall", "great wall"}), "The city wall of "
	+ "Palanthas towers high above to the northwest.  It is faced with "
	+ "large block panels of polished, translucent marble, but atop "
	+ "its crenallated defenses you spot the dark grey rock "
	+ "which comprises its core.  The wall is in good shape.\n");

	EXIT(SHIP + "w29", "north", 0, 0);
	EXIT(MERCH + "nwr7", "southwest", 0, 0);

}
