/*
 * Cleaned up by Finwe, September 1998
 */
 
#include "/d/Shire/sys/defs.h"
inherit "/std/weapon";
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
 
create_weapon()
{
    set_name("sword");
    set_short("war sword");
    set_pshort("swords");
    set_adj(({"troll","large","alloy","war"}));
    set_long("This a large troll sword. It is made of alloy and " +
        "has a black blade which is decorated with some strange " +
        "runes. The hilt is made of steel and has a good grip " +
        "so it will not easily slip out of your hands. The " +
        "sword is covered with blood,and seems to have been " +
        "used a lot. The sword is large and quite heavy, and " +
        "you notice it is made for being used in both hands.\n");
            
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hit(25);
    set_pen(30);
    set_hands(W_BOTH);
    
    add_prop(OBJ_I_WEIGHT, 19000);
    add_prop(OBJ_I_VOLUME, 20000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(30,32));
}
