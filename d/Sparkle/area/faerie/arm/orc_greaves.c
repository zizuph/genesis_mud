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
    
    set_name("greaves");
    set_adj("heavy");
    set_adj("iron");
    add_name("pair of heavy iron greaves");
    set_pname("pairs of heavy iron greaves");
    set_pname("pairs of heavy iron greaveses");
    set_short("pair of heavy iron greaves");
    set_pshort("pairs of heavy iron greaves");
    set_pshort("pairs of heavy iron greaveses");

    set_long("These are a pair of heavy iron greaves. They are forged from iron plates and riveted together. The armour fits over the legs and looks dented from heavy use.\n");
    	
    set_ac(AC);
    set_at( A_LEGS);
    set_am(({ 0, 0, 0 }));
    set_af(TO);

    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 1500);
    
}
