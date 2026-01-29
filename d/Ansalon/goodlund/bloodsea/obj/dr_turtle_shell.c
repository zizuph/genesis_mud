/* Navarre: October 22nd 2011:
 *     Removed the randomness of the shield ac (was 35+random(11)).
 *     Trippled the weight of the shield (from 2000 to 6500).
 *     Removed the randomness of acid protection (was 40+random(20)).
 */
inherit "/std/armour";

inherit "/lib/keep";
#include <wa_types.h>
#include <formulas.h>
#include "/d/Ansalon/common/defs.h"

object wearer;

public void
create_armour()
{
    set_name("shell");
    set_pname("shells");
    add_name(({"armour", "shield"}));
    add_pname(({"armours", "shields"}));
    set_adj("dragon");
    add_adj(({"turtle"}));
    set_short("dragon turtle shell");
    set_pshort("dragon turtle shells");
    set_ac(43);
    set_at(A_SHIELD);
    set_am( ({0,0,0}) );
    set_af(TO);
    set_long("This large shell has come from a mythical beast of the sea, " +
             "the fearsome dragon turtle. Exceedingly thick and tough, even powerful " +
             "ballista bolts would have trouble piercing it!  As such, it would make " +
             "a great, albeit heavy, shield.\n");

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO,"This shield is made from the shell of a dragon turtle. " +
           "It gives good protection, as well as offers resistance to acid attacks.\n");
    add_prop(MAGIC_AM_ID_INFO,
             ({"This shield is made from the shell of a dragon turtle of the Bloodsea " +
                 "of Istar, a magical creature that has imbued its essence to its remains.\n", 20,
                 "This shield offers good protection.\n", 50,
                 "In particular, it protects from acid attacks.", 70}));
    add_prop(MAGIC_AM_MAGIC,({100, "enchantment"}));
    add_prop(MAGIC_AM_MAGIC,({100, "enchantment"}));


    add_prop(OBJ_I_VOLUME, 600);
    add_prop(OBJ_I_WEIGHT, 6500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25) );

}


int query_magic_protection(mixed prop, object for_who)
{
   if (for_who == wearer)
      if (prop == MAGIC_I_RES_ACID)
      return 47;
   else
      return 0;
   else
      return ::query_magic_protection(prop, for_who);
}
 

wear(object to)
{
   wearer = TP;
   wearer->add_magic_effect();
}
 
remove(object to)
{
   wearer->remove_magic_effect();
   wearer = 0;
}

public int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY, A_LEGS }) );
}
