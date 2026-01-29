/* Mortis 12.2005
 * Door east to house.
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
	string road = "  Old Circle curves north through a housing district "
	+ "towards Merchants' Way and southeast along the curve of the city wall "
	+ "towards Vingaard road.  A large residence is to the east, and to the "
	+ "southwest the city wall towers high above.\n";
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
    SHORT("On Old Circle in the southwest of the merchant quarter");
    LONG("@@get_time_desc@@");

	ITEM(({"wall", "city wall", "great wall"}), "The city wall of "
	+ "Palanthas towers high above to the southwest.  It is faced with "
	+ "large block panels of polished, translucent marble, but atop "
	+ "its crenallated defenses you spot the dark grey rock "
	+ "which comprises its core.  The wall is in fair shape.\n");
	ITEM("housing district", "Here in the southwest of the merchant "
	+ "quarter, a row of good sized houses runs north and south near "
	+ "the city wall.  One of the residences is to your east.\n");
	ITEM("residence", "It is a two-story house of marble, kept clean, and "
	+ "with a small yard.\n");
	ITEM("yard", "The residence to your east has a small yard of cut, green "
	+ "grass.\n");
	ITEM("grass", "This isn't the kind of area of the city to find "
	+ "\"that\"!\n");

	EXIT(MERCH + "w22", "north", 0, 0);
	EXIT(MERCH + "w20", "southeast", 0, 0);

}
