/*
 * /d/Gondor/anorien/cairandros/obj/rtable.c
 *
 * Varian - February, 2020
 *
 */

#pragma strict_types
#pragma save_binary

inherit "/std/container";

#include "../../defs.h"
#include <stdproperties.h>
#include <files.h>
#include "contobjs.c"

public void
create_container()

{
    set_adj("round");
    add_adj("wooden");
    set_name("table");

    set_short("round wooden table");
  
    set_long("This large table is about ten feet in " +
        "diameter, and it made entirely of wood. It " +
        "appears to be well used by the soldiers here, " +
        "and is a little worse for wear.\n");

    cont_add_object(AN_OBJ_DIR + "rope");

    add_prop(CONT_I_VOLUME, 810000);
    add_prop(CONT_I_WEIGHT, 45350);
    add_prop(CONT_I_MAX_VOLUME, 1200000);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(CONT_I_ATTACH, 1);

    reset_object();
}
