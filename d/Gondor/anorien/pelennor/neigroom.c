#include "negatedefs.h"
inherit "/d/Gondor/minas/lib/igroom";
#include "/d/Gondor/defs.h"

create_room()
{
  set_wfile(WFILE);
  ::create_room();
  set_long(BSN("This is the guardroom where the soldiers of the "+
    "Causeway Fort rest when they are off-duty. There are chairs and "+
    "tables here, and racks where they put their weapons. An open "+
    "doorway leads out to the gatehouse south."));
  add_exit(INGATE,"south",0,0);
}
