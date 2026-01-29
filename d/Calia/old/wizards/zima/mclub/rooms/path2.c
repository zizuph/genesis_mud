/*
**  MCLUB - Memorial Shrine, Path to shrine/hill
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       4/7/95    Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
create_room() {
    set_short("In a tranquil forest");
   set_long(
      "The forest crowds around you on all sides, the bark "+
      "of the surrounding trees twisting in grotesque figures. A path "+
      "seems to start here and lead off to the east through the trees. "+
      "The thick canopy above allows only spots of sunshine to hit the "+
      "ground. A mysterious silence seems to pervade the forest here.\n");
   add_item("path",
      "The shaded path leads east through the trees.\n");
   add_item(({"woods","forest","trees"}),
      "Large trees crowd around the edges of the path, a thick forest "+
      "which of various types of trees, their canopy of branches and "+
      "leaves shading the forest's floor.\n");
   add_item(({"bark","figures"}), "The weathered bark of the old trees "+
            "is black and twisted, like worn and frayed ropes frozen "+
            "in wood.\n");
 
   add_exit(ROOM_DIR+"path1","southwest",0);
   add_exit(ROOM_DIR+"path3","east",0);
}
