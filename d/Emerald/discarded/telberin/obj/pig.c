/**
*** Coded by darius based on a press by zima
**/
inherit "std/object";
#include <stdproperties.h>
 
void create_object() {
    set_name("statue");
    set_adj(({"pig","dancing","porcine"})) ;
    set_short("statue of a dancing pig") ;
    set_long("This statue is chiseled from basalt.  It is a life-sized "+
         "statue of the mascot, a large pig, dancing happily in a pit of mud.  Given that"+
        " this is Telberin, you're not suprised that even the mud seems "
        +"clean.  You don't expect to find meat on the menu here.\n");
    add_prop(OBJ_I_WEIGHT, 200000);
    add_prop(OBJ_I_WEIGHT, 200000);
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_I_NO_INS, 1);
    add_prop(OBJ_M_NO_INS, 1);
}
