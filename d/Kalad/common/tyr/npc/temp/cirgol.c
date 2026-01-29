/* Captain of the guards in Tyr jail.. Zayn march 97 */

#pragma strict_types
 
inherit "/d/Cirath/std/monster.c";
#include "defs.h"
#include <wa_types.h>

object me=this_object();

void
create_monster ()
{
	set_name("cirgol");
	set_title("Captain of the Guards");
	set_race_name("human");
	set_adj("grim");
	set_adj("massive");

	set_long("By the looks of this human you can understand that he is not "
		+"one you want to mess with. As a Captain of the Guards you "
		+"will probably have to be more cruel and feared than the rest "
		+"of the soldier. He looks rather uncomfortable here in this "
		+"office, maybe he wants to torment some prisoners.\n");

	set_stats(({ 150, 180, 150, 100, 100, 120}));

	set_skill(SS_DEFENCE, 100);
	set_skill(SS_PARRY, 100);
	set_skill(SS_WEP_AXE, 100);
	set_skill(SS_AWARENESS, 60);

	set_alignment(-300);

	set_act_time(5);
	set_cact_time(3);

	add_act("emote starts to organize some papers on the desk.");
	add_act("emote gives you a grim look, that makes you shiver.");
	add_act("emote sighs deeply");
	add_act("emote grumbles loudly");
	add_act("say What are you doing here, leave now!");
	add_act("say Hmm I wonder where i put that cell key.");
	add_act("shout Slave come here now! I want my desk polished.");
	add_act("say I hate sitting in here. If i only could beat up some "
		+"prisoners or slaves.\n");
	add_act("say You stink like a corpse. Go and lie down on the pile "
		+"outside the window.\n");

	add_cact("emote goes into a battle frenzy.");
	add_cact("emote grins evilly.");
	add_cact("emote gasps in astonishment.");
	add_cact("shout Guards. Come here. Spanking time.");
	add_cact("say Well well, you gonna regret this.");
	add_cact("say Hmm looks like i have to put you in a cell.");
	add_cact("say I have waited for a real fight for a very long time.");

	set_speak("You better leave, or I'll put you in a cell for sure.");
}

void
arm_me()
{
	clone_object(TYR_ARM + "jail_body.c")->move(TO);
	clone_object(TYR_ARM + "jail_head.c")->move(TO);
	clone_object(TYR_ARM + "jail_cloak.c")->move(TO);
	clone_object(TYR_WEP + "great_axe.c")->move(TO);
	command("wear all");
	command("wield all");
}

/* SPECIAL ATTACK */
int
special_attack(object enemy)
{
	object me;
	mixed* hitresult;

	me=this_object();

	if(random(4)) return 0;

	hitresult=enemy->hit_me(200+random(200), W_SLASH, me, -1);

	enemy->catch_msg(QCTNAME(me) + " tries to chop your head off!\n");

	tell_watcher(QCTNAME(me) + " tries to chop " + QCTNAME(enemy)+
		"'s head off!\n",me,enemy);

	if(enemy->query_hp() <= 0) enemy->do_die(me);

	return 1;
}
