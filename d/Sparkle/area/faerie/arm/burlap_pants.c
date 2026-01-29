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

#define AC 3
create_armour()
{
    int cc = ((AC*AC) /3) + (AC*7) + 20;
    set_name("pants");
    add_name("pair of pants");
    set_name("burlap pants");
    set_pname("pairs of pants");
    set_adj("old");
    set_adj("burlap");
    set_short("pair of old burlap pants");
    set_pshort("pairs of old burlap pants");
    set_long(
    	"These are a pair of old burlap pants. They look like they were " +
        "once in good shape, but now have several holes in them, and " +
        "look like they wouldn't offer much protection when worn.\n");
    	
    set_ac(AC);
    set_at( A_LEGS | A_WAIST);
    set_am(({ 0, 0, 0 }));
    set_af(TO);

    add_prop(OBJ_I_VALUE, 123);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 1000);
    
}
