/*
 * /d/Kalad/common/guilds/new_thanar/arm/pmail.c
 *
 * Chainmail used by Moderate Priests in Thanar Cathedral
 * Coded by Mirandus
 */
#pragma strict_types
inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../local.h"

#define ADJ1 ({"extravagant","pristine"})
#define ADJ2 ({"mithril","platinum"})

/*
 * Function name: create_armour()
 * Description  : Constructor, redefine this to configure your armour
 */
void
create_armour()
{
    string adj1 = one_of_list(ADJ1);
    string adj2 = one_of_list(ADJ2);
    
    set_name("chainmail");
    set_adj(adj1);
    add_adj(adj2);
    set_short(adj1 + " " + adj2 + " chainmail");
    set_long("A "+adj1+" "+adj2+ " chainmail. "
    +"Incredibly well designed and made. It is obvious that the wearer "
    +"of this has money. It are emblazoned with a black snake indicating "
    +"it is worn by the warrior class of priests within the Thanarian "
    +"order.\n");
    set_default_armour(35, A_BODY|A_ARMS, 0, this_object());
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE, 500+random(1000));
    
    
}

