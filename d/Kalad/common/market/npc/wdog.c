inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* War dog, by Sarr */
void
create_monster()
{
    ::create_monster();
    set_name("dog");
    set_adj("ferocious");
    add_adj("war");
    set_long(
    "This is one huge dog that is foaming at the mouth. Its teeth and claws\n"+
    "are very sharp and unpleasant looking.\n");
    set_stats(({50,60,50,10,5,40}));
    set_random_move(90);
    set_act_time(3);
    add_act("growl all");
    add_act("snarl all");
    add_act("emote barks loundly.");
    set_cact_time(3);
    add_cact("emote eyes your throat hungrily.");
    add_cact("emote licks his teeth as he tastes your blood.");
    set_alarm(1.0, 0.0, "arm_me");
}
void
arm_me()
{
    object arm1;
    arm1 = clone_object("/d/Kalad/common/market/arm/dcollar.c");
    arm1 -> move(TO);
    command("wear all");
}

