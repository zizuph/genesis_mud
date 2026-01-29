inherit "/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"


create_room() {
  set_short("a small cottage");
  set_long(BS("The cottage seems to be well kept. However nobody seems to "
	      + "be at home. The small door is closed.\n"));

  add_item(({"door","small door"}),BS("The door seems to be locked, or maybe "
				      + "magicaly held.\n"));

  add_prop(ROOM_I_INSIDE,0);

  add_exit(STAND_DIR + "er4", "south",0);

}

init()
{
    ::init();
    add_action("do_knock","knock");
}

int
do_knock(string str)
{

   if(str != "on door")
   SAY("You knock on the "+str+" but nothing happens.\n");
   return 0;

   write("You knock on the door, and walk right in.\n");
    TP->move_living("M","/d/Shire/common/hobbiton/in_house",1);
     return 1;


}
