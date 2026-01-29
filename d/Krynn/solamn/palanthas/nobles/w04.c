/* Mortis 11.2005
 * Alleys?
 * Roof/tower access via a climb?
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit NOBLE_BASE;

string
query_to_jail()
{
  return "northwest";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Old Circle curves from the northwest south along the "
	+ "city wall.  The great wall towers above you to the east.\n";
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
	+ "gleams in the midday sun as people travel to and from the harbor "
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
	object gate;

    SHORT("On Old Circle in the northeast of the Nobles quarter");
    LONG("@@get_time_desc@@");

	ITEM(({"wall", "city wall", "great wall"}), "The city wall of "
	+ "Palanthas towers high above to your east.  It is faced with "
	+ "large block panels of polished, translucent marble, but atop "
	+ "its crenallated defenses you spot dark grey rock which comprises "
	+ "its core.  The wall is in good shape.\n");

	EXIT(NOBLE + "w03", "northwest", 0, 0);
	EXIT(NOBLE + "w05", "south", 0, 0);

}
