
/*  
    Standard guard code in Gelan, inherited by monsters that need
    aid from guards, or guards themselves who aid other guards.	

    coder(s):   Merlin & Maniac

    history:   
               17/7/2000  introduced enemy / murder support   Maniac
               13/2/2000  added query_calia_gelan_npc         Maniac
                3/4/97    incorporated cadet friend npc       Maniac
                18/2/97    auto intro support added           Maniac
                26/7/95    Major revision of old file         Maniac

    purpose:    Monsters inheriting this code will make an automatic 
                call for help to the guards when attacked, and some 
                active guards will respond by coming to the monster's
                aid if there are any.

*/

#include "monster.h"
#include CADET_INCLUDE
#include <macros.h>
#include GELAN_ENEMY_INCLUDE


inherit "/std/monster";
inherit "/d/Calia/std/intro"; 
inherit GC_FRIEND_NPC;


int
query_calia_gelan_npc()
{
    return 1; 
}


/*
 * Function name: help_me
 * Description:   send help request to the master guard
 * Arguments:     meeting point, room, attacker
 * Returns:       number of guards alarmed
 */
int
help_me(string room, object attacker)
{
    return (GELAN_SPECIALS + "head_guard")->help_me(room, attacker);
}


/*
 * Function name: attacked_by
 * Description:   this is the function which is called when we are attacked
 *                here we inform the head guard about the attack
 * Arguments:     attacker
 * Returns:       none
 */
void
attacked_by(object attacker)
{
    string fn;

    ::attacked_by(attacker);

    attack_cadet_friend(attacker);

    if (!(attacker->query_prop(ATTACKED_GELAN)))
      attacker->add_prop(ATTACKED_GELAN, 1); 

    fn = file_name(environment(this_object()));

    help_me(fn, attacker);
}


/*
 *  Function:     query_murder_recorded
 *  Description:  Called when this npc dies, this function should return
 *                1 if the killing should be recorded as a murder. By
 *                default it returns 1 if the killer is interactive,  
 *                0 otherwise. Inheriting npcs mask this function if 
 *                it's desirable to introduce different interpretations. 
 */ 
int
query_murder_recorded(object killer)
{
    if (interactive(killer))
        return 1; 

    return 0; 
}


/* 
 * Function:      second_life 
 * Description:   Called when this npc dies. This instance records 
 *                the murder in the Gelan enemy control code if 
 *                query_murder_recorded() returns 1. 
 */
int
second_life(object killer)
{
    seteuid(getuid()); 
    if (query_murder_recorded(killer)) 
        GELAN_ENEMY_CONTROL->record_murder(killer, this_object()); 
    return 0; 
}
