/* 
	*Borrowed/adapted from the trollshaw troll maker
	*Altrus, June 2005
*/

//inherit "/std/monster";
//inherit "/d/Shire/esgaroth/npcs/assist_friend";
inherit "/d/Shire/orcmaker/team";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/archet/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Shire/common/make_money.h"

string shire_npc_name = "_archet_npc_";

create_monster()
{
	seteuid(getuid());
	if(!IS_CLONE)
		return;
	create_guards(random(4));
}

create_guards(int i)
{
	object wep, arm;
	int y,z;
	string *desc, *woodsmen_type;

// sets up arrays for different adjectives and types of woodsmen

	desc  = (({"hardy", "rugged", "brawny", "implaccable", "ruddy", "muscular", "tense", "fearless", "thick-armed", "rude", "hairy", "scruffy", "proud", "imposing", "powerful", "broad-shouldered", "polite", "friendly"}));

	woodsmen_type  = (({"tall", "short", "massive"}));

// randomly chooses adjectives and type of woodsmen to create

	y = random(sizeof(woodsmen_type));
	z = random(sizeof(desc));

	add_prop(LIVE_I_NEVERKNOWN, 1);

	set_name("woodsman");
	add_name(shire_npc_name);

	set_adj(woodsmen_type[y]);
	set_adj(desc[z]);
	set_race_name("human");
	set_long("This is a woodsman of Archet. He is one of many men that have travelled from the south in hopes of avoiding the brewing trouble there. He looks like an experienced woodsman, and seems quite formidable.\n");

	set_alignment(100 + random(100));
	set_gender(0);

	add_prop(CONT_I_WEIGHT, 100*1000);
	add_prop(CONT_I_HEIGHT, 350);
	add_prop(LIVE_I_SEE_DARK, 80);

	switch (woodsmen_type[y]) // set's stats based on size
	{
		case "short": 
		{
		    set_stats(({120+random(20),
			120+random(20),
			125+random(20),
			20+random(20),
			20+random(20),
			100}));
		    break;
		}
		
		case "tall": 
		{
		    set_stats(({130+random(20),
			130+random(20),
			135+random(20),
			25+random(20),
			25+random(20),
			150}));
		    break;
		}
		case "massive":
		{
		    set_stats(({150+random(50),
			150+random(50),
			155+random(50),
			25+random(50),
			25+random(50),
			150+random(5)}));
		    break;
		}
	}
	
	make_gold(1+random(5));

	set_act_time(6);
	add_act("emote laughs long and loud!");
	add_act("shout Timber!!");
	add_act("emote looks appraisingly at the trees.");
	add_act("chuckle");
	add_act("emote inhales a deep breath of forest air.");
	
	set_cact_time(2);
	add_cact("emote curses at you.");
	add_cact("smile grimly");
	add_cact("emote vows to have revenge on you.");

	set_skill(SS_WEP_AXE, 90);
	set_skill(SS_WEP_KNIFE, 100);
	set_skill(SS_2H_COMBAT,90);
	set_skill(SS_DEFENCE, 95);
	set_skill(SS_PARRY, 100);
	set_skill(SS_AWARENESS, 85);
	set_skill(SS_BLIND_COMBAT, 75);

	add_prop(LIVE_I_NEVERKNOWN, 1);

// Armours

	if(woodsmen_type[y] == "massize")
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
	
	if(woodsmen_type[y] == "massize")
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

	hitresult = enemy->hit_me(350 + random(100), W_BLUDGEON, me, -1);
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
