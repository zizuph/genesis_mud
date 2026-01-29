/*
 *  /d/Gondor/minas/houses/stable4.c
 *
 *  Stable for the errand-riders of Gondor
 *
 *  Alto, 10 April 2001
 * 
 *  Revision history:
 *    - Fixed quest for modern uptimes (Gorboth, Aug. 2018)
 * Finwe April 2019: Fixed ring quest stage time so it calls rq_stage() 
 *   instead of rq_stage_stored.
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/drink_water.c";


#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/clock.h"

#define INNER_MINAS "/d/Gondor/minas"
//int     rq_stage_stored = rq_stage();

public object    Horse;


public int
query_igard_broken()
{
    if (rq_stage()< RQ_LEFT_HENNETH_ANNUN)
    {
        return 0;
    }

    return 1;
}


public void
create_gondor()
{
    set_short("The stable for the errand-riders of Gondor");
    set_long("This is a relatively large stable with room enough for "
        + "several horses to live comfortably. This is where "
        + "the mounts of the errand-riders are stabled. This is also "
        + "the stable in which the horses of ambassadors and other "
        + "important guests of the Lord of the city are housed. The floor "
        + "is covered "
        + "with deep straw and a window lets in a fresh breeze. Near "
        + "the gate, there is a bin for food and a basin for water.\n");

    add_item(({"stable"}), "This is a place where horses live.\n");
    add_item(({"floor", "straw"}), "The floor is covered by a thick "
        + "layer of fragrant straw. Be careful where you step, though, "
        + "as from the look of things the grooms have yet to clean the "
        + "stable today.\n");
    add_item(({"window"}), "The large square window set into the east "
        + "wall lets in a cool breeze of fresh air. This is not only "
        + "pleasant for the horses that lives here, but also for the "
        + "groomsmen who must work here.\n");
    add_item(({"bin"}), "A large bin from which the resident horses may "
        + "eat. It is presently filled with oats.\n");
    add_item(({"oats"}), "Food for horses. It probably would not taste "
        + "very good to a person.\n");
    add_item(({"basin"}), "A rectangular basin made of stone. It is "
        + "presently half-filled with water. You may drink out of it if "
        + "the horse hair floating on the surface does not quench your "
        + "desire to do so.\n");
    add_item(({"horse hair", "hair"}), "It seems to be everywhere. There is "
        + "a particularly revolting film of it floating in the basin.\n");
    add_item(({"water"}), "The water in the basin does not look especially "
        + "inviting, but you may drink some if you wish.\n");

    set_drink_from("basin");

    add_prop(OBJ_I_CONTAIN_WATER, -1);
    add_prop(ROOM_I_INSIDE, 1);

    clone_object(INNER_MINAS + "/doors/stablegate_e1")->move(TO);

    reset_room();

}

public void
init()
{
    ::init();
    init_drink();
}


/*
 * Function name:        reset_room
 * Description  :        get the horse there if the correct
 *                       stage is happening
 */
public void
reset_room()
{
    ::reset_room();

    if (query_igard_broken())
    {
        if (!objectp(Horse))
        {
            Horse = clone_npc(Horse, INNER_MINAS + "/npc/shadowfax");
            Horse->move(this_object);
        }
        return;
    }

    if (objectp(Horse))
    {     
        tell_room(environment(Horse),
            "The horse gallops suddenly away!\n");
        Horse->remove_object();
    }
} /* reset_room */
