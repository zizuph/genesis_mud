/*
 * Burlap shirt for zombies
 * By Finwe, August 2004
 */

inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>

#define AC 5 + random(5)
create_armour()
{
    set_name("pants");
    add_name("pair of pants");
    set_name("leather pants");
    set_pname("pairs of nice leather pants");
    set_adj("nice");
    set_adj("leather");
    set_short("pair of nice leather pants");
    set_pshort("pairs of nice leather pants");
    set_long(
    	"These are a pair of nice leather pants. They look sturdy and " +
        "well worn. They are often worn by travellers and offer some " +
        "protection during battles.\n");
    	
    set_ac(AC);
    set_at( A_LEGS | A_WAIST);
    set_am(({ 0, 0, 0 }));
    set_af(TO);

    add_prop(OBJ_I_VALUE, 123);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 1000);
    
}
