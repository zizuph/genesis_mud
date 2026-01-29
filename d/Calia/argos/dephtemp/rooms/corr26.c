/*
**  Temple of Dephonia, Second Level Corridor
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       1/10/95    Created
**
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "vqscenes.h"
#define  SCENE_NUM 13
 
create_room() {
   set_short("Corridor in the Temple of Dephonia");
   set_long(
      "You walk into the end of a narrow corridor in the temple where "+
      "there are entrances to chambers to the north, south and west. "+
      "The corridor leads east into another passage, where you can "+
      "see light falling in from a window. You notice a relief "+
      "which has been sculpted into the southern wall of the corridor.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item("window","It is further east.\n");
   add_item("corridor","It is a narrow passage which ends here and "+
                       "leads east.\n");
 
   add_item("relief","Sculpted into the wall on the south, "+
            "the relief portrays a scene of "+vq_scene[SCENE_NUM]+
            ". The relief is framed with a thick marble border.\n");
 
   add_item(({"frame","border"}), "It is a large rectangular frame "+
            "around the relief on the south wall. There are some "+
            "words written along the upper length.\n");
 
   add_item("words","They are written on the flat face of the "+
            "frame of the relief. Perhaps you can read them.\n");
 
   add_cmd_item("words","read",
                "They read: " + vq_prayer[SCENE_NUM]+ ".\n");
 
   add_exit(ROOM_DIR+"qrtprn",  "north", 0);
   add_exit(ROOM_DIR+"qrtprw",  "west", 0);
   add_exit(ROOM_DIR+"qrtprs",  "south", 0);
   add_exit(ROOM_DIR+"corr25",  "east", 0);
}
