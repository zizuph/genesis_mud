// grace
// 09 Feb 1995
// kitchen utensil2

inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_weapon()
{
    switch (random(3))
    {
    case 0:
        set_adj(({ "paring" }));
        set_name("knife");        
        set_short("paring knife");
        break;
    case 1:
        set_adj(({ "bread" }));
        set_name("knife");
        set_short("bread knife");
        break;
    case 2:
        set_short("skewer");
        set_name("skewer");
        break;
    }

    
    add_name(({"knife", "kitchen utensil", "weapon"}));
    set_long("This looks like one of the cooking utensils used "+
        "by the Cook at the Knights' Spur kitchen.  It looks "+
        "rather sharp, and could probably do some damage "+
        "if you were stabbed with it.\n");
    
  set_default_weapon(11,12,W_KNIFE,W_SLASH|W_IMPALE,W_ANYH,0);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(11,12)+random(80)-20);
}


