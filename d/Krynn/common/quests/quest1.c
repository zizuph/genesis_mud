/* A real quest. Made by Aridor */
// Changed the age check to a size check, July 2002 by Boron


inherit "std/object";
#include "/d/Krynn/common/defs.h"
#include QUESTH

/* Function name: size
 * Description:   Sets how big the player has to be to solve this quest
 * Arguments:     none
 * Returns:       the required size
 */
int
size()
{
    return 80;
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
    string task;

    if (!ob)
    return 1; /* If there was an object we would have written something. */

    if (ob->test_bit("Krynn",2,12))
      return 0; /* did the quest already */

    if (ob->query_average_stat() < size())
      return 2;

    if (!("/d/Krynn/solamn/thief/theiwar/r11"->query_gate_state()) ==
    (ob->query_alignment() >= 0))
    {
    tell_object(ob, "The Master says: 'Unfortunately, I do not need your " +
            "help just now. Please check back with me again soon.'\n");
    return 1;
    }

    if (ob->query_alignment() >= 0)
      task = "once again bring the joy of light to them.";
    else
      task = "once again bring the embrace of darkness to them.";
    tell_object(ob,"The Master says: 'It has come to my attention that the " +
        "mountain dwarves need your assistance. It is your task to " +
        task + "'\n");
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
    tell_object(ob, "I don't reward this quest.\n");
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
    return 0;
}
