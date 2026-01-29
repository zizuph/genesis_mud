inherit "/d/Shire/eastroad/eroad";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include <macros.h>

#define EXIT1 ER_DIR + "er18","southwest",0,1
#define EXIT2 ER_DIR + "er20","east",0,1

void
create_room()
{
   area = "passing through";
   areaname = "Frogmorton";
   land = "the Shire";
   areatype = 10;
   areadesc = "village";
   grass = "green";
   
   extraline = "Frogmorton is the halfway point between the village "+
   "of Bywater, to the west and Buckland, to the east. The village "+
   "proper lies north of Eastroad. The northern end of "+
   "Frogmorton borders The Water, a tributary of the Brandywine "+
   "river. While to the south, far from the village, the woods "+
   "and hills of Green Hill Country can be seen, however, "+
   "there seems to be no way of reaching them from here. "+
   "Because of recent flooding, Frogmorton is closed as busy "+
   "hobbits spend most of their time cleaning up and rebuilding "+
   "this once beautiful village.";
   
   add_item ("Frogmorton", "This small Hobbit Village spreads out "+
      "mostly to the north, on a narrow plain between Eastroad "+
      "and The Water.\n");
   
   add_item(({"bywater"}),"The village of Bywater is just off to the "+
      "west, past the Three Farthing Stone. Set on the junction "+
      "of the East Road and the road to Hobbiton, Bywater still "+
      "maintains the appearance of a peaceful Hobbit village.\n");
   
   add_item(({"water","the water","river"}),"At this distance "+
      "The Water only appears as a thin, narrow river, running "+
      "across the gentle rolling hills of the Shire.\n");
   
   
   
   add_exit(EXIT1);
   add_exit(EXIT2);
   
   make_the_room();
}
