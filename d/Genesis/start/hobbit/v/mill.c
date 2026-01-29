/*
 *  The watermill
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"

int wheel_fixed;

create_room()
{
       add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("Watermill");
   set_long("@@my_long");
   add_item(({"machine","sawing machine","big machine"}), "@@my_item_long");

   add_exit(STAND_DIR + "h_lane4","west",0);
   add_exit(STAND_DIR + "mill2","up",0);

   add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */

   clone_object(STAND_DIR + "sandyman")->move(this_object());
   wheel_fixed = 0;
}

reset_room() {
 /* Put the miller back if he was killed */
   if (!present("sandyman"))
      clone_object(STAND_DIR + "sandyman")->move(this_object());
 /* Don't reset quest every reset. */
   if (wheel_fixed && !random(4))
      wheel_fixed = 0;
}

my_long() {
   string mylong;
   mylong =
      "You have entered a watermill of some sort. The power generated "
    + "by the current in the Bywater river is here utilized to saw "
    + "wood. There is a big sawing machine standing against "
    + "the southern wall. ";

   if(wheel_fixed)
      mylong += "Some hobbits are sawing a tree trunk into smaller parts.\n";
   else
      mylong += ("A hobbit is desperately trying to repair the sawing "
        + "machine, without much effect.\n");

   return break_string(mylong,70);
}

my_item_long() {
   string mylong;
   mylong =
      "The big sawing machine is old, but does the job well. "
    + "It has been kept in a perfect state by the hobbits who work "
    + "in this mill. It uses the waterwheel outside to get the "
    + "sawing blades in motion. ";

   if(wheel_fixed)
      mylong += "The machine makes a loud buzzing noise when it saws wood.\n";
   else
      mylong += "Unfortunately, it is now out of order.\n";

   return break_string(mylong,70);
}

query_wheel_fixed() {
   return wheel_fixed;
}

set_wheel_fixed(val) {
   wheel_fixed = val;
}
