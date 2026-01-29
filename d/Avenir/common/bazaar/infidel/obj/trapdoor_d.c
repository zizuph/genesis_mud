
// file name: trapdoor_d.c
// creator(s): Ilyian, Oct 1995
// last update:
// purpose: Trapdoor that enters the infidel hideout
// note:
// bug(s):
// to-do:

inherit "/std/door";
#include "../infidel.h"

create_door()
{
   set_door_id("_infidel_trapdoor_");
   set_pass_command(({"up","sneak up","enter trapdoor"}));
   set_fail_pass("The trapdoor is closed.\n");
   set_door_name(({"trapdoor"}));

   set_door_desc("This simple trapdoor is made from "
                +"hardwood slats.\n");
   set_other_room(INFID + "house");
   set_open(0);
   set_locked(0);
   set_open_desc("An open trapdoor leads up.\n");
   set_closed_desc("A closed trapdoor lies above you.\n"); 
   set_open_command(({"open","turn","push","lift","raise"}));

   set_open_mess(({"swings the trapdoor open.\n",
      "The trapdoor opens.\n"}));
   set_fail_open(({"The trapdoor is already open.\n",
      "The trapdoor is locked.\n"}));
   set_close_command(({"close","pull", "pull closed", "shut"}));
   set_close_mess(({"swings the trapdoor shut.\n", "The trapdoor "+
       "closes.\n"}));
   set_fail_close("The trapdoor is already closed.\n");

}
