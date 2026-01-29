/* Mortis 11.2005
 * Alleys behind constabulary tower?
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
	+ "to the east gates.  Through the marble buildings to your west, you "
	+ "can see the top of a white marble tower rising at least two score "
	+ "feet into the air, and to the northwest curves a side street.  The "
	+ "city wall towers above you to the east.\n";
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
	+ "gleams in the midday sun as people travel about the "
	+ "noble district filling the street with the noisy murmurings "
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
	object gate;

    SHORT("On Old Circle south of the eastern gates");
    LONG("@@get_time_desc@@");

	ITEM(({"short tower", "short marble tower", "marble tower"}), "A tower "
	+ "of translucent, white marble rises at least forty feet into the air "
	+ "above the buildings to your west, higher than nearly all of the "
	+ "buildings in this section of the noble quarter.\n");
	ITEM(({"gate", "gates", "eastern gate", "eastern gates", "e gate",
		   "e gates", "east gate", "east gates"}), "A large metal gate.\n");
	ITEM(({"wall", "city wall", "great wall"}), "The city wall of "
	+ "Palanthas towers high above to your east.  It is faced with "
	+ "large block panels of polished, translucent marble, but atop "
	+ "its crenallated defenses you spot dark grey rock which comprises "
	+ "its core.  The wall is in good shape.\n");

	EXIT(NOBLE + "er5", "north", 0, 0);
	EXIT(NOBLE + "n17", "northwest", 0, 0);
	EXIT(NOBLE + "w08", "south", 0, 0);

}
