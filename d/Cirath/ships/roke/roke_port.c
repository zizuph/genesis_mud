 /* /d/Cirath/ships/roke/roke_port.c
  * The roke end of the Tyr-Roke shipline.
  * Decius, December 1996.
  */

#pragma strict_types
#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "ship.h"
#include "defs.h"



void
create_room()
{
  set_short("End of the Road.\n"+
    "There is one obvious exit: south.\n"+
    "A large wooden sign");
  set_long("This is the end of the trail. "+
    "Far to the south is a grove of trees. "+
    "Above loom massive mountains, which spread "+
    "their shadow over you. There is a distinct "+
    "chill in the air.\n"+
    "There is one obvious exit: south.\n"+
    "A large wooden sign.\n");

  add_item("sign","It is a large sign attached to "+
    "a tall wooden post.\n");


  add_item(({"mountain","mountains","cliff"}),
    "The huge cliffs tower above you.\n"+
    "You feel very very small...\n");

  add_item(({"road","track","trail"}),
    "The road is little more than a dirt track with the "+
    "only exit south.\n");

  add_item(({"orchard","tree","trees"}),
    "You can no longer see the orchard to the south.\n");

  OUTSIDE;
  add_exit("/d/Roke/varl/atuan/r14","south",0,1,1);

  add_cmd_item("sign","read",
  "****************************************************\n"+
  "*                                                  *\n"+
  "*  Here may be found transportation to the mighty  *\n"+
  "*  city of Tyr, courtesy of His Majesty, Kalak.    *\n"+
  "*                                                  *\n"+
  "****************************************************\n");
}
