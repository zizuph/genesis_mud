inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <money.h>
/* by Antharanos */
create_monster()
{
    ::create_monster();
    set_name("guide");
    add_name("tour guide");
    set_race_name("human");
    set_adj("lackadaisical");
    set_short("tour guide");
    set_long("This man is standing here, apparently trying to sound "+
      "knowledgeable, but failing. His posture, tone of voice and entire "+
      "attitude indicates that he's one of those people that doesn't give "+
      "a damn about the world or his duties. Other than "+
      "the fact that he is breathing and occasionally speaking, he seems "+
      "as lifeless as decaying driftwood.\n");
    set_stats(({40,35,30,33,33,35}));
    set_alignment(100);
    set_skill(SS_UNARM_COMBAT,15);
    set_skill(SS_DEFENCE,30);
    set_skill(SS_AWARENESS,30);
    set_skill(SS_SWIM,10);
    set_random_move(10);
    set_act_time(6);
    add_act("say Welcome to the city of Kabal, the largest city in all of Kabal, erm...I mean Kalad.");
    add_act("say This fine ship you are on is the proud vessel known as the Seahawk.");
    add_act("say Um, it was first named...after a bird...yeah, that's it.");
    add_act("say I also believe this was the first ship launched from Kabal.");
    add_act("say Don't wander away from the tour group, because I won't be held responsible.");
    add_act("say Don't touch anything, or I'll...oh nevermind, I don't care what you do.");
    add_act(({"open map","read map","yawn"}));
    set_cact_time(6);
    add_cact("sigh");
    add_cact("ponder");
    set_default_answer("The tour guide says: I don't care about that.\n");
    add_ask(({"seahawk","ship"}),"The tour guide says: Its the oldest ship "+
      "in Kabal, duh.\n");
    set_knight_prestige(-1);
    set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
    object item;
    seteuid(getuid(TO));
    item = clone_object("/d/Kalad/common/caravan/obj/portmap");
    item -> move(TO);
    command("yawn");
    MONEY_MAKE_SC(random(10))->move(TO,1);
}
