/*
 * /d/Kalad/common/kill_logger.c
 * 
 * This file will write a log whenever the npc that
 * inherits this kills a player. The log can be
 * found in /d/Kalad/log/killed_players
 *
 * Created Nov 2017, by Andreas Bergstrom ( Zignur )
 *
 */

#include <macros.h>
#include <time.h>
#include "/d/Kalad/defs.h"

#define KILL_LOG "killed_players"

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
