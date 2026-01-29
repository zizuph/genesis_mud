/*
 * Bywater Road 
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>

create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("The Bywater road outside the Church");
   set_long("You are standing on Bywater road outside the church. "
    + "The road stretches out from the east to the west. "
    + "On the north side of the road are some houses which obviously "
    + "are inhabited by hobbits, since they lack windows. "
    + "To the south is a small opening that leads into the church "
    + "of Hobbiton. You see a few hobbits walking around whereas some of "
    + "them are just standing there talking to each other.\n");

   add_item(({"entrance","opening","small opening"}), 
      "The entrance leads to the inside of the Hobbiton church. "
    + "It looks only big enough for small people, like hobbits.\n");

   add_exit(STAND_DIR+"church","south","@@sblock");
   add_exit(STAND_DIR+"bw_road2","east");
   add_exit(STAND_PARENT+"forest/forest1","west",0);

   add_prop(ROOM_I_INSIDE, 0);  /* This an open air room */

   reset_room();
}

sblock() {
   object tp;

   tp = this_player();
   if (tp->query_wiz_level() > 0)
      return 0;

/* Humans and elves are too big to enter the church. Maybe a replacement
   should be made for them, so they too have a place to pray in.
 */
   if ((tp->query_race() == "human") || (tp->query_race() == "elf"))
   {
      write("You are too large to get through that small opening.\n");
      say(QCNAME(tp)+" tries in vain to enter the church.\n");
      return 1;
   }
  return 0;
}

reset_room() {
   if (!present("meriadoc",this_object()))
      clone_object(STAND_DIR + "merry")->move(this_object());
}