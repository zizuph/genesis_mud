/*
 * abbasi.c
 * Tomas  -- April 2000
 */

#include "/d/Terel/include/Terel.h"

inherit "/d/Terel/include/cloned_weapons.c";
inherit STDWEAPON;


#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>


create_weapon()
{
    ::create_weapon();
    set_wf(TO);

    set_name("abbasi");
    set_pname("abbasis");
    set_adj(({"straight-bladed"}));
    set_adj("steel");
    add_name("sword");
    set_short("straight-bladed abbasi");
    set_pshort("straight-bladed abbasis");
    set_long("The straight-bladed steel abbasi is adorned with gold " +
       "inlay and gilt. The back of the blade is strengthened " +
       "by hardened steel alloy supports.\n");

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VALUE, 8640);
    add_prop(OBJ_S_WIZINFO, "This sword has been magically altered " +
       "to increase its pen and weight for wielders with sword skill > 75.\n");
    add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,
        ({"The steel abbasi seems sharper and lighter for those " +
          "skilled enough to use it.\n",20}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    set_hit(35);
    set_pen(38);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_RIGHT);
    add_prop(OBJ_I_WEIGHT, 4500);
    add_prop(OBJ_I_VOLUME, 1000);
}

public mixed
wield(object wep)
{
   if (TP->query_skill(0) > 75)
   {
       write("You feel elated as you test the superior weight and agility of the " +
          "steel abbasi in your hand.\n");
       say(QCTNAME(TP) + " sweeps the " + short() + " through the air, testing " +
          "its weight agility.\n");
       set_hit(45);
       set_pen(50);
       TP->update_weapon(TO);

   }
   return 0;     
}


public mixed
unwield(object wep)
{
    set_hit(35);
    set_pen(38);
    return 0;     
}
