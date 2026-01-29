/*
	*Orc guards near the backdoor
	*Altrus, June 2005
*/
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/greymount/defs.h"

inherit SHIRE_MONSTER;
inherit "/std/act/attack";

string get_adjective_one();
string get_adjective_two();

void create_shire_monster()
{
	set_name("orc");
	set_race_name("orc");
	set_adj(({get_adjective_one(), get_adjective_two()}));
	set_long("This orc has a fierce look on his face. He appears ready for a fight, and probably would not give any quarter.\n");
	
	set_gender(0);
	set_appearance(-95);
	set_alignment(-900 - random(200));
	set_stats(({190 + random(20), 175 + random(50), 200 + random(25), 50 + random(10), 25 + random(10), 180 + random(10)}));
	add_prop(CONT_I_WEIGHT, 35000 +random(500));
	add_prop(CONT_I_HEIGHT, 800 + random(20));
	add_prop(LIVE_I_NEVERKNOWN, 1);
	add_prop(LIVE_I_SEE_DARK, 100); 
	add_prop(LIVE_I_SEE_INVIS, 75);
	add_prop(LIVE_I_QUICKNESS, 25);
	add_prop("_live_m_no_drain", 1);
	
	set_skill(SS_BLIND_COMBAT, 75);
	set_skill(SS_DEFENCE, 90);
	set_skill(SS_PARRY, 75);
	set_skill(SS_UNARM_COMBAT, 60);
	set_skill(SS_WEP_SWORD, 80);
	set_skill(SS_WEP_AXE, 80);
	set_skill(SS_WEP_CLUB, 80);
	set_skill(SS_WEP_KNIFE, 80);
	set_skill(SS_2H_COMBAT, 80);
	
	set_attack_chance(100);
	set_aggressive(1);
	
	set_act_time(7);
	add_act("grumble");
	add_act("spit");
	add_act("curse");
	add_act("emote scratches his filth-encrusted body.");
	add_act("emote mutters something about dead elves.");
	add_act("emote curses the sun.");
	add_act("emote tells you to shove it!");
	
	set_introduce(0);
	
	object arm, wep;
	
	arm = ({"iron_chainmail", "leather_armour", "leather_shirt"})[random(3)];
	clone_object(ARM_DIR + arm)->move(TO);

	arm = ({"iron_greaves", "dented_greaves", "shin_guards"})[random(3)];
	clone_object(ARM_DIR + arm)->move(TO);
	
	arm = ({"leather_cap", "metal_cap"})[random(2)];
	clone_object(ARM_DIR + arm)->move(TO);

	arm = ({"leather_arm", "metal_arm"})[random(2)];
	clone_object(ARM_DIR + arm)->move(TO);
	
	wep = ({"rusty_blade", "chipped_knife", "steel_axe", "iron_club", "war_pick", "studded_club"})[random(6)];
	clone_object(WEP_DIR + wep)->move(TO);
	
	wep = ({"rusty_blade", "chipped_knife", "heavy_sword", "studded_club", "iron_club"})[random(5)];
	clone_object(WEP_DIR + wep)->move(TO);
	
	command("wear armours");
	command("wield weapons");
}

public string get_adjective_one()
{
	string *adjectives, adj;

	adjectives = ({"large", "massive", "muscular", "tall" , "lean"});
	
	adj = adjectives[random(sizeof(adjectives))];

	return adj;
}

public string get_adjective_two()
{
	string *adjectives, adj;

	adjectives = ({"ruthless", "cruel", "cunning", "powerful", "snarling", "fearless", "green-skinned", "black-haired", "pock-marked", "slobbering", "fanged"});
	
	adj = adjectives[random(sizeof(adjectives))];

	return adj;
}

int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
    string what;
    me = TO;

    if (random(3))
        return 0;

    what = ({"headbutts", "kicks", "punches"})[random(3)];
    
    hitresult = enemy->hit_me(250 + random(100), W_BLUDGEON, me, -1);
    how = " with little effect";
    if (hitresult[0] > 0)
        how == " feebly";
    if (hitresult[0] > 5)
        how = " lightly";
    if (hitresult[0] > 10)
        how = " hard";
    if (hitresult[0] > 15)
        how = " painfully";
    if (hitresult[0] > 20)
        how = " brutally";
    if (hitresult[0] > 25)
        how = " savagely";
    if (hitresult[0] > 30)
        how = " mercilessly";
    enemy -> catch_msg(QCTNAME(me) + " " + what + " you" + how + ".\n");
    tell_room(ENV(TO),QCTNAME(me) + " " + what + " " + QTNAME(enemy) + "" + how + ".\n",enemy);
    if (enemy->query_hp() <= 0)
        enemy->do_die(me);
    return 1;
}
