/*
 * /d/Gondor/defs.c
 *
 * This object contains code that is used by the defines in the Gondorian
 * defines file /d/Gondor/defs.h
 *
 * /Mercade, 15 March 1994
 *
 * Revision history:
 */

#include "/d/Gondor/defs.h"
#include <time.h>

#define QUEST_STRLEN 25
#define QTIMES "/d/Gondor/log/quest_times"
#define PLAYER_I_QUESTING_ "_player_i_questing_"

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
}

void
end_quest(object player, string quest)
{
    int qtime;

    if (!objectp(player) || !strlen(quest))
        return;

    qtime = player->query_prop(PLAYER_I_QUESTING_ + quest);

    if (!qtime)
        return;

    qtime = time() - qtime;
    write_file(QTIMES, extract(ctime(time()), 4, 18) +
        " " + capitalize(player->query_real_name()) +
        " finished " + quest + " in " + CONVTIME(qtime) +
        ".\n");
}

void
start_quest(object player, string quest)
{
    if (!objectp(player) || !strlen(quest))
        return;

    if (!player->query_prop(PLAYER_I_QUESTING_ + quest))
    {
        write_file(QTIMES, extract(ctime(time()), 4, 18) +
            " " + capitalize(player->query_real_name()) +
            " started " + quest + ".\n");
        player->add_prop(PLAYER_I_QUESTING_ + quest, time());
    }
}

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
    end_quest(player, name);
}
