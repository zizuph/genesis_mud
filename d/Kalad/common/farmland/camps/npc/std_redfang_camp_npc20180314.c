/*
 *  /d/Kalad/common/farmland/camps/npc/std_orc_camp_npc.c
 *
 *  This is the base file for all npcs in the red fang camp
 *  in Kalad
 *
 *  Created October 2015, by Andreas Bergstrom (Zignur)
 */
#pragma strict_types

inherit "/std/monster";

#include <macros.h>
#include "../defs.h"


/* Global Variables */


/* Prototypes */
public string         create_redfang_camp_npc();
nomask string         create_monster();
public void           return_object(object obj, object to);
public void           enter_inv(object ob, object from);

/*
 * Function name:        redfang_camp_npc
 * Description  :        dummy function to be replaced in inheriting files
 */
public string
create_redfang_camp_npc()
{
} /* create_redfang_camp_npc */


/*
 * Function name:        create_monster
 * Description  :        The constructor for the monster
 */
nomask string
create_monster()
{
    setuid();
    seteuid(getuid());
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_I_NO_LOOKS,1);
    set_not_here_func("not_here_func");	
    create_redfang_camp_npc();
} /* create_monster */


/* 
 * Function name:        return_object
 * Description  :        have npcs give things they are given back
 *                       to players
 * Arguments    :        object obj - the object given
 *                       object to  - the player who gave it
 */
public void
return_object(object obj, object to)
{
    command("say I have no use of this!");
    command("give " + OB_NAME(obj) + " to " + OB_NAME(to));
    if (environment(obj) == this_object())
    {
       command("drop " + OB_NAME(obj));
    }
} /* return_object */


/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(ob) || !objectp(from) || !living(from))
    {
        return;
    }

    set_alarm(0.5, 0.0, &return_object(ob, from));
} /* enter_inv */



 /*
 * Function name:       notify_attack_on_team
 * Description  :       Called when the npc is attacked
 * Arguments    :       object friend, object attacker
*/
public void
notify_attack_on_team(object friend, object attacker)
{
    /* We dont want them to assist each other so do nothing */
    return;
}/* notify_attack_on_team */


/*
 * Function name:       do_die
 * Description  :       Called when the npc is killed
 * Arguments    :       object killer - the killer
*/
public void
do_die(object killer)
{
    // Remove 1 from the war rooms npc counter
    RF_WAR_ROOM->remove_goblin_warriors(1);
    
    ::do_die(killer);
}/* do_die */
