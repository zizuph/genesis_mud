#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>

#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE
inherit AUTO_TEAM

#define ARM1 ARMOUR + "shield"
#define ARM2 ARMOUR + "l_gauntlets"
#define ARM3 ARMOUR + "breastplate"
#define WEP WEAPON + "mace"
#define WEP2 WEAPON + "axe"

int rf = random(26);
string *gAdj1 = ({"mighty","strong","black-bearded",
  "scarred","muscular","buff","proud","gay"});

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_pick_up_team(({"centaur"}));
    set_max_team_size_auto_join(4);

    set_name("centaur");
    set_adj(ONE_OF(gAdj1));
    set_race_name("centaur");
    set_gender(G_MALE);
    set_short(implode(query_adjs()," ") + " centaur");
    set_long("Before you stands one of the mythical children of Krynn, " +
      "a centaur. Appearing as a cross between a powerful horse and a " +
      "broad-chested human with rippling muscles and a handsome, angular " +
      "face, you do not doubt that when angered " +
      "he would make a powerful " +
      "opponent.\n");

    set_stats(({136 + rf,139 + rf,145 + rf,137 + rf,137 + rf,135 + rf}));
    set_hp(10000);
    set_all_hitloc_unarmed(23);

    set_alignment(500);
    set_knight_prestige(-200);
    set_skill(SS_WEP_CLUB, 75 + rf);
    set_skill(SS_WEP_AXE, 70 + rf);
    set_skill(SS_DEFENCE,75);
    set_skill(SS_PARRY, 65 + rf);
    set_skill(SS_BLIND_COMBAT, 30 + rf);
    set_skill(SS_AWARENESS, 20 + rf);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    remove_attack(W_FOOTR);
    remove_attack(W_FOOTL);

    set_act_time(10);
    add_act("emote bows in greeting before you, extending his " +
      "foreleg and touching his hand to his shaggy hair.");
    add_act("emote stamps the ground aggressively with his hooves.");
    add_act("say I wish the kender would quit trying to ride me. It is " +
      "quite annoying.");
    add_act("assist");
    add_act("assist");
    add_act("assist");
    add_act("emote flicks his tail at an annoying insect.");
    add_act("chuckle merr");

    set_cact_time(5);
    add_cact("emote booms: Put thy puny weapons down. Ye surely do not have " +
      "a chance against me!");
    add_cact("emote rears up aggressively at you!");
    add_cact("say Leave our glade fiend or thou shalt surely die!");
    add_cact("say For the love of Chislev begone!");

    equip(({ (random(2) ? WEP : WEP2), ARM1, ARM2, ARM3 }));


    /* Cotillion for AoB, 2020-07-13 */
    set_exp_factor(80);
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
	pen = 35 + rf;

	hitres = enemy->hit_me(F_PENMOD(pen, 80), W_BLUDGEON, TO, -1);

	if(enemy->query_weapon(W_BOTH))
	{
	    wep_string = enemy->query_weapon(W_BOTH)->short();

	    if(enemy->query_skill(SS_PARRY) > 60+random(30))
	    {
		enemy->catch_msg(QCTNAME(TO)+ " strikes out at your "+
		  wep_string+ " with his front hooves, but you manage to "+
		  "parry them away.\n");
		tell_room(E(TO), QCTNAME(TO)+ " strikes out at "+
		  QTNAME(enemy)+ " with his front hooves, but "+ QTNAME(enemy)+
		  " manages to parry the attack away.\n", ({enemy,TO}));
		return 1;
	    }
	    enemy->catch_msg(QCTNAME(TO)+ " strikes out at your " +
	      wep_string+ " with his front hooves!\n");
	    tell_room(E(TO), QCTNAME(TO)+ " strikes out at " +
	      QTNAME(enemy)+ "'s " +wep_string+ " with his " +
	      "front hooves!\n", ({enemy, TO}));

	    weapon = enemy->query_weapon(W_BOTH);
	    weapon->remove_broken();
	}
	else
	{

	    enemy->catch_msg(QCTNAME(TO) + 
	      " strikes you savagely with his front hooves!\n");
	    tell_room(E(TO), QCTNAME(TO) + " strikes out at " +
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
