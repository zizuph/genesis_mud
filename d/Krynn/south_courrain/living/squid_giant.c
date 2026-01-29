/*
 *  Giant squid of the Courrain Sea, Arman - Feb 2021
 *
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

#define A_TENT 0
#define A_BEAK 1
#define H_TENT 0
#define H_BODY 1

#define SQUID_INK  "/d/Krynn/south_courrain/obj/squid_blind_obj"
#define SAC        "/d/Krynn/south_courrain/obj/squid_ink"
#define TENTACLE   "/d/Krynn/south_courrain/obj/squid_tentacle"

#define SEA_NET_ID "_sea_net_id"

void
create_creature()
{
    set_name("squid");
    set_race_name("squid");
    set_adj("collosal");

    set_short("collosal squid");

   set_gender(G_NEUTER);
   set_long("This is a collosal squid. Rarely sighted but incredibly " +
       "territorial, these creatures are highly aggressively and " +
       "dangerous adversaries. Fighting with eight hooked arms, " +
       "two club-like tenticles with great rotating hooks to grab " +
       "their prey, and a huge beak-like maw - collosal squid are a " +
       "fearsome enemy. It is rumoured that these creatures are " +
       "a bane to even large fishing vessels, and its only natural " +
       "enemies are the great whales of the Courrain Sea.\n");

    // 154 stat average with a 10% variance.
    int sl = SD_AV_TITAN;

    set_stats(({sl, sl, sl, sl, sl, sl}), 10);

    set_aggressive(1, 100);

    set_hp(10000);
    set_alignment(0);
    set_knight_prestige(50);

    add_prop(CONT_I_WEIGHT, 200000);
    add_prop(CONT_I_VOLUME, 250000);
    add_prop(MAGIC_I_BREATHE_WATER, 100);

    set_skill(SS_DEFENCE, 100);  
    set_skill(SS_UNARM_COMBAT, 100);

    NEVERKNOWN;
   
    set_attack_unarmed(A_TENT, 45, 40, W_BLUDGEON, 90, "great tentacle");
    set_attack_unarmed(A_BEAK, 40, 60, W_IMPALE, 10, "great beak-like maw");
   
    set_hitloc_unarmed(H_BODY, ({ 40, 35, 35, 35}), 60, "body");
    set_hitloc_unarmed(H_TENT, ({ 30, 28, 30, 30}), 40, "great tentacle");

    int tent_num = 3 + random(6);

    add_leftover(SAC, "sac", 1, "", 0, 0);
    add_leftover(TENTACLE, "tentacle", tent_num, "", 0, 0);

    // Tough npc with nasty special attack and blind.
    set_exp_factor(110);
}

int
special_attack(object enemy)
{

    int attacktype, pen, wloc;
    mixed hitres;

    string *hitloc, how;

    attacktype = random(12);
    hitloc = ({"left arm","right arm","body","left leg","right leg"});

    if(!attacktype)
    {
        // Squid blind object applied to all enemies.
        object * enemies;

        enemies = TO->query_enemy(-1) & all_inventory(environment(TO));

        foreach(object inked: enemies)
        {
            object blind = clone_object(SQUID_INK);

	    inked->catch_msg(QCTNAME(TO)+ " sprays you with blinding ink!\n");
	    tell_room(E(TO), QCTNAME(TO)+ " sprays " +QTNAME(inked)+ 
                " with blinding ink!\n", ({inked, TO}));

            blind->move(inked, 1);
        }

        return 1;
    }

    if(attacktype == 1 || attacktype == 2)
    {
	pen = 100 + random(500);
	hitres = enemy->hit_me(pen, 50, TO, -1);
	wloc = random(5);

	if(hitres[0] <= 0)
	    how = "ineffectually piercing";
	if(hitres[0] > 0)
	    how = "pricking";
	if(hitres[0] > 10)
	    how = "stabbing";
	if(hitres[0] > 20)
	    how = "piercing";
	if(hitres[0] > 40)
	    how = "deeply penetrating";
	if(hitres[0] > 60)
	    how = "horribly impaling";

	enemy->catch_msg(QCTNAME(TO)+ " grabs you with its hooked arms, " +
	  how+ " your " + hitloc[wloc]+ ".\n");
	tell_room(E(TO), QCTNAME(TO)+ " grabs " +QTNAME(enemy)+ 
          " with its hooked arms, " +how+ " " +HIS(enemy)+ " " +
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