/*
 *  /d/Kalad/common/farmland/camps/npc/std_orc_camp_npc.c
 *
 *  This is the base file for all npcs in the red fang camp
 *  in Kalad
 *
 *  Created October 2015, by Andreas Bergstrom (Zignur)
 *  Modified 2018-03-14 Added attacked_by to let the wolfes assist
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
public void           attacked_by(object ob);
public void           command_wolf(object ob);


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
    if (!objectp(obj) || obj->query_prop(OBJ_I_NO_DROP) 
        || !CAN_SEE(this_object(), obj))
        return;

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


/*
 * Function name:       attacked_by
 * Description:         This routine is called when we are attacked.
 * Arguments:           ob: The attacker
 *
 */
public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    command_wolf(ob);
} /* attacked_by */

/*
 * Function name:       command_wolf
 * Description:         This function will let the attacked npc command
 *                      one of the red fang wolves to assist, if its present.
 * Arguments:           ob: The attacker
 *
 */
public void
command_wolf(object ob)
{
    object  wolf;
    object * wolves;
   
    /* Find out if the are any wolves in the room */
           
    /* Returns a array of all objects in the room with
     * the name _rf_camp_wolf_
     */ 
    
    wolves = filter(all_inventory(environment(this_object())),
                    &->id("_rf_camp_wolf_"));
    
    if(sizeof(wolves))
    {     
        /* First hit here will be the wolf we want */
        wolf = wolves[0];  
        tell_room(environment(this_object()), "The " + short() +
            " barks a command to the " + wolf->short() + ".\n"); 
        wolf->command("emote snarls in anger.");
        wolf->command("$kill " +  lower_case(ob->query_real_name()));
    }   
    
} /* command_wolf */
