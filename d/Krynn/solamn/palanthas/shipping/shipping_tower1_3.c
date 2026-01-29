/* Mortis 12.2005 
 * Smells of what's below and streets?
 * Get msgs of people travelling by.
 * Make sure <view dir> returns contents of room, too.
 * -This could be a great feature for a lot of rooms,
 *  but in particular all the T's.
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>

inherit SHIP_BASE;

#define VIEWWEST			(MERCH + "nwr7")
#define VIEWSE				(SHIP + "s05")

string
query_to_jail()
{
  return "down";
}

object cmdr;

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "Wide, polished oak floorboards run flat against the "
	+ "curved, translucent white marble of this perfectly circular rooftop "
	+ "of a Palanthas guard tower.  Translucent white marble forms a low, "
	+ "crenellated wall overlooking the streets below.  The tower is taller "
	+ "than nearly any building in this part of the city providing a good "
	+ "view.  Down below, ";
	  // ...continued in TIMEOFDAY description.
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += road + "the clean marble of Palanthas Circle and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains.  The air is rich with the smells of wood, tar, and coffee "
	+ "borne on a cool, misty breeze from the bay.\n";
	break;

    case TOD_DAY:
	desc += road + "the well-worn marble of Palanthas Circle and its "
	+ "buildings gleams in the midday sun as people travel to and from "
	+ "the piers filling the street with the noisy murmurings of their "
	+ "daily business.  A cool, salty breeze blows south off the bay.\n";
	break;

    case TOD_TWILIGHT:
	desc += road + "the translucent marble of Palanthas Circle catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as travellers, sailors, and dockhands make their way about the "
	+ "street.  A misty, salty breeze blows south off the bay.\n";
    break;

    case TOD_NIGHT:
	desc += road + "the moon and stars shed pale light across the "
	+ "translucent marble of Palanthas Circle amplifying the yellow glow "
	+ "of the street lamps.  A few dock workers still make their way about "
	+ "at this hour.  A cool, salty breeze blows south off the bay.\n";
    break;

    default:
	break;
    }
    return desc;
}

void
reset_palan_room()
{
	if (!cmdr)
		cmdr = clone_object(LIV + "city_guard_cmdr");
		cmdr->move(TO);
}

void
create_palan_room()
{
	object trapdoor;

    SHORT("The outdoor top floor of a Palanthas guard tower");
    LONG("@@get_time_desc@@");

	ITEM(({"short tower", "short marble tower", "marble tower"}), "You're "
	+ "atop a tower of translucent, white marble rising at least forty "
	+ "feet into the air.  Why not have a <look> around?\n");
	ITEM(({"floor", "floorboard", "floorboards"}), "The floor must be "
	+ "heavily reinforced and the oak floorboards exceptionally sturdy for "
	+ "there is neither give nor creak when trod upon.  The floorboards are "
	+ "long, wide, and of smoothly polished oak.\n");	
	ITEM(({"wall", "walls"}), "Built entirely of large, translucent white "
	+ "marble blocks, the walls are at least two feet thick and polished to "
	+ "a reflective shine.  They are low and crenellated.\n");
	ITEM("view", "From atop this guard tower you are afforded a good view of "
	+ "the city, the shipping quarter in particular.  North you can see over "
	+ "and past the buildings to the docks where ships arrive in the bay at "
	+ "the piers.  East along Palanthas Circle are tons of warehouses and a "
	+ "pair of great estates.  To the south, the shops, woods, and Tower of "
	+ "Arms can be seen.  You can also <view west> to peer down at the city "
	+ "gates on Horizon road and <view southeast> to see what's just outside "
	+ "the tower.\n");

	CMD(({"west", "w"}), "view", "@@view_west");
	CMD(({"southeast", "se"}), "view", "@@view_southeast");

	trapdoor = clone_object(SHIP + "doors/tower1_3_trapdoor");
	trapdoor->move(TO);

	reset_palan_room();
}

view_west()
{
	//This function returns 'look' from the NW city gates.
	/* This function returns an equivalent of 'look' from nwr7
	 * most importantly without any supporting code from the
	 * target room.
	 */

	object *inv, *obs, *ppl, target;
    string desc;

	write(VIEWWEST->long());
	target = find_object(VIEWWEST);
	inv = all_inventory(target);
	obs = FILTER_SHOWN(FILTER_DEAD(inv));
	ppl = FILTER_LIVE(inv);

	if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
	write(one_of_list(({"From above you can make out ",
						"You believe you spot ",
						"Your eyes come across "}))
						+ desc + " on the ground.\n");

	if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
	write(one_of_list(({"Down below you see ",
						"You notice below ",
						"Down below you spy "}))
						+ desc + " outside the tower.\n");
 
	return 1;
}

view_southeast()
{
	/* This function returns an equivalent of 'look' from s05
	 * most importantly without any supporting code from the
	 * target room.
	 */

	object *inv, *obs, *ppl, target;
    string desc;

	write(VIEWSE->long());
	target = find_object(VIEWSE);
	inv = all_inventory(target);
	obs = FILTER_SHOWN(FILTER_DEAD(inv));
	ppl = FILTER_LIVE(inv);

	if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
	write(one_of_list(({"From above you can make out ",
						"You believe you spot ",
						"Your eyes come across "}))
						+ desc + " on the ground.\n");

	if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
	write(one_of_list(({"Down below you see ",
						"You notice below ",
						"Down below you spy "}))
						+ desc + " outside the tower.\n");
 
	return 1;
}
