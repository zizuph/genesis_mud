/*
 * 2015-07-25 - Elmore
 * New boss creature
 *
 */

#pragma save_binary
#pragma strict_types

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <composite.h>

inherit AM_FILE
inherit "/lib/unique";
inherit "/d/Krynn/open/auto_teaming";

object weapon;

string *gAdj1 = ({ "gigantic", "colossal", "enormous", "titanic",
    "scarred", "gargantuan"});
string *gAdj2 = ({ "forceful", "repulsive", "horrid", "snarling",
    "beastly", "frightening", "dangerous", "lethal" });
	
#ifndef ONE_OF
#define ONE_OF(x)   (x[random(sizeof(x))])
#endif

void
create_krynn_monster()
{
    set_name("malak");
    set_race_name("troll");
    set_living_name("malak");
    set_title("Bonebreaker, the Protector of the Fifth Talisman"); 
    set_adj(({"gigantic","mean-looking"}));
    string adj1 = ONE_OF(gAdj1);
    string adj2 = ONE_OF(gAdj2);
    set_adj(adj1);
    add_adj(adj2);
    set_short(adj1+ " "+adj2+" forest troll");
    set_gender(0);
    set_long("The " + short() + " is a gigantic humanoid creature, covered " +
        "in thick fur. Long, yellow fangs reach out of his cruel mouth, " +
        "and a foul smell surrounds him. His skin is covered with scars "+
		"and he seems quite capable of defending himself.\n"+
        "He is a member of the fifth talisman.\n"+
        "He has a tattoo on his forehead that looks like a five-pointed star.\n"+
        "He is bald.\n");
    set_knight_prestige(100);
    set_stats(({250+random(100),200+random(20),300+random(40),170,140,220}));
    set_introduce(1);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_WEP_AXE, 200);
	set_skill(SS_WEP_POLEARM, 200);
    set_skill(SS_WEP_CLUB, 200); 
    set_skill(SS_BLIND_COMBAT, 80);
    set_alignment(-500);
    set_all_hitloc_unarmed(60);
    set_pick_up_team(({"troll"}));
    add_prop(LIVE_I_SEE_DARK, 7);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    set_hp(query_max_hp());
    set_exp_factor(200);
    set_alarm(0.0, 5.0, "heal", TO);

    if (random(2))
    {
        weapon = clone_unique(MWEP + "crystalAxe", 3, MWEP + "tree",0, 20);
        weapon->move(TO, 1);
    }
    else
    {
        weapon = clone_unique(MWEP + "war_maul", 4, MWEP + "tree",0, 30);
        weapon->move(TO, 1);
    }
    command("wear all");
    command("wield all");
}

void
heal()
{
	if (TO->query_hp() < TO->query_max_hp())
	{
		TO->heal_hp(400+random(200));
		tell_room(E(TO), "The "+ QCTNAME(TO) + "'s wounds begins to close and he looks healthier!\n",TO);
	}
}

int
special_attack(object enemy)
{
    int pen;
    mixed hitres;
    string how;

    if (random(5))
    {
        pen = 500+random(750);
        hitres = enemy->hit_me(pen, 40, TO, -1);

        if(hitres[0] <= 10)
            how = "absolutely no sound";
        if(hitres[0] > 10)
            how = "a cracking sound";
        if(hitres[0] > 30)
            how = "a shattering sound";
        if (hitres[0] > 60)
            how = "a crunching sound";

        enemy->catch_msg(QCTNAME(TO) + 
          " grabs you by the throat with one if his massive hands and " +
          "punches you in your chest with a clenched fist.\n" +
		  "You hear " + how + " from your bones as you land after flying through the air.\n");

        tell_room(E(TO), QCTNAME(TO) + " grabs "+ QTNAME(enemy) +"'s throat with one of " +
		  "his massive hands and punches him in the chest with a clenched fist.\n" +
          "You see " + QTNAME(enemy) + " fly through the air.\n",({enemy, TO}));

        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(TO);
			TO->command("shout Come back, you forgot your corpse!");
			TO->command("get all from corpse");
			TO->command("wear all");
			TO->command("spit corpse");
			TO->command("growl");
        }
		string *exists = E(TO)->query_obvious_exits();
		string random_exit = exists[random(sizeof(exists))];
			
		// Check available exists and select a random direction to move the enemy in
		if(!P("Serion_stun",enemy))
		{
			enemy->command(random_exit);
		}
		
		// 20% chance of stunning the enemy (Serion's stun works nice for this)
		if (!random(4))   
			if(!P("Serion_stun",enemy))
				clone_object("/d/Ansalon/balifor/port_balifor/obj/serion_stun")->move(enemy);

		if (!random(1))
			if(!P("Serion_stun",enemy))
				TO->command("shout Hey! You no run!");
		
		// 50% chance to follow the target
		if (!random(1) && !P("Serion_stun",enemy))
		{
			TO->command(random_exit);  
			// 25% chance to force him in a different location again
			if (!random(3) && !P("Serion_stun",enemy))
			{
				enemy->catch_msg(QCTNAME(TO) + " punches you hard in the chest with a clenched fist.\n" +
				  "You fly through the the air.\n"+
				  "You land hard on the ground.\n");

				tell_room(E(TO), QCTNAME(TO) + " punches "+ QTNAME(enemy) + " hard in the chest with " +
				  "a clenched fist.\n"+
				  "You see "+ QTNAME(enemy) + " fly through the air.\n",({enemy, TO}));

				string *exists = E(TO)->query_obvious_exits();
				string random_exit = exists[random(sizeof(exists))];
				enemy->command(random_exit);
				// 50% chance to follow the target
				if (!random(1))
					TO->command(random_exit);
			}	
		}
        return 1;
    }
    return 0;
}
