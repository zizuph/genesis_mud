// -*-C++-*-
// Raising pillar, part of magic square quest
// Boriska@Genesis, Nov 1994
// Revision: Lilith Jun 2004: took out do_die, also changed to task ROUTINE.
//             We are killing players and I don't like it.
//           Zizuph Aug 2022 - typo and grammar fixes found while looking
//             for quest bug.

inherit "/std/room";

#include <tasks.h>
#include <formulas.h>
#include "/d/Avenir/common/dark/dark.h"
#include "/d/Avenir/include/magic_square.h"

// what to say on each step
static string *text = ({
  "Rumbling slightly, the dais you are standing on slowly rises up from " +
  "the ground, becoming a pillar.\n",
    
  "Suddenly a 'thunk' seems to stop the pillar halfway in its ascent,\n" +
  "leaving you too high to jump down, yet too far from the ceiling to\n" +
  "grab ahold.\n",
    
  "The pillar starts swaying from side to side. " +
  "You begin to wonder how safe it is...\n",
    
  "After what seems an eternity, the pillar moves up again,\n" +
  "more slowly than before.\n",

  "The structure comes closer to the the top of the cavern,\n" +
  "leaving only a handspan of room above your head.\n"
});

// what to do on each step, should be the same length as text
// 0 means do nothing
// if action returns 0, sequence is terminated
static string *actions = ({
  0,
  0,
  "check_fall",
  0,
  0
});
  
int length = sizeof(text);
int alarm_id = 0;
int step;
private void impress(object tp);

void
create_room ()
{
  set_short ("on the pillar");
  set_long ("You are standing on the pillar, which slowly rises up " +
	   "into the cavern by an invisible but powerful " +
	   "mechanism. As you rise higher and higher, you feel a warm " +
	   "flow of air and notice a faint spot of light above your head. " +
	   "You can see more of the cavern ceiling above by this light.\n"
	    );
  add_item(({"ceiling", "cavern ceiling", "above"}), 
       "The rough and craggy stone ceiling is becoming more visible " +
       "as if it is being illuminated by something hidden from view.\n");
  add_item(({"faint spot of light", "spot", "light", "illumination"}),
       "Something is glowing faintly by the cavern ceiling but you " +
       "can't quite see what it is. Yet...\n");
  add_prop(ROOM_I_LIGHT, 0);
  add_prop(ROOM_M_NO_TELEPORT,
	   "The ancient magic keeps you from doing that.\n");
  // no way out...
  IN;
}

void
enter_inv(object ob, object from)
{
  ::enter_inv (ob, from);
  
  if (!ob || !living(ob))
    return;

  if (!alarm_id)
    {
      alarm_id = set_alarm ( 2.0, 10.0, &impress(ob));
      step = 0;
    }
}    
     
private void
impress (object tp)
{
  if (objectp(tp) && environment(tp) != this_object()) { // we're no longer here
    remove_alarm(alarm_id);
    alarm_id = 0;
    return;
  }
  
  if (step == length)
    {
      remove_alarm (alarm_id);
      alarm_id = 0;
      tp->add_prop(SQUARE_SOLVED, 1); // we got that far on our own
      tp->catch_msg ("The pillar ceases its movement.\n");
      tp->move_living ("M", ARTIFACT_ROOM);
      tp->catch_msg (
      "When you step from the pillar, it starts moving soundlessly " +
      "down toward the floor, where it becomes a dais once again.\n");
      say (QCTNAME(tp) + " steps from pillar onto the ledge.\n");
      say ("As " + tp->query_pronoun() + " leaves the pillar, it " +
	   " stards moving back down to the floor.\n"); 
      DAIS_ROOM->set_pillar_raised (0); // tell the room below pillar is back
      return;
    }

  tp->catch_msg (text[step]);
  
  // should we call some function on this step ?
  if (!actions[step] || call_other (this_object(), actions[step], tp))
    {
      step++;
      return;
    }
  else
    {
      remove_alarm(alarm_id);
      alarm_id = 0;
      DAIS_ROOM->set_pillar_raised (0); // tell the room below pillar is back
    }
}


int
check_fall (object player)
{
  
  if (player->resolve_task (TASK_ROUTINE, ({SS_CLIMB, SS_ACROBAT, TS_DEX})) > 0)
    return 1;
  
  player->catch_msg (
	"You struggle valiantly to keep your balance but fail!\n" +
	 "You fall down to the floor and hurt your head.\n");

  player->move_living("M", DAIS_ROOM); // here we go again...
  player->heal_hp(-random(F_MAX_HP(140)));
  
  if (player->query_hp() <= 0 )  // we broke our neck
    {
      player->catch_msg("You broke your neck!\nMaybe, if you hold very still "+
          "for a while, you won't die.\n");
// No more killing players. -- Lilith
//      player->do_die();
    }
  return 0;
}
