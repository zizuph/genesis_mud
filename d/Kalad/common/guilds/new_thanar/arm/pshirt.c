/*
 * /d/Kalad/common/guilds/new_thanar/arm/pshirt.c
 *
 * Shirt used by Zombie Citizens of Il Aluk
 * Coded by Mirandus with help from Mercade
 */
#pragma strict_types
inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>


#define ADJ1 ({"crimson", "black"})
#define ADJ2 ({"silk","wool"})

void
create_armour()
{
    
    string adj1 = one_of_list(ADJ1);
    string adj2 = one_of_list(ADJ2);
    
    set_name(({"shirt","armour",}));
    set_adj(adj1);
    add_adj(adj2);
    set_short(adj1 + " " + adj2 + " shirt");
    set_long("This is "+LANG_ASHORT(this_object())+" shirt. Worn by the "
    +"priests of the Thanarian order.\n");
    set_default_armour(15, A_BODY|A_ARMS, 0, this_object());
    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 200);
    
    
}

