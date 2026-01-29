// file name:
// creator(s): Denis
// revision history:
// purpose: Unterdark altar guardian armour.
//          ~Avenir/common/dark/ghost.c
// note: When on the ghost, is extremely protective.
// bug(s):
// to-do:
 
inherit "/std/armour";
 
#include "/d/Avenir/common/common.h"
#include "/sys/formulas.h"
 
void
create_armour()
{
    set_name("cloak");
    set_adj("old");
    add_adj("dusty");
    set_long("An old elven cloak made of black material "+
             "covered with dust.\n"+
             "There is a strange writing on its left side.\n"+
             "The cloak seems to emanate strange aura.\n");
 
    set_ac(5);
 
    set_am( ({ -2, 1, 1 }) );
 
    set_at(A_ROBE);
 
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(5, A_ROBE));
    add_prop(OBJ_I_VOLUME, 1000);
}
 
add_cloak_ac()
{
    set_ac(30);
}
 
remove_cloak_ac(string str)
{
    set_ac(5);
}
