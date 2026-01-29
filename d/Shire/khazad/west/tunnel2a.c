
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("Mining tunnel");
  set_long("A narrow mining tunnel runs to the north and to "+
     "the south down a shallow slope. Rough walls and a low ceiling "+
     "characterize the mining tunnels which stand in stark contrast "+
     "to most places here in Khazad-dum.\n");

  add_item(({ "walls", "wall" }),
     "The smooth, uneven walls show no signs of "+
     "anything worth mining.\n");
  add_item(({ "ceiling", "roof" }),
     "Jagged like the walls this ceiling is low enough for a tall "+
     "human to hurt himself on in some places.\n");
  add_item("slope",
     "A shallow, rocky slope that rises to the north and "+
     "descends in the south.\n");
  add_exit("/d/Shire/khazad/west/wp10","south",0,1);
  add_exit("/d/Shire/khazad/west/tunnel2b","north",0,1);
}
