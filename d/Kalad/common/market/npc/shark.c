inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* Loan shark, by Sarr */
void
create_monster()
{
    ::create_monster();
    set_name("shadar");
    set_race_name("human");
    set_adj("slender");
    add_adj("lazy-eyed");
    set_long(
     "This guy is dressed in a fine black tuxedo. He leans againts the wall\n"+
     "in the back corner, observing the room. He loans out money to those\n"+
     "who are in need...but be sure to pay him back! He has a wicked gleam\n"+
     "his eye, and something tells you, you don't want to mess with him.\n");
    set_stats(({100,130,110,100,100,100}));
    set_skill(SS_WEP_SWORD,80);
    set_skill(SS_DEFENCE,80);
    set_skill(SS_PARRY,80);
    add_speak(
     "I can loan you money, if you need it. If you don't pay me\n"+    
     "back, you will be sorry.");
    set_act_time(6);
    add_act("emote glances around the room.");
    add_act("emote folds his arms across his chest.");
    add_act("emote pulls the brim of his hat down to shade his eyes.");
    add_act("emote scratches his chin thoughtfully.");
    add_act("emote ponders breaking the legs of those who don't pay back.");
    set_alarm(1.0, 0.0, "arm_me");
    set_alignment(100);
    set_knight_prestige(-100);
}

void
arm_me()
{
    object arm1,arm2,wep1;
    seteuid(getuid(TO));
    arm1 = clone_object("/d/Kalad/common/market/arm/stux");
    arm1 -> move(TO);
    arm2 = clone_object("/d/Kalad/common/market/arm/bhat");
    arm2 -> move(TO);
    command("wear all");
    wep1 = clone_object("/d/Kalad/common/market/wep/bssword");
    wep1 -> move(TO);
    command("wield all");
}

