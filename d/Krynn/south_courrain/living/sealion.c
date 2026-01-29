/*
 *  Sea Lion of the Courrain Sea, Arman - Feb 2021
 *
 *  It's heart is the primary component for swimming
 *  potions.
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <state_desc.h>
#include <files.h>

inherit C_FILE
inherit "/std/act/attack";
inherit "/std/act/action";

#define CLAW   "/d/Krynn/south_courrain/obj/sealion_claw"
#define HEART  "/d/Krynn/south_courrain/obj/sealion_heart"

string *gAdj1 = ({"ferocious", "territorial", "vicious",
          "huge","strong","thick-maned", "wild"});

#define SEA_NET_ID "_sea_net_id"

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void
create_creature()
{
    int i;

    string a1 = ONE_OF(gAdj1);

    set_name("lion");
    set_race_name("sea lion");
    set_adj("sea");
    set_adj(a1);

    set_short(a1 + " sea lion");

    set_gender(0);
    set_long("Before you is a fearsome aquatic creature with the head " +
        "and fore-paws of a lion and the scaled body of a fish. " +
        "12 feet in length and a hefty 800 pounds, this huge territorial " +
        "beast is a fisherman's nightmare!\n");

    // 169 stat average with a 10% variance.
    int sl = SD_AV_CHAMPION;

    set_stats(({sl, sl, sl, sl, sl, sl}), 10);

    set_aggressive(1, 100);

    set_hp(10000);
    set_alignment(0);
    set_knight_prestige(50);

    add_prop(CONT_I_WEIGHT, 400000);
    add_prop(CONT_I_VOLUME, 450000);
    add_prop(MAGIC_I_BREATHE_WATER, 100);

    set_skill(SS_DEFENCE, 100);  
    set_skill(SS_UNARM_COMBAT, 100);

    NEVERKNOWN;

    set_attack_unarmed(0, 50, 60, W_SLASH,  80, "claws");
    set_attack_unarmed(1, 35, 80, W_IMPALE, 20, "bite");

    set_hitloc_unarmed(1,  60, 60, "body");
    set_hitloc_unarmed(1,  80, 30, "tail");
    set_hitloc_unarmed(2, 20, 10, "head");

    add_leftover(CLAW, "claw", 2, "", 0, 0);
    add_leftover(HEART, "heart", 1, "", 0, 0);

    set_cact_time(10);
    add_cact("roar aggres");
    add_cact("emote tosses its pure white mane.");
    add_cact("emote rears back on its massive scaled tail.");

    // Tough npc with nasty special attack.
    set_exp_factor(110);
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
	pen = 100 + random(500);
	hitres = enemy->hit_me(pen, 50, TO, -1);
	wloc = random(5);

	if(hitres[0] <= 0)
	    how = "just missing";
	if(hitres[0] > 0)
	    how = "grazing the skin of";
	if(hitres[0] > 10)
	    how = "slashing deeply into";
	if(hitres[0] > 20)
	    how = "deeply penetrating";
	if(hitres[0] > 40)
	    how = "tearing apart";
	if(hitres[0] > 60)
	    how = "rending to shreds";

	enemy->catch_msg(QCTNAME(TO)+ " mauls you with his claws, " +
	  how+ " your " + hitloc[wloc]+ ".\n");
	tell_room(E(TO), QCTNAME(TO)+ " mauls " +QTNAME(enemy)+ 
          " with his claws, " +how+ " " +HIS(enemy)+ " " +
          hitloc[wloc] + ".\n", ({enemy,TO}));

	if(enemy->query_hp() <= 0)
	{
	    enemy->do_die(TO);
	}
	return 1;
    }
    return 0;
}

/*
 * Function name:   do_die
 * Description:     Called from enemy combat object when it thinks we died.
 * Arguments:       killer: The enemy that caused our death.
 */
public void
do_die(object killer)
{
    object * players = FILTER_PLAYER_OBJECTS(all_inventory(environment(killer)));

    players -= ({ killer });
    players = ({ killer }) + players; // ensure killer is first
    foreach (object player : players)
    {
        object net = present(SEA_NET_ID, killer);
        if (!objectp(net))
        {
            continue;
        }
        net->sea_creature_do_die_post_actions(killer);
        break;
    }
    
    ::do_die(killer);
}