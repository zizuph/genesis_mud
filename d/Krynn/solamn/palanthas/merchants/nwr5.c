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

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  The great white tower of the palatial plaza is still "
	+ "visible to the southeast from this intersection.  Palanthas Circle "
	+ "curves southwest into the heart of the merchant quarter and to the "
	+ "northeast leads to the shipping quarter.  Horizon road leads "
	+ "northwest towards the city gates between a pair of short, white "
	+ "towers, one to the west and one north.\n";
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
    SHORT("On Horizon road at the intersection of Palanthas Circle");
    LONG("@@get_time_desc@@");

	ITEM(({"gate", "gates", "northwestern gate", "northwest gates",
		   "nw gate", "nw gates", "northwest gate", "northwest gates"}),
	  "A large metal gate.\n");
	ITEM(({"short tower", "short marble tower", "marble tower"}), "A tower "
	+ "of translucent, white marble rises at least forty feet into the air "
	+ "to the west and another to the north, higher than all of the "
	+ "buildings in this section of the merchant quarter.\n");

	EXIT(SHIP + "s05", "northeast", 0, 0);
	EXIT(MERCH + "nwr4", "southeast", 0, 0);
	EXIT(MERCH + "m01", "southwest", 0, 0);
	EXIT(MERCH + "nwr6", "northwest", 0, 0);

}