/*
 *  /d/Sparkle/area/orc_temple/lib/quest_reward.c
 *
 *  This module handles the giving of quest rewards here in the orc
 *  temple.
 *
 *  The function log_quest is copied with permission from:
 *    /d/Gondor/defs.c
 *
 *  Created October 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../defs.h"
#include <time.h>

/* Definitions */
#define QUEST_STRLEN 16

/* Prototypes */
public void        give_reward(object player, int group, int bit, int exp,
string name);


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
    write_file(QUEST_LOG, sprintf("%s %-20s %-12s (%3d) %6d\n",
        ctime(time()),
        ((strlen(name) > QUEST_STRLEN) ? name[0..(QUEST_STRLEN - 1)] : name ),
        (string)player->query_name(),
        (int)player->query_average_stat(),
        exp));
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
