
/* 
 *  Garbage Bin for the Spirit Circle of Psuchae
 *  July 29th, 2003
 */


inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>

#include "defs.h"

void
create_container()
{
    set_name("bin");
    add_name("can");
    set_adj("silver");
    add_adj("garbage");
    set_short("silver garbage bin");
    set_long("This silver garbage bin is to place broken items and other "+
        "items you do not want in either the weapons chest, armour rack or "+
        "on the shelf.\n"); 

    add_prop(CONT_I_MAX_WEIGHT, 5000000);
    add_prop(CONT_I_MAX_VOLUME, 5000000);
    add_prop(CONT_I_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME, 500000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "The silver garbage bin is attached to the floor.\n");
}

