/*
This is the marble sarcophagus room.
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

#define DIFFICULTY     TASK_SIMPLE /* It's easy to climb */
#define DAMAGE         10      /* Let it hurt somewhat */

void
reset_room()
{
}

void
create_room()
{
   object door;
   
   set_short("inside marble sarcophagus");
   set_long(BS(
         "You are now inside the marble sarcophagus. It is nothing but a " +
         "secret passage that may take you downwards, if you dare to climb " +
         "the ladder.\n"
         ));
   
   add_prop(ROOM_I_INSIDE, 1);
   add_item(({"ladder"}), BS(
      "The ladder seem to be somewhat brittle.\n"
      ));
   
   add_cmd_item(
      ({"wall", "sarcophagus"}),
      "climb",
      "The sarcophargus walls are too slippery...\n");
   
   add_cmd_item(
      ({"ladder", "down"}),
      "climb",
      "@@climb_ladder");
   
   door = clone_object(MANSION + "chapel/sarc_door2");
   door -> move(TO);
   
   reset_room();
}

climb_ladder() {
   int success;
   
   success = TP -> resolve_task(DIFFICULTY,
      ({ SKILL_WEIGHT, 100, SS_CLIMB,
            SKILL_WEIGHT, 100, SS_DEX }) );
   if (success < 0) {
      write(BS(
            "You try to climb down on the ladder, but you slip!  " +
            "You start to fall! Reaching out, you try to grab the " +
            "ladder, but you are too late.\n"
            ));
      say(QCTNAME(TP) + " tried to climb the ladder but fell down.\n");
      TP -> reduce_hit_point(DAMAGE);
      TP -> move_living("falling, screaming, downwards",
         MANSION + "colors/maze_entrance");
      TP -> do_die();
      return 1;
   }
   write(BS(
      "Being such a swift climber you climb down on the ladder easily.\n"
      ));
   TP -> move_living("down", MANSION + "colors/maze_entrance");
   return 1;
}
