/*
 * An example bag, made by Nick
 *
 * This bag is based on the receptacle, which means that you can open and
 * close it. For a chest or safe you might also add a lock to it.
 *
 * /Mercade
 */
 
inherit "/std/container";
 
#include <stdproperties.h>
 
void
create_container()
{
    set_name("vase");
    set_adj("large");
    set_long("A large crystal vase.\n");
 
    add_prop(CONT_I_WEIGHT, 250);      /* It weights 250 grams */
    add_prop(CONT_I_MAX_WEIGHT, 562);  /* It can hold 562 grams of weight. */
    add_prop(CONT_I_VOLUME, 8);        /* Only 8 ml volume  */
    add_prop(CONT_I_MAX_VOLUME, 508);  /* .5 litres of volume */
 
    add_prop(OBJ_I_VALUE, 40);         /* Worth 40 cc */
}
