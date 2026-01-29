/*
 * A scribe's robe.
 * Raymundo, Feb 2020
 */

#include "/d/Shire/sys/defs.h"
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/armour";
inherit "/lib/keep";

#define AC  1

create_armour() 
{
    set_name("robe");
	
	add_name("armour");
    
    add_adj(({"brown","scratchy"}));
    set_short("scratchy brown robe");
   
    set_long("This scratchy brown robe is made of low-quality wool. "
		+ "It's hard to tell if it was dyed brown or if it's just that "
		+ "dirty. About the only nice thing you can say about this robe "
		+ "is that it would keep you warm if you were sitting in a dark "
		+ "basement scribing parchments all day.\n");
    set_default_armour(AC,A_BACK ,({0,0,0}),0);
    
    set_ac(AC);

    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,1000);
    add_prop(OBJ_I_VALUE,10);
    set_keep(0);
}


string query_recover()
{
    return MASTER + ":" + query_arm_recover();
}


void init_recover(string arg)
{
    init_arm_recover(arg);
}
