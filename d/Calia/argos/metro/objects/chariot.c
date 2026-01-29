/**
*** A chariot and horses. Part of the chariot transports. This object
*** just a decoration.
***
*** Date      Coder      Action
*** ------- ----------- -----------------------------
*** 9/24/95   Zima       Created
***
**/
inherit "std/object";
#include <stdproperties.h>
 
void create_object() {
    set_name("chariot");
    set_short("team of horses hitched to a chariot");
    set_long("It is a long chariot cast of orichalcum hitched to a team "+
             "of horses.\n");
    add_item(({"team","horses","horse"}),
       "The horses hitched to the chariot look strong and well-groomed. "+
       "Their short snow-white coats are accented by their long flowing "+
       "manes and tails which are braided with blue ribbons. They are "+
       "a pair of magnificent animals.\n");
 
    add_prop(OBJ_I_WEIGHT, 200000);
    add_prop(OBJ_I_WEIGHT, 200000);
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_I_NO_INS, 1);
    add_prop(OBJ_M_NO_INS, 1);
}
