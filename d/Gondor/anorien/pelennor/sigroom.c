inherit "/d/Gondor/minas/lib/igroom";
#include "/d/Gondor/defs.h"
#include "sgatedefs.h"

create_room()
{
  set_wfile(WFILE);
  ::create_room();
  set_long(BSN("This is the guardroom where the soldiers of the "+
    "Harlond Fort rest when they are off-duty. There are chairs and "+
    "tables here, and racks where they put their weapons. An open "+
    "doorway leads out to the gatehouse west."));
  add_exit(INGATE,"west",0,0);
}
