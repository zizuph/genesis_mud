
// file name: /d/Avenir/common/dead/mon/skeleton.c
// creator(s):   Lilith June 2021
// last update:  Lilith Sept 2021: added some skills and updated magic res.
//               Lilith Feb 2022: removed magic res since combat sys
//                  calcs it based on AC now. 
//               Lilith May 2022: fixed indents and update statserv logging.
// purpose: skeleton for the catacombs stat av 40-75.
// note:    These are cloned as players enter rooms
//          and they block exits in the catacombs.


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
   MONEY_MAKE_GC(2)->move(this_object());
    command("emote rises up from a pile of bones.");
   
}


void
create_monster()
{
    set_name(({"skeleton", "_Dead_Isle_Skeleton","undead", "_crypt_crawler"}));
    set_short("animated skeleton");
    set_adj("animated");
    set_race_name("skeleton");
    set_gender(G_NEUTER);

    set_long("This skeleton has pulled itself together "
        +"from some knocked-over bones.\n");
    set_appearance_offset(50);
    set_alignment(0);
    
	// Don't want them to be too big since questors will
	// have to kill them to get out of the crypts and
	// to get to the Meet Mascarvin quest area.
    default_config_npc(40 +random(35));   
 
    set_restrain_path(CRYPT);

    /* They are skeletons, they don't have eyes, but they can still 'see' */	
    add_prop(LIVE_I_NO_CORPSE,1);
    add_prop(LIVE_I_SEE_DARK,20);
    add_prop(LIVE_I_UNDEAD,1);
    add_prop(LIVE_I_NEVERKNOWN,1);
 	
	// hit 25, pen 25
    set_all_attack_unarmed(25, 25); 

    set_hitloc_unarmed(A_TORSO,({10,10,10}),25,"sternum");
    set_hitloc_unarmed(A_CHEST,({10,10,10}),25,"ribs");
    set_hitloc_unarmed(A_HEAD,({10,10,10}),10,"skull");
    set_hitloc_unarmed(A_LEGS,({10,10,10}),20,"leg bone");
    set_hitloc_unarmed(A_ARMS,({10,10,10}),20,"leg bone");
   
    set_skill(SS_SPELLCRAFT, 70);  // reduce caster damage
    set_skill(SS_FORM_ABJURATION, 70);  // reduce caster damage
    set_skill(SS_AWARENESS, 70);   // reduce theiving of imbues
    set_skill(SS_DEFENCE, 40);     // reduce melee damage
    set_skill(SS_ACROBAT, 40);     // reduce melee damage
    set_skill(SS_BLIND_COMBAT, 50); 
    set_skill(SS_UNARM_COMBAT, 50);

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
	
    STATSERV_LOG_EVENT("crypt", "skeleton killed");
    ::do_die(killer);
}
