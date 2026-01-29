/*
 * /d/Raumdor/common/beach/bountiful/obj/bountiful.c
 *
 * The Bountiful. Ship object.
 *
 * Nerull 2021
*/

inherit "/std/object";
#include "../../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <filter_funs.h>


/*
 * Function name: create_object()
 * Description  : Constructor. Creates the object.
 */
void
create_object()
{
    set_name("frigate");
    add_name("bountiful");
    add_name("_bountiful_true");
    add_name("ship");
    set_adj("three");
    add_adj("masted");
    set_long("This Frigate is quite large. Having three masts "
    +"adorned with black sails makes you wonder if this is a pirate "
    +"ship. But it isn't the odd colour of the masts that draws "
    +"your eye, it is the massive opulent sterncastle. This sterncastle "
    +"overhangs the sides of the frigate by at least eight feet on each "
    +"side and all the wood work is enchanced by white ivory inlays and "
    +"solid gold trim. There are also bars upon all the sterncastle "
    +"windows making you wonder if it is for visiting or never "
    +"leaving. The frigate is at a very short distance from the beach, and "
    +"you notice the gangway is lowered into the water.\n");

    add_prop(CONT_I_RIGID,  1);
    add_prop(OBJ_M_NO_GET, "Ehm...no.\n");
    add_prop(OBJ_M_NO_STEAL, "Ehm...no.\n");

}


/*
 * Function name: enter_ship()
 * Description  : Determines if possible to enter the ship.
 */
int
enter_ship(string str)
{
    if (!str)
    {
        return 0;
    }

	if (str == "ship" || str == "bountiful" || str == "frigate")
    {
        write("You swim out in the sea and enter the lowered gangway of the three masted frigate.\n");

        tell_room(BEACH_DIR + "bountiful/bounty_gangway", QCNAME(this_player())
        +" enters from the sea.\n", this_player());

        tell_room(environment(this_object()), QCTNAME(this_player())
        + " swims out in the sea and enters the lowered gangway of the three masted frigate.\n", this_player());

        this_player()->move_living("M", BEACH_DIR + "bountiful/bounty_gangway", 1);

        return 1;
    }

    return 0;
}


/*
* Function name: init()
* Description  : Enables the commands when a mortal enters.
*/
void init()
{
    ::init();
    add_action(enter_ship, "enter");
    add_action(enter_ship, "board");
}
