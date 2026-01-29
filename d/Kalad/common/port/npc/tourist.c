/* Changed the alignment from 666 to 100
 * 666 seemed rather extreme for this NPC
 * Damaris 2/2002
 */
inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <money.h>
/* by Antharanos */
create_monster()
{
    ::create_monster();
    set_name("tourist");
    set_race_name("human");
    set_adj("curious");
    set_short("tourist");
    set_long("By the constant movement of this man's head from one sight "+
      "to another and by the many questions he continually asks, it is "+
      "obvious that he is a foreign tourist, come here to Kalad to see what "+
      "interesting things he can find.\n");
    set_stats(({30,35,25,20,20,20}));
    set_alignment(666);
    set_skill(SS_DEFENCE,20);
    set_skill(SS_AWARENESS,10);
    set_skill(SS_SWIM,10);
    set_random_move(10);
    set_act_time(9);
    add_act("say Why is the ship called the Seahawk?");
    add_act("say What's that bell I keep hearing?");
    add_act(({"open map","read map","scratch"}));
    add_act("say What's at the top of the plateau?");
    add_act("say How big is the city?");
    add_act("say How long is the tour?");
    add_act("say Am I bothering you?");
    set_cact_time(6);
    add_cact("scream");
    add_speak("I'm brand new around here, how about you?\n");
    set_knight_prestige(-7);
    set_default_answer("The tourist gives you a puzzled expression.\n");
    add_ask(({"tourist"}),"The tourist says: That's me of course! And "+
      "possibly you too.\n");
    set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
    object item;
    seteuid(getuid(TO));
    item = clone_object("/d/Kalad/common/caravan/obj/portmap");
    item -> move(TO);
    command("emote looks around.");
    MONEY_MAKE_CC(random(20))->move(TO,1);
}
void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	command("say You are such a rude " + ob->query_race_name() + "!");
	command("say Let me teach you some manners!");
	command("kill " + lower_case(ob->query_real_name()));
    }
}
