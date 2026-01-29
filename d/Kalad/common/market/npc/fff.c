/* Town fool, by Sarr */
inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
void
create_monster()
{
    ::create_monster();
    set_name("fool");
    set_race_name("human");
    set_adj("goofy");
    add_adj("funny");
    set_long(
     "This guy is the town fool. He walks around the market juggling balls\n"+
     "around. He is happy and playfull, with a wry wit.\n");
    set_act_time(3);
    add_act("say Yo mamma so fat, when her beeper goes of, people think\n"+ 
     "she backing up.\n");
    add_act("emote juggles his balls around skillfully.");
    add_act("say Laughter is the best cure for depression.");
    add_act("say What's the difference between a porcupine and a BMW?\n"+
     "Why...the porcupine has spikes poking out, but in the BMW, the pricks\n"+
     "are in the inside!\n");
   set_aggressive(1);
    add_act("flip");
    add_act("say more jokes to come later.\n");
     set_stats(({200,200,400,1,1,300}));
    set_alarm(1.0, 0.0, "arm_me");
    call_out("arm_me",1);
    add_speak("I love you man\n");
}
void
arm_me()
{
    object arm1;
    if (!arm1)
    {
        arm1 = clone_object("/d/Kalad/common/market/arm/clowns");
        arm1 -> move(TO);
        command("wear all");
    }
}

