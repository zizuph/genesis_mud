/*
**  Sheep Pasture Fold
**
**  This room is part of the Vision of Delphia quest in the DEPTEMP
**  area of Argos. Part of the quest requires the player to find the
**  lamb which is in this fold and kill it. The lamb can only be attacked
**  when the player is properly equipped. The corpse of the lamb is
**  actually just an object so that it does not decay.
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       1/10/95    Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "defs.h"
 
object lamb=0;
 
void
reset_room()
{
    if (lamb) return;
    lamb=clone_object(DEPHTEMP_DIR+"monsters/vqlamb");
    lamb->move(THIS);
    tell_room(THIS, QCTNAME(lamb)+" rises from slumber.\n");
}
 
create_room() {
   set_short("Inside a sheep fold");
   set_long(
      "You squat down beneath the low roof of this crude sheep "+
      "fold, which is actually just a small hut built from sticks. "+
      "There is loose wool laying everywhere, but thankfully the "+
      "sheep do not relieve themselves in here. There is a "+
      "small hole to the south which leads out.\n");
 
   add_item("fold","It is a low, mound-shaped structure made of sticks.\n");
   add_item("wool","Loose wool from the sheep who sleep here is laying "+
                   "all around.\n");
   add_item("hole","It leads outside.\n");
 
   add_prop(ROOM_I_INSIDE,1);
   add_exit(ROOM_DIR+"past7","out",0);
   reset_room();
}
