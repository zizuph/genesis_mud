inherit "/d/Gondor/minas/lib/igroom";
#include "/d/Gondor/defs.h"
#include "ngatedefs.h"

create_room()
{
  set_wfile(WFILE);
  ::create_room();
  set_long(BSN("This is the guardroom where the soldiers of the "+
    "Anorien Fort rest when they are off-duty. There are chairs and "+
    "tables here, and racks where they put their weapons. An open "+
    "doorway leads out to the gatehouse east."));
  add_exit(INGATE,"east",0,0);
}
