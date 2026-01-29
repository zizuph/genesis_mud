/*
 * An old woman's anklet.
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
    set_name("anklet");
    add_name("jewlery");
    add_name("armour");
    
    add_adj(({"dainty","gold"}));
    set_short("dainty gold anklet");
   
    set_long("This dainty gold anklet looks well-worn. The links "
		+ "are thin in some places, nearly worn through with use. "
		+ "It bears no inscription, nor any gems, but the wear "
		+ "patterns let you know its owner loved it and wore it "
		+ "often.\n");
    set_default_armour(AC,A_ANY_ANKLE ,({0,0,0}),0);
    
    set_ac(AC);

    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_I_VALUE,100);
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
