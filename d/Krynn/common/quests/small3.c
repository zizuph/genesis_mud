/* A small adventure. Made by Aridor for Krynn, 06/15/94 */
// Changed the age check to a size check, July 2002 by Boron


inherit "std/object";
#include "/d/Krynn/common/defs.h"
#include QUESTH
#define NAME "small3"

/* Function name: size
 * Description:   Sets how big the player has to be to solve this quest
 * Arguments:     none
 * Returns:       the required size
 */
int
size()
{
    return 35;
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

    tell_object(ob,"Poor little Brimsch the gnome is a good friend of mine.\n" +
        "He is having big difficulties with his life quest. Please\n" +
        "help him.\n");
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
    object note = present("brimsch_note", ob);
    int bas_xp, prp;

    if (!note)
      {
      tell_object(ob,"You have to solve this quest in order to get a reward.\n");
      return 0;
      }

    note->remove_object();

    prp = ob->query_prop(PLAYER_I_BRIMSCH_LIFE_QUEST);
    bas_xp = 1000;
    if (prp & 1)
      bas_xp += 1500;  /* player got the muffin him/herself */
    if (prp & 2)
      bas_xp += 2500;  /* player smashed the muffin him/herself near gully dwarf */

    ob->add_exp(bas_xp, 0);
    seteuid(getuid(TO));

    K_QUEST_LOG("quest", "Small 3", ob, bas_xp);

    return bas_xp;
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
    /* ob->add_exp(-200, 0);  Lose xp if you pass a quest. */
    return 1;
}

