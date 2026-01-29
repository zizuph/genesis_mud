#pragma save_binary

inherit "/d/Gondor/common/room";
#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

create_room()
{
  set_short("A dark stairway landing");
  set_long("You are standing by the foot of a long stairway leading up\n"+
    "into darkness. The dark and narrow passage now continues west, where\n"+
    "you think you hear the faint sound of rushing water.\n");
  add_item("passage","The passage is dark and narrow, with walls rough and uneven. It runs\n"+
    "west into darkness, and up a great many steps also leading to darkness.\n");
  add_item(({"steps","stairway"}),BS("The stairway consists of a great many "+
    "steps leading up into darkness. The steps are neatly carved out of the "+
    "rock, and are seemingly timeless.\n"));
  add_item("water","You see only a little water dripping from the roof, but you\n"+
    "hear a faint sound of rushing water in the distance.\n");
  add_item(({"roof","walls","floor"}),BS("The passage is tunneled through "+
    "the very rock of the hill, and the walls, roof and floor are rough "+
    "and uneven, with water dripping from the roof, gathering in pools.\n"));
  add_exit(RANGER_ITH_DIR+"passage1","west",0);
  add_exit(RANGER_ITH_DIR+"passage3","up",0);
  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_LIGHT,0);
}