/*
 * /w/Sparkle/area/city/bank/obj/bank_vest.c
 *
 * This vest is intended to be worn by npcs of the Gnomes
 * of Genesis.
 *
 * Created March 2008, by Aeg (Matthew Morin)
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
    set_name("vest");
    add_name( ({"bank_vest"}) );
    set_short("formal banker's vest");
    set_adj( ({"formal", "banker's", "bankers"}) );
    set_long("This vest is gray in colour and soft to the touch. "
        + "Two buttons allow one to fasten the vest in place. "
        + "They are brass and in the shape of the Gnomes of Genesis "
        + "crest. It has two pockets that mirror each other on "
        + "either side of the buttons.\n");
    set_ac(0);          /* won't protect much */
    set_at(A_TORSO); 
    set_layers(0);      
    set_looseness(5);
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE, 100);
} /* create armour */    