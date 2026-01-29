/*
 * OBJ + table1.c
 *
 * Varian - Feb 2020
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
    set_adj("long");
    add_adj("wooden");
    set_name("table");

    set_short("long wooden table");
  
    set_long("This is a long wooden table crafted from a " +
        "beautiful dark wood, polished from years of frequent " +
        "use. The table is the focal point of the living room, " +
        "sitting in front of a soft brown couch.\n");

    add_prop(CONT_I_VOLUME, 810000);
    add_prop(CONT_I_WEIGHT, 45350);
    add_prop(CONT_I_MAX_VOLUME, 1200000);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(CONT_I_ATTACH, 1);
}
