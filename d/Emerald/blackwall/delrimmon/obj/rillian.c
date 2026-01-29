/*
 *  /d/Emerald/blackwall/delrimmon/obj/rillian.c
 *
 *  This is the long-dead body of Rillian, the elvish mage and scientist
 *  who hoped to make a name for himself by discovering the secrets of
 *  Del Rimmon. Misfortune befell him, and he lies where he died in
 *  the Northwestern Outpost after the earthquake rocked the region.
 *
 *  Copyright (c) 1996 (?) by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/container";

#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"


/* prototypes */
public void    create_container();
public void    reset_container();


/*
 * Function name:        create_container
 * Description  :        set up the corpse
 */
public void
create_container()
{
    set_name("corpse");
    add_name("body");
    add_name("corpse_of_rillian");
    add_adj(({"skeletal", "human",}));
    set_short("skeletal elven corpse");
    set_long(BSN(
        "Covered with dust and cobwebs, this appears to be the corpse"
      + " of a long-dead elven male, lying face down upon the"
      + " chamber floor. The flesh upon the face and hands has"
      + " shriveled and hardened with age, and now clings to the"
      + " bones like dried leather."));

    add_item( ({ "rillian", "corpse of rillian", "rillians corpse",
                 "rillian's corpse" }), BSN(
        "The look of this long dead man is rather grim. However,"
      + " it does not appear as if he died due to any sort of"
      + " violence."));

    add_prop(CONT_I_WEIGHT, 22000);
    add_prop(CONT_I_MAX_WEIGHT, 26000);
    add_prop(CONT_I_VOLUME, 23000);
    add_prop(CONT_I_MAX_VOLUME, 30000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "Trying to lift the corpse would only"
                         + " destroy it.\n");

    FIX_EUID

    reset_container();
}

/*
 * Function name:        reset_container
 * Description  :        put things back into the corpse, if they
 *                       have been taken
 */
public void
reset_container()
{
    object  torch;

    if (!present("del_rimmon_quest_journal", TO))
    {
        clone_object(DELRIMMON_DIR + "obj/journal")->move(TO);
    }

    if (!present("torch", TO))
    {
        torch = clone_object(DELRIMMON_DIR + "obj/rillian_torch");
        torch->burned_out();
        torch->move(TO);
    }
} /* reset_container */
