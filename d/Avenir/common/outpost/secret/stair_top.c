/* 
 * Back entrance into the Fort. Added when Gate was put in.
 * Lilith, June 2004.
 *
 * Revisions: Lilith Nov 2021: added prop to prevent Source-related messages.
 */
#include "outpost.h"
inherit OUTPOST +"secret/tunnel_base";
#define CONNECTION "/d/Avenir/common/outpost/cv/cv_ledge"

void
create_room()
{
		IN_IN; // not in flux zone.
    set_short("chasm wall");

    set_long("You stand on a ledge of the chasm wall, where the "+
        "base of the bridge that spans the abyss rests against "+
        "the immovable stone. A low grinding sound emanates from "+
        "deep below, and hot dry winds buffet you. Your eyes "+
        "pick out cracks and gaps in the "+
        "wall that might make it possible for you to work your "+
        "way downward.\n");

    add_item(({"handholds","footholds","wall","cracks","gaps"}), 
        "There are gaps and cracks in the chasm wall which "+
        "might allow you work your way down--if you are "+
        "very careful.\n");
    add_item(({"bridge", "underside", "footing", "footings", "base"}),
        "The bridge appears to be sound, and the immense footings "+
        "directly west of you do not appear to be in any danger of "+
        "being dislodged.\n");
    add_item(({"abyss", "down", "lava", "lava flow"}), 
        "You stare down into the fiery abyss. The abyss looks "+
        "back into you.\n"+ VBFC_ME("see_abyss"));
    add_item(({"ledge", "west"}), "The ledge rapidly narrows as "+
        "as it leads west, under the bridge. The ledge supports "+
		"the massive footings which angle into the wall of the "+
		"abyss.\n");
    add_prop(ROOM_I_LIGHT, -1);
    add_prop(ROOM_I_INSIDE, 1);

    /* 
     * This will be the master object for the cloned rooms which
     * a player will pass through on the way down.
     */
    link_master("/d/Avenir/common/outpost/secret/stair_link");

    add_exit("../cave3", "up", 0, 20);
    add_exit("stair_bottom", "down", -5, 50, 1);   // non-obvious
	add_exit(CONNECTION, "west", 0, 1, 1);    // non-obvious

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
