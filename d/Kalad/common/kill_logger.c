/*
 * /d/Kalad/common/kill_logger.c
 * 
 * This file will write a log whenever the npc that
 * inherits this kills a player. The log can be
 * found in /d/Kalad/log/killed_players
 * It also logs everyone that kills the npc ( including
 * the team thats present in the room).
 * The log for that is /d/Kalad/log/boss_killers
 *
 * Created Nov 2017, by Andreas Bergstrom ( Zignur )
 *
 */
inherit "/d/Kalad/std/monster";
#include <macros.h>
#include <time.h>
#include "/d/Kalad/defs.h"

#define KILL_LOG "killed_players"
#define KILL_BOSSES "boss_killers"

/*
 * Function name: notify_you_killed_me
 * Description  : This routine is called in the killer when it causes the death
 *                of the victim. It can be used for additional processing.
 *
 *                This routin does not actually exist. It is a trick to fool
 *                the document maker.
 * Arguments    : object victim - the victim we caused to perish.
 */
public void
notify_you_killed_me(object player)
{
    string l_file;
    /* Loot the corpse. */
    command("get all from corpse");
    
    /* Only logs. player kills. */
    if (player->query_npc()) 
        return;
    seteuid(getuid(this_object()));
    l_file = TIME2FORMAT(time(), "dd/mm/yyyy");
    l_file += " " + player->query_real_name() + " (" 
             + player->query_average_stat() + ") killed by "
             + TO->query_name() + "\n";
        // Write a log file.
    log_file(KILL_LOG, l_file);
    
}

/*
* Function name: do_die()
* Description  : This is called when the npc is slain.
*
* This will also log who killes him, and the members of the
* team.
*
*/
public void
do_die(object killer)
{
    object *team;
    int i, size;
    string l_file;
     
    if (!objectp(killer) || !living(killer))
        return 0;
    
    // Check if other members in the team.        
    team = killer->query_team_others();
    // See if they are in the same room.
    team = filter(team, &operator(==) (environment(killer)) @ environment);
    // Find out the size of the team.
    size = sizeof(team);
    // Add timestamp, avg, and names.
    l_file = ctime(time()) + " " + killer->query_real_name()+
    " (" + killer->query_average_stat() + ") killed " + TO->query_name() +
    // Write down the teammembers also.
    (sizeof(team) ? " with assistance of:\n" : " ");
        
        for (i = 0; i < size; i++)
        {
            l_file += team[i]->query_real_name()+ " ("+
            team[i]->query_average_stat()+ ")     ";
        }
    l_file += "\n";
    // Write a log file.
    log_file(KILL_BOSSES, l_file);
    
    ::do_die(killer);
}

