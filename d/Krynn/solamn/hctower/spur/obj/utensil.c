// grace
// 09 Feb 1995
// kitchen utensil

inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>

void
create_weapon()
{
    string name, *parts;
    name = ({"rolling pin", "frying pan", "cutting board", 
                 "wooden spoon", "broom"})[random(5)];
    
    set_short(name);
    
    parts = explode(name, " ");
    set_adj(parts[0..-2]);
    set_name(parts[sizeof(parts) - 1]);

    add_name(({"club", "kitchen utensil", "weapon"}));
    set_long("This looks like something from the Knights' Spur "+
        "kitchen.  If you aren't careful the cook might take it from "+
        "you and club you over the head with it!\n");
    set_default_weapon(10,10,W_CLUB,W_BLUDGEON,W_ANYH,0);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(10,10)+random(40)-20);
}

