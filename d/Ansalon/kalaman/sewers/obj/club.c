inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    string name, *first, *second, *weapons;

    first = ({"small", "dirty", "fragile", "broken", "large", "burned" });
    second = ({"wooden", "metal", "bronze", "rusty", "rotting", "slime-covered" });
    weapons = ({"stick", "plank", "club", "bar", "mace" });
    
    string temp1 = one_of_list(first);
    string temp2 = one_of_list(second);
    string temp3 = one_of_list(weapons);
    
   /* set_adj(temp1);
    add_adj(temp2);*/
    set_name(temp3);
    
    set_short(temp1 + " " + temp2 + " " + temp3);

    set_long("This " + short() + " looks like rubbish which has been mistaken as a weapon by the gully dwarven race. " +
      "You guess that you might be able to get a hit on someone with this thing.\n");

    set_default_weapon(19 + random(10), 20 + random(20), W_CLUB, W_BLUDGEON, W_ANYH);
    add_prop(OBJ_I_VOLUME, 3000 + random(2000));
    add_prop(OBJ_I_WEIGHT, 3000 + random(2000));
}
