/* 
	*Borrowed/adapted from the trollshaw troll maker
	*Altrus, July 2005

    ChangeLog:

    April 27, 2006 Palmer:
    Added _uruk_ally_npc_ to block north passage


*/
#include "/d/Shire/sys/defs.h"
inherit SHIRE_MONSTER;
inherit "/d/Shire/lib/assist_friend";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include "/d/Shire/common/make_money.h"

#define ARM_DIR "/d/Shire/moria/arm/"
#define WEP_DIR "/d/Shire/moria/wep/"

string shire_npc_name = "_uruk_ally_npc_";

create_shire_monster()
{
	object wep, arm;
	int y,z;
	string *desc, *orc_type;

// sets up arrays for different adjectives and types of woodsmen

	desc  = (({"hardy", "rugged", "smelly", "rude", "black-skinned", "dim-witted", "tense", "fearless", "thick-armed", "green-skinned", "hairy", "bald", "shifty", "furtive", "powerful", "wide-nosed", "putrid", "mean"}));

	orc_type  = (({"short", "wiry", "broad"}));

// randomly chooses adjectives and type of orc to create

	y = random(sizeof(orc_type));
	z = random(sizeof(desc));

	set_name("orc");
	add_name(shire_npc_name);

	set_adj(orc_type[y]);
	set_adj(desc[z]);
	set_race_name("orc");
	set_long("This is one of the many orc infesting the mines of Moria. He may be short, but he looks ferocious, and ready for a fight.\n");

	set_alignment(-500 - random(100));
	set_gender(G_MALE);

	add_prop(CONT_I_WEIGHT, 100*1000);
	add_prop(CONT_I_HEIGHT, 250);
	add_prop(LIVE_I_SEE_DARK, 80);
	add_prop(LIVE_I_SEE_INVIS, 99);


	switch (orc_type[y]) // set's stats based on size
	{
		case "short": 
		{
		    set_stats(({160+random(20),
			170+random(20),
			125+random(20),
			20+random(20),
			20+random(20),
			250}));
		    break;
		}
		
		case "wiry": 
		{
		    set_stats(({170+random(20),
			180+random(20),
			135+random(20),
			25+random(20),
			25+random(20),
			250}));
		    break;
		}
		case "broad":
		{
		    set_stats(({180+random(50),
			190+random(50),
			155+random(50),
			25+random(50),
			25+random(50),
			250}));
		    break;
		}
	}
	
	make_gold(1+random(5));

	set_cact_time(2);
	add_cact("emote curses at you.");
	add_cact("smile bloodthirstily");
	add_cact("emote vows to pick your bones clean.");

	set_skill(SS_WEP_AXE, 90);
	set_skill(SS_WEP_KNIFE, 100);
	set_skill(SS_2H_COMBAT,90);
	set_skill(SS_DEFENCE, 95);
	set_skill(SS_PARRY, 100);
	set_skill(SS_AWARENESS, 85);
	set_skill(SS_BLIND_COMBAT, 75);

	add_prop(LIVE_I_NEVERKNOWN, 1);
	
	set_attack_chance(100);
	set_aggressive(1);
	
// Armours

	if(orc_type[y] == "broad")
		arm = ({"leather_plate", "leather_stud", "leather_tunic"})[random(3)];
	else
		arm = ({"leather_stud", "leather_tunic"})[random(2)];

	clone_object(ARM_DIR + arm)->move(TO);

	arm = ({"leather_cap", "metal_cap", "leather_hood"})[random(3)];
	clone_object(ARM_DIR + arm)->move(TO);

	arm = ({"leather_guards", "metal_guards"})[random(2)];
	clone_object(ARM_DIR + arm)->move(TO);

	arm = ({"leather_arm", "metal_arm"})[random(2)];
	clone_object(ARM_DIR + arm)->move(TO);

// Weapons
	
	if(orc_type[y] == "broad")
	{
		wep = ({"long_knife", "short_knife", "broad_knife"})[random(3)];
		clone_object(WEP_DIR + wep)->move(TO);
	}
	
	wep = ({"broad_axe", "long_axe", "iron_axe", "steel_axe", "double_axe", "wood_axe"}) [random(6)];
	clone_object(WEP_DIR + wep)->move(TO);

	command("wear armours");
	command("wield weapons");
}

int special_attack(object enemy)
{
	object me;
	mixed* hitresult;
	string how;
	me = TO;

	if (random(3))
		return 0;

	hitresult = enemy->hit_me(400 + random(200), W_BLUDGEON, me, -1);
	how = " with little effect";
	if (hitresult[0] > 0)
		how == " lightly";
	if (hitresult[0] > 5)
		how = " hard";
	if (hitresult[0] > 10)
		how = " intensely, leaving bruises";
	if (hitresult[0] > 15)
		how = " forcefully, bruising and battering";
	if (hitresult[0] > 20)
		how = " mightily, crushing limbs";
	if (hitresult[0] > 25)
		how = " brutally, causing blood to flow";
	if (hitresult[0] > 30)
		how = " ruthlessly, breaking bones";
	
	enemy -> catch_msg(QCTNAME(me) + " slams you" + how + ".\n");
	
	tell_watcher(QCTNAME(me) + " rushes " + QTNAME(enemy) + "!\n"+ capitalize(enemy->query_pronoun()) + " is slammed" + how + ".\n", enemy);
	
	if (enemy->query_hp() <= 0)
		enemy->do_die(me);
    
	return 1;
}
