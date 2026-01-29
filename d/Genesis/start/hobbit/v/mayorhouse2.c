/*
 *  This is the house of the mayor of Hobbiton
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

create_room() 
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("Inside the Mayors reception room");
   set_long("This is the Mayors reception room. The Mayor likes to sit here "
    + "in his chair, counting his valuables, brushing his hair, or "
    + "helping out citizens. That is, if he is not gone fishing in the "
    + "Bywater river. To the south is the reception hall of the "
    + "house.\n");

   add_exit(STAND_DIR+"mayorhouse", "south", 0);

   add_item("chair", "The chair looks old, but comfortable.\n");

   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

   if (!present("mayor"))
      clone_object(STAND_DIR + "mayor")->move(this_object());
}

reset_room() {
   if (!find_living("_hobbiton_mayor_"))
      clone_object(STAND_DIR + "mayor")->move(this_object());
}