/*
The mansion stairs. Mortricia 920906.
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

void
create_room()
{
   set_short("Stairs");
   set_long(BS(
         "You stand in a large hall. The room being governed by a large " +
         "balustrade staircase that goes up and down. If it were not so " +
         "dirty and coated with cobwebs, this room would be quite grand. " +
         "The stairs lead up to the second level and down to the dark " +
         "reaches of the basement.\n"
));
   
   add_prop(ROOM_I_INSIDE, 1);
   
   add_exit(MANSION + "second/front_stairs", "up", "@@creak1");
   add_exit(BASE + "hall5", "down", "@@creak0");
   add_exit(MANSION + "grand", "east", 0);
   
   add_item(({"stairs", "staircase", "balustrade stairs"}),
      "A gothic set of oak balustrade stairs leading up and down.\n");
   add_exit(MANSION + "wing_w3", "west", 0);
}

creak0()
{
   write("You feel uneasy using these old stairs, but you continue " +
      "anyhow.\n");
   write("CRACK!!\n");
   write("CREAK!!\n");
   return 0;
}

creak1()
{
   if (this_player()->query_wiz_level()) {
         write("You deftly leap up onto the second floor using " +
               "your super-wizard powers!\n");
   say(QCTNAME(TP) + " sprouts wings and flutters upto the second floor!\n");
   return 0;
   }
   write("CREAK!!\n");
   write(BS(
         "You feel uneasy using these old stairs, and you decide not to " +
         "go any further.\n"
         ));
   return 1;
}
