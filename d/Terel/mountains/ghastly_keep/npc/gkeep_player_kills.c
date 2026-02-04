/*  /d/Terel/mountains/ghastly_keep/npc/gkeep_player_kills.c
 *
 *  A simple file that logs player kills in Ghastly Keep.
 *
 *  This will be inherit in all the npc files in Ghastly Keep.
 *
 *  Created by Znagsnuf.
 *
 *  Date:                      What is done:                           By whom:            
 *  --------------------------------------------------------------------------- 
 *
*/

#include "defs.h"
#include <macros.h>
#include <time.h>

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

    // Loot the corpse.
    command("get all from corpse");
    
    // Only logs. player kills.
    if (player->query_npc()) 
        return;

    seteuid(getuid(this_object()));

    l_file = TIME2FORMAT(time(), "dd/mm/yyyy");

    l_file += " " + CAP(player->query_real_name()) + " (" 
             + player->query_average_stat() + ") killed by "
             + CAP(TO->query_name() + "\n");

        // Write a log file.
    write_file(P_KILL_IN_GKEEP, l_file);
}
