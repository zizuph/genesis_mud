/*
 * /d/Gondor/mordor/obj/treasure_chest.c
 *
 * It is a treasure chest. You can find it in the hidden room in the tower at
 * Cirith Ungol.
 *
 * /Mercade, 28 November 1993
 *
 * Revision history:
 */
#pragma strict_types

inherit "/std/receptacle.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

/*
 * Called to create the chest.
 */
void
create_container()
{
    set_name("chest");
    add_name("_treasure_chest_at_cirith_ungol_");
    set_pname("chests");
    set_short("ornamented treasure chest");
    set_pshort("ornamented treasure chests");
    set_adj("wooden");
    set_adj("magnificent");
    set_adj("ornamented");
    set_adj("treasure");
    set_long(BSN("It is a magnificent ornamented treasure chest. This chest " +
        "itself is probably also a treasure of the orcs that stole it on " +
        "one of their plunderings. The ornamtented chest is made of wood " +
        "secured with several iron bands."));

    add_item( ({ "band", "bands", "iron band", "iron bands" }),
        BSN("Several iron bands are fastened to the chest to make it " +
        "stronger than it already is."));
    add_item( ({ "ornament", "ornaments" }),
        BSN("The ornaments on the treasure chest look like they were not " +
        "made by the orcs that dwell in this tower. It are very nice " +
        "ornaments, carved in the wood by skilled masters."));
    add_item( ({ "lock" }),
        BSN("It is an iron lock."));

    /* You will have to pick the lock in order to get the contents. */
    set_key("_no_key_should_fit_this_treasure_chest_at_cirith_ungol_");
    set_pick(40);

    set_cf(TO);

    add_prop(CONT_M_NO_REM, "@@can_approach_container");
    add_prop(CONT_M_NO_INS, "@@can_approach_container");
    add_prop(OBJ_M_NO_GET,
        BSN("You cannot take the chest, it must be bolted to the floor."));
    add_prop(CONT_I_WEIGHT,      40000);
    add_prop(CONT_I_VOLUME,      20000);
    add_prop(CONT_I_MAX_WEIGHT, 140000);
    add_prop(CONT_I_MAX_VOLUME, 120000);
    add_prop(CONT_I_RIGID,           1);
    add_prop(OBJ_I_VALUE, 150 + random(50));
    add_prop(CONT_I_CLOSED,          1);
    add_prop(CONT_I_LOCK,            1);
}

/*
 * Open/close/lock/unlock/pick protection: are there any orcs present.
 */
int
open()
{
    object orc = (object)ENV(TP)->query_living_orc();

    if (((ENV(TO)) == (ENV(TP))) && (objectp(orc)))
    {
        write(BSN("The " + check_call(orc->short()) + " stops you from " +
            "touching the " + short() + "."));
        return 1;
    }

    return 0;
}

/*
 * It is not my custom to write functions like these, but otherwize they would
 * take a lot of space without any use.
 */
int close()  { return open(); }
int lock()   { return open(); }
int unlock() { return open(); }
int pick()   { return open(); }

/*
 * This procedure will refrain people from inserting stuff into the container
 * or remove stuff from it if there is an orc present in the room.
 */
mixed
can_approach_container()
{
    object orc = (object)ENV(TP)->query_living_orc();

    if (((ENV(TO)) == (ENV(TP))) && (objectp(orc)))
    {
        return BSN("The " + check_call(orc->short()) + " stops you from " +
            "touching the " + short() + ".");
    }

    return 0;
}

/*
 * Stuff for recovery.. . Though it is impossible to recover this chest for
 * you cannot get it, I added it for later use.
 */
string query_recover()
{
    return MASTER + ":" + query_container_recover();
}

void
init_recover(string arg)
{
    init_container_recover(arg);
}
