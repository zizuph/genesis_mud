/* Mortis 12.2005 

 */

#include "../local.h"
#include CLOCKH

inherit MERCH_BASE;

string
query_to_jail()
{
  return "east";
}

void
reset_palan_room()
{
 
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  The road leads east through the heart of the busy "
	+ "merchants quarter while Old Circle leads curves away north and south "
	+ "along the city wall towering above you to the west.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Merchants' Way and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and coffee borne on a cool, misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Merchants' Way and its buildings "
	+ "gleams in the midday sun as people travel to and from the plaza "
	+ "filling the street with the noisy murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Merchants' Way catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as merchants and shoppers make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent "
	+ "marble of Merchants' Way amplifying the yellow glow of the street "
	+ "lamps.  A few people still make their way about at this hour." + road;
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

    SHORT("On Merchants' Way inside the city gates");
    LONG("@@get_time_desc@@");

	ITEM(({"wall", "city wall", "great wall"}), "The city wall of "
	+ "Palanthas towers high above to the west.  It is faced with "
	+ "large block panels of polished, translucent marble, but atop "
	+ "its crenallated defenses you spot dark grey rock which comprises "
	+ "its core.  The wall is in good repair.\n");

	EXIT(MERCH + "w24", "north", 0, 0);
	EXIT(MERCH + "wr4", "east", 0, 0);
	EXIT(MERCH + "w23", "south", 0, 0);

	gate = clone_object(MERCH + "doors/city_wgate1.c");
	gate->move(TO);

	reset_palan_room();

}
