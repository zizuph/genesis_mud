#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE
inherit AUTO_TEAM

#define ARM2 ARMOUR + "l_gauntlets"
#define ARM3 ARMOUR + "breastplate"
#define WEP WEAPON + "lance"

int rf = random(31);
object unicorn;

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_pick_up_team(({"centaur"}));
    set_max_team_size_auto_join(4);

    set_name("centaur");
    add_name("chieftain");
    set_adj("noble");
    set_race_name("centaur");
    set_gender(G_MALE);
    set_short("centaur chieftain");
    set_long("Before you stands one of the mythical children of Krynn, " +
      "a centaur. Appearing as a cross between a powerful horse and a " +
      "broad-chested human with rippling muscles and a handsome, angular " +
      "face, you do not doubt that when angered " +
      "he would make a powerful " +
      "opponent.\n");

    set_stats(({149 + rf,137 + rf,143 + rf,137 + rf,136 + rf,139 + rf}));
    set_hp(10000);
    set_all_hitloc_unarmed(25);

    set_alignment(500);
    set_knight_prestige(-200);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_DEFENCE,55+random(35));
    set_skill(SS_PARRY, 55+random(35));
    set_skill(SS_BLIND_COMBAT, 30 + rf);
    set_skill(SS_AWARENESS, 20);

    remove_attack(W_FOOTR);
    remove_attack(W_FOOTL);

    set_act_time(10);
    add_act("emote bows in greeting before you, extending his " +
      "foreleg and touching his hand to his shaggy hair.");
    add_act("emote stamps the ground aggressively with his hooves.");
    add_act("say I wish the kender would quit trying to ride me. It is " +
      "quite annoying.");
    add_act("emote flicks his tail at an annoying insect.");
    add_act("chuckle merr");

    set_cact_time(5);
    add_cact("emote booms: Put thy puny weapons down. Ye surely do not have " +
      "a chance against me!");
    add_cact("emote rears up aggressively at you!");
    add_cact("say Leave our glade fiend or thou shalt surely die!");
    add_cact("say For the love of Chislev begone!");
}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(WEP)->move(TO,1);
    command("wield all");
    clone_object(ARM2)->move(TO,1);
    clone_object(ARM3)->move(TO,1);
    command("wear all");
}

int
special_attack(object enemy)
{
    int attacktype,
    pen,
    att,
    wloc;

    mixed hitres;

    string *hitloc,
    *attack,
    how;
    object weapon;
    string wep_string;

    attacktype = random(5);

    if (attacktype == 1)
    {
	pen = 50 + random(100);
        
	hitres = enemy->hit_me(pen, 20,TO,-1);
	if(enemy->query_weapon(W_BOTH))
	{
	    wep_string = enemy->query_weapon(W_BOTH)->short();
	    weapon = enemy->query_weapon(W_BOTH);

	    if(enemy->query_skill(SS_PARRY) > 74+random(20))
	    {
		enemy->catch_msg(QCTNAME(TO)+ " strikes out at your "+
		  wep_string+ " with his front hooves, but you manage to " +
		  "parry the attack away.\n");
		tell_room(E(TO), QCTNAME(TO)+ " strikes out at " +QTNAME(enemy)+
		  " with his front hooves, but "+QTNAME(enemy)+ " manages to "+
		  "parry the attack away.\n", ({enemy, TO}));
		return 1;
	    }
	    enemy->catch_msg(QCTNAME(TO) + " strikes out at your " +
	      wep_string+ " with his front hooves!\n");
	    tell_room(E(TO), QCTNAME(TO)+ " strikes out at " +QTNAME(enemy)+
	      "'s " +wep_string+ " with his front hooves!\n",
	      ({enemy, TO}));
	    weapon->remove_broken();
	}
	else
	{

	    enemy->catch_msg(QCTNAME(TO) + 
	      " strikes you savagely with his front hooves!\n");
	    tell_room(E(TO),QCTNAME(TO) + " strikes out at " +
	      OBJECTIVE(enemy) + " savagely with his hooves!\n",
	      ({enemy, TO }));
	}

	if (enemy->query_hp() <= 0)
	{
	    enemy->do_die(TO);
	}
	return 1;
    }
    return 0;
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}

public void
do_die(object killer)
{
       command("shout Chislev! Protect my grove!");
       tell_room(E(TO),"Suddenly the grove becomes extremely quiet in expectation. " +
         "And then with a shrill neigh, a mythical unicorn gallops into the grove!\n");
       unicorn = clone_object(FNPC + "unicorn");
       unicorn->move(E(TO));
       unicorn->command("kill " +killer->query_real_name()); 
    ::do_die(killer);
}
