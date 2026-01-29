inherit "/d/Emerald/std/clone_handler";

#include "defs.h"

#define TRAVELLER_ID 1

/* Loaded by ... */

public void
do_reset()
{
    reset_room();
    set_alarm(itof(150 + random(300)), 0.0, do_reset);
}

public object
mktrav()
{
    object traveller;

    setuid();
    seteuid(getuid());
    traveller = clone_object(DOCK_NPC_DIR + "traveller");
    traveller->startup();

    return traveller;
}

void
create_clone_handler()
{
    set_default_area("/d/Emerald/docks/");

    add_clone(mktrav, TRAVELLER_ID, 10,
        ({ DOCK_DIR + "pav5", DOCK_DIR + "pav6",
           DOCK_DIR + "pav7", DOCK_DIR + "pav8" }));

    set_excluded_destinations(({ DOCK_DIR + "sea1",
                                 DOCK_DIR + "pav_path_room",
                                 DOCK_DIR + "pavilion_room",
                                 DOCK_DIR + "dock_room", }));

    /* We want a steady stream of travellers, so we want a very fast
     * reset time.  Since enable_reset() doesn't allow us to have a
     * reset as fast as we want, we just disable it and implement our
     * own.
     */
    enable_reset(0);
    do_reset();
}

/* 
 * Function name: clones_needed
 * Description:   This determines how many new clones are required to bring
 *                the total number to the appropriate level.
 * Arguments:     (int) The id of the clones
 * Returns:       The number of new clones required
 */
public int
clones_needed(int id)
{
    int num = ::clones_needed(id);

    if (id == TRAVELLER_ID)
    {
        /* We only want to clone 1 - 4 travellers at a time.  This makes for
         * a slower, steadier release.
         */
        return min(random(3) + 1, num);
    }

    /* We have a fast reset time for the travellers, but we don't want
     * everything to reset so quickly, so we only make new clones one
     * in ten times.
     */
    return (!random(10) ? num : 0);
}
