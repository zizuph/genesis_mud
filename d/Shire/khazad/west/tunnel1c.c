
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("Mining tunnel");
  set_long("You stand within a winding tunnel that gradually "+
     "decends. Rough walls show signs of mining activity. Loose chunks "+
     "of rock litter the uneven ground. The tunnel runs off to the "+
     "northwest and southeast.\n");
 
  add_item(({ "rock", "rocks"}),
     "They range from tiny pebbles to large fist sized chunks.\n");
  add_item(({ "walls", "wall" }),
     "Unfortunately these jagged, uneven walls show no signs of "+
     "anything worth mining.\n");
  add_item(({ "ceiling", "roof" }),
     "Jagged like the walls this ceiling is low enough for a tall "+
     "human to hurt himself on in some places.\n");
  add_exit("/d/Shire/khazad/west/tunnel1d","northwest",0,1);
  add_exit("/d/Shire/khazad/west/tunnel1b","southeast",0,1);
}
