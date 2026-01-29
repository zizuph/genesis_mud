/* /d/Gondor/tharbad/road/r27.c */
#pragma strict_types

inherit "/d/Gondor/common/lib/roads.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define HARD_TO_CLIMB  3 /* how hard is it to negotiate the rubble? */

public int    climb();

public void   
create_roads() 
{
    set_street("old stone road");
    set_where("southeast");
    set_county("Tharbad");
    set_land("Enedwaith");
    set_mountain("Greyflood valley");
    set_vegetation("hanging moss and lichen");
    set_extraline("The old South Road enters the ruins of Tharbad here. "
        + "To both sides of the road are the remains of the city walls "
        + "and the gatehouse that once guarded the entrance into the city. "
        + "Just inside the city, there is a stone statue.");

    add_exit(THARBAD_DIR + "ford/f01", "northwest", climb, 4);
    add_exit(THARBAD_DIR + "road/r26", "southeast", climb, 2);

    add_item(({ "city", "ruin", "ruins", "tharbad", 
                    "ruins of tharbad"}), 
        BSN("The city lies in ruins, and " + Vegetation + " cover the "
            + "tumbled walls and pillars. All the buildings have "
            + "collapsed and are no more than large heaps of hewn "
            + "rock and stone."));
    add_item( ({ "city walls", "city wall", "gate", "city gate", 
                     "city gates", "gates", "gatehouse", }),
        BSN("The city walls fared no better than the rest of the "
            + "city and lie in ruins. Where once the road entered "
            + "the city, there is just a narrow gap between the "
            + "heaps of rubble to both sides of the road."));
    add_item( ({ "road", }), BSN("On the other side of what remains "
        + "of the city walls and the gatehouse, the road is "
        + "half-choked with cracked and broken stone and masonry."));
    add_item(({"statue","stone","obelisk"}), BSN("This is a weathered "
        + "statue of a man with a high winged crown. Beside him are "
        + "two smaller men wearing emblems of the sun and moon.")); 
   
}

/*
 * Function name:climb 
 * Description  : This function is run every time someone tries to climb
 * The returning value decides what will happen to the player.
 * 0 means that the player isn't delayed.
 * 1 means that the player don't move, and that no other exits are tried.
 * 2 and more also stops the player, but the player can still move if 
   * there's another exit in the same dir. 2 is a very good value if you want
   * to make an 'enter mansion' direction.
*/

public int
climb()
{   
    int    diff = random(HARD_TO_CLIMB);

    if (TP->query_skill(SS_CLIMB) < diff)
    {
        TP->reduce_hit_point(diff - TP->query_skill(SS_CLIMB));
        write("You stumble over some unstable rubble.\n");
        say(QCTNAME(TP) + " stumbles.\n");
        return 1;
    }

    write("You climb over the rubble.\n");
    return 0;
}

