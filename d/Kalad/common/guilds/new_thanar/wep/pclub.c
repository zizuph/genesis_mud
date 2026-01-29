/*
 * /d/Kalad/common/guilds/new_thanar/wep/pclub.c
 *
 * Club used by Moderate Priests in Thanar Cathedral
 * Coded by Mirandus
 */

inherit "/std/weapon";
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../local.h"

#define ADJ1 ({"glistening","blackened"})
#define ADJ2 ({"magnificent","leather-wrapped"})


/*
 * Function name: create_weapon()
 * Description  : Constructor, redefine this to configure your weapon
 */
void
create_weapon() 
{
    
    string adj1 = one_of_list(ADJ1);
    string adj2 = one_of_list(ADJ2);
    
    set_name(({"club","mace"}));
    set_adj(adj1);
    add_adj(adj2);
    set_short(adj1 + " " + adj2 + " mace");
    set_long("This is "+LANG_ASHORT(this_object())+". It bears the mark "
    +"of the Thanarian order, a black serpent. It has "
    +"been well maintained and looks as though it would hurt. Small metal "
    +"nodules bulge out from a solid steel head. The handle is a strange "
	+"wood wrapped in a black leather. Overall it feels quite well-made and "
	+"incredibly sturdy.\n");
    set_default_weapon(35,35,W_CLUB,W_BLUDGEON,W_NONE,0);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 600);
    add_prop(OBJ_I_VALUE,500+random(1000));
    
}

