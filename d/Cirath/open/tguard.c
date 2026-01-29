inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
    ::create_monster();
    set_name("mordur");
    add_name("captain");
    set_race_name("human");
    set_adj("tall");
    add_adj("dark-haired");
    set_long("A dark, brooding figure that nevertheless commands some "+
      "respect in your eyes, for he appears quite skilled in the use of "+
      "the sword.\n");
    set_stats(({90,80,80,60,60,75}));
    set_alignment(250);
    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_WEP_KNIFE, 60);
    set_skill(SS_2H_COMBAT, 70);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_PARRY, 75);
    set_skill(SS_AWARENESS,30);
    set_act_time(6);
    add_act("peer all");
    add_act("say Beware.");
    set_cact_time(3);
    add_cact("shout Fellow guardsmen, come to my aid!");
    add_cact("say You will die for this cowardly attack, you miserable cur.");
    add_speak("If you had a rope, you could get to the third floor.\n");
    set_knight_prestige(-3);
    set_default_answer("The kabal guard says: What?\n");
    set_title("the Captain of the Guard");
    set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
    object wep, arm;
    seteuid(getuid(this_object()));

    arm = clone_object("/d/Kalad/common/caravan/arm/gchain");
    arm -> move(this_object());
    arm = clone_object("/d/Kalad/common/caravan/arm/ghelm");
    arm -> move(this_object());
    command("wear all");
    wep = clone_object("/d/Kalad/common/caravan/wep/gsword");
    wep -> move(this_object());
    wep = clone_object("/d/Kalad/common/caravan/wep/gdagger");
    wep -> move(this_object());
    command("wield all");
    MONEY_MAKE_GC(random(5))->move(this_object(),1);
}
void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	command("say Villanous retch! Die!");
	command("kill " + lower_case(ob->query_real_name()));
    }
}
