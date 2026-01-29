/*
  Modified by Zignur 2017-09-13 

*/

#include "default.h"
inherit "/d/Kalad/std/monster";

void
create_kalad_monster()
{
    set_name("nadar");
    add_name("guard");
    set_race_name("human");
    set_adj("elite");
    add_adj("company");
    set_short("elite company guard");
    set_long("This man is one of the elite members of the Trading Company "+
      "guards. He looks extremely skilled in the art of fighting with "+
      "polearms and in defending himself from any attackers. He doesn't "+
      "look too happy to see you here.\n");
    
    /* New stats changed by Zignur 2017-09-13 */
    set_stats(({95,95,95,95,95,95}));
    set_alignment(0);
    
    /* New skills changed by Zignur 2017-09-13 */
    set_skill(SS_WEP_POLEARM, 80);
    set_skill(SS_UNARM_COMBAT, 60);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_PARRY, 80);
    set_skill(SS_AWARENESS, 70);
    set_skill(SS_BLIND_COMBAT, 50);
    set_act_time(6);
    add_act("frown");
    add_act("say You'd better leave now, or I'll hurt you.");
    add_act("say I'm warning you...leave now, before it is too late.");
    add_act(({"shout Die then, miserable cur!", "kill elf", "kill dwarf", "kill gnome", "kill hobbit", "kill goblin"}));
    set_cact_time(3);
    add_cact("say You ignored my warning, now I'm going to slay you!");
    add_cact("emote looks like he's going to slay you.");
    add_cact("say You are such a pitiful fighter, go back to school!");
    add_cact("say Oooh, That didn't hurt at all.");
    add_cact("fume");
    add_speak("No strangers are allowed beyond this point, and that "+
      "includes you.\n");
    set_knight_prestige(0);
    set_title("the Elite Company Guardsman");
    set_alarm(1.0, 0.0, "arm_me");
    trig_new("%w 'haughtily' 'shows' 'off' %s", "react_show");
}

void
arm_me()
{
    
    /* Use Equip instead changed by Zignur 2017-09-13 */
    equip( ({ ARM + "tcgplate",
              ARM + "tcghelm",
              ARM + "tcggaunt",
              ARM + "tcggreav",
              WEP + "tcghalb1"  }));
    command("wear all");
    command("wield all");
    
    MONEY_MAKE_GC(random(5))->move(this_object(), 1);
}

void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
    command("growl");
    command("say Die! Enemy of the Company!");
    command("kill " + OB_NAME(ob));
    command("say Prepare to meet your maker, " + ob->query_nonmet_name() + "!");
    }
}

void
return_show(string who)
{
    object obj;
    int ran;

    if(obj = present(who, environment()))
    {
    command("say Lord!");
    command("worship " + OB_NAME(obj));
    }
}

int
react_show(string who, string dummy)
{
    if(who)
    {
    who = lower_case(who);
    set_alarm(2.0, 0.0, &return_show(who));
    return 1;
    }
}
