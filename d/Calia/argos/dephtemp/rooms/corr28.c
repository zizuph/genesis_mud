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
#define  SCENE_NUM 7
 
create_room() {
   set_short("Corridor in the Temple of Dephonia");
   set_long(
      "You walk into the end of a narrow corridor in the temple where "+
      "there are entrances to chambers to the north, south and east. "+
      "The corridor leads west into another passage, where you can "+
      "see light falling in from a window. You notice a relief "+
      "which has been sculpted into the southern wall of the corridor.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item("window","It is further west.\n");
   add_item("corridor","It is a narrow passage which ends here and "+
                       "leads west.\n");
 
   add_item("relief","Sculpted into the wall to the south, "+
            "the relief portrays a scene of "+vq_scene[SCENE_NUM]+
            ". The relief is framed with a thick marble border.\n");
 
   add_item(({"frame","border"}), "It is a large rectangular frame "+
            "around the relief on the south wall. There are some "+
            "words written along the upper length.\n");
 
   add_item("words","They are written on the flat face of the "+
            "frame of the relief. Perhaps you can read them.\n");
 
   add_cmd_item("words","read",
                "They read: "+vq_prayer[SCENE_NUM]+ ".\n");
 
   add_exit(ROOM_DIR+"qrtpsn", "north", 0);
   add_exit(ROOM_DIR+"qrtpse", "east", 0);
   add_exit(ROOM_DIR+"qrtpss", "south", 0);
   add_exit(ROOM_DIR+"corr23", "west", 0);
}
