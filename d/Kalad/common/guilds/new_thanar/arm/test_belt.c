/*
 * /d/Kalad/common/guilds/new_thanar/arm/belt.c
 * Test belt that modifies the AC based on a calculation in a
 * new standard armour file.
 * 
 * Coded by Mirandus 
 */
#pragma strict_types

#include "../local.h"
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
inherit STDIR + "thanar_armour_std";

#define ADJ1 ({"extravagant","pristine"})
#define ADJ2 ({"silk","linen"})

void
create_armour()
{
	string adj1 = one_of_list(ADJ1);
	string adj2 = one_of_list(ADJ2);
	
    set_name("belt");
    set_adj(adj1);
    add_adj(adj2);
    set_short(adj1 + " " + adj2 + " belt");
    set_long("A "+LANG_ASHORT(this_object())+ ". It appears to be made of "
    +"an odd material. While more like silk, or linen, it feels very sturdy "
    +"and durable.\n");
    set_default_armour(30, A_WAIST, 3, 0);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 100);
    
    
}

