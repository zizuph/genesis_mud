/**
*** The press found the Royal Press building (rooms/press)
*** All associated commands and detailed descriptions found in room defn.
***
*** Date      Coder      Action
*** ------- ----------- -----------------------------
*** 8/24/95    Zima       Created
***
**/
inherit "std/object";
#include <stdproperties.h>
 
void create_object() {
    set_name("press");
    set_adj(({"large","wooden"}));
    set_short("large wooden press");
    set_long("It is a large wooden press used to crush the juice from "+
             "grapes and the oil from olives. It is set on a large "+
             "frame with a square funneled bin on the top, a long "+
             "lever on the side, and a spigot at the bottom. There "+
             "is a plaque nailed to its frame with instructions on "+
             "its use.\n");
 
 
    add_prop(OBJ_I_WEIGHT, 200000);
    add_prop(OBJ_I_WEIGHT, 200000);
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_I_NO_INS, 1);
    add_prop(OBJ_M_NO_INS, 1);
}
