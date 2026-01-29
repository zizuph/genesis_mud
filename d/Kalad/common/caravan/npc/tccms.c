#include "default.h"
inherit "/d/Kalad/std/monster";

void
create_kalad_monster()
{
    set_name("human");
    add_name("council speaker");
    set_race_name("human");
    set_adj("council");
    set_short("council speaker");
    set_long("This elegantly dressed man gazes around with an arrogant to the "+
      "point of over-confidence kind of look. By his bearing you surmise "+
      "that he is a wealthy noble, even by noblemen standards. He seems "+
      "to be rather upset about something.\n");
    set_stats(({100, 110, 100, 125, 125, 100}));
    set_alignment(0);
    set_skill(SS_AWARENESS, 70);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_TRADING, 100);
    set_act_time(3);
    add_act("shout We must open up all of Kalad to trade!");
    add_act("shout Without trade Kabal shall fester into ruin!");
    add_act("shout Fools! Through the new shipline we can expand our "+
      "operations and make even more money!");
    add_act("shout Shut up and listen to me!");
    add_act("sigh");
    set_cact_time(3);
    add_cact("shout Guards help! Intruders are attacking me!");
    add_cact("shout Run for your lives! The peasants are attacking!");
    add_cact("scowl all");
    add_speak("Only the speaker is allowed up here, and that is me!\n");
    set_knight_prestige(0);
    MONEY_MAKE_SC(random(50))->move(TO, 1);
    set_alarm(1.0, 0.0, "arm_me");
}

void
arm_me()
{
    object arm;
    seteuid(getuid(TO));
    arm = clone_object(ARM + "tccmsrobe");
    arm->move(TO);
    command("wear all");
    command("say What are you doing up here?");
}
