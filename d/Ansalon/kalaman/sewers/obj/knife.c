inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    string name, *first, *second, *weapons;

    first = ({"small", "dirty", "fragile", "black", "old" });
    second = ({"sharp", "blunt", "rusty", "shiny", "dull" });
    weapons = ({"knife", "dagger", "piece of glass"});
    
    string temp1 = one_of_list(first);
    string temp2 = one_of_list(second);
    string temp3 = one_of_list(weapons);
    
    set_adj(temp1);
    add_adj(temp2);
    set_name(temp3);
    
    set_short(temp1 + " " + temp2 + " " + temp3);

    set_long("This " + short() + " looks like rubbish which has been mistaken as a weapon by the gully dwarven race. " +
      "You think that you might be able to get a scratch on someone with this thing though.\n");

    set_default_weapon(10 + random(10), 10 + random(20), W_KNIFE, W_SLASH | W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 3000 + random(2000));
    add_prop(OBJ_I_WEIGHT, 3000 + random(2000));
}
