/*
 * Maintains quest information
 * -- Finwe, April 2005
 */
#include "defs.h"
#include "../quests/qbits.h"

#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <std.h>

/*
 * Function name : log_quest
 * Description   : logs quest information when completed
 */
nomask varargs int
log_quest(object player, string long_name, int quest_bit, int exp)
{
    string log_str;

    log_str = ctime(time()) + " "+ capitalize(player->query_real_name()) +
    " (" + player->query_average_stat() + ") did " + long_name + ".\n";

    log_file("faerie_quests", log_str);
    return 1;
    
}
