/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * fire.c
 *
 * Used in the zodiac quest.
 */

#include "/d/Terel/include/Terel.h"

inherit "/std/container";

#include "/d/Terel/include/zodiac.h"



/*
 * Function name: create_container
 * Description:   Reset the container (standard)
 */
public void
create_container()
{
    object coal, thisroom;
    int hint;

    FIX_EUID;
    set_name("ashes");
    add_name(({"ash","Zodiac:ash"}));
    add_name("pile");
    set_pname("ashes");
    set_short("pile of ashes");
    set_pshort("pile of ashes");
    set_adj("pile of");
    set_long("This is a pile of cold ashes, probably remainings of a fire.\n");
    add_item("fire", "Maybe the pile of ashes once was a fire, but not " +
             "anymore.\n");
    add_item("light", "The pile of ashes doesn't emit any light.\n");
    add_prop(CONT_I_WEIGHT,1000);
    add_prop(CONT_I_MAX_WEIGHT,1100);
    add_prop(CONT_I_VOLUME,0);
    add_prop(CONT_I_MAX_VOLUME,200);
    add_prop(CONT_I_TRANSP,1);
    add_prop(CONT_I_RIGID,1);
    coal = clone_object(ZODIAC_DIR + "coal");
    coal->move(TO);
    thisroom = find_object(HINT_ROOMS[1]);
    hint = thisroom->query_real_hint();
    coal->set_shape(SIGPR[hint] + SIGEQ[hint]);
}