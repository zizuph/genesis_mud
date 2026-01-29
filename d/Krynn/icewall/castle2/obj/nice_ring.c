inherit "/std/armour";
inherit "/lib/keep";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

#define STRENGTH           10
/* The ring drains FATIGUE units of fatigue every DELAY seconds */
#define FATIGUE            4
#define DELAY              60.0

int fatiguedrainalarm = 0;

void
create_armour()
{
    set_name("ring");
   
    set_adj("shiny");
    add_adj("silver");
    set_short("shiny silver ring");
    set_long("This is an unadorned, small and shiny band of silver. " +
        "If not for its eye-catching sheen, it wouldn't appear " +
        "special at all.\n");
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO,
        ({ "The ring is enchanted with a minor spell.\n", 5,
           "When worn, it will strengthen the wearer a bit." +
           "The ring takes the strength for this from the wearer.\n",20,
           "Though the enchantment is simple and to the point, the " +
           "magic seems ancient, and strange in nature.\n",40,
           "You recognize this ring as timeless artifact created " +
           "with dragon magic.\n", 50}));
    add_prop(MAGIC_AM_MAGIC,({30,"enchantment"}));
    add_prop(OBJ_S_WIZINFO,
        "The ring gives the wearer a strength bonus of " + STRENGTH +
        "This drains " + FATIGUE + " fatigue every " + ftoi(DELAY) +
        " seconds.\n");
   
    set_ac(3);
    set_at(A_ANY_FINGER);
    set_af(TO);
   
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VOLUME, 60);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(10) + 1000);
}

void
fatiguedrain()
{
    object p;
    p = E(TO);
    if (p->query_fatigue() < FATIGUE)
    {
        p->catch_msg("Feeling faint with exhaustion, you remove the " +
            short() + ".\n");
        LTELL_ROOMBB(E(p),p,"About to faint from exhaustion, ", " removes " +
            POSSESSIVE(p) + " " + short() + ".\n",p);
        remove_me();
        if (fatiguedrainalarm)
            remove_alarm(fatiguedrainalarm);
        fatiguedrainalarm = 0;
        return;
    }
    p->add_fatigue(-FATIGUE);
    p->catch_msg("The magical power coursing through your veins " +
                 "slowly but surely draws your life force away...\n");
    return;
}

mixed
wear(object what)
{
    object p;
    p = E(TO);
    
    if (p->query_fatigue() < FATIGUE)
    {
        return "You are too tired to slip the ring on your finger.\n";
    }
    p->add_fatigue(-FATIGUE);
    if (fatiguedrainalarm)
        remove_alarm(fatiguedrainalarm);
    if (!p->query_npc())
        fatiguedrainalarm = set_alarm(DELAY,DELAY,&fatiguedrain());
    TP->set_stat_extra(0, (TP->query_stat_extra(SS_STR) + 10));
    p->catch_msg("You slip the ring on a finger, and immediately feel " +
        "more confident.\n");
    return 0;
}

mixed
remove(object what)
{
    object p;
    p = E(TO);

    if (fatiguedrainalarm)
        remove_alarm(fatiguedrainalarm);
    fatiguedrainalarm = 0;
    write("As you pull off the ring, you feel less confident.\n");
    TP->set_stat_extra(0, (TP->query_stat_extra(SS_STR) - 10));
    return 0;

}

void
enter_env(object env, object from)
{

    ::enter_env(env,from);
}
