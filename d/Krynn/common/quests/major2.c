/* A major adventure. Made by Nick for Krynn */
// Changed the age check to a size check, July 2002 by Boron

inherit "std/object";
#include "/d/Krynn/common/defs.h"
#include QUESTH
#define NAME "salamic"

/* Function name: size
 * Description:   Sets how big the player has to be to solve this quest
 * Arguments:     none
 * Returns:       the required size
 */
int
size()
{
    return 40;
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

    if (ob->query_average_stat() < size())
      return 2;

    if(ob && QUEST_MASTER->query_quest_number(MAJADV, ob) == 1)
    {
    tell_object(ob,
        "You have a reward to collect for helping Salamic first.\n");
    return 1;
    }
    return 0;
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
    int exp_val = 0;
    int prop = ob->query_prop(PLAYER_I_HELP_SALAMIC);
    if (QUEST_MASTER->query_quest_number(MAJADV, ob) != 1)
    {
        tell_object(ob,
        "You have to solve this quest in order to get a reward.\n");
        return 0;
    }


    exp_val += 5000;             /*player freed salamic*/
    if ((prop | 3) == 7)
      exp_val += 3000;           /*player killed hobgoblin*/
    if ((prop | 5) == 7)
      exp_val += 800;            /*player killed cook*/
    if ((prop | 6) == 7)
      exp_val += 1700;           /*player got key from highlord*/


    ob->add_exp(exp_val, 0);
    tell_object(ob,
        "Thank you for your help, please accept my help.\n");

    seteuid(getuid(TO));

    K_QUEST_LOG("quest", "Salamic", ob, exp_val);

    return exp_val;
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

