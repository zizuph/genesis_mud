/*
 * WoHS test npc
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <const.h>
#include "/d/Krynn/common/defs.h"

inherit C_FILE
inherit "/std/act/attack";
inherit "/std/act/action";

string *gAdj1 = ({"grey-skinned","stony","chiselled",
  "grey","dusty","winged"});

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void
create_creature()
{
    if(!IS_CLONE)
	return;

    set_name("gargoyle");
    set_adj(ONE_OF(gAdj1));
    add_adj("guardian");
    set_race_name("gargoyle");
    set_short(ONE_OF(gAdj1)+ " guardian gargoyle");
    set_long("This monstrous winged creature before you is one of the "+
          "magical stone guardians of the Tower of High Sorcery "+
          "in Daltigoth. Armed with sharp claws and a spear-like tail, "+
          "it is a formidable guardian indeed!\n");
    set_gender(G_NEUTER);

    set_stats(({200, 250, 200, 40, 30, 100}));
    set_intoxicated(1000);
    set_hp(10000);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    add_prop(OBJ_I_RES_EARTH, 80);
    add_prop(OBJ_I_RES_MAGIC, 20);

    set_alignment(0);
    set_knight_prestige(0);

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 60);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 70);

    set_attack_unarmed(0, 50, 35, W_SLASH,  80, "claws");
    set_attack_unarmed(1, 35, 80, W_IMPALE, 20, "spear-like tail");

    set_hitloc_unarmed(1,  60, 80, "body");
    set_hitloc_unarmed(2, 50, 10, "head");
    set_hitloc_unarmed(3, 40, 10, "wings");


    set_act_time(10);
    add_act("emote flaps its wings, stirring up dust on the ground " +
        "around it.");
    add_act("emote rumbles deep in its chest, a sound like boulders "+
        "rubbing together.");
    add_act("emote stretches its stony wings.");
    add_act("emote gazes around with blazing red eyes, looking for "+
        "invaders to the tower.");

    set_cact_time(5);
    add_cact("emote gazes at the invaders with blazing red eyes.");
    add_cact("emote extends its claws aggressively.");
    add_cact("emote keens silently.");
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
	    how = "its claws just missing";
	if(hitres[0] > 0)
	    how = "its claws grazing the skin of";
	if(hitres[0] > 10)
	    how = "its claws slicing deeply into";
	if(hitres[0] > 20)
	    how = "its claws deeply penetrating";
	if(hitres[0] > 40)
	    how = "burying its claws deeply into";
	if(hitres[0] > 60)
	    how = "its claws almost rendering";
	enemy->catch_msg(QCTNAME(TO)+ " reaches for you, " +
	  how+ " your " +hitloc[wloc]+ ".\n");
	tell_room(E(TO), QCTNAME(TO)+
	  " reaches for " +QTNAME(enemy)+ ", " +how+ 
          " " +QTNAME(enemy)+ "'s"+
	  " " +hitloc[wloc] + ".\n", ({enemy,TO}));

	if(enemy->query_hp() <= 0)
	{
	    enemy->do_die(TO);
	}
	return 1;
    }
    return 0;
}
