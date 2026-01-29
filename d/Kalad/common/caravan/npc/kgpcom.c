#include "default.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

void
create_kalad_monster()
{
    set_name("arvin");
    add_name("patrol commander");
    add_name("commander");
    set_race_name("human");
    set_adj("swarthy");
    add_adj("kabal");
    set_short("patrol commander");
    set_long("A tall, dark-haired man whose job is to insure the Caravan "+
      "route is free of brigands and other criminals that prey upon hapless "+
      "travellers. His bearing indicates a man of noble intentions and "+
      "sworn convictions.\n");
    set_stats(({110, 100, 100, 80, 80, 95}));
    set_alignment(600);
    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_UNARM_COMBAT, 60);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_PARRY, 80);
    set_random_move(10);
    set_act_time(6);
    add_act("emote looks around warily.");
    add_act("say Don't wander off the route, unknown creatures lurk just off of it.");
    set_cact_time(3);
    add_cact("shout Fellow patrolmen, help me dispatch this dog!");
    add_cact("say You will die for this cowardly attack, you miserable cur.");
    add_speak("If you are thinking of taking up the life of a highwayman, "+
      "then be advised, you shall be hunted down until you and any of "+
      "your cohorts are nothing but vulture meat.\n");
    set_knight_prestige(-6);
    set_title("the Commander of the Caravan Route Patrols");
}

void
arm_me()
{
    object wep, arm;
    seteuid(getuid(this_object()));

    arm = clone_object(ARM + "gchain");
    arm->move(this_object());
    arm = clone_object(ARM + "ghelm");
    arm->move(this_object());
    command("wear all");
    wep = clone_object(WEP + "pcsword");
    wep->move(this_object());
    command("wield all");
    MONEY_MAKE_GC(random(6))->move(TO, 1);
}

void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	command("say Prepare to be cut to ribbons, " + ob->query_nonmet_name() + "!");
	command("kill " + OB_NAME(ob));
    }
}
