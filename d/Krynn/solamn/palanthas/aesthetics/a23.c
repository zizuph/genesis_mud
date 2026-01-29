/* Mortis 11.2005
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit MONKS_BASE;

string
query_to_jail()
{
  return "southeast";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Through a couple buildings to the north can be seen "
	+ "a water spraying fountain above the tops of green bushes.  Muest "
	+ "street curves west through a somewhat dense area of shops, homes, "
	+ "and buildings and southeast towards Old Circle and the city wall.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The worn marble of Muest street and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and " + one_of_list(({"tea", "coffee"})) + " borne on a cool, "
	+ "misty breeze." + road;
	break;

    case TOD_DAY:
	desc += "The worn marble of Muest street and its buildings lights up "
	+ "in the midday sun as people and maroon robed aesthetics travel "
	+ "throughout the Aesthetics quarter filling the street with the "
	+ "murmurings of their daily business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The worn marble of Muest street catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as travellers and maroon robed aesthetics make their way about the "
	+ "street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Muest street amplifying the yellow glow of the street lamps.  "
	+ "A few people and maroon robed aesthetics still make their way about at "
	+ "this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void
create_palan_room()
{
    SHORT("On Muest street in the southeast of the city near the city wall");
    LONG("@@get_time_desc@@");

	ITEM(({"wall", "city wall", "great wall"}), "The city wall of "
	+ "Palanthas towers high above to the southeast.\n");
	ITEM("fountain", "To the north through a few buildings you see the top "
	+ "of a water spraying fountain above low, green bushes.\n");
	ITEM(({"bush", "bushes"}), "Low, green bushes surround a grassy area "
	+ "with a fountain to your north.\n");
	
	EXIT(MONKS + "a24", "west", 0, 0);
	EXIT(MONKS + "w12", "southeast", 0, 0);

}
