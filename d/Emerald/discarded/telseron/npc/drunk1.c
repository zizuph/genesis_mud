inherit "/std/monster";
 
#include "/d/Emerald/defs.h"
#include "/d/Emerald/lib/prestige.h"
#include <money.h>
 
#define NAMES ({ "seletin", "perso", "randol" })
#define ADJ ({ "drunk", "blitzed", "tanked" })
 
void
create_monster()
{
    int    ran;
 
    if (!IS_CLONE)
        return;
 
    ran=random(sizeof(NAMES));
    set_name(NAMES[ran]);
    set_living_name("_" + NAMES[ran] + "_");
 
    add_name("drunk");
    add_name("drunk1");
 
    set_race_name("elf");
 
    add_adj("slightly");
    ran=random(sizeof(ADJ));
    add_adj(ADJ[ran]);
 
    set_long("A local drunk. This elf looks to have had a little " +
        "to much to drink.\n");
 
    add_prop(OBJ_I_WEIGHT, 50000);
    add_prop(CONT_I_MAX_WEIGHT, 90000);
    add_prop(OBJ_I_VOLUME, 48000);
    add_prop(CONT_I_MAX_WEIGHT, 80000);
 
    set_gender(random(2));
 
    set_stats( ({ 15+random(85), 12+random(88), 24+random(76),
     7+random(93), 18+random(82), 10+random(90) }) );
 
    heal_hp(10000);
 
    set_act_time(5);
    add_act("giggle");
    add_act("buy ale");
    add_act("drink ale");
    add_act("burp");
    add_act("wink all");
    add_act("puke");
    add_act("say Would you care to buy me a drink?");
 
    trig_new("%w 'introduces' %s", "react_introduce");
 
    seteuid(getuid());
    MONEY_MAKE_SC(2)->move(TO, 1);;
}
 
int
react_introduce(string by, string who)
{
    who=explode(who, " ")[0];
    if (by && (who == "himself" || who == "herself" || who == "itself")) {
 by = lower_case(by);
 set_alarm(itof(random(2)+1),0.0,"return_introduce",by);
 return 1;
    }
    return 0;
}
 
void
return_introduce(string who)
{
    object obj;
    int    ran;
 
    if (obj = present(who, environment())) {
 if (!interactive(obj))
     return;
 ran = random(3);
 if (ran == 0)
     command("introduce myself to " + who);
 else if (ran == 1)
     command("bow " + who);
 else if (ran == 2)
     command("say Nice to meet you, " + capitalize(who) + ".");
    }
}
