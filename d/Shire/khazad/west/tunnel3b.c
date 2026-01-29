
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("Windy tunnel");
  set_long("A wide tunnel with a low ceiling. The ceiling, walls "+
     "and floor in here are very smooth. A strong wind continually "+
     "surges through here from the south. The tunnel continues north "+
     "and south. Another small passage runs off to the west.\n");

  add_item(({"walls", "ceiling", "floor", "ground", "tunnel" }),
     "Very smooth to the touch. Probably caused by the strong wind "+
     "blowing through here over the course of time.\n");
  add_exit("/d/Shire/khazad/west/tunnel3a","north",0,1);
  add_exit("/d/Shire/khazad/west/tunnel3c","south",0,1);
  add_exit("/d/Shire/khazad/west/random_tunnel2","west",0,1);
}

public void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if (!living(ob))
    return;
  if (file_name(from) == "/d/Shire/khazad/west/tunnel3a")
  {
    write("A strong wind buffets your body as you attempt to go "+
       "south.\n");
  }

  else if (file_name(from) == "/d/Shire/khazad/west/tunnel3c")
  {
    write("You are forcefully hurried through the tunnel by the "+
    "powerful wind at your back.\n");
  }
}
