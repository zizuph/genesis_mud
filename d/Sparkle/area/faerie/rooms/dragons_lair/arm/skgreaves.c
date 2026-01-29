/*
 *
 * blackened tungsten greaves.
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
    set_name("greaves");
    add_name("leggings");
    set_adj("tungsten");
    set_adj("blackened");
    set_short("pair of blackened tungsten greaves");
    set_pshort("pairs of blackened tungsten greaves");
    set_long("These blackened tungsten greaves gives excellent " +
    "protection to your legs, and partically the top of " +
    "the legs.\n");
    set_ac(40);
    set_at(A_LEGS);
    add_prop(OBJ_I_VOLUME, 3500);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VALUE, 1500);
}



