inherit "/d/Shire/std/room";

#include "defs.h"


void
create_shire_room()
{


   set_short("Mountain pass");
   set_long("@@long_desc");

   add_exit("/d/Shire/common/trollsh/mpath7","southwest",0);
   add_exit("/d/Rhovanion/common/shirelink", "northeast", 0);
}

string long_desc() {

  string str;

  str = "You are walking on a path that winds upwards in the northeast "+
        "further into a high pass in the Misty Mountains. The path leads "+
        "west down into the lowlands of Rhudaur.\n";
  return break_string(str,77);

}

