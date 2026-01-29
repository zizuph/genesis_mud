/* Mortis 12.2005
 */

#include "../local.h"
#include CLOCKH

inherit MERCH_BASE;

string
query_to_jail()
{
  return "southeast";
}

void
reset_palan_room()
{
 
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  You are inside the northwest gates of Palanthas and "
	+ "the city wall which curves southwest and northeast from here.  A "
	+ "pair of short, white marble towers rise above the buildings, one "
	+ "to the south and one east.  The city wall rises high above you to "
	+ "the northwest.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Horizon road and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and coffee borne on a cool, misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Horizon road and its buildings "
	+ "gleams in the midday sun as people travel about the merchant quarter "
	+ "filling the street with the noisy murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Horizon road catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as merchants and travellers make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Horizon road amplifying the yellow glow of the street lamps.  "
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

    SHORT("On Horizon road inside the northwest city gates");
    LONG("@@get_time_desc@@");

	ITEM(({"short tower", "short marble tower", "marble tower"}), "A tower "
	+ "of translucent, white marble rises at least forty feet into the air "
	+ "to the south and another to the east, higher than all of "
	+ "the buildings in this section of the merchant quarter.\n");
	ITEM(({"wall", "city wall", "great wall"}), "The city wall of "
	+ "Palanthas towers high above to the northwest.  It is faced with "
	+ "large block panels of polished, translucent marble, but atop "
	+ "its crenallated defenses you spot dark grey rock which comprises "
	+ "its core.  The wall is in good repair.\n");

	EXIT(SHIP + "w28", "northeast", 0, 0);
	EXIT(MERCH + "nwr6", "southeast", 0, 0);
	EXIT(MERCH + "w27", "southwest", 0, 0);

	gate = clone_object(MERCH + "doors/city_nwgate1.c");
	gate->move(TO);

	reset_palan_room();

}