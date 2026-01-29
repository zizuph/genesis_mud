
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("Mining tunnel");
  set_long("A narrow mining tunnel runs to the northwest and to "+
     "the south down a shallow incline. Rough walls and a low ceiling "+
     "characterize the mining tunnels which stand in stark contrast "+
     "to most places here in Khazad-dum.\n");

  add_item(({ "walls", "wall" }),
     "Unfortunately these jagged, uneven walls show no signs of "+
     "anything worth mining.\n");
  add_item(({ "ceiling", "roof" }),
     "Jagged like the walls this ceiling is low enough for a tall "+
     "human to hurt himself on in some places.\n");
  add_item(({ "incline", "slope" }),
     "A shallow, rocky slope rising to the north and "+
     "descending in the south.\n");
  add_exit("/d/Shire/khazad/west/tunnel2a","south",0,1);
  add_exit("/d/Shire/khazad/west/tunnel2c","northwest",0,1);
}

public void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if (file_name(from) == "/d/Shire/khazad/west/tunnel2a")
  write("The tunnel narrows at this point.\n");
}
