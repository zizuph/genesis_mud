/*
 * /d/Gondor/anorien/cairandros/obj/rack.c
 *
 * Varian - February, 2020
 *
 */

#pragma strict_types
#pragma save_binary

#include "../../defs.h"
#include <stdproperties.h>
#include <files.h>

inherit "/std/container";

public void
create_container()

{
    set_adj("series of");
    add_adj("wooden");
    set_name("racks");

    set_short("series of wooden racks");
  
    set_long("These wooden racks have been lined up against " +
        "the western wall, clearly designed to hold dozens " +
        "of different weapons and suits of armour in an " +
        "organized fashion.\n");

/*  To add dice at a later time.
    
    cont_add_object(OBJ + "dice");
*/

    add_prop(CONT_I_VOLUME, 810000);
    add_prop(CONT_I_WEIGHT, 45350);
    add_prop(CONT_I_MAX_VOLUME, 1200000);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(CONT_I_ATTACH, 1);
}
