/*
 * Coded by Arman ages ago.
 *
 * Modified by Arman July 2016 to add minor fire vulnerability
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE


string *gAdj1 = ({"gigantic","massive","huge",
  "ferocious","warty","green-hided"});

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;


    set_name("troll");
    set_adj(ONE_OF(gAdj1));
    add_adj("river");
    add_adj(ONE_OF(gAdj1));
    set_race_name("troll");
    set_short(ONE_OF(gAdj1)+ " river troll");
    set_long("This massively muscled creature is a fearsome " +
      "river troll! While it is stooped from spending its life crouched " +
      "under a bridge, you would estimate that its full height " +
      "would be well above ten feet tall.\n");

    set_stats(({250, 100, 200, 40, 30, 100}));
    set_intoxicated(1000);
    set_hp(10000);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    // vulnerability to fire
    add_prop(OBJ_I_RES_FIRE, -35);

    // vulnerability to acid
    add_prop(OBJ_I_RES_ACID, -35);

    set_alignment(-450);
    set_knight_prestige(50);

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 60);
    set_skill(SS_AWARENESS, 10);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 70);

    set_all_hitloc_unarmed(40);

    set_act_time(10);
    add_act("emote mutters: Is dat someone crossin da " +
      "bridge?");
    add_act("emote grumbles about being hungry.");
    add_act("say Kenda ah tasty! Dwarfies taste like " +
      "leather. Yuck!");
    add_act("emote grumbles as he searches through " +
      "the bones under the bridge.");

    set_cact_time(0);
    add_cact("say Chomp on dis, scumbag!");


}


int
special_attack(object enemy)
{

    int attacktype, pen, wloc;
    mixed hitres;

    string *hitloc, how;

    attacktype = random(5);
    hitloc = ({"left arm","right arm","body","left leg","right leg"});

    if(attacktype == 1)
    {
    // Make sure that we can actually attack the target
    if (enemy->query_not_attack_me(TO, -1))
    {
        return 1; // round is ended so return 1.
    }
        
	pen = 100 + random(500);
	hitres = enemy->hit_me(pen, 50, TO, -1);
	wloc = random(5);

	if(hitres[0] <= 0)
	    how = "his claws just missing";
	if(hitres[0] > 0)
	    how = "his claws grazing the skin of";
	if(hitres[0] > 10)
	    how = "his claws slicing deeply into";
	if(hitres[0] > 20)
	    how = "his claws deeply penetrating";
	if(hitres[0] > 40)
	    how = "burying his claws deeply into";
	if(hitres[0] > 60)
	    how = "his claws almost rendering";
	enemy->catch_msg(QCTNAME(TO)+ " reaches for you " +
	  "in a rage, " +how+ " your " +
	  hitloc[wloc]+ ".\n");
	tell_room(E(TO), QCTNAME(TO)+
	  " reaches for " +QTNAME(enemy)+ " in a rage, " +
	  how+ " " +QTNAME(enemy)+ "'s"+
	  " " +hitloc[wloc] + ".\n", ({enemy,TO}));

	if(enemy->query_hp() <= 0)
	{
	    enemy->do_die(TO);
	}
	return 1;
    }
    return 0;
}
