/*
 * /d/Emerald/sys/questlog.c
 *
 * This object contains code that is used by the defines in the Emerald
 * macros file /d/Emerald/sys/macros.h
 *
 * Based on code created for Gondor by Mercade, 15 March 1994
 *
 * Revision history:
 */

#include "/d/Emerald/sys/macros.h"
#include "/d/Emerald/sys/paths.h"

#define QUEST_STRLEN 25

/*
 * Function name: create
 * Description  : This function is called when the file is loaded into
 *                memory. Note that there is no reason to make this an
 *                object, so it is not an object.
 */
nomask void
create()
{
    setuid();
    seteuid(getuid());
} /* create */

/*
 * Function name: log_quest
 * Description  : This function makes the log of a quest when it is
 *                solved and is placed here to make a uniform log-format.
 * Arguments    : player - the player who did the quest
 *                exp    - the experience gained
 *                name   - the name of the quest
 */
nomask varargs void
log_quest(object player, int exp, string name)
{
    write_file(QUEST_LOG, sprintf("%s %-29s %-12s (%3d) %6d\n",
        ctime(time()),
        ((strlen(name) > QUEST_STRLEN) ? name[0..(QUEST_STRLEN - 1)] : name ),
        (string)player->query_name(),
        (int)player->query_average_stat(),
        exp));
} /* log_quest */
