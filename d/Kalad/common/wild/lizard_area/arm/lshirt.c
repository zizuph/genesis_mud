/*
 * /d/Kalad/common/wild/lizard_area/arm/lshirt.c
 *
 * Shirt used by Lizard Folks
 * Coded by Mirandus 02/22
 */
#pragma strict_types
inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>


#define ADJ1 ({"common", "warm"})
#define ADJ2 ({"scale","wool"})

void
create_armour()
{
    
    string adj1 = one_of_list(ADJ1);
    string adj2 = one_of_list(ADJ2);
    
    set_name(({"shirt","armour",}));
    set_adj(adj1);
    add_adj(adj2);
    set_short(adj1 + " " + adj2 + " shirt");
    set_long("This is "+LANG_ASHORT(this_object())+" shirt. It is warm "
    +"and appears to have spent a long time underground.\n");
    set_default_armour(15, A_BODY|A_ARMS, 0, this_object());
    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 200);
    
    
}

