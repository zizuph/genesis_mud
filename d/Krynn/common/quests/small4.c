/* A small adventure. Made by Aridor for Krynn, 06/15/94 */
// Changed the age check to a size check, July 2002 by Boron


inherit "std/object";
#include "/d/Krynn/common/defs.h"
#include QUESTH
#define NAME "small4"
#define PLAYER_I_PICKED_UP_GLASSES "_player_i_picked_up_glasses"

/* Function name: size
 * Description:   Sets how big the player has to be to solve this quest
 * Arguments:     none
 * Returns:       the required size
 */
int
size()
{
    return 38;
}

/*
 * Function name: ask
 * Description:   The function called when somebody asks about this quest
 * Arguments:     ob - the object asking
 * Returns:       0 - if nothing is written to the object
 *                1 - if something was written
 *                2 - nothing was written, can't do quest (yet)
 */
int
ask(object ob)
{
    if (!ob)
      return 1; /* If there was an object we would have written something. */

    if (ob->query_average_stat() < size())
      return 2;

    tell_object(ob,"I must have lost my spectacles the last time I visited my " +
        "friends among the mountain dwarves. If you happen to find the " +
        "glasses, would you please be so kind and return them to me?\n");
    return 1;
}

/*
 * Function name: reward
 * Description:   Function called when an object wants a reward
 * Arguments:     The object wanting the reward
 * Returns:       0 - if no reward was given, I write the error code
 *                1 - Reward was given, you write the standard messages
 *                2 - Reward given, I write the standard message
 */
int
reward(object ob)
{
    object specs = present("qmaster_spectacles", ob);
    int bas_xp, prp, ret;

    if (!specs)
      {
      tell_object(ob,"You have to solve this quest in order to get a reward.\n");
      return 0;
      }

    specs->remove_object();

    prp = ob->query_prop(PLAYER_I_PICKED_UP_GLASSES);
    if (!prp) /*if prop isn't set, player cheated - no reward :) */
      {
      tell_object(ob, "The quest master thinks you cheated. You won't get a " +
              "reward now. Please try to find the glasses again!\n");
          ret = 0;
      }
    else /* player found the glasses */
      {
      ob->remove_prop(PLAYER_I_PICKED_UP_GLASSES);
      bas_xp = 1500;  /* player found the glasses (if prop isn't set, player cheated :) */
      ob->add_exp(bas_xp, 0);
      ret = 1500;

      seteuid(getuid(TO));

      K_QUEST_LOG("quest", "Small 4", ob, bas_xp);
      }

    return ret;
}

/*
 * Function name: pass
 * Description:   Function called when player wants to pass
 * Arguments:     The object wanting to pass
 * Returns:       0 - if no pass granted, I write the error code
 *                1 - pass granted, you write the standard messages
 *                2 - pass granted, I write the standard message
 */
int
pass(object ob)
{
    return 1;
}


