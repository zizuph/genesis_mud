#pragma strict_types
#pragma save_binary

inherit "/d/Cirath/std/monster";
#include <wa_types.h>
#include <options.h>
#include "/d/Cirath/common/defs.h"

void
arm_me();

void
kick_me_out();

void
brutus_help();

void
create_monster()
{
        ::create_monster();
        set_race_name("human");
   	add_name("guard");
   	set_name("gladiator");
        set_adj("tough");
        set_adj("gladiator");

        set_short("tough gladiator guard");
        set_long("This gladiator is apparently spending time "
        	+"assisting Brutus as a guard for the Gladiator's "
        	+"of Athas. He looks to be a capable opponent.\n");

        add_prop(LIVE_I_NEVERKNOWN, 1);

        set_stats(({ 120, 120, 120, 90, 85, 120}));

        set_skill(SS_DEFENCE, 80);
        set_skill(SS_PARRY, 85);
        set_skill(SS_WEP_AXE, 90);
        set_alignment(-300 + random(60));

        set_act_time(10);
        set_cact_time(5);
	set_alarm(300.0,0.0,kick_me_out);
}

void
arm_me()
{
    clone_object(TYR+"wep/axe_hevy")->move(TO);
    clone_object(TYR+"arm/body_hid.c")->move(TO);
    clone_object(TYR+"arm/head_pot.c")->move(TO);
    command("wield all");
    command("wear all");
}

/* sets unarmed combat off, giving more weapon attacks! */

void
kick_me_out()
{
	if (present("brutus", ENV(TO)))
	{
		say("Guard steps back to his chamber.\n");
		environment(this_object()) -> jalla_func1();
		remove_object();
	}
}

void
brutus_help()
{
	command("assist brutus");
}

int
query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}
int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;

    me=this_object();

    if(random(5)) return 0;

   hitresult = enemy->hit_me(250+ random(150), W_BLUDGEON, me, -1);
    how = "amazed by such a feeble attack";
    if (hitresult[0] > 0) how = "dazed";
    if (hitresult[0] > 15) how = "injured";
    if (hitresult[0] > 30) how = "hurt";
    if (hitresult[0] > 50) how = "severely hurt";
    if (hitresult[0] > 75) how = "on the verge of collapse";

    enemy->catch_msg(QCTNAME(me) + " strikes you with "+
                     HIS_HER(me) + " charge.\n");
    enemy->catch_msg("You feel " + how + ".\n");

    tell_watcher(QCTNAME(me)+" strikes "+QCTNAME(enemy)+
                 " with " + HIS_HER(me) + " charge.\n",
                 me, enemy);

    if(enemy->query_hp() <= 0) enemy->do_die(me);

    return 1;
}

