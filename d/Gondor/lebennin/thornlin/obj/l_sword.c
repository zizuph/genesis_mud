inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_weapon() 
{
    set_name(({"steel sword","sword","light sword","light steel sword"}));
    set_adj(({"steel","light"}));
    set_short("light steel sword");
    set_pshort("light steel swords");

    set_long("It is a very old and very light sword and it is very well kept "+
      "and it seems very deadly in the wrong hands.\n");

    set_default_weapon(25+random(3),25+random(2),W_SWORD,W_SLASH | W_IMPALE,W_NONE,0);

    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME, 400);

    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(27,26) + random(500) - 350);
}

query_recover()
{
    return MASTER+":"+query_wep_recover();
}


init_recover(arg)
{
    init_wep_recover(arg);
}

