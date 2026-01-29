/*******************************************************
 * Name: Ghost                                                    
 * By: Elmore
 * Desc: A ghost for Dargaard Keep.
 * Note: Has a hunting function.
 *                                                                             
 * Modified by Louie 2005-07- fix query_not_attack_me call.
 * Modified by Navarre May 3rd 2006, someone removed call to arm_me,
 * This call was restored.
 * Added prop to not run away, and changed weapon to attack
 * in the attack description, so unarmed people dont see
 * that their weapon pass through the ghost.
 *******************************************************/
  
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

inherit AUTO_TEAM
inherit "/lib/unique";
inherit AM_FILE

#define WEP1 "/d/Ansalon/goodlund/bloodsea/obj/chemosh_axe"

void arm_me();
object axe;

int
check_aggressive()
{
    return !TP->query_prop(LIVE_I_UNDEAD);
}


void
create_krynn_monster()
{
    set_pick_up_team(({"gully dwarf","dwarf"}));
    set_max_team_size_auto_join(6);
 
    set_name("kharasa");
    set_living_name("kharas");
    set_title("Blackbeard the Cursed, Ghostly Pirate Captain of the Bloodsea of Istar");
    add_name("ghost");
    add_name("captain");
    add_name("dwarf");    
    set_race_name("undead");
    set_adj("dwarven");
    add_adj("ghost");
    set_short("dwarven ghost captain");
    set_long("Fearsome? Aye, this ghostly spectre is the captain of this ghostly " +
       "pirate ship! Short and squat with a wild black beard, this revenant is " +
       "garbed in a flamboyant and frilly shirt that you would normally find " +
       "rediculous if it wasn't for the crazy glint in this dwarf-ghost's eyes!\n");

    add_prop(CONT_I_HEIGHT, 120);
    add_prop(CONT_I_WEIGHT, 150);
    add_prop(CONT_I_VOLUME, 140);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_UNDEAD, 100);
    add_prop(LIVE_I_SEE_DARK, 5);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    set_gender(G_NEUTER);

    set_stats(({200, 140, 240, 120, 140, 100}));
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

    set_act_time(5);
    add_act("emote roars eerily: Ye little rodents! Get out the oars!");
    add_act("emote grumbles: A crew of gully dwarves? Truly i am in hell..");
    add_act("cackle");
    add_act("emote looks out towards the sea for a ship to raid.");
    add_act("say This is all Ashlar's fault! No, Jeremiah's fault!");
    add_act("emote fades out of view temporarily.");
    add_act("say Woe is me! Never again shall dwarven spirits pass my lips!");
    add_act("emote yanks at his beard in frustration.");

    set_exp_factor(120);  // Ignores most physical attacks.

    trig_new("%w 'introduces' %s","react_to_intro"); 
    arm_me();
}

void
arm_me()
{
    seteuid(getuid(TO));

    axe = clone_unique(WEP1, 4,({ ({ WEP1, 1 }) }), 0, 25);
    if(axe)
    {
       axe->set_axe_souls(6);
       axe->move(TO, 1);
       command("wield all");
    }
}

void
react_to_intro(string who,string garbage)
{
    set_alarm(2.0,0.0,"return_intro",who);
}
 
void
return_intro(string who)
{
    who = L(who);
    if (P(who,E(TO)))
    {
        command("introduce myself");
    }
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

void
init_living()
{
    init_team_pickup();
    ::init_living();
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
