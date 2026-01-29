/*
 * Hill lane 
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>
#include <wa_types.h>

create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("On the Hill lane, north of the crossroad");
   set_long("You are standing on the Hill lane north of the crossroad. "
    + "West of you is a beautiful garden, where you can relax. "
    + "To the north is a wooden bridge leading over "
    + "the river Bywater. South is a crossroad in the middle of "
    + "Hobbiton.\n");

   add_exit(STAND_DIR + "bridge","north");
   add_exit(STAND_DIR + "cr_road","south");
   add_exit(STAND_DIR + "garden","west");

   add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */
   place_knife();
}

reset_room() {
   place_knife();
}

place_knife() {
   object knife;

   if (!present("knife")) {
      knife = clone_object(STAND_DIR + "knife");
      knife->move(this_object());
   }
}