
inherit "/d/Shire/khazad/moria_room_drip";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("Mining tunnel");
  set_long("You stand before a bend in the winding tunnel. Rough "+
     "walls show signs of mining activity. Loose chunks of rock "+
     "litter the uneven ground. The tunnel runs slighty uphill to "+
     "the southeast and descends gradually around a bend to the "+
     "northeast.\n");

  add_item(({ "rock", "rocks"}),
     "They range from tiny pebbles to large fist sized chunks.\n");
  add_item(({ "walls", "wall" }),
     "Unfortunately these jagged, uneven walls show no signs of "+
     "anything worth mining.\n");
  add_item(({ "ceiling", "roof" }),
     "Jagged like the walls this ceiling is low enough for a tall "+
     "human to hurt himself on in some places.\n");
  add_exit("/d/Shire/khazad/west/tunnel1c","southeast",0,1);
  add_exit("/d/Shire/khazad/west/random_tunnel1","northeast",0,1);
}
