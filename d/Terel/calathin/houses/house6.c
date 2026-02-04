/*  This is a house.  Coded by Vader on 7/22/92 for the town of Calathin.

    This basic house will be standard for all in the northeast region
    of town (see ~common/town/town_map_draft3)

    modified by Tomas for new Calathin code, 11/19/1999
*/

inherit "/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Terel/include/Terel.h"

/*  THIS HOUSE IS TO REMAIN EMPTY!!! PLEASE DO NOT ADD NPC's TO THIS ROOM */

create_room()
{
  set_short("A house");
  set_long(break_string("There is blood everywhere.  It looks like " +
   "a slaughter house.  You know that nothing human could have done " +
   "this.  The smell from the kitchen to the north is terrible.  You " +
   "wonder how long whatever is in there has been dead.  " +
   "The ceiling is made of wood, and is riddled with leaks.  " +
   "There is no furniture within, only piles of straw and hay used as " +
   "beds.  These beds, however, are scattered throughout the room.  " +
   "There are also blood stains on the walls. The kitchen is to the north.\n", 70));

  add_item(({"floor"}), "It is filthy.  Insects abound here.\n");

  add_item(({"ceiling"}), "It is made of wood, and leaks water in " +
   "several places.\n");

  add_item(({"beds", "bed", "hay", "straw"}), "Several piles of hay and " +
   "straw were used for beds, but are now scattered.\n");

  add_item(({"kitchen"}), "There is a terrible smell coming from it.\n");

  add_item(({"walls", "blood", "blood stains"}), "Some poor soul's life " +
   "blood was splattered across this house by\nsomething inhuman..\n");

  add_exit(CALATHIN_DIR + "paths/path_n04", "south", 0);
  add_exit(CALATHIN_DIR + "houses/house6_ktchn", "north", 0);

}
 
