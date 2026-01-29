/*
**  ARGOS - Metro - Sculptor's shop - CLOSED FOR NOW
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       8/24/95    Created
**
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
object dagger; /* just something to attract an occassional visitor */
 
void reset_room() {
   if (present("dagger",THIS)) return;
   dagger=clone_object(WEAPON_DIR+"czdagger");
   dagger->move(THIS);
}
 
create_room() {
   set_short("A sculptor's studio");
   set_long(
      "Various unfinished statues and reliefs made of marble sit around "+
      "the floor of this studio, where artisans transform blocks of "+
      "marble into works of art. A large work table sits in the center "+
      "of the studio with a note on top of it.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item(({"building","shop","studio"}),
      "It is the studio where sculptors work to make the many pieces "+
      "of art found all around the city.\n");
   add_item(({"statues","statue","people","animals"}),
      "A collection of statues of people and animals, most unfinished "+
      "sit around the floor of the studio.\n");
   add_item(({"reliefs","relief","scene","scenes"}),
      "Reliefs are being sculpted on flat squares of marble, dipicting "+
      "various scenes, though you can't make out any in their "+
      "unfinished condition.\n");
   add_item("table",
      "It is a large sturdy table made of marble, strong enough to "+
      "support the huge blocks of marble placed on it. There is a "+
      "note laying on it.\n");
   add_item("note",
      "It is a short note written on a piece of paper. Perhaps you "+
      "can read it.\n");
   add_cmd_item("note","read",
      "It reads: The studio is closed until further notice.\n");
 
   add_exit(ROOM_DIR+"trroad9","east");
   reset_room();
}
