/*
 *  /d/Kalad/common/farmland/camps/npc/goblin_wolf.c
 *
 *  A wolf in the red fang camp in Kalad
 *
 *  Created October 2015, by Andreas Bergstrom ( Zignur )
 */
#pragma strict_types
#include "../defs.h"

inherit NPC_DIR + "std_redfang_camp_npc";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

/* Prototypes */
public void        create_redfang_camp_npc  ();
public void        arm_me();
public string      default_answer();
public void        do_die(object killer);

/* Global variables */
string *ArrAdj1 = ({ "small","tiny","skinny","puny","small"});
string *ArrAdj2 = ({ "weak","young","furry","fluffy","ragged" });
string Adj1 = one_of_list(ArrAdj1);
string Adj2 = one_of_list(ArrAdj2); 


/*
 * Function name:        create_redfang_camp_npc  
 * Description  :        The constructor for the monster
 */
public void
create_redfang_camp_npc  ()
{
    set_name("wolf");
    add_name("puppy");
    set_race_name("wolf");
    add_name(({ "wolf", "puppy","wolf puppy", REDFANG_CAMP_NPC }));
    add_adj(({ Adj1, Adj2 }));
    set_short( Adj1+ " "+ Adj2 +" wolf");
    set_long("A " +Adj1 + " " + Adj2 + " wolf. This must be one"
      + " of the wolf pups that the Red Fang are training"
      + " for riding in the future. He looks quite deadly even" 
      + " though he is just a puppy.\n");

    set_stats( ({ NPC_GOBLIN_WOLF_STR,
                  NPC_GOBLIN_WOLF_DEX,
                  NPC_GOBLIN_WOLF_CON,
                  NPC_GOBLIN_WOLF_INT,
                  NPC_GOBLIN_WOLF_WIS,
                  NPC_GOBLIN_WOLF_DIS,
               }) );
    
      
    set_hitloc_unarmed(1, 10, 15, "head");
    set_hitloc_unarmed(2, 10, 20, "right paw");
    set_hitloc_unarmed(3, 10, 20, "left paw");
    set_hitloc_unarmed(4, 10, 45, "body");
    
    set_attack_unarmed(0, 10, 10, W_SLASH,50, "teeth");
    set_attack_unarmed(1, 10, 10, W_SLASH,25, "left claws");
    set_attack_unarmed(2, 10, 10, W_SLASH,25, "right claws");
            
    set_skill(SS_DEFENCE,      25);
    set_skill(SS_PARRY,        25);
    set_skill(SS_UNARM_COMBAT, 50);
    add_prop(NPC_I_NO_LOOKS, 1);

    setuid();
    seteuid(getuid());
} /* create_redfang_camp_npc  */


/*
 * Function name:        arm_me
 * Description  :        set up the npc with any gear it needs
 */
public void
arm_me()
{
        
} /* arm_me */

/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    return "";
} /* default_answer */


/*
 * Function name:       do_die
 * Description  :       Called when the npc is killed
 * Arguments    :       object killer - the killer
*/
public void
do_die(object killer)
{
    // Keep track of the number of killed warriors
    int killed;
    if (interactive(killer))
    {
        killed = killer->query_prop(RF_WOLVES_KILLED) + 1;
        killer->add_prop(RF_WOLVES_KILLED, killed);
    }    
    
    ::do_die(killer);
}
/* do_die */ 
