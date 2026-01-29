/* Mortis 12.2005
 * Smells
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

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
	string road = "  Palanthas Circle curves north towards Horizon road "
	+ "and south past the southwest shopping district.  To the east is a "
	+ "thick wood from which rises a squat, square tower of marble.  Three "
	+ "long flights of marble steps climb southeast up a short hill to a "
	+ "marble road leading east into the wood.  Green Marble road leads "
	+ "west from this intersection towards several shops.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The clean marble of Palanthas Circle and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and coffee borne on a cool, misty breeze." + road;
	break;

    case TOD_DAY:
	desc += "The worn marble of Palanthas Circle and its buildings lights up "
	+ "in the midday sun as travellers, merchants, and shoppers travel "
	+ "throughout the Merchant quarter filling the street with the noisy "
	+ "murmurings of their daily business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Palanthas Circle catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as travellers and merchants make their way about the "
	+ "street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Palanthas Circle amplifying the yellow glow of the street lamps.  "
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
    SHORT("On Palanthas Circle between a shopping district and a thick "
	+ "wood");
    LONG("@@get_time_desc@@");

	ITEM(({"wood", "woods", "north wood", "north woods", "thick wood",
		   "thick woods"}), "A thick wood of trees stands to your east.  "
	+ "They are the Gallant Field Woods and home to the constabulary of "
	+ "Palanthas, the Palanthian Guard.  Their Tower of Arms rises from "
	+ "the vast field at its center.\n");
	ITEM(({"green marble road", "green road", "green marble"}),
	  "The marble blocks of Green Marble road are indeed imbued with a "
	+ "tinge of light, mossy green!  There is no road like it in all the "
	+ "city.  How is it these blocks alone are tinted green?  How did it "
	+ "come to be?  Who would know such a thing?\n");

	EXIT(MERCH + "m01", "north", 0, 0);
	EXIT(MERCH + "m05", "southeast", 0, 0);
	EXIT(MERCH + "m06", "south", "@@tell_watchers", 0);
	EXIT(MERCH + "m02", "west", 0, 0);

}

int
tell_watchers()
{
	string walker, hiswalker;
	walker = QTNAME(TP);
	hiswalker = HIS(TP);

	tell_room(MERCH + "m05", "Below you on Palanthas Circle, " + walker
		+ " passes by on " + hiswalker + " way south.\n");
	return 0;
}
