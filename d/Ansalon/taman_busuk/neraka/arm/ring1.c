/* Shield ring by Ashlar, inspired by black-gem ring
   of Flotsam Forest.

   When worn, the ring gives the wearer ARMOUR_CLASS protection
   in all hitlocations. In return for this, it drains MANA units
   of mana every DELAY seconds. If the wearer has less than MANA
   units of mana, the ring is removed, and cannot be worn.

   This ring is originally worn by an npc, and is much more
   effective for him.
*/

inherit "/std/armour";
inherit "/lib/keep";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

#define ARMOUR_CLASS        10
/* The ring drains MANA units of mana every DELAY seconds */
#define MANA            35
#define DELAY           30.0

int manadrainalarm = 0;

void
create_armour()
{
    set_name("ring");
   
    set_adj("thin");
    add_adj("gold");
    set_short("thin gold ring");
    set_long("This is a thin ring of gold, @@ornament@@. The " +
        "ring feels warm to the touch.\n");
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO,
        ({ "The ring is enchanted with some protective powers.\n", 5,
           "When worn, it will surround the wearer with a field of " +
           "protection good against any normal weapon. The ring takes " +
           "the strength for this from the wearer.\n",20,
           "The ring was custom made for one individual, and it is " +
           "likely to be less effective for others that use it.\n",40 }));
    add_prop(MAGIC_AM_MAGIC,({40,"enchantment"}));
    add_prop(OBJ_S_WIZINFO,
        "The ring gives the wearer " + ARMOUR_CLASS + " ac in all " +
        "hitlocations. This drains " + MANA + " mana every " + ftoi(DELAY) +
        " seconds. The ring is twice as effective for npc's.\n");
   
    set_ac(ARMOUR_CLASS);
    set_at(A_ANY_FINGER);
    set_af(TO);
   
    add_prop(OBJ_I_WEIGHT, 120);
    add_prop(OBJ_I_VOLUME, 70);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS) + 1000);
}

string
ornament()
{
    if (manadrainalarm)
        return "inscribed with strange, glowing patterns";
    else
        return "with no obvious ornaments";
}

public int *
query_shield_slots()
{
    return ({ A_HEAD, A_BODY, A_L_ARM, A_R_ARM, A_LEGS});
}

void
manadrain()
{
    object p;
    p = E(TO);
    if (p->query_mana() < MANA)
    {
        p->catch_msg("Feeling faint with exhaustion, you remove the " +
            short() + ".\n");
        LTELL_ROOMBB(E(p),p,"About to faint from exhaustion, ", " removes " +
            POSSESSIVE(p) + " " + short() + ".\n",p);
        remove_me();
        if (manadrainalarm)
            remove_alarm(manadrainalarm);
        manadrainalarm = 0;
        return;
    }
    p->add_mana(-MANA);
    p->catch_msg("You feel the power of the " + short() + " draining you " +
        "mentally.\n");
    return;
}

mixed
wear(object what)
{
    object p;
    p = E(TO);
    
    if (p->query_mana() < MANA)
    {
        return "Fearing exhaustion, you dare not wear the ring.\n";
    }
    p->add_mana(-MANA);
    if (manadrainalarm)
        remove_alarm(manadrainalarm);
    if (!p->query_npc())
        manadrainalarm = set_alarm(DELAY,DELAY,&manadrain());
    p->catch_msg("You slip the ring on a finger, and a warm tingling " +
        "sensation spreads up your arm and through your body.\n");
    return 0;
}

mixed
remove(object what)
{
    object p;
    p = E(TO);

    if (manadrainalarm)
        remove_alarm(manadrainalarm);
    manadrainalarm = 0;
    p->catch_msg("As you pull off the ring, the warm sensation leaves you.\n");
    return 0;
}

void
enter_env(object env, object from)
{
    if (env->query_prop(LIVE_I_IS) && env->query_npc())
        set_ac(25);
    else
        set_ac(ARMOUR_CLASS);

    ::enter_env(env,from);
}
