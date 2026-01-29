
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("Western passage");
  set_long("The ground levels out here. The main corridor "+
     "runs to the west and southeast. To the northeast a rough "+
     "cut tunnel branches off down a steep slope. A faint, "+
     "repetitious noise can be heard echoing off the stone "+
     "walls.\n");

  add_item(({ "ground", "floor" }),
     "It appears to be smooth and level at this point.\n");
  add_item(({ "corridor", "passage" }),
     "You estimate the walls to be over twenty feet apart at the "+
     "southern passage.\n");
  add_item(({ "tunnel", "rough cut tunnel" }),
     "It appears to have been hastily made with little "+
     "concern for asthetics. You need to get closer to "+
     "discern anything else.\n");
  add_item(({ "slope", "steep slope" }),
     "From here it appears to descend at a near 45 degree "+
     "angle.\n");
  add_item(({ "walls", "wall" }),
     "Hewn from the very mountain itself these walls have "+
     "a dull grey color.\n");
  add_exit("/d/Shire/khazad/west/wp3","west",0,1);
  add_exit("/d/Shire/khazad/west/wp5","southeast",0,1);
  add_exit("/d/Shire/khazad/west/tunnel1a","northeast",0,1);
}
