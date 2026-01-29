/*  
 * Standard Undead Base
 *  
 * This is the base class for all undeads in Calia. It sets up basic things
 * like skills, stats, and treasure.
 *
 * Created by Petros, November 2008
 */

inherit "/std/creature";
inherit "/d/Calia/eldoral/std/undead_content_base";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include "/d/Genesis/gems/gem.h"
#include "../defs.h"

#define A_CLAWS 0
#define A_LCLAW 1
#define A_RCLAW 2
#define A_BITE  3

#define H_HEAD 0
#define H_BODY 1
#define H_ARMS 2
#define H_LEGS 3

/*
 * Function:    create_undead_creature
 * Description: Default configure function to mask for undeads
 *              Define this in your own undead to override the standard
 *              stuff set here.
 * Arguments:   none
 * Returns:     nothing
 */
public void
create_undead_creature()
{
}

/*
 * Function:    set_attacks_and_hitlocs
 * Description: Default function for setting all the attacks and hitlocs
 *              for the undead creature. Mask this to override and set
 *              your own.
 * Arguments:   none
 * Returns:     nothing
 */
public void
set_undead_attacks_and_hitlocs()
{
    // Wep_type,   to_hit,   pen,   Dam_type,   %usage,   attack_desc
    // Standard undeads have two claws to use. When using both claws,
    // the attack is even stronger. This happens 30% of the time.
    set_attack_unarmed(A_CLAWS, 35, 40, W_SLASH, 25, "claws");
    set_attack_unarmed(A_LCLAW, 30, 30, W_SLASH, 30, "left claw");
    set_attack_unarmed(A_RCLAW, 30, 30, W_SLASH, 30, "right claw");
    set_attack_unarmed(A_BITE,  30, 35, W_IMPALE, 15, "bite");
    
    // Hit_loc,   *Ac (im/sl/bl/ma),   %hit,   hit_desc
    // Standard undeads have a base 40 AC. Bludgeoning attacks tend to
    // hurt undeads more so than other types of attacks, so I've lowered
    // their ACs here. Certain undeads like skeletons will have very
    // high impale AC, medium slashing AC, and low bludgeoning AC.
    set_hitloc_unarmed(H_HEAD, ({40, 40, 25, 0}), 15, "head");
    set_hitloc_unarmed(H_BODY, ({40, 40, 25, 0}), 35, "body");
    set_hitloc_unarmed(H_ARMS, ({40, 40, 25, 0}), 25, "arms");
    set_hitloc_unarmed(H_LEGS, ({40, 40, 25, 0}), 25, "legs");
}

public nomask void
create_creature()
{
    object gem;

    add_prop(LIVE_I_NO_CORPSE,1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_SEE_DARK, 5); // Undeads typically inhabit dark places
    add_prop(OBJ_I_RES_COLD, 100);
    
    add_prop(CONT_I_WEIGHT, 70000);
    add_prop(CONT_I_VOLUME, 70000);
    add_prop(CONT_I_MAX_VOLUME, 150000);
    add_prop(CONT_I_MAX_WEIGHT, 150000);
    
    set_alignment(-(350 + random(200)));
    set_gender(G_NEUTER);

    // Setup the adjectives for the undead.
    string *adj1 = ({"ugly", "smelly", "rancid", "putrid", "rotting", 
                     "repulsive", "loathsome", "horrid", "nasty"});
    string *adj2 = ({"foul", "odious", "unearthly", "disgusting", 
                     "unholy", "vile", "corrupt", "ungodly"});
    set_adj(one_of_list(adj1));
    add_adj(one_of_list(adj2));
    set_race_name("undead");
    set_short(implode(query_adjs(), " ") + " " + query_race_name());
    set_long("This " + query_short() + " is a Soulless being who inhabits "
        + "the dark places of Calia.\n");
    
    set_undead_attacks_and_hitlocs();
    
    create_undead_creature();
    
    add_name("undead");
}

public void
default_config_undead(int level)
{
    int skill, avg_stat;
    
    // We set the stat to somewhere between 80-120% of the passed in
    // level. That means that if you set it to 100, you can get an undead
    // between the levels of 80-120.
    avg_stat = ((4 * level) / 5) + random((level / 5) + 1) + random((level / 5) + 1);
    default_config_creature(avg_stat);
    add_prop(LIVE_I_UNDEAD, level);
    set_undead_skills(this_object());
    
    add_treasure(this_object());
}
