inherit "/std/room";

#include "defs.h"

create_room() {
   set_short("Main road");
   set_long(break_string(
      "You are on the great Eastroad. Birds are whistling and "
    + "every now and then you spot a squirrel running over the "
    + "road in this happy part of the Shire." 
    + " If you look closely you can see a sign lying on the ground.\n",70));

   add_exit(STAND_PARENT + "evendim/ev1", "north", 0);
   add_exit(STAND_DIR + "er14", "east", 0);
   add_exit(STAND_DIR + "er16", "west", 0);

   add_item("sign", "@@sign_long");
   add_item("bird", "You cannot see them, just hear.\n");
   add_item("birds", "You cannot see them, just hear.\n");
   add_item("squirrel", " Brown, small, quick.\n");

}

string sign_long() {

  return "The sign looks like it has been lying in the dirt for ages,\n"
    + "maybe even longer. When you wipe of some dirt you can make out\n"
    + "the following text:\n"
    + "A..um..e. .. l.\n"
    + "The rest of the sign is broken.\n"
    + " You think that it once pointed north.\n";
}
