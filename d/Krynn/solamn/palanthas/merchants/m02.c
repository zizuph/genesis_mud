/* Mortis 12.2005
 * Smells
 * Alleys northward
 */

#include "../local.h"
#include CLOCKH

inherit MERCH_BASE;

object wguard;

string
query_to_jail()
{
  return "east";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Green Marble leads east and west through a district "
	+ "thick with shops and buildings.  A side street leads to a wide, "
	+ "busy court.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The clean marble of Green Marble road and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and coffee borne on a cool, misty breeze." + road;
	break;

    case TOD_DAY:
	desc += "The worn marble of Green Marble road and its buildings lights up "
	+ "in the midday sun as travellers, merchants, and shoppers travel "
	+ "throughout the Merchant quarter filling the street with the noisy "
	+ "murmurings of their daily business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Green Marble road catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as travellers and merchants make their way about the "
	+ "street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Green Marble road amplifying the yellow glow of the street lamps.  "
	+ "A few people still make their way about at this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void
reset_palan_room()
{
	if (!wguard)
	{
		wguard = clone_object(LIV + "city_guard_wander");
		wguard->set_monster_home(MERCH + "m02");
		wguard->set_restrain_path(MERCH);
		wguard->set_random_move(55);
		wguard->move(TO);
	}
}

void
create_palan_room()
{
    SHORT("On Green Marble road in the center of a great deal of shops");
    LONG("@@get_time_desc@@");

	ITEM(({"wood", "woods", "north wood", "north woods", "thick wood",
		   "thick woods"}), "A thick wood of trees stands off to the east.  "
	+ "They are the Gallant Field Woods and home to the constabulary of "
	+ "Palanthas, the Palanthian Guard.  Their Tower of Arms rises from "
	+ "the vast field at its center.\n");
	ITEM(({"green marble road", "green road", "green marble"}),
	  "The marble blocks of Green Marble road are indeed imbued with a "
	+ "tinge of light, mossy green!  There is no road like it in all the "
	+ "city.  How is it these blocks alone are tinted green?  How did it "
	+ "come to be?  Who would know such a thing?\n");
	ITEM("shops", "This district is thick with a variety of shops.\n");

	EXIT(MERCH + "m03", "east", 0, 0);
	EXIT(MERCH + "m04", "south", 0, 0);
	EXIT(MERCH + "w25", "west", 0, 0);

	reset_palan_room();
}
