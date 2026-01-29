#include "default.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

void
create_kalad_monster()
{
    set_name("replin");
    set_race_name("human");
    set_adj("strong");
    add_adj("middle-aged");
    /* set_short("strong middle-aged human and a large cart"); */
    add_prop(LIVE_S_EXTRA_SHORT, " and a large cart");
    set_long("This average-looking middle-aged man is dragging a large "+
      "cart behind him with one hand, and cupping his mouth with the other "+
      "to help amplify his voice.\n");
    add_item(({"large cart", "cart"}), "A large rectangular-shaped wooden cart "+
      "where the corpses are placed. It smells quite bad.\n");
    set_stats(({250, 65, 65, 10, 10, 20}));
    set_alignment(100);
    set_skill(SS_UNARM_COMBAT, 60);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_AWARENESS, 50);
    set_act_time(3);
    add_act("wimpy feeling very well");
    add_act("shout Bring out your dead!");
    add_act("say Hello, got any corpses you'd like to give me?");
    add_act("smile grimly");
    set_title("Mel, the Bearer of the Dead");
    add_speak("I keep the streets clean...of corpses.\n");
    set_knight_prestige(-1);
    set_random_move(3);
    MONEY_MAKE_SC(500)->move(TO, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    trig_new("%w 'gives' 'you' 'a' 'corpse' %s", "react_corpse");
}

void
return_corpse(string who)
{
    object obj;
    int ran;

    if (obj = present(who, environment()))
    {
	command("say Why thank you " + obj->query_nonmet_name() + ".");
	command("emote places the corpse inside the large cart.");
	command("give 25 silver coins to " + OB_NAME(obj));
    }
}

int
react_corpse(string who, string dummy)
{
    if (who)
    {
	who = lower_case(who);
	set_alarm(3.0, 0.0, &return_corpse(who));
	return 1;
    }
}
