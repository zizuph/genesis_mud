/* Typo fixed by Vadiem 1:12:94 */

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "defs.h"

create_room() {
   set_short("Whitefurrows southern half");
   set_long(break_string(
      "This is the southern half of the little village called Whitefurrows. "
    + "On the roadside several hobbit-houses have been built. Most of them "
    + "have a closed door, but the door in the house west of you seems to "
    + "be open. North lies the great Eastroad which cuts the village in "
    + "half.\n",70));

   add_item("door", "The door of the little house is made of oak and has rusty hinges.\n");

   add_item(({"house","houses"}), break_string(
      "The houses are actually more like holes, but that is the way the "
    + "hobbits like them. All of them have little round doors and windows, "
    + "but only the door of the house to the west seems to be open.\n",70));

   add_exit(STAND_DIR + "er8", "north");
   add_exit(STAND_DIR + "wf_house1", "west", "@@make_noise");

   add_prop(ROOM_I_INSIDE,0); /* This room lies outside */
}

make_noise() {
   write("The door squeaks as you push it open.\n");
   say("The door squeaks as " + QCTNAME(this_player()) + " pushes it open.\n");

   seteuid(getuid());      /* You must do this in a VBFC function */
   (STAND_DIR + "wf_house1")->open_door();  /* Make noise in other room */
}

open_door() {
   tell_room(this_object(), "The door squeaks as someone pulls it open from the inside.\n");
}
