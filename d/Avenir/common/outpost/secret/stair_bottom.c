#include "outpost.h"
inherit OUTPOST +"/secret/tunnel_base";


void
create_room()
{
    set_short("ledge of the chasm wall");

    set_long("You are on a tiny little ledge dangling over the "+
        "abyss, which glows red-orange below you. High above, "+
        "you see the base of the bridge that "+
        "spans the chasm. You can pick out cracks and gaps in the "+
        "wall that will make it possible for you to work your "+
        "way upward, or you can follow this poor excuse for a "+
        "ledge east. A low grinding sound emanates from "+
        "the lava flowing below, and hot dry winds buffet you, "+
        "making every breath agony.\n");

    add_item(({"handholds","footholds","wall","cracks","gaps"}), 
          "There are gaps and cracks in the chasm wall which "
        + "might allow you work your way up--if you are "
        + "very careful.\n");
    add_item(({"abyss", "down", "lava", "lava flow"}), 
        "You stare down into the fiery abyss. The abyss looks "+
        "back into you.\n"+ VBFC_ME("see_abyss"));

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);

    /* 
     * This will be the master object for the cloned rooms which
     * a player will pass through on the way down.
     */
    link_master("/d/Avenir/common/outpost/stair_link");

    add_exit("tunnel1", "east", 0, 40);
    add_exit("stair_top", "up", -5, 40);
}

/*
 * When you look into the abyss, the abyss may look back
 * into you ;)
 */
string
see_abyss()
{
    TP->add_panic(40);
    say(QCTNAME(TP) + " stares into the abyss.\n");
    return "";
}

/*
 * Function name: link_room
 * Description:   Create a corridor room. Set the descriptions of it.
 *                Does not add exits. This is supposed to be replaced by 
 *                the actual room inheriting this standard room. It is supposed
 *                to set proper descriptions (long and short) instead of
 *                copying the endpoint description. Corridor rooms are
 *		  created when the delay value in the third parameter to
 *		  add_exit() is a negative integer. Length of corridor is
 *		  the absolute value of the delay parameter.
 * Arguments:	  lfile: Suggested filename to clone to get a corridor room.
 *                dest:  The other endpoint of the corridor.
 *		  pos:   The position away from this startpoint
 * Returns:       Objectpointer of the cloned room.
 */
varargs public object
link_room(string lfile, mixed dest, int pos)
{
    object ob;
  
    ob = clone_object("/d/Avenir/common/outpost/secret/stair_link");

    return ob;
}
