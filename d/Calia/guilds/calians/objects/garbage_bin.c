/* 
 * Garbage Bin for the Calian Warriors
 *
 * Code copied from the Spirit Circle of Psuchae
 *  
 * Adapted by Petros, January 2015
 */

inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>

#include "defs.h"

public void
create_container()
{
    set_name("bin");
    add_name("can");
    set_adj("crystalline");
    add_adj("garbage");
    set_short("crystalline garbage bin");
    set_long("This crystalline garbage bin is to place broken items and other "+
        "items you do not want in either the weapons rack, armour rack or " +
        "miscellaneous rack.\n"); 

    add_prop(CONT_I_MAX_WEIGHT, 5000000);
    add_prop(CONT_I_MAX_VOLUME, 5000000);
    add_prop(CONT_I_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME, 500000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "The crystalline garbage bin is attached to the floor.\n");
}

