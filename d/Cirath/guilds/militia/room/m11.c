inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/defs.h"


void
create_room()
 {
  set_short("Hallway");
  set_long("This is a narrow hallway that runs around the northwestern "
  	+"corner of this tower.  A window overlooks the street below, "
  	+"giving a view of the Warrior's School of Tyr across the "
  	+"street.  In the courtyard below, you can see other militia "
  	+"members practicing the skills they have trained.  The hall "
  	+"turns south here towards the barracks, and heads west to "
  	+"the central staircase of the guild.\n");
  add_item("window","It looks out over the street and courtyard below.\n");
  add_exit(MILITIA_ROOM + "startroom","south");
    add_exit(MILITIA_ROOM + "m10","east");
}

