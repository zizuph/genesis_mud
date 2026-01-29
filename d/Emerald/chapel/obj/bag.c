/* chapel/obj/bag.c is cloned by chapel/jewelers.c */
inherit "/std/container";
 
#include <stdproperties.h>
#include "../chapel.h"
 
void
create_container()
{
    set_name("bag");
    set_adj("ring");
    set_long("It is a small satin bag. On the side, there is "+
      "some markings in gold.\n");
 
    add_item("markings", "It looks like \"Marital Services\".\n");
 
    add_prop(CONT_I_WEIGHT, 50);    /* It weights 50 grams */
    add_prop(CONT_I_MAX_WEIGHT, 1050);  /* It can hold 2000 grams of weight. */
    add_prop(CONT_I_VOLUME, 30);   /* Only 30 ml volume (very small) */
    add_prop(CONT_I_MAX_VOLUME, 60);    /* 280 millilitres of volume */
    add_prop(CONT_M_NO_REM, "The ring cannot be removed until the marriage ceremony.\n");
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_I_VALUE, 40);       /* Worth 40 cc */
}
