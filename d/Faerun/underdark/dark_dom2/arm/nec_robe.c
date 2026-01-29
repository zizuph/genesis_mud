/* 
 * Originally coded as /d/Kalad/common/wild/pass/arm/mfrobe.c by Antharanos
 * Converted by Finwe for illithids of the Underdark.
 * Changed Abaddon for Necro in the Underdark
 * -- Abaddon, July 2006
 */ 

#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Faerun/defs.h"
#include "defs.h"

inherit FAERUN_ARM_BASE;

void create_faerun_armour()
{
    set_name("robe");
    set_adj("tattered");
    add_adj("dark");
    set_short("tattered dark robe");
    set_long("A long, hooded robe, stained with blood and faded with " +
        "time. The sleeves are long, extending far past the wrists. T" + 
        "he hood is large, likely too large to conceal your identity.\n");
    
    add_item(({"stains", "blood"}),
        "Blood covers the areas around the wrists and waist, as if the " +
        "original owner slaughtered countless creatures while wearing it.\n");

    set_ac(6);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE,1200);
    add_prop(OBJ_I_VOLUME,2500);
    add_prop(OBJ_I_WEIGHT,2500);
}