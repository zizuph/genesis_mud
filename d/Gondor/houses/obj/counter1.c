/*
 * OBJ + counter1.c
 *
 * Varian - Feb 2020
 *
 */

#pragma strict_types
#pragma save_binary 

#include <stdproperties.h>
#include <files.h>
#include "defs.h"

inherit "/std/container";

public void
create_container()

{
    set_adj("narrow");
    add_adj("wooden");
    set_name("counter");
  
    set_long("This narrow wooden counter runs along the " +
        "entire length of the kitchen's eastern wall. " +
        "It has clearly been well used for preparing " +
        "serving food for the household.\n");

    add_prop(CONT_I_VOLUME, 810000);
    add_prop(CONT_I_WEIGHT, 45350);
    add_prop(CONT_I_MAX_VOLUME, 1200000);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(CONT_I_ATTACH, 1);
}
