/*
 * /d/Kalad/common/guilds/new_thanar/arm/probe.c
 *
 * Robe for the common priests in Thanar Church
 * Coded by Mirandus - 01/18
 */
#pragma strict_types
inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>


#define ADJ1 ({"black", "crimson"})
#define ADJ2 ({"wool","silk"})

void
create_armour()
{
	
	string adj1 = one_of_list(ADJ1);
	string adj2 = one_of_list(ADJ2);
	
    set_name("robe");
    set_adj(adj1);
    add_adj(adj2);
    set_short(adj1 + " " + adj2 + " robe");
    set_long("This is "+LANG_ASHORT(this_object())+". Woven into the "
	+"fringes of the robe is a subtle white stripe, indicating it belongs "
	+"to a priest.\n");
    set_default_armour(5, A_ROBE, 0, this_object());
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5));
    add_prop(OBJ_I_WEIGHT,  1000);
    add_prop(OBJ_I_VOLUME,  250);
    
    
}

