/*
 * hardened leather breastplate for skeletons
 * By Finwe, August 2004
 */

inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>

#define AC 8
create_armour()
{
    int cc = ((AC*AC) /3) + (AC*7) + 20;
    set_name("breastplate");
    add_name("leather breastplate");
    set_pname("breastplates");
    set_adj("hardened");
    set_adj("leather");
    set_short("hardened leather breastplate");
    set_pshort("hardened leather breastplates");
    set_long("This is a " + short() + ". The leather is hard and protects " +
        "the chest. It looks like it would provide limited protection " +
        "during battles.\n");
    	
    set_ac(AC);
    set_at(A_BODY);
    set_am(({ 0, 1, -1 }));

    set_af(TO);

    add_prop(OBJ_I_VALUE,  250);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 4000);
    
}
