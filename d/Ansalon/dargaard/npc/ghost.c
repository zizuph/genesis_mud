/*******************************************************
 * Name: Ghost                                                    
 * By: Elmore
 * Desc: A ghost for Dargaard Keep.
 * Note: Has a hunting function.
 *                                                                             
 *******************************************************/
  
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

inherit AM_FILE

int
check_aggressive()
{
    return !TP->query_prop(LIVE_I_UNDEAD);
}


void
create_krynn_monster()
{
    set_name("ghost");    
    set_race_name("undead");
    set_adj("transparent");
    add_adj("aggressive");
    set_short("transparent aggressive ghost");
    set_long("These ghosts are the spirits of humans who were either "+
             "so greatly evil in life or whose deaths were so "+
             "unusually emotional they have been cursed with the "+
             "gift of undead status. Thus, they roam about in "+
             "this Keep seeking revenge. The ghosts hate "+
             "goodness and life, hungering to draw the living "+
             "essences from the living.\n");

    add_prop(CONT_I_HEIGHT, 180);
    add_prop(CONT_I_WEIGHT, 150);
    add_prop(CONT_I_VOLUME, 140);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_UNDEAD, 100);
    add_prop(LIVE_I_SEE_DARK, 5);
    set_aggressive(VBFC_ME("check_aggressive"));
    set_gender(G_NEUTER);
    set_random_move(50);
    set_aggressive(1);

    set_stats(({110+random(30),110+random(80),110+random(60),50,90,170}));
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 80);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 60);
    set_alignment(-1150);
    set_knight_prestige(100);
    set_all_hitloc_unarmed(20);

    set_exp_factor(150);  // Ignores most physical attacks.
}

/*
 * Function name:   query_enemy
 * Description:     Gives information of recorded enemies. If you want to
 *                  know currently fought enemy (if any) call query_attack()
 * Arguments:       arg: Enemy number (-1 == all enemies)
 * Returns:         Object pointer to the enemy
 */
public int
query_not_attack_me(object who, int aid)
{
    object attack_ob;
    mixed attack;
    string attack_desc;
    
    attack_ob = who->query_combat_object();
    attack = attack_ob->query_attack(aid);

    // ATTACK WAS MAGICAL.   
    if (attack == 0)
        return TO->query_not_attack_me(who, aid);

    attack_desc = attack_ob->cb_attack_desc(aid);

    if (random(10) <= 7)
        return  ::query_not_attack_me(who, aid);
	
   	who->catch_msg("Your weapon passes right through the "+
                   "ghost, causing no damage at all!\n");
	  TO->tell_watcher(QCTNAME(who) + "'s weapon passes right "+
                     "through the ghost, causing no damage at all!\n", who);
    return 1;
}

/*
varargs public mixed
hit_me(int wcpen, int dt, object attacker, int
attack_id, int target_hitloc = -1)
{
    
    if (random(4) == 1)
        return ::hit_me(wcpen, dt, attacker, attack_id, target_hitloc);
    else
    {
        attacker->catch_msg("Your weapon passes right through the ghost, causing no "+
                            "damage at all!\n");
        return 0;
    }
}
*/
