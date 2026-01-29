
// file name: /d/Avenir/common/dead/mon/skeleton.c
// creator(s): Lilith June 2021
// last update:
// purpose: skeleton for the catacombs
// note:    These are cloned as players enter rooms
//          and they block exits in the catacombs.
// bug(s):
// to-do:

inherit "/std/monster";

#include "../dead.h"
#include "money.h";
#include <formulas.h>
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

void
equip_me()
{
    object ring;
	
   seteuid(getuid());
   /* A gold coin for each eye */
   MONEY_MAKE_SC(2)->move(this_object());
   
   clone_object("/d/Avenir/common/dark/obj/bones")->move(TO, 1);
   
    if (random(3) > 1) // 1 in 3 chance
    {
	   clone_object(OBJ +"ring")->move(TO, 1);
    }   
    command("emote rises up from a pile of bones.");
   
}


void
create_monster()
{
    set_name(({"skeleton", "_Dead_Isle_Skeleton","undead"}));
    set_short("animated skeleton");
    set_adj("animated");
    set_race_name("skeleton");
    set_gender(G_NEUTER);

    set_long("This skeleton has pulled itself together "
        +"from the bones you knocked over.\n");
    set_appearance_offset(50);
    set_alignment(0);
    set_hp(query_max_hp());
    
	// Don't want them to be too big since questors will
	// have to kill them to get out of the crypts and
	// to get to the Meet Mascarvin quest area.
	default_config_npc(50 +random(25));   
 
    set_restrain_path(CRYPT);

    /* They are skeletons, they don't have eyes, but they can still 'see' */	
    add_prop(LIVE_I_NO_CORPSE,1);
    add_prop(LIVE_I_SEE_DARK,20);
    add_prop(LIVE_I_UNDEAD,1);
    add_prop(LIVE_I_NEVERKNOWN,1);
 
    // Goddess of Death and Rebirth Mascarvin's protection
// Nerull tells you: 30% damage immunity is approximately 19 magic res in the prop, 
// and 40% damage immunity is magic res 25 in the prop.
// Nerull tells you: Npcs starts to become practically immune to magic near 45 resist
    // 19 res = 30 AC  25 res = 40 AC 	
    add_prop(OBJ_I_RES_MAGIC,   19 +random(7));
    add_prop(OBJ_I_RES_DEATH,   19 +random(7));
    add_prop(OBJ_I_RES_LIFE,    19 +random(7));

    set_skill(SS_AWARENESS, 70);
    set_skill(SS_BLIND_COMBAT, 70 +random(20));
	set_skill(SS_UNARM_COMBAT, 70 +random(20));
	
	// hit 35, pen 25
	set_all_attack_unarmed(30, 25); 
	
	// av ac is 35
    set_hitloc_unarmed(A_TORSO,({50,35,20}),25,"sternum");
    set_hitloc_unarmed(A_CHEST,({50,35,20}),25,"ribs");
    set_hitloc_unarmed(A_HEAD,({50,35,20}),10,"skull");
    set_hitloc_unarmed(A_LEGS,({50,35,20}),20,"leg bone");
    set_hitloc_unarmed(A_ARMS,({50,35,20}),20,"leg bone");
   
	set_cact_time(5);
	add_cact("emote tries to poke you in the eyes with a skeletal finger.");
	add_cact("emote opens its mouth in a silent scream."); 
	add_cact("emote throws a bone at you.");
	add_cact("emote grabs a bone from nearby and starts swinging it around.");
	add_cact("emote tries to bite you.");
	
    set_act_time(20);
    add_act("emote moves slightly.");
    add_act("emote clinks its bones together.");
    add_act("emote looks like it is chewing on air.");

    equip_me();
}

public string cr_attack_desc(int id)
{
    if (id == W_LEFT)
    {
        return "boney left hand";
    }
    if (id == W_RIGHT)
    {
        return "boney right hand";
    }
	
    return ::cr_attack_desc(id);
}


/*
 * Function name: notify_death
 * Description:   Notify onlookers of my death
 * Arguments:     object killer - the object that killed me
 */
public void
notify_death(object killer)
{
    tell_room(environment(this_object()),
        QCTNAME(this_object()) + " crumbles to bones and dust.\n", this_object());
    if (interactive(killer))
    {    
        tell_object(killer,
            "You defeated " + this_object()->query_the_name(killer) + ".\n");
        tell_room(environment(this_object()),  QCTNAME(killer) + " defeated " +
            this_object()->query_objective() + ".\n", ({ this_object(), killer }));
	}
}

/* Logging death info. */
void
do_die(object killer)
{
	
    if (query_hp() > 0)
        return;
	
    if (!killer)
        killer = previous_object();
	
    STATSERV_LOG_EVENT("Crypt", "skeleton killed");
    ::do_die(killer);
}
