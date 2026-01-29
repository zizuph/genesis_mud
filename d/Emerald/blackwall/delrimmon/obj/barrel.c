/*
 *  /d/Emerald/blackwall/delrimmon/obj/cask.c
 *
 *  This cask is somewhat out of view in a dank store room in
 *  the ancient system of caves created by the Elves under
 *  the supervision of Formandil in the Blackwall Mountains. It may just
 *  contain some ancient antique.
 *
 *  Copyright (c) December 1998, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
inherit "/std/receptacle";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void  create_receptacle();
public void  fill_cask();

/*
 * function name:        create_receptacle
 * description  :        set up the cask
 */
public void
create_receptacle()
{
    set_name("cask");
    add_adj( ({"sturdy"}) );

    set_short("sturdy cask");
    set_pshort("sturdy casks");
    set_long(BSN("This particularly sturdy looking cask has somehow"
               + " managed to avoid the plunder to which the barrels have"
               + " been subject."));

    add_prop(OBJ_I_WEIGHT, 40000);
    add_prop(OBJ_I_VOLUME, 100000);
    add_prop(CONT_I_MAX_VOLUME, 50000);
    add_prop(CONT_I_MAX_WEIGHT, 75000);
    add_prop(CONT_I_VOLUME,  4500);
    add_prop(CONT_I_WEIGHT,  5000);
    add_prop(CONT_I_RIGID,      1);
    add_prop(CONT_I_TRANSP,     0);
    add_prop(OBJ_M_NO_GET, "The sturdy cask is far too large to pick"
                         + " up.\n");

    set_no_show_composite(1);

    FIX_EUID

    fill_cask();

    add_prop(CONT_I_CLOSED, 1);  /* we fill it first, then close it */
} /* create_container */

/*
 * function name:        fill_cask
 * description  :        fill the cask with something interesting
 */
public void
fill_cask()
{
    object   sword,
             shovel;

    if (!(sword = present("_del_rimmon_antique_sword", this_object())))
    {
        sword = clone_object(DELRIMMON_DIR + "obj/wep/antique_sword");
        sword->move(this_object(), 1);
    }

    if (!(shovel = present("shovel", this_object())))
    {
        shovel = clone_object(DELRIMMON_DIR + "obj/shovel");
        shovel->move(this_object(), 1);
    }
} /* fill_cask */
