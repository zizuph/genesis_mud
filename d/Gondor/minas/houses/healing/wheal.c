inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"

create_room()
{
  set_short("A bedroom in the Houses of Healing");
  set_long("This is a small bedroom, with two bunks by the north and south walls.\n"+
    "A doorway leads back east to the main hall.\n");
  add_prop(ROOM_I_NO_ATTACK,1);
  add_prop(ROOM_I_INSIDE,1);
  add_item("bunks","The bunks are empty right now, no healing patient is occupying them.\n");
  add_exit("/d/Gondor/minas/houses/healing","east",0,0);
}
