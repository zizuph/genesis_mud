/*
    A Santa Claus
*/

inherit "/std/monster";
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>

#define GBREAD "/d/Calia/deinonychus/tmp/gbread.c"

/*
 * Function name: create_monster
 * Description:   creates the monster (what else?)
 * Arguments:     none
 * Returns:       nothing
 */

create_monster()
{
  set_living_name("Santa Claus");
  set_name("santa claus");
  set_long(break_string("That's Santa Claus. Everybody knows and loves him. " +
    "He'll punish those who've been bad this year and will reward those " +
    "who've been nice. He's carrying a sack filled with goodies and a rod " +
    "to hit the bad people.\n", 70));
  set_restrain_path("/d/Calia");
  set_monster_home("/d/Calia/deinonychus/tmp/room");
  set_random_move(20);
  enable_commands();
  add_prop(OBJ_M_NO_ATTACK, "You don't want to attack Santa Claus, do you?\n");
  add_prop(LIVE_I_ALWAYSKNOWN, 1);
}

/*****************************************************************************/

/*
 * Function name: init_living
 * Description:   add some commands to the player
 * Arguments:     none
 * Returns:       nothing
 */

void
init_living()
{
  call_out("react", 1, this_player());
}

void
react(object player)
{
  object gingerbread;
  if(!present(player, environment(this_object())))
    return;
  if(player->query_invis() > 0)
    return;
  if(sizeof(FIND_STR_IN_OBJECT("gingerbread", player)))
    return;
  if(player->query_alignment() >= 0)
  {
    command("say You've been nice this year " + player->query_name() +
      ". Therefore you shall be rewarded!");
    gingerbread = clone_object(GBREAD);  
    gingerbread->move(this_object());
    command("give gingerbread to " + player->query_real_name());
  }
  else
  {
    command("say You've been bad this year " + player->query_name() +
      ". Therefore you shall be punished!");
    say("The Santa Claus hits " + QCTNAME(player) + " with his rod.\n");
    write("Santa Claus hits you with his rod.\n");  
  }  
}
