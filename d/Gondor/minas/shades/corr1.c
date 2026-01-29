inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

create_room()
{
  set_short("A gloomy corridor");
  set_long("This gloomy passageway has dusty grey-white stone walls lining\n"+
    "it, running east and west. In both ends of the corridor you see open\n"+
    "doorways, and larger rooms beyond. A single torch lights the corridor.\n");
  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_LIGHT,1);
  add_item("walls","The walls are made of grey-white stone.\n");
  add_item("torch","One single torch is fastened to the wall, giving a gloomy light\n"+
    "to the corridor.\n");
  add_exit(SHADES_DIR+"corr2","west",0);
  add_exit(SHADES_DIR+"shadeentr","east",0);
}

