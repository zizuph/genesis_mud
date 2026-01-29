/* Mortis 11.2005
 * Alleys?
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
	string road = "  Nobil Row runs north and south to the entrances of "
	+ "several large, noble estates.  A side street leads east to Old "
	+ "Circle where you can make out the old, city wall.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Nobil Row and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above "
	+ "the mountains.  The air is rich with the salty smells from the bay "
	+ "borne on a cool, misty breeze." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Nobil Row and its buildings "
	+ "gleams in the midday sun as people travel to and from the estates "
	+ "of the noble quarter filling the street with the noisy murmurings "
	+ "of their daily business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Nobil Row catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as travellers, merchants, and seamen make their way about the street."
	+ road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Nobil Row amplifying the yellow glow of the street lamps.  "
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
    SHORT("On Nobil Row in the heart of the nobles quarter");
    LONG("@@get_time_desc@@");

	ITEM(({"short tower", "short marble tower", "marble tower"}), "A tower "
	+ "of translucent, white marble rises at least forty feet into the air "
	+ "above the buildings to the northeast, higher than nearly all of the "
	+ "buildings in this section of the noble quarter.\n");
	ITEM(({"wall", "city wall", "great wall"}), "The city wall of "
	+ "Palanthas towers high above to your east.  It is faced with "
	+ "large block panels of polished, translucent marble.\n");
	ITEM(({"estates", "estate", "noble estate", "noble estates"}),
	  "To the north and south along Nobil Row can be seen some of the "
	+ "larger, great noble estates among the other marble buildings.\n");

	EXIT(NOBLE + "n16", "north", 0, 0);
	EXIT(NOBLE + "w08", "east", 0, 0);
	EXIT(NOBLE + "n14", "south", 0, 0);

}
