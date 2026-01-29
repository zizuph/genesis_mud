inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"

create_room()
{
  set_short("The Entrance Hall of the White Tower");
  set_long("You are in a paved passage in the great halls of the White Tower.\n"+
    "The stone hall is cold and empty, your footsteps echoing from the shadows.\n"+
    "An arched doorway of stone leads south into the Library of Minas Tirith.\n"+
    "To the east are the great doors leading out of the White Tower.\n");
  add_prop(ROOM_I_INSIDE,1);
  add_exit("/d/Gondor/minas/citadel/entryhall2","west",0,0);
  clone_object("/d/Gondor/minas/obj/entry_door_in")->move(this_object());
  add_exit("/d/Gondor/minas/citadel/mtlibrary","south",0,0);
}

