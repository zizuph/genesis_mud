/*
 * /d/Kalad/common/guilds/new_thanar/arm/pleggings.c
 *
 * Leg armour used by Moderate Priests in Thanar Cathedral
 * Coded by Mirandus
 */
#pragma strict_types
inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../local.h"

#define ADJ1 ({"sturdy","well-made"})
#define ADJ2 ({"iron","steel"})

/*
 * Function name: create_armour()
 * Description  : Constructor, redefine this to configure your armour
 */
void
create_armour()
{
    string adj1 = one_of_list(ADJ1);
    string adj2 = one_of_list(ADJ2);
    
    set_name(({"leggings"}));
    set_adj(adj1);
    add_adj(adj2);
    set_short(adj1 + " " + adj2 + " leggings");
    set_long("A pair of "+adj1+" "+adj2+ " leggings. "
    +"Incredibly well designed and made. It is obvious that the wearer "
    +"of these has money. They are emblazoned with a black snake indicating "
    +"they are worn by the warrior class of priests within the Thanarian "
    +"order.\n");
    set_default_armour(35, A_LEGS, 0, this_object());
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE, 500+random(1000));
    
    
}

