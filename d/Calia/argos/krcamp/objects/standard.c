/** A Kretan standard, carried by Ensigns
***
*** Date      Coder      Action
*** ------- ----------- -----------------------------
*** 7/15/96   Zima       Created
***
**/
inherit "std/object";
#include <stdproperties.h>
 
void create_object() {
    set_name("standard");
    add_name(({"flag","banner"}));
    set_short("black standard");
    set_long("It is a large black standard or flag, attatched to a tall "+
             "spear, obviously carried in battle. The black silk banner "+
             "is embroidered with a seven-headed hydra with red thread.\n");
 
    add_prop(OBJ_I_WEIGHT, 1000);
}
