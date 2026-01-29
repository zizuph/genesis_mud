/* Mortis 11.2005
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit NOBLE_BASE;

string
query_to_jail()
{
  return "southwest";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Old Circle runs northeast along the curve of the city "
	+ "wall and southwest to the main city gates on Knight's High road.  The "
	+ "city wall towers above you to the southeast.\n";
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
	+ "gleams in the midday sun as people travel to and from the city gates "
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
    SHORT("On Old Circle northeast of the main city gates in the southeast "
	+ "of the city");
    LONG("@@get_time_desc@@");

	ITEM(({"gate", "gates", "southeastern gate", "southeastern gates",
		   "se gate", "se gates", "southeast gate", "southeast gates",
		   "main gates", "main city gates", "main gate", "main city gate"}),
	  "A large metal gate.\n");
	ITEM(({"wall", "city wall", "great wall"}), "The city wall of "
	+ "Palanthas towers high above to the southeast.  It is faced with "
	+ "large block panels of polished, translucent marble, but atop "
	+ "its crenallated defenses you spot dark grey rock which comprises "
	+ "its core.  The wall is in fair shape.\n");
	ITEM(({"estates", "estate", "noble estate", "noble estates"}),
	  "To the north along Nobil Row can be seen some of the larger, great "
	+ "noble estates among the other marble buildings.\n");
	ITEM(({"nw alley", "northwest alley"}), "An alley winds between the "
	+ "marble buildings to your northwest.\n");

	add_alley("nw", "northwest", NOBLE + "n13");

	EXIT(NOBLE + "w09", "northeast", 0, 0);
	EXIT(NOBLE + "ser7", "southwest", 0, 0);

}
