inherit "/d/Gondor/minas/lib/ogroom";
#include "/d/Gondor/defs.h"
#include "ngatedefs.h"

create_room()
{
  set_wfile(WFILE);
  ::create_room();
  set_long(BSN("This is a guardroom where soldiers of the Anorien Fort "+
    "rest when they are off duty. There are chairs and tables here, and "+
    "racks where they place their weapons. An open doorway leads west."));
  add_exit(INGATE,"west",0,0);
}
