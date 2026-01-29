/*
 * A wolf pelt.
 * Raymundo, March 2020
 */

#include "/d/Shire/sys/defs.h"
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/armour";
inherit "/lib/keep";

#define AC  10

create_armour() 
{
    add_name(({"_waymeet_wolf_pelt", "pelt", "robe"}));
    
    add_adj(({"bloody","grey", "wolf", "armour"}));
    set_short("bloody grey pelt");
   
    set_long("Bloody and untanned, this is a pelt that was recently "
		+ "cut from a grey wolf. There are scraps of meat and fat "
		+ "still clinging to the underside of it, while the fur "
		+ "has clumps of mud and dirt from farmers' fields clinging "
		+ "to it. This is the type of thing a farmer would be happy "
		+ "to have as proof that a wolf was killed.\n");
    set_default_armour(AC,A_ROBE,({0,0,0}),0);
    
    set_ac(AC);
    set_af(TO);
    add_prop(OBJ_I_WEIGHT,2500);
    add_prop(OBJ_I_VOLUME,1000);
    add_prop(OBJ_I_VALUE,100);
    set_keep(1);
}


string query_recover()
{
    return MASTER + ":" + query_arm_recover();
}


void init_recover(string arg)
{
    init_arm_recover(arg);
}
