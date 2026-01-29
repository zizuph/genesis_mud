/*
 * An example bag, made by Nick
 */

inherit "/std/container";
#include <stdproperties.h>

void
create_container()
{
    set_name("rod");
    set_adj("fishing");
    set_short("fishing rod");
    set_long("A typical fishing rod with a little hook at the end of the line.\n");

    add_prop(CONT_I_WEIGHT, 250); 	/* It weights 250 grams */
    add_prop(CONT_I_MAX_WEIGHT, 270); 	/* It can hold 2000 grams of weight. */
    add_prop(CONT_I_VOLUME, 2000); 	/* Only 30 ml volume (very small) */
    add_prop(CONT_I_MAX_VOLUME, 2020); 	/* 2 litres of volume */

    add_prop(OBJ_I_VALUE, 20); 		/* Worth 40 cc */
}
