/* Mortis 12.2005 
 * Smells?.  Inn door.
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
	string road = "  Many shops and inns can be found in this quarter.  Over "
	+ "the open doorway of a large shop to the north hangs a thick, brown "
	+ "banner.  To the south is a two-story, marble inn with the symbol of a "
	+ "long, silver dragon hanging from a dark iron rod above its doorway.  "
	+ "The road leads to the city gates to the west.\n";
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
reset_palan_room()
{
	if (!wguard)
	{
		wguard = clone_object(LIV + "city_guard_wander");
		wguard->set_monster_home(MERCH + "wr4");
		wguard->set_restrain_path(MERCH);
		wguard->set_random_move(55);
		wguard->move(TO);
	}
}

void
create_palan_room()
{
	object door;

    SHORT("On Merchants' Way by an inn east of the city gates");
    LONG("@@get_time_desc@@");

	ITEM(({"shop", "north shop", "large shop", "marble shop"}), "A large, "
	+ "two-story shop of clean and polished marble is to your north.  Above "
	+ "its doorway hangs a thick, brown banner upon which is the image of a "
	+ "maroon robe flowing in a breeze.  Below the robe is written in silver "
	+ "leaf, \"Magical Robes of Wisdom\".\n");
	ITEM(({"banner", "thick banner", "brown banner", "thick brown banner"}),
	  "A thick, brown banner in the shape of a shield hangs above the doorway "
	+ "of the shop to the north.  Upon it is the image of a maroon robe "
	+ "flowing in a breeze.  Below the robe is written in silver "
	+ "leaf, \"Magical Robes of Wisdom\".\n");
	ITEM(({"inn", "leiden's", "leidens", "silver dragon inn", "south inn"}),
	  "A two-story marble inn sits beside the road to the south.  Above its "
	+ "open doorway hanging on thin chains from a dark iron rod is the "
	+ "symbol of a long, silver dragon bearing one of its front claws.\n");

	EXIT(MERCH + "robemaker", "north", 0, 0);
	EXIT(MERCH + "wr3", "east", 0, 0);
	EXIT(MERCH + "wr5", "west", 0, 0);

	door = clone_object(MERCH + "doors/wooddoor");
    door->move(TO);

	reset_palan_room();

}
