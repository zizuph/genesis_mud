/* highpass */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include "/sys/stdproperties.h"

create_room()
{
    add_prop(ROOM_I_INSIDE, 0);
    set_short("path");
    set_long("You are on a nice grassy path. To the west it goes straight " +
             "towards dark Misty Mountains. To the east it goes towards " + 
             "dark Mirkwood forest. Either direction you choose, nothing " + 
             "good awaits you there.\n");


              /* The other room,           direction, VBFC, fatigue */
    add_exit(MISTY_DIR+"p16", "west",    0,    1);
    add_exit(MIRK_DIR+"mirk-2-10", "east", "@@block");
}

int 
block(){
  if (TP->query_wiz_level())
  {
    write("This part of Rhovanion isn't open for mortals but "+
          "you are welcome to have a look.\n");
    return 0;
  }
  write("This way to rest the of Rhovanion is still closed. "+
        "We hope to open it soon.\n");
  return 1;
}
