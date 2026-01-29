/*  An inheriatable file used for when we give players general exp
 *  for just going somewhere "out of the way" or a place that was
 *  difficult to find.  Not worthy of Qexp, but some reward is deserving.
 *
 *  Created by Igneous@Genesis,  aka Chad Richardson
 *
 *  Exmaple on how to use this file:

  inherit "/d/Khalakhor/std/room";
  inherit "/d/Khalakhor/lib/exploration";

  #include "/d/Khalakhor/sys/skills.h"
  //  Include the area exploration defines
  #include "/d/Khalakhor/se_speir/exploration.h"

  void
  create_khalakhor_room()
  {
      // Configure and create your room
      set_explore_exp(100);
      set_explore_skill(SS_EXPLORATION_SE_SPEIR);
      set_explore_place(EXPLORE_TEST_AREA);
  }

  void
  enter_inv(object ob, object from)
  {
      ::enter_inv(ob, from);
      explore(ob);
  }

 *
 */

// Global Vars
static int gExplore_exp, gExplore_skill, gExplore_place;

/* Function name: set_explore_exp
 * Description:   set the amount of exp a player will get for exploring
 * Arguments:     int exp:  amount of experience
 */
public void
set_explore_exp(int exp)
{
    gExplore_exp = exp;
}

/* Function name: set_explore_place
 * Description:   sets the explore bit for this place.
 * Arguments:     int place: the bit number used for this place
 */
public void
set_explore_place(int place)
{
    gExplore_place = place;
}

public void
set_explore_skill(int skill)
{
    gExplore_skill = skill;
}

public int
query_explore_skill()
{
    return gExplore_skill;
}

/* Function name: query_explore_exp
 * Description:   a query to find how much exp this place gives
 * Returns:       int
 */
public int
query_explore_exp()
{
    return gExplore_exp;
}

/* Function name: query_explore_place
 * Description:   a query to find the bit number this palce uses
 * Returns:       int
 */
public int
query_explore_place()
{
    return gExplore_place;
}

/* Function name: hook_explored_place
 * Description:   a hook which is called by an alarm to give a delayed
 *                message to the player that they have gotten some exp
 * Arguments:     object player:  Player to receive the message
 */
public void
hook_explored_place(object player)
{
    player->catch_tell("You feel a little more experienced for finding this "+
      "place.\n");
}

/* Function name: explore
 * Description:   Takes care of the skill checks and the exp giving for
 *                the exploration of this room.
 * Arguments:     object player:  The player that is exploring this area
 */
public varargs void
explore(object player, int slient)
{
    // Make sure we are dealing with a player (No need to set this for npcs)
    if (!interactive(player))
	return;
    // Make sure everything is set up
    if (!gExplore_exp || !gExplore_skill || !gExplore_place)
	return;
    // If we have someone leading us we don't deserve any exp!
    if (player->query_leader())
	return;
    // Now check to see if we've been here before
    if (player->query_skill(gExplore_skill) & gExplore_place)
	return;

    // We haven't been here before so reward the player for showing up!
    player->set_skill(gExplore_skill, player->query_skill(gExplore_skill) |
      gExplore_place);
    /* Not ready for this quite yet.
    player->add_exp_general(gExplore_exp);
    */
    if (!slient)
	set_alarm(0.1,0.0, &hook_explored_place(player));
}
