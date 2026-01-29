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
    set_name("shirt");
    add_name("burlap shirt");
    set_pname("shirts");
    add_pname("burlap shirts");
    set_adj("old");
    set_adj("burlap");
    set_short("old burlap shirt");
    set_pshort("old burlap shirts");
    set_long(
    	"This is an old burlap shirt. It was once in good shape but " +
        "now is full of holes and looks like it would offer little " +
        "protection.\n");
    	
    set_ac(AC);
    set_at( A_BODY | A_ARMS | A_WAIST);
    set_am(({ 0, 0, 0 }));
    set_af(TO);

    add_prop(OBJ_I_VALUE,  123);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 1000);
    
}
