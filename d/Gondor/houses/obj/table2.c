/*
 * OBJ + table2.c
 *
 * Varian - Aug 2021
 *
 */

#pragma strict_types
#pragma save_binary 

#include <stdproperties.h>
#include <files.h>

inherit "/std/container";

public void
create_container()

{
    set_adj("low");
    add_adj("brown");
    set_name("table");

    set_short("low brown table");
  
    set_long("This low table has been crafted from a dark " +
        "brown wood which has been finely polished to " +
        "provide a beautiful, luxurious appearance.\n");

    add_prop(CONT_I_MAX_WEIGHT, 15000);
    add_prop(CONT_I_MAX_VOLUME, 15000);
    add_prop(CONT_I_WEIGHT, 10000);
    add_prop(CONT_I_VOLUME, 10000);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(CONT_I_ATTACH, 1);
}
