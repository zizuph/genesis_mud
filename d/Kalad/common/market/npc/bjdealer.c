inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* Black Jack Game Dealer, by Sarr */
void
create_monster()
{
    ::create_monster();
    set_name("dealer");
    set_race_name("dealer");
    set_adj("tall");
    add_adj("crafty");
    set_long("This is the dealer for the black jack game. If you want\n"+
    "to play, just read the sign on the table.\n");
    set_stats(({180,180,180,100,100,100}));
    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_BLIND_COMBAT,100);
    add_prop(LIVE_I_NEVERKNOWN,1);
    set_cact_time(5);
    add_cact("say I am trained in the martial arts, my friend.");
    add_cact("say Begone! You are not welcome here!");
    add_speak("Read the sign, my friend.\n");
    set_alarm(1.0, 0.0, "arm_me");
}
void
arm_me()
{
    object arm;
    if(!arm)
    {
    arm = clone_object("/d/Kalad/common/market/arm/stux.c");
    arm -> move(TO);
    command("wear all");
    }
}

