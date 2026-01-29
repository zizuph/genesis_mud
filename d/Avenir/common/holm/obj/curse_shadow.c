// Curse shadow 
// creator(s):  Lilith Jan 96
// last update: 
// purpose:     Shadowing player eating and drinking
// note:        There is an object associated with this file
//         
// bug(s):
// to-do:

inherit "/std/shadow.c";
#include "/d/Avenir/common/common.h"

/*
 * Function name:   team_join
 * Description:     Sets this living as the leader of another
 *                  Fails if we have a leader, then we can't lead others.
 * Arguments:	    member: The objectpointer to the new member of my team
 * Returns:         True if member accepted in the team
 */
public int
team_join(object member)
{
   shadow_who->catch_msg("The penalty for your blasphemy is "+
      "loneliness! I will not permit you the company of others...\n");
   return 0;
}

/*
 * Function name:    set_leader
 * Description:      Sets this living as a member in a team
 *                   It will fail if this living is a leader itself
 * Arguments:	     leader: The objectpointer to the leader of the team
 * Returns:	     True if successfull
 */
public int
set_leader(object leader)
{
   shadow_who->catch_msg("A triumphant voice rings inside your head: "+
      "The penalty for your blasphemy is loneliness! "+
      "I will not permit you the company of others...\n");
   return 0;

}

/*
 * Function name: 	eat_food
 * Description:   	Eats a certain amount of food.
 * Arguments:		amount: The amount of food.
 *			ask: True if we only want to know IF we can eat this
 * Returns:		True if successfully eaten.
 */
public int
eat_food(int amount, int ask)
{
  return (shadow_who->query_wiz_level() ? shadow_who->eat_food(amount, ask) : 0);
}
/*
 * Function name: 	drink_soft
 * Description:   	Drinks a certain amount of liquid
 * Arguments:		amount: The amount of the drink
 *			ask: True if we only want to know IF we can drink this
 * Returns:		True if successfully drunk.
 */
public int
drink_soft(int amount, int ask)
{
  return (shadow_who->query_wiz_level() ? shadow_who->drink_soft(amount, ask) : 0);
}

/*
 * Function name: 	drink_alco
 * Description:   	Drinks alcohol of a certain potency
 * Arguments:		strength: The strength of the drink
 *			ask: True if we only want to know IF we can drink this
 * Returns:		True if successfully drunk.
 */
public int 
drink_alco(int strength, int ask)
{
  return (shadow_who->query_wiz_level() ? shadow_who->drink_alco(strength, ask) : 0);
}




