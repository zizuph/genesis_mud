/*
**  MCLUB - Memorial Shrine, North West garden
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
   set_short("Rose garden of a shrine");
   set_long(
      "The pleasant smell of roses drifts in the breeze here in this "+
      "garden made in the corner of the stone shrine. Roses climb "+
      "trellises which form the northern and western walls of this "+
      "enclave, the outer stone walls of the shrine on the south and "+
      "east. A small font rests in the center of the garden, a statue "+
      "placed in its center. A stone bench sits beneath the blooming "+
      "roses on the east side. Two entrances lead into the shrine to "+
      "the south and east.\n");
 
   add_item("roses",
      "They climb the high trelisses on the north and west sides of "+
      "the garden, their red blooms perfuming the enclave.\n");
   add_item(({"garden","enclave"}),
      "The garden is set in a corner of the shrine, a place for "+
      "relaxation and meditation.\n");
   add_item(({"trellis","trellises"}),
      "The trellises are made of long interwoven strips of wood, "+
      "barely visible behind the growth of the roses.\n");
   add_item(({"shrine","walls"}),
      "The stone walls of the shrine form the southern and eastern "+
      "boundaries of the garden. New growths of ivy begin to climb "+
      "them.\n");
   add_item("ivy",
      "Small vines with lush green leaves which have begun to grow "+
      "along the walls. Left unabated, they will soon cover the "+
      "smooth stones of the shrine.\n");
   add_item("font",
      "It is a flat bowl-shaped font on a pedestal made of stone. A "+
      "small statue stands in the center, while rain water has collected "+
      "in its basin.\n");
   add_item("basin","The basin of the font is filled with rain water.\n");
   add_item(({"water","rain water"}),"It fills the basin of the font.\n");
   add_item("statue","It is a small statue of a fawn standing on one foot.\n");
   add_item("bench","It is a long stone bench. It doesn't look very "+
                    "comfortable, but it withstands the wind and rain of "+
                    "the outdoors.\n");
   add_item(({"entrance","entrances"}),
      "Two simple entrances lead back into the shrine, one to the east "+
      "and the other to the south.\n");
 
   add_exit(ROOM_DIR+"shvestw","south", 0);
   add_exit(ROOM_DIR+"shvestn","east",0);
}
