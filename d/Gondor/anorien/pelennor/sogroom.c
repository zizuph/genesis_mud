inherit "/d/Gondor/minas/lib/ogroom";
#include "/d/Gondor/defs.h"
#include "sgatedefs.h"

create_room()
{
  set_wfile(WFILE);
  ::create_room();
  set_long(BSN("This is a guardroom where soldiers of the Harlond Fort "+
    "rest when they are off duty. There are chairs and tables here, and "+
    "racks where they place their weapons. An open doorway leads east."));
  add_exit(INGATE,"east",0,0);
}
