/*
 * /d/Kalad/common/wild/lizard_area/arm/lcloak.c
 *
 * Cloak for the Lizard Folks
 * Coded by Mirandus - 02/22
 */
#pragma strict_types
inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>


#define ADJ1 ({"woven", "hand-made"})
#define ADJ2 ({"wool","scale"})

void
create_armour()
{
	
	string adj1 = one_of_list(ADJ1);
	string adj2 = one_of_list(ADJ2);
	
    set_name("cloak");
    set_adj(adj1);
    add_adj(adj2);
    set_short(adj1 + " " + adj2 + " cloak");
    set_long("This is "+LANG_ASHORT(this_object())+". Made by hand "
	  +"to be strong and protective, it appears to have spent a long time "
   	+"underground.\n");
    set_default_armour(8, A_ROBE, 0, this_object());
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(8));
    add_prop(OBJ_I_WEIGHT,  1000);
    add_prop(OBJ_I_VOLUME,  250);
    
    
}

