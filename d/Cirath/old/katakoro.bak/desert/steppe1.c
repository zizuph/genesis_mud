inherit "/std/room.c";
#include "/d/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#define PATH "/d/Cirath/katakoro/"

create_room()
{
  set_short("Northern Wastelands");
   set_long("Vast emptiness seems to stretch out forever.  Scattered "+
	"about the northern steppes are many hills, but even those "+
	"blur in the distance, minor changes in a seemingly "+
	"unchanging wasteland.\n");

  set_noshow_obvious(1);
  
   add_exit(KAT_DIR+"desert/steppe2","southeast");
   add_exit(KAT_DIR+"encampment/camp23","north");

}
