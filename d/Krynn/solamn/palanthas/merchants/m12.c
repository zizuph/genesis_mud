/* Mortis 12.2005
 */

#include "../local.h"
#include CLOCKH

inherit MERCH_BASE;

string
query_to_jail()
{
  return "south";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Emptoris Row curves continues north into the arms "
	+ "district and to the south curves toward Vingaard road.  A massive, "
	+ "three-story building of marble with a wide, double doored entrance "
	+ "is east.  A pair of grey posts on either side of the marble path "
	+ "leading to it display an arched iron bar sign between them.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The worn marble of Emptoris Row and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and coffee borne on a cool, misty breeze." + road;
	break;

    case TOD_DAY:
	desc += "The worn marble of Emptoris Row and its buildings lights up "
	+ "in the midday sun as travellers, merchants, and shoppers travel "
	+ "throughout the Merchant quarter filling the street with the noisy "
	+ "murmurings of their daily business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Emptoris Row catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as travellers and merchants make their way about the "
	+ "street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Emptoris Row amplifying the yellow glow of the street lamps.  "
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
    SHORT("On Emptoris Row west of a massive, marble building");
    LONG("@@get_time_desc@@");

	ITEM(({"sign", "bars", "iron bars", "iron sign"}), "Arching from a "
	+ "pair of grey lamp posts to either side of a marble walkway to the "
	+ "massive eastern building is a sign made of iron bars that reads, "
	+ "\"Palanthas Auction House\".\n");
	ITEM(({"auction house", "massive building"}), "The building to your "
	+ "east is approached by a walkway of marble over which a sign of "
	+ "iron bars arches.  Built of polished, translucent white marble "
	+ "blocks, the building is three-stories high with a marble dome "
	+ "over its great, round foyer room.  It is busy at all hours with "
	+ "people carrying all manner of items in and out through the wide "
	+ "entrance.\n");
	ITEM(({"path", "walkway", "marble path", "marble walkway"}), "A wide "
	+ "sidewalk of polished, translucent white marble leads from Emptoris "
	+ "Row to the massive, marble building east.\n");

	CMD("sign", "read", "@@read_sign");

	EXIT(MERCH + "m11", "north", 0, 0);
	EXIT(MERCH + "auction", "east", "@@place_closed", 0);
	EXIT(MERCH + "m15", "south", 0, 0);

}

read_sign()
{
	write("Written with iron bars in a simple form of the ancient style, "
	+ "it reads, \"Palanthas Auction House\".\n");
	return 1;
}

int
place_closed()
{
	write("The auction house's permit is under review by the High "
	+ "Bureaumancers.\n");
	return 1;
}