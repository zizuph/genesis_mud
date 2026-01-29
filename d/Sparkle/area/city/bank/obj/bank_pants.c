/*
 * /d/Sparkle/area/city/bank/obj/bank_pants.c
 *
 * These pants are intended to be worn by npcs of the Gnomes
 * of Genesis.
 *
 * Created March 2009, by Aeg (Matthew Morin)
 */

#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

/*
 * Function name:       create_armour
 * Description  :       creates the armour.
 */
public void
create_armour()
{
    set_name("pants");
    add_name( ({"bank_pants"}) );
    set_short("formal banker's pants");
    set_adj( ({"formal", "banker's", "bankers"}) );
    set_long("These pants are gray in colour and soft to the touch. "
        + "They are made of cloth and will not offer any protection.\n");
        
    set_ac(0);          /* won't protect much */
    set_at(A_LEGS); 
    set_layers(0);      
    set_looseness(5);
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE, 100);
} /* create armour */    