/* High Templar of Tyr jail.. Zayn april 97 */

#pragma strict_types
 
inherit "/d/Cirath/std/monster.c";
#include "defs.h"
#include <wa_types.h>

object me=this_object();

void
create_monster ()
{
        set_name("ulf");
        set_title("of Tyr, High Templar of the Jail");
        set_race_name("templar");
        set_adj("giant");
        set_adj("blocky");

        set_long("This is the High Templar of this prison. He is massive "
		+"extremely muscular, he must have recieved his training "
		+"from the gladiator school here in Tyr. A narrow poined "
		+"beard juts from his chin, and a mustache drops off his "
		+"upper lip. His weathered face show signs of past battles. "
		+"He gives the impression of being hard and fixed of "
		+"purpose.\n");

        set_stats(({ 250, 250, 250, 100, 100, 130}));

        set_skill(SS_DEFENCE, 100);
        set_skill(SS_PARRY, 100);
        set_skill(SS_WEP_AXE, 100);
	set_skill(SS_BLIND_COMBAT, 100);
        set_skill(SS_AWARENESS, 100);

        set_alignment(0);

        set_act_time(5);
        set_cact_time(3);

        add_act("emote glance suspiciously on you.");
        add_act("emote gives you a grim look, that makes you shiver.");
        add_act("emote peers at you with his black eyes.");
        add_act("emote grumbles loudly.");
        add_act("say What are you doing here, leave now!");
        add_act("say Hmm this prison is getting rather full. I probably "
		+"have to kill some prisoners to make room.\n");
        add_act("emote smiles confidently.");
        add_act("say Greetings travellers.");

        add_cact("emote laughs satanically.");
        add_cact("emote grins evilly.");
        add_cact("emote cheers enthusiastically.");
        add_cact("say Make yourself ready to meet death");
        add_cact("say Well well, you gonna regret this.");
        add_cact("say Your future ends here!");
        add_cact("say You are as good as dead.");

        set_speak("I am the one who makes the final decisions in this jail.");
}

void
arm_me()
{
        clone_object(TYR_ARM + "jail_body.c")->move(TO);
        clone_object(TYR_ARM + "jail_head.c")->move(TO);
        clone_object(TYR_ARM + "jail_cloak.c")->move(TO);
        clone_object(TYR_WEP + "sorslayer.c")->move(TO);
        command("wear all");
        command("wield all");
}

/* SPECIAL ATTACK */
int
special_attack(object enemy)
{
	object me;
	mixed* hitresult;
	string how;
 
	me=this_object();
 
	if(random(6)) return 0;
 
	hitresult = enemy->hit_me(300 + random(300), W_BLUDGEON, me, -1);
	how = "amazed by such a feeble attack";
	if (hitresult[0] > 0) how = "dazed";
	if (hitresult[0] > 15) how = "injured";
	if (hitresult[0] > 30) how = "hurt";
	if (hitresult[0] > 50) how = "severely hurt";
	if (hitresult[0] > 75) how = "on the verge of collapse";
 
	enemy->catch_msg(QCTNAME(me) + " strikes you with "+
                     HIS_HER(me) + " body slam.\n");
	enemy->catch_msg("You feel " + how + ".\n");
 
	tell_watcher(QCTNAME(me)+" strikes "+QCTNAME(enemy)+
		" with " + HIS_HER(me) + " body slam.\n",
		me, enemy);
	tell_watcher(QCTNAME(enemy) + " looks " + how + ".\n");
 
	if(enemy->query_hp() <= 0) enemy->do_die(me);
 
	return 1;
}
