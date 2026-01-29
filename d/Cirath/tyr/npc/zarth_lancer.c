
#pragma strict_types
#pragma save_binary 

inherit "/d/Cirath/std/monster";
#include <wa_types.h>
#include <options.h>
#include "defs.h"

#define JDESC ({"agile", "menacing", "savage", "huge"})[random(4)]
#define JWEP ({"guard_spear", "steel_spear"})[random(2)]

void
arm_me();

void
zarth_help();

void
create_monster()
{
	::create_monster();
	set_race_name("guard");
	set_name(({"human", "lancer"}));
	set_adj("brutal");
	set_adj(JDESC);

	set_long("This is a Lancer. He looks very grim and he "
		+"would probably not hesitate kill you.\n");

	add_prop(LIVE_I_NEVERKNOWN, 1);

	set_stats(({ 140, 160, 140, 100, 100, 120}));

	set_skill(SS_DEFENCE, 60);
	set_skill(SS_PARRY, 45);
	set_skill(SS_WEP_POLEARM, 90);
	set_skill(SS_BLIND_COMBAT, 35);

	set_alignment(-300 + random(601));

	set_act_time(10);
	set_cact_time(5);

	add_act("emote peers around menacingly.");
	add_act("emote sighs deeply.");
	add_act("' You better leave now.");
	add_act("poke all");

	add_cact("' Stop this! Now I am really angry.");
	add_cact("emote grumbles loudly.");
	add_cact("' Leave now or die!");
	add_cact("emote gasps in astonishment.");

	set_default_answer("Don't ask me. Ask someone else.");
}

void
arm_me()
{
	clone_object(TYR_ARM + "jail_body.c")->move(TO);
	clone_object(TYR_ARM + "jail_head.c")->move(TO);
	clone_object(TYR_ARM + "jail_cloak.c")->move(TO);
	clone_object(TYR_WEP + JWEP)->move(TO);
	command("wear all");
	command("wield all");
}

void
zarth_help()
{
	command("assist zarth");
}

/* sets unarmed combat off, giving more weapon attacks! */

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
 
    if(random(4)) return 0;
 
    if (me->query_weapon(W_RIGHT) || me->query_weapon(W_BOTH))
   hitresult = enemy->hit_me(150+ random(50), W_BLUDGEON, me, -1);
    how = "pathetically";
    if (hitresult[0] > 0) how = "lightly";
    if (hitresult[0] > 15) how = "hard";
    if (hitresult[0] > 30) how = "painfully";
    if (hitresult[0] > 50) how = "smashingly";
 
    enemy->catch_msg(QCTNAME(me) + " hits you " + how + " with the butt of "+
                     HIS_HER(me) + " spear.\n");
 
    tell_watcher(QCTNAME(me)+" hits "+QCTNAME(enemy)+ " " + how +  
                 " with the butt of " + HIS_HER(me) + " spear.\n",
                 me, enemy);
 
    if(enemy->query_hp() <= 0) enemy->do_die(me);
 
    return 1;
}