// Place where player is moved from moving pillar,
// part of magic square quest.
// Boriska@Genesis, Nov 1994
// Revisions: Zizuph Aug 2022 for once-per-reboot quest fix. 
//              Made sure the room resets with the flame in 
//              it after player leaves. Made sure the flame 
//              moved properly to the vial. Added more verbs 
//              for leaving the room.

inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"

#include <tasks.h>

#include "/d/Avenir/include/magic_square.h"

int artifact_alarm = 0;
int do_climb(string str);
int do_jump(string str);

object artifact;

// This resets the artifact. It is called by set_alarm when
// player leaves the room and when the room resets. No more
// player finishing the magic square and getting here to find
// there is no flame to collect.
void reset_artifact()
{
   if (!present(artifact))
   {	   
     artifact = clone_object(ARTIFACT);
     artifact->move(this_object());
   }	
}	

void reset_room()
{
   // make sure alarm is removed if reset happens.
   if (artifact_alarm)
      remove_alarm(artifact_alarm);
   artifact_alarm = 0;
   
   // make sure quest resets
   reset_artifact();
}

void
create_room ()
{
  set_short ("cavern ceiling");
  set_long ("You are in a small room formed by a narrow ledge high up " +
	    "on the cavern walls near the ceiling, which cannot be seen " +
	    "from below. You hardly manage to keep your balance with the " +
        "air rushing past you and up through an opening in the ceiling.\n");

  add_item (({"wall", "walls"}), "The walls are raw stone, black and wet.\n");
  add_item ("ledge",
      "The ledge is narrow, no wonder you could not see it from below.\n");
  add_item (({"ceiling", "crack", "hole", "opening", "spot"}),
      "There is an opening in the ceiling through which the air flows. " +
      "You realize that climbing through it is the only way off this "+
      "ledge.\n");

  add_prop (ROOM_I_LIGHT, 0);
  IN;

  reset_room();
}

// used by L4/cr22 to alter long room description
int
query_artifact () { return present (ARTIFACT_ID, this_object()) ?  1 : 0; }
     
void
init()
{
  ::init();
  add_action (do_climb, "climb");
  add_action (do_jump, "jump");
  add_action (do_jump, "leap");
  add_action (do_jump, "fall");
  
}


int
do_climb (string str)
{
  object tp = this_player();
  
  notify_fail ("Climb where?\n");
  if (!str) 
    return 0;

  notify_fail("That is not possible from here.\n");
  if (str == "down")
  return 0;	

  notify_fail ("Climb through what?\n");  
  if ((str != "through hole" && str != "through crack" &&
       str != "through opening"))
    return 0;	
	
  if (tp->query_fatigue() < tp->query_max_fatigue()/7)
    {
      tp->catch_msg ("You are too tired to climb.\n");
      return 1;
    }
  
  if (tp->resolve_task (TASK_DIFFICULT, ({ SS_CLIMB, TS_DEX})) > 0)
    {
      tp->catch_msg ("You reach upwards and climb up through the hole in ceiling.\n");
      tp->move_living ("through hole", "/d/Avenir/common/dark/l3/center");
      tp->add_fatigue (- tp->query_max_fatigue()/7);
      say (QCTNAME(tp) + " appears from a jagged patch in the wall.\n");
	  // If player leaves, reset the room 5 mins later
      if (!artifact_alarm)
          artifact_alarm = set_alarm(300.0, 0.0, &reset_artifact());		  
      return 1;
    }

  // failure
  tp->catch_msg ("You start climbing up but lose your grasp and fall back "+
       "Perhaps you are too tired to make the climb?\n");
  say (QCTNAME(tp) + " starts to climb up the hole but falls back.\n");
  tp->add_fatigue (- tp->query_max_fatigue()/7);
  // adds some spice, as player has to rush to NPC before flame burns out
 
  return 1;
}


int
do_jump (string str)
{
  object tp = this_player();
  
  notify_fail ("Jump where? Down?\n");
  if (!str) 
    return 0;

  notify_fail("On second thought, no. The fall would surely kill you.\n");
  if (str == "down")
  return 0;	  

  notify_fail ("Jump through what?\n");  
  if ((str != "through hole" && str != "through crack" &&
       str != "through opening"))
    return 0;	
	
  if (tp->query_fatigue() < tp->query_max_fatigue()/7)
    {
      tp->catch_msg ("You are too tired to pull yourself up into the hole.\n");
      return 1;
    }
  
  if (tp->resolve_task (TASK_DIFFICULT, ({ SS_CLIMB, TS_DEX})) > 0)
    {
      tp->catch_msg ("You reach upwards and climb up through the hole in ceiling.\n");
      tp->move_living ("through hole", "/d/Avenir/common/dark/l3/center");
      tp->add_fatigue (- tp->query_max_fatigue()/7);
      say (QCTNAME(tp) + " appears from a jagged patch in the wall.\n");
      // If player leaves, reset the room 5 mins later	  
      if (!artifact_alarm)
          artifact_alarm = set_alarm(300.0, 0.0, &reset_artifact());
      return 1;
    }

  // failure
  tp->catch_msg ("You jump up into the hole but lose your grasp and fall "+
       "back onto the ledge. Perhaps you are too tired?\n");
  say (QCTNAME(tp) + " starts to climb up the hole but falls back.\n");
  tp->add_fatigue (- tp->query_max_fatigue()/7);
  // adds some spice, as player has to rush to NPC before flame burns out
 
  return 1;
}



