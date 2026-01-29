/*
 *   A temporary room for the mail pidgeons. Nobody is supposed to come here.
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"

create_room() {
   set_short("Waiting room");
   set_long(break_string(
      "You are in the very room where the carrier pidgeons take a rest "
    + "after a long journey. Please leave them alone.\n",70));
}