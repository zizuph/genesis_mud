/* Mortis 11.2005
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit NOBLE_BASE;

string
query_to_jail()
{
  return "north";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Old Circle runs south along the city wall and north "
	+ "to the east gates.  Through the marble buildings to the northwest, "
	+ "you can see the top of a white marble tower rising at least two score "
	+ "feet into the air.  The city wall towers above you to the east, and "
	+ "a side street leads west to Nobil Row and the great noble estates.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Old Circle and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above "
	+ "the mountains.  The air is rich with the salty smells from the bay "
	+ "borne on a cool, misty breeze." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Old Circle and its buildings "
	+ "gleams in the midday sun as people travel to and from the estates "
	+ "and noble district filling the street with the noisy murmurings "
	+ "of their daily business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Old Circle catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as travellers, merchants, and seamen make their way about the street."
	+ road;
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
    SHORT("On Old Circle in the southeast of the nobles quarter");
    LONG("@@get_time_desc@@");

	ITEM(({"short tower", "short marble tower", "marble tower"}), "A tower "
	+ "of translucent, white marble rises at least forty feet into the air "
	+ "above the buildings to the northwest, higher than nearly all of the "
	+ "buildings in this section of the noble quarter.\n");
	ITEM(({"gate", "gates", "eastern gate", "eastern gates", "e gate",
		   "e gates", "east gate", "east gates"}), "A large metal gate.\n");
	ITEM(({"wall", "city wall", "great wall"}), "The city wall of "
	+ "Palanthas towers high above to your east.  It is faced with "
	+ "large block panels of polished, translucent marble, but atop "
	+ "its crenallated defenses you spot dark grey rock which comprises "
	+ "its core.  The wall is in good shape.\n");
	ITEM(({"estates", "estate", "noble estate", "noble estates"}),
	  "To the west along Nobil Row can be seen some of the larger, great "
	+ "noble estates among the other marble buildings.\n");

	EXIT(NOBLE + "w07", "north", 0, 0);
	EXIT(NOBLE + "n15", "west", 0, 0);
	EXIT(NOBLE + "w09", "south", 0, 0);

}
