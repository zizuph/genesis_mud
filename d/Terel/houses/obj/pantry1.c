/*
 * OBJ + pantry1.c
 *
 * Varian - Feb 2020
 *
 */

#pragma strict_types
#pragma save_binary 

inherit "/std/receptacle";

#include <stdproperties.h>
#include <files.h>
#include "../defs.h"
#include "contobjs.c"

public void
create_receptacle()
{
    set_adj("wide");
    add_adj("pine");
    set_name("pantry");
  
    set_long("This pantry has is mde of the same pine wood as the " +
        "rest of the house. It is built into the southwest corner "+
        "of the kitchen.\n");

    cont_add_object(HOBJ + "nuts", 20);
    cont_add_object(HOBJ + "wine", 20);

    add_prop(CONT_I_VOLUME, 81000);
    add_prop(CONT_I_WEIGHT, 4535);
    add_prop(CONT_I_MAX_VOLUME, 120000);
    add_prop(CONT_I_MAX_WEIGHT, 10000);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(OBJ_M_NO_GET, 1);

    set_no_show_composite(1);
}