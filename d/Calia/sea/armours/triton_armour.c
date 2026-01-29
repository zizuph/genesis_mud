
 /*    Triton Armour

    coder(s):    Jaacar
                                                 
    history:
              2010.09.04  Fixed names/adjs      Lavellan
              1996.02.09  Last update           ? 
                8.2.96    Created               Jaacar

 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
                      
void
create_armour()
{
//    set_name(({"mail","triton mail","armor","armour","black armour"}));
//    set_adj("black");
    set_name(({"armour", "mail"}));
    set_adj(({"sea-serpent", "seaserpent", "serpent", "black"}));
    set_short("sea-serpent armour");
//    set_long("It is a suit of armour to wear over your shoulders.  "+
    set_long("It is a suit of armour to wear over your shoulders. "+
        "It is made out of the skin of a sea-serpent, which is "+
        "black in colour, and has plates of orichalcum on it to "+
        "cover the chest, back and shoulder areas.\n");
    set_ac(32);
    set_at(A_BODY);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VOLUME, 6000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(45) + 200);
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}
