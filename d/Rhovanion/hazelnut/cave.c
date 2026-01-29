inherit "/std/room.c";
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"

void
create_room()
{
    set_short("A cave under the tree");
    set_long("You are in an extremely cramped and slippery tunnel underneath "
  + "the island. There are holes dug in the north and south directions.\n");

     add_exit("/d/Shire/common/island/n_tunnel","north",0,100);
     add_exit("/d/Shire/common/island/s_tunnel","south",0,100);

   add_item("walls","The walls are made of slippery mud.\n");
   add_prop(ROOM_I_LIGHT, -4);

}
