/*
 *  The kitchen of the farm
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("Kitchen");
   set_long(
      "You are inside the kitchen of the farm. It smells like sweet apple "
    + "pies here. The smell is coming from the stove that is standing "
    + "against the north wall, beside the kitchen sink. "
    + "To the south is the living room of the farm.\n");

   add_item(({"sink","kitchen sink"}),
      "The kitchen sink has been cleaned regularly, so it shines like a "
    + "mirror.\n");

   add_exit(STAND_DIR + "farm2","south");

   add_prop(ROOM_I_INSIDE, 1);  /* This is an indoor room */

   if(!present("stove"))
      clone_object(STAND_DIR + "stove")->move(this_object());
   reset_room();
}

reset_room()
{
   if (!present("parsley"))
      clone_object("/d/Shire/common/herbs/parsley")->move(this_object());
}