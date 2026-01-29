/* A small adventure. Made by Nick for Krynn */
// Changed the age check to a size check, July 2002 by Boron


inherit "std/object";
#include "/d/Krynn/common/defs.h"


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

    tell_object(ob,
    "Pick an apple from the apple tree in Solace for experience.\n");
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
    tell_object(ob,"You have to solve this quest in order to get a reward.\n");
    return 0;
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
    /* ob->add_exp(-300, 0);  Lose quest xp if you pass a quest. */
    return 1;
}
