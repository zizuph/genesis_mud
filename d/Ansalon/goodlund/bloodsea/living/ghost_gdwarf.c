/* Navarre June 25th 2006, added prop to not run away.
 * changed attack description from weapon to attack, 
 * so the description still works for people 
 * fighting unarmed.
 */

/* Navarre August 7th 2008, Cot pointed out a bug with the
   way the objects were being cloned:
   if(random(4)) that was a bug and meant to be if(!random(4)).
   And even then it was done wrong, should use clone_unique
   instead. So I fixed this.
*/

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

inherit AUTO_TEAM
inherit "/lib/unique";
inherit AM_FILE

int
check_aggressive()
{
    return !TP->query_prop(LIVE_I_UNDEAD);
}


void
create_krynn_monster()
{
    set_pick_up_team(({"gully dwarf"}));
    set_max_team_size_auto_join(6);
 
    set_name("dwarf");
    set_race_name("gully dwarf");
    add_name("ghost");   
    set_adj("gully");
    add_adj("ghostly");
    set_short("ghostly gully dwarf");
    set_long("Before you stands the wretched ghost of a gully dwarf, doomed to " +
       "spend eternity as crew for Captain Kharasa the cursed!\n");

    add_prop(CONT_I_HEIGHT, 80);
    add_prop(CONT_I_WEIGHT, 150);
    add_prop(CONT_I_VOLUME, 140);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_UNDEAD, 100);
    add_prop(LIVE_I_SEE_DARK, 5);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    set_gender(G_NEUTER);

    set_stats(({120, 200, 200, 70, 70, 100}));
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 80);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 60);
    set_alignment(-1150);
    set_knight_prestige(100);
    set_all_hitloc_unarmed(40);

    set_act_time(20);
    add_act("emote mumbles: Two? No more than two!");
    add_act("emote raises a grubby hand towards the ghostly rigging.");
    add_act("think");
    add_act("emotes looks around in desperate hope for a ghostly rat to gnaw on.");
    add_act("say Ashlar did it!");
    add_act("emote fades out of view temporarily.");
    add_act("emote scurries around at the order of his cursed captain.");
    add_act("emote yanks at his ghostly whiskers in vain.");

    set_exp_factor(120);  // Ignores most physical attacks.

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
        return ::query_not_attack_me(who, aid);

    attack_desc = attack_ob->cb_attack_desc(aid);

    if (random(10) <= 7)
        return  ::query_not_attack_me(who, aid);
	
   	who->catch_msg("Your attack passes right through the "+
                   "ghost, causing no damage at all!\n");
	  TO->tell_watcher(QCTNAME(who) + "'s attack passes right "+
                     "through the ghost, causing no damage at all!\n", who);
    return 1;
}

public void
do_die(object killer)
{
    object room = E(TO), orb;

    setuid();
    seteuid(getuid());
    orb = clone_unique("/d/Ansalon/goodlund/bloodsea/obj/dark_obj", 5); 

    if(orb)
    {
        command("emote eeks loudly, and implodes in a ball of negative energy!"); 
        orb->remove_dark_obj();
        orb->move(room);
    }
    else
    {
        command("emote eeks loudly, and explodes noisily into nothing!");
    }   
    ::do_die(killer);
}
