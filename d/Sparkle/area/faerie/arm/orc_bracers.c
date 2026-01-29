/*
 * Iron greaves for orc lord
 * By Finwe, February 2008
 */

inherit "/std/armour";
#include "defs.h"
#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>

#define AC 25 + random(5)
create_armour()
{
    setuid(); 
    seteuid(getuid());
    
    set_name("bracers");
    set_adj("heavy");
    set_adj("iron");
    add_name("pair of heavy iron bracers");
    set_pname("pairs of heavy iron bracers");
    set_pname("pairs of heavy iron bracers");
    set_short("pair of heavy iron bracers");
    set_pshort("pairs of heavy iron bracers");

    set_long("These are a pair of heavy iron bracers. They are forged from iron plates and riveted together. The armour fits over the bracers and looks dented from heavy use.\n");
    	
    set_ac(AC);
    set_at( A_ARMS);
    set_am(({ 0, 0, 0 }));
    set_af(TO);

    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 1500);
    
}
