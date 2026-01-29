/*
 * Breastplate for orc lord
 * By Finwe, February 2008
 */

inherit "/std/armour";
#include "defs.h"
#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>

#define AC 35 + random(5)
create_armour()
{
    setuid(); 
    seteuid(getuid());
    
    set_name("breastplate");
    set_adj("iron");
    add_name("iron breastplate");

    set_short("iron breastplate");
    set_long("This is a " + short() + ". It has been hammered from plates of iron and riveted together. Flakes of dried blood encrust the rivets, making the metal darker and more fearsome looking.\n");
    	
    set_ac(AC);
    set_at(A_BODY);
    set_am(({ 0, 1, -1 }));

    set_af(TO);

    add_prop(OBJ_I_VALUE,  250);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 4000);
    
}
