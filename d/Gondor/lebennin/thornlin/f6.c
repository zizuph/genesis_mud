/*
 * Modified by Alto, 10 June 2001
 *    Added clone of Farmer quest npc
 * Finwe April 2019: Fixed ring quest stage time so it calls rq_stage() 
 *      instead of rq_stage_stored.
 *
 */

#include "/d/Gondor/defs.h"
inherit (THORN_DIR + "out_door_master.c");

#include "locals.h"
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/common/lib/clock.h"

static object *Farmer = allocate(1);
int           rq_stage_stored = rq_stage();


public int
query_igard_broken()
{
//    if (rq_stage_stored < RQ_LEFT_HENNETH_ANNUN)
    if (rq_stage() < RQ_LEFT_HENNETH_ANNUN)
    {
        return 0;
    }

    return 1;
}

void
create_area_room()
{
    set_areatype(3);
    set_areadesc("dry");
    set_whereis("near");
    set_cityname("Thornlin");
    set_crop("barley");
    set_areaname("Lossarnach");
    set_land("Gondor");
    set_extraline("You see the main village southwest of here. A busy road "+
      "leads southwest-east just south of here.");

    add_item("road","You might be able to walk through the field and out "+
      "on the road.\n");
    add_item("village","You see some houses surounded by fields " +
      "and trees.\n");
    add_item(({"tree","trees"}), "You see some tall trees surounding the "+
      "houses.\n");

    add_exit(THORN_DIR + "r5.c","south",0,2);

    reset_room();
}

public void
reset_room()
{
    /* This room was coded incorrectly. It assumes that there will
     * be an Armageddon each day (as there was at the time it was
     * originally coded.) Code should *never* count on a specific
     * time for Armageddon cycle length. What happened, as a
     * result, is that if the Ringquest cycle did not happen to
     * be a the correct stage when the room was first loaded, then
     * the quest would remain unavailable for the duration of the
     * Armageddon uptime, which has (at time of this writing) become
     * more than two weeks. The simple fix is to reclone the npc
     * each room reset, thus performing a fresh check for the
     * Ringquest stage. - Gorboth
     */
    Farmer->remove_object();

    if (!query_igard_broken())
    {
       clone_npcs(Farmer, "/d/Gondor/minas/npc/faradan_noquest", -1.0);
    }

    if (query_igard_broken())
    {
       clone_npcs(Farmer, "/d/Gondor/minas/npc/faradan", -1.0);
    }
}


