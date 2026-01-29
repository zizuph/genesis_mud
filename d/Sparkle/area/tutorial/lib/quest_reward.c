/*
 *  /d/Sparkle/area/tutorial/lib/quest_reward.c
 *
 *  This module can be inherited to handle the giving out of quest
 *  experience, assigning bits, and making log entries.
 *
 *  The function log_quest is copied with permission from:
 *    /d/Gondor/defs.c
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../defs.h"
#include <time.h>

/* Definitions */
#define QUEST_STRLEN 16


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
    /* NONONO! Don't use write_file() for logging!!! */
    if (file_size(TUTORIAL_QUEST_LOG) > 100000)
	rename(TUTORIAL_QUEST_LOG, TUTORIAL_QUEST_LOG + ".old");
    write_file(TUTORIAL_QUEST_LOG, sprintf("%s %-20s %-12s (%3d) %6d\n",
        ctime(time()),
        ((strlen(name) > QUEST_STRLEN) ? name[0..(QUEST_STRLEN - 1)] : name ),
        player->query_name(), player->query_average_stat(), exp));
} /* log_quest */


/*
 * Function name:        give_reward
 * Description  :        If the bits aren't already set in the player,
 *                       give them the reward.
 * Arguments    :        object player - the player,
 *                       int group     - the group number,
 *                       int bit       - the bit number,
 *                       int exp       - the exp reward,
 *                       string name   - the name of the quest
 */
public void
give_reward(object player, int group, int bit, int exp, string name)
{
    int  reward = player->query_exp();

    if (player->test_bit(getuid(), group, bit))
    {
        player->catch_tell("You don't feel any more experienced this"
          + " time.\n");
        return;
    }

    if (reward > exp)
    {
        reward = exp; /* we only give out as much exp as the player has */
    }

    player->set_bit(group, bit);
    player->add_exp_quest(reward);
    player->catch_tell("You feel more experienced!\n");
    log_quest(player, reward, name);
} /* give_reward */

