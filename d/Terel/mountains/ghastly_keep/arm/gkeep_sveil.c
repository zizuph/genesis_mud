/*
 * /d/Terel/mountains/ghastly_keep/arm/gkeep_sveil.c
 *
 * Ghastly veil 
 *
 * Znafsnuf
 *
 * - Language tweak complete (Gorboth)
 */

inherit "/std/armour";
 
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include "defs.h";
 
void
create_armour()
{
    set_name("veil");
    set_short("shimmering veil");
    set_long("This transparent-looking veil feels cold to the touch, like "
    	    + "touching arctic air.\n");
    set_ac(15);
    set_am(({ 0, 0, 0 }));
    set_at(A_HEAD);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15)
                        + random(100) + 100);
}