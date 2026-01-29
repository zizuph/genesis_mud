/*
 *
 * blackened breastplate.
 * Nerull, 21/2/09.
 */
 
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../defs.h";

inherit "/std/armour";

void
create_armour()
{
    set_name("breastplate");    
    set_adj("tungsten");
    set_adj("blackened");
    set_short("blackened tungsten breastplate");
    set_long("This blackened tungsten breastplate appears to give extremely " +
    "good protection for the torso.\n");
    set_ac(40);
    set_at(A_BODY);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VALUE, 1650);

}



