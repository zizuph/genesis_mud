/*
**  Temple of Dephonia, Dining Hall, south end
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
#define  SCENE_NUM 3
 
create_room() {
   set_short("Banquet Hall of the Temple of Dephonia");
   set_long(
      "A very long polished antique table dominates this chamber and "+
      "extends into the next chamber to the north, surrounded by "+
      "dozens of chairs. This must be the banquet hall of the temple, "+
      "a place where many can gather to commune around a meal. A large "+
      "mural is painted on the eastern wall. The hall continues to "+
      "the north while there is an entrance to the corridor to the "+
      "west.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item("table","It is a very long table which extends into the "+
            "hall to the north, made of polished mohagany, it looks "+
            "very old but thick and sturdy.\n");
   add_item("chairs","Made of the same polished wood as the table, "+
            "the chairs are lined up around the table in perfect "+
            "perspective.\n");
   add_item("mural","Covering the entire wall, the mural is painted "+
            "with somber, pleasing color and portrays a scene of "+
            vq_scene[SCENE_NUM]+". A long narrow plaque hangs on "+
            "it just beneath the ceiling.\n");
   add_item("plaque","It is a long wooden plaque with words carved "+
            "into it. Perhaps you can read them.\n");
   add_item("words","They are carved into the plaque on the wall. "+
                    "perhaps you can read them.\n");
   add_cmd_item(({"plaque","words"}), "read","The plaque reads: "+
                vq_prayer[SCENE_NUM]+".\n");
 
   add_exit(ROOM_DIR+"corr21", "west", 0);
   add_exit(ROOM_DIR+"dine1",  "north", 0);
}
