/*
 * /d/Gondor/anorien/cairandros/obj/table.c
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
    set_adj("long");
    add_adj("wooden");
    set_name("table");

    set_short("long wooden table");
  
    set_long("This long wooden table has been pushed up " + 
        "against the wall of the barracks. There are plenty " +
        "of foodstains here, suggesting that this is where " +
        "the soldiers eat their meals.\n");
    
    cont_add_object(AN_OBJ_DIR + "dicecup");

    add_prop(CONT_I_VOLUME, 810000);
    add_prop(CONT_I_WEIGHT, 45350);
    add_prop(CONT_I_MAX_VOLUME, 1200000);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(CONT_I_ATTACH, 1);

    reset_object();
}
