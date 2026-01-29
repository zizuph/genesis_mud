/*
 * /w/aeg/sparkle/bank/obj/bank_hat.c
 *
 * This hat is intended to be worn by npcs of the Gnomes
 * of Genesis.
 *
 * Created April 2008, by Aeg (Matthew Morin)
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
    set_name("hat");
    add_name( ({"bank_hat"}) );
    set_short("brimmed banker's hat");
    set_adj( ({"formal", "banker's", "bankers"}) );
    set_long("This grey hat has a black, beaked brim. It allows the wearer "
           + "to block rays of light that might cause squinting. It is worn "
           + "by bankers of the Gnomes of Genesis bank.\n");
           
    set_ac(0);          /* won't protect much */
    set_at(A_HEAD); 
    set_layers(0);      
    set_looseness(5);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 50);
} /* create armour */    