/*
 * hardened leather bracers for skeletons
 * By Finwe, August 2004
 */

inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>

#define AC 5
create_armour()
{
    set_name("bracers");
    add_name("pair of bracers");
    set_name("leather bracers");
    set_pname("pairs of bracers");
    set_adj("hardened");
    set_adj("leather");
    set_short("pair of hardened leather bracers");
    set_pshort("pairs of hardened leather bracers");
    set_long(
    	"These are " + short() + ". They look old and worn. When worn, " +
        "they look like they'd offer some protection to the legs\n");
    	
    set_ac(AC);
    set_at( A_ARMS );
    set_am(({ 0, 1, -1 }));
    set_af(TO);

    add_prop(OBJ_I_VALUE,  200);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 4000);
    
}
