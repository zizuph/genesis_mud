#include "local.h"
inherit TDIR+"eplain_base";

#define LIVE_I_CAN_FISH      "_live_i_can_fish"

public void
create_eplains_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(LIVE_I_CAN_FISH, "freshwater");

    set_special_short("On the bank of the Vingaard River");
    set_short("On the bank of the Vingaard River");

    set_long("You are standing on the shore of " +
		"a great river, uncrossable at this place. " +
		"From the river southeastwards, the plains of Solamnia stretch " +
		"out as far as you can see. To the east, far in the distance, " +
		"something dark and menacing rises on the horizon.\n");

    add_item(({"river","shore","water"}),
		"The shore is down at the bottom a small cliff, " +
		"and you can't see any way to reach the water " +
		"from here.\n");
    add_item(({ "horizon", "dark", "something dark" }),
		"Squinting, you make out the dark and menacing form " +
		"of the Dargaard Mountains far over to the east.\n");

    add_std_exits();

    herbs = HERB_MASTER->query_herbs( ({ "shore", }) );
}

/* Function name: query_map_fatigue
 * Description:	  Return fatigue value for leaving this room for this_player()
 *		  Redefine it in ROOM base file.
 * Returns:	  int fatigue value
 */
public int
query_map_fatigue()
{
    return 4;
}
