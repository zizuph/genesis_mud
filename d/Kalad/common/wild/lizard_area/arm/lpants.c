/*
 * /d/Kalad/common/wild/lizard_area/arm/lpants.c
 *
 * Pants used by Lizard Folks
 * Coded by Mirandus 02/22
 */
#pragma strict_types
inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#define ADJ1 ({"simple","functional"})
#define ADJ2 ({"wool","linen"})

void
create_armour()
{
	string adj1 = one_of_list(ADJ1);
	string adj2 = one_of_list(ADJ2);
	
    set_name("pants");
    set_adj(adj1);
    add_adj(adj2);
    set_short(adj1 + " " + adj2 + " pants");
    set_long("A pair of "+LANG_ASHORT(this_object())+ ". Hand made and "
	  +"functional. They appear to have been underground.\n");
    set_default_armour(15, A_LEGS, 0, this_object());
    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 200);
    
    
}

