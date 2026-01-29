inherit "/std/container";
 
#include <stdproperties.h>
 
void
create_container()
{
    set_name("vase");
    set_adj("beautiful");
    set_long("A polished crystal vase.\n");
 
    add_prop(CONT_I_WEIGHT, 100);      /* It weights 250 grams */
    add_prop(CONT_I_MAX_WEIGHT, 250);  /* It can hold 562 grams of weight. */
    add_prop(CONT_I_VOLUME, 20);        /* Only 8 ml volume  */
    add_prop(CONT_I_MAX_VOLUME, 250);  /* .5 litres of volume */
 
    add_prop(OBJ_I_VALUE, 100);         /* Worth 40 cc */
}
