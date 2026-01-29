/*  
 * A greater version of the normal dragon turtle shell.
 * /d/Ansalon/goodlund/bloodsea/obj/dr_turtle_shell.c
 *
 * Arman, Feb 2021
 *
 * Reduced armour benefit for A_BODY and A_LEGS
 * Changed fixed weight to 
 *     F_WEIGHT_DEFAULT_ARMOUR(60, A_SHIELD) * 3
 * Arman, May 2021
 */
inherit "/std/armour";

inherit "/lib/keep";
#include <wa_types.h>
#include <formulas.h>
#include "/d/Krynn/common/defs.h"

object wearer;

public void
create_armour()
{
    set_name("shell");
    set_pname("shells");
    add_name(({"armour", "shield"}));
    add_pname(({"armours", "shields"}));
    set_adj("dragon");
    add_adj(({"turtle", "black" }));
    set_short("black dragon turtle shell");
    set_pshort("black dragon turtle shells");
    // Provides 60 ac to A_SHIELD, with reduced ac for 
    // A_BODY (56) and A_LEGS (52)
    set_ac(60);
    set_at(A_SHIELD);
    set_am( ({0,0,0}) );
    set_af(TO);
    set_long("This huge shell has come from a mythical beast of the sea, " +
        "a dragon turtle. And not just any dragon turtle, but the " +
        "rare gigantic black, a terror the size of a galleon! This shell " +
        "is exceedingly thick and tough, even powerful ship ballista bolts " +
        "would have trouble piercing it! As such it makes it an impenetrable, " +
        "albeit heavy, shield.\n");

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO,"This shield is made from the shell of a gigantic " +
        "dragon turtle.\n" +
        "/d/Krynn/south_courrain/living/ancient_dragon_turtle.c\n" +
        "It gives unrivaled protection as a shield (ac 60 A_SHIELD, ac 56 A_BODY, " +
        "and ac 52 A_LEGS), as well as " +
        "offers resistance to acid attacks when worn (55 resistance).\n");
    add_prop(MAGIC_AM_ID_INFO,
        ({"This shield is made from the shell of a gigantic dragon turtle of " +
        "the Courrain Ocean, a magical creature that has imbued its essence " +
        "to its remains.\n", 20,
        "This shield offers unrivaled protection.\n", 50,
        "In particular, it protects from acid attacks.", 70}));
    add_prop(MAGIC_AM_MAGIC,({100, "enchantment"}));
    add_prop(MAGIC_AM_MAGIC,({100, "enchantment"}));

    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_WEIGHT, (F_WEIGHT_DEFAULT_ARMOUR(60, A_SHIELD) * 3) );
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(60) );

}

int query_magic_protection(mixed prop, object for_who)
{
   if (for_who == wearer)
      if (prop == MAGIC_I_RES_ACID)
      return 55;
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

varargs int
query_ac(int hid)
{
    if (hid & A_LEGS)
      return (::query_ac(hid) - 8);

    if (hid & A_BODY)
      return (::query_ac(hid) - 4);
 
    return ::query_ac(hid);
    
}