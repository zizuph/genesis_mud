inherit "/d/Cirath/std/monster";
#include <wa_types.h>
#include <options.h>
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/common/introfnc.h"
#include "wbt.h"

void
arm_me();

void
create_monster()
{
	::create_monster();
	set_race_name("teacher");
	set_name("rasin");
   set_title("Head Instructor of the Warrior's School of Tyr");
	set_adj("old");
	set_adj("learned");

	set_short("old learned great teacher");
   set_long("An older human, Rasin has been at the Warrior's "
	+"School of Tyr since it opened.  Rumor has it that "
	+"at one time he was a gladiator, but that he won his "
	+"freedom during the invasion of Uruk by single-handedly "
	+"killing the personal guard of the King of Uruk, and "
	+"then grievously wounding the King himself.  His "
	+"body looks to be solid muscle beneath the darkly "
	+"tanned skinned, and innumerable scars cover all "
	+"of his exposed flesh.  You are not sure if "
	+"the years have been kind to him, and are not sure "
	+"you want to find out.\n");

	add_prop(LIVE_I_NEVERKNOWN, 1);

	set_stats(({ 195, 190, 210, 130, 150, 120}));

	set_skill(SS_DEFENCE, 100);
	set_skill(SS_PARRY, 100);
	set_skill(SS_WEP_AXE, 100);

	set_alignment(120);

	set_act_time(10);
	set_cact_time(5);

	add_act("' Hey, you fool in the corner, don't stay at one place! Fight!");
	add_act("' Hello, little one! You wanna learn in this school ?");


	add_cact("shout Noone can slay me!");
	add_cact("' What ??? You think I'll let you go now?");
	add_cact("emote smiles sadistically.");

	set_default_answer("Teacher says: I know many, many things, but never heard about that.\n");
}

void
arm_me()
{
	clone_object(WWORK+"tbracers.c")->move(TO);
	clone_object(WWORK+"tcloak.c")->move(TO);
	clone_object(WWORK+"thelm.c")->move(TO);
	clone_object(WWORK+"tplate.c")->move(TO);
	clone_object(WWORK+"taxe.c")->move(TO);
	clone_object(WWORK+"tshield.c")->move(TO);
	command("wield all");
	command("wear all");
}

int
query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
    me=this_object();

    if(random(12)) return 0;

    hitresult = enemy->hit_me(400 + random(150), W_BLUDGEON, me, -1);
    how = "unharmed";
    if (hitresult[0] > 0) how = "barely touched";
    if (hitresult[0] > 15) how = "slightly hurt";
    if (hitresult[0] > 30) how = "damaged";
    if (hitresult[0] > 50) how = "massively injured";
    if (hitresult[0] > 75) how = "on the verge of death";

    enemy->catch_msg(QCTNAME(me) + " lashes out at you with "+
                     "a kick.\n");
    enemy->catch_msg("You feel " + how + ".\n");

    tell_watcher(QCTNAME(me)+" strikes "+QCTNAME(enemy)+
                 " with a brutal kick.\n",
                 me, enemy);

    if(enemy->query_hp() <= 0) enemy->do_die(me);

    return 1;
}

