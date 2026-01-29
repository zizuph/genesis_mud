/*
 * /w/aeg/sparkle/bank/obj/tube.c
 * 
 *Tubes for the movement of coins in the bank of Sparkle.
 * 
 * Feb 2009, Aeg
 */
 
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
 
void
create_object()
{
    set_name("tube");
    add_name("glass tube");
    set_pname("tubes");
    add_pname("glass tubes");
    set_adj("cylindrical");
    set_adj("glass");
    set_long("This tube sticks out of the ground at a decent diagonal angle. "
        + "A spinning, metallic screw sticks out of the tube.\n"); 
    add_prop(OBJ_I_VALUE, 2);
    add_prop(OBJ_I_WEIGHT, 100000000);
    add_prop(OBJ_I_VOLUME, 400);
    
} /* create_object() */
