/**
*** A "no move" wagon; property of the travelling merchant; just for looks
***
*** 12/14/94  Zima       Created wagon
***
**/
 
inherit "std/object";
#include <stdproperties.h>
 
void
create_object()
{
    set_name("wagon");
    set_adj("rickety");
    set_adj("wooden");
    set_short("wagon");
    set_long("It is a rickety old merchants' wagon with a roof " +
             "and two wheels, its red and yellow paint peeling " +
             "off. It is covered with trinkets hanging from old " +
             "strips of leather. A crude sign is tacked to "+
             "the wagon's wall.\n");
 
    add_prop(OBJ_I_WEIGHT, 200000);
    add_prop(OBJ_I_WEIGHT, 200000);
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_M_NO_DROP,1);
    add_prop(OBJ_I_NO_GIVE,1);
    add_prop(OBJ_M_NO_GIVE,1);
    add_prop(OBJ_I_NO_INS, 1);
    add_prop(OBJ_M_NO_INS, 1);
}
