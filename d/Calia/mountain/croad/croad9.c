/* Maniac 9/3/95 */
/* Slip code by Overlord */
/* A room on the crystalline road up Mount Kyrus in Calia. 
   One of the scout krougs resets to here. 

   Modified, Maniac 19/9/95  

   History: 

   2/7/01    arm_me call to kroug removed (done from std kroug)   Maniac 

 */


inherit "/d/Calia/std/std_croad_mountain";

#include <macros.h>
#include "crdefs.h"

inherit SLIP;

object kroug;

void
reset_room()
{
    if (!objectp(kroug)) {
        kroug = clone_object(MOUNTAIN_MONSTERS + "kroug_scout");
        kroug->move_living("M", this_object());
        kroug->command("hide");
        tell_room(this_object(), QCTNAME(kroug) + " creeps stealthily in.\n");
   }
}


void
create_room()
{
    make_the_room("The road leads upwards to the southwest " +
      "and down to the north.\n", 10);
    add_exit(CROAD+"croad10","southwest","@@slip", 2);
    add_exit(CROAD+"croad8","north", "@@slip");

    reset_room();
}

