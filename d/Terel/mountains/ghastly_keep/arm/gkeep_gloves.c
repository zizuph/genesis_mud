/*
 * /d/Terel/mountains/ghastly_keep/arm/gkeep_gloves.c
 *
 * Gloves.
 *
 *  Created by Znagsnuf.
 *
 *  Date:                      What is done:                           By whom:            
 *  ---------------------------------------------------------------------------
 *  20/04-17                   Language tweak complete                  Gorboth
 *  28/04-17                   Fixed a bug                             Znagsnuf 
 */

inherit "/std/armour";

#include "defs.h";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
 
void
create_armour()
{
    set_name("gloves");
    set_adj( ({"sheer", "gossamer"}) );
    set_short("sheer gossamer gloves");
    set_long("These gloves are made from the very finest type "
    	    +"of thread - spider's silk.\n");

    set_default_armour(10, A_HANDS, 0, TO);

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10)
                        + random(100) + 100);
}