inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
  set_short("in the torch room");
  set_long(BSN("You are in the torch room of the lighthouse. "+
      "From this room you can hear the crash of the waves on the "+
      "rocks below as well as the creak of the wood as the wind "+
      "constantly buffets the tower. There is an amazingly "+
      "brightly burning torch on a pedestal in the middle of the "+
      "room, surrounded by mirrors which somehow magnify its "+
      "brilliance all the more. When you turn away from the light "+
      "you can see tiny dots up and down the river which could only "+
      "be travelling ships."));
   add_prop(ROOM_I_INSIDE,1);
   add_item(({"mirror","mirrors"}),BSN("These mirrors are "+
       "positioned in such a way as to reflect and magnify "+
       "the torchlight. It is difficult to look too close though, "+
       "as the light becomes so bright it is nearly blinding."));
   add_item(({"dots","ships","tiny dots"}),BSN("After staring "+
      "at a few of the specks for a while you are just sure "+
      "that they actually move... ")+"Yep, they must be ships.\n");
   add_item("torch",BSN("This torch is covered in some kind of "+
      "strange oil.  That must be why it burns so bright."));
   add_exit(PELAR_DIR + "docks/light2","down",0);
}
