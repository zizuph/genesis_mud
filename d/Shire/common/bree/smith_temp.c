inherit "/d/Shire/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

create_room()
{
  set_short("A vacated blacksmith's shop");
  set_long("It looks like the former tenant of this shop has just "+
     "moved out. Most of the items previously here have been packed "+
     "away and moved to a new location. You notice a sign sitting on "+
     "a cold forge near the back of the room. Some construction "+
     "seems to be going on to the west. Dwarves are working hard "+
     "renovating the room and adding more rooms to the existing "+
     "buildling.\n");

  add_item("dwarves", "They seem to be working hard so stay out of their "+
           "way!\n");
  add_item("forge", "It's cold and apparently unused for days.\n");
  add_item("shop", "It's undergoing a major renovation for its new "+
           "tenants.\n");
  add_item("sign", "Perhaps you should read it?\n");
  add_cmd_item("sign","read", "Open for business.\n"+
			"Please excuse the renovation work.\n"+
			"It should be done fairly soon.\n");
  add_exit("/d/Shire/common/bree/ncross","east",0,1);
  add_exit("/d/Shire/smiths/rooms/entrance","west",0,1);
  add_prop(ROOM_I_INSIDE, 1);
}
