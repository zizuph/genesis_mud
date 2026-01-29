/*
*   Boss engaged effects/abilities/actions
*   Lair actions/Legendary actions etc
*
*   This is to be used in boss_engaged_routine() on
*   the monster.
*
*   Nerull 2018
*/
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
inherit "std/monster.c";
inherit "/std/combat/unarmed";



/* Function name: max_health_while_not_in_combat
* Description  : If the monster is not engaged, give it
*                max health and fatigue.
*               
* Arguments    : 
*/
void
max_health_while_not_in_combat()
{
    int healmeamount = 0;
    
    // If the boss is left unattendend, it quickly regenerates to
    // max health. This enforces an enemy encounter/team to keep
    // it engaged at all times in order to defeat it.
    if (this_object()->query_attack() == 0)
    {
        tell_watcher(QCTNAME(this_object())
        + " regenerates to full health.\n");
        
        healmeamount = this_object()->query_max_hp();

        this_object()->heal_hp(healmeamount);
        this_object()->set_fatigue(1000);
        
        engaged = 0;
        
        return;
    }
    
    return;
}



    