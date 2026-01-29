inherit "/std/container";
 
#include <stdproperties.h>
 
void
create_container()
{
    set_name("vase");
    set_adj("small");
    set_long("A small crystal vase.\n");
 
    add_prop(CONT_I_WEIGHT, 50);      /* It weights 250 grams */
    add_prop(CONT_I_MAX_WEIGHT, 105);  /* It can hold 562 grams of weight. */
    add_prop(CONT_I_VOLUME, 2);        /* Only 8 ml volume  */
    add_prop(CONT_I_MAX_VOLUME, 100);  /* .5 litres of volume */
 
    add_prop(OBJ_I_VALUE, 40);         /* Worth 40 cc */
}
