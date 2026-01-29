/* Mortis 12.2005
 * Alley?
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
	string road = "  Old Circle curves south towards the city gates on "
	+ "Merchants' Way and north along the curve of the city wall.  Green "
	+ "Marble road leads east towards an area thick with shops.  The city "
	+ "wall towers high above to the west.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The clean marble of Old Circle and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and coffee borne on a cool, misty breeze." + road;
	break;

    case TOD_DAY:
	desc += "The clean marble of Old Circle and its buildings lights up "
	+ "in the midday sun as travellers, merchants, and shoppers travel "
	+ "throughout the Merchant quarter filling the street with the noisy "
	+ "murmurings of their daily business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Old Circle catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as travellers and merchants make their way about the "
	+ "street." + road;
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
    SHORT("On Old Circle north of Merchants' Way at the intersection of "
	+ "Green Marble road");
    LONG("@@get_time_desc@@");

	ITEM(({"gate", "gates", "western gate", "west gates",
		   "w gate", "w gates", "west gate", "west gates"}),
	  "A large metal gate.\n");
	ITEM(({"wall", "city wall", "great wall"}), "The city wall of "
	+ "Palanthas towers high above to the west.  It is faced with "
	+ "large block panels of polished, translucent marble, but atop "
	+ "its crenallated defenses you spot the dark grey rock "
	+ "which comprises its core.  The wall is in good shape.\n");
	ITEM(({"green marble road", "green road", "green marble"}),
	  "The marble blocks of Green Marble road are indeed imbued with a "
	+ "tinge of light, mossy green!  There is no road like it in all the "
	+ "city.  How is it these blocks alone are tinted green?  How did it "
	+ "come to be?  Who would know such a thing?\n");

	EXIT(MERCH + "w26", "north", 0, 0);
	EXIT(MERCH + "m02", "east", 0, 0);
	EXIT(MERCH + "w24", "south", 0, 0);

}
