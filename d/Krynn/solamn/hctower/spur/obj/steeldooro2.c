/* created by Aridor 06/25/93 */

inherit "/std/door";
#include "../local.h"

create_door()
{
   set_door_id("_steeldoor_2_");
   set_pass_command(({"nw","northwest","enter","go through","in"}));
   set_fail_pass("Walking through gates is a skill you haven't " +
      "mastered yet. Try opening them first.\n");
   set_door_name(({"sturdy steel gate","steel gate", "gate"}));  
   set_door_desc("A sturdy steel gate.\n");
   set_other_room(ROOM + "hall6");
   set_open(0);
   /*set_locked(1);   --not yet*/
   
}
