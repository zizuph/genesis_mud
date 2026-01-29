inherit "/d/Shire/eastroad/eroad";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include <macros.h>

#define EXIT1 ER_DIR + "er17","southwest",0,1
#define EXIT2 ER_DIR + "village/frog/er1","northeast",0,1
#define EXIT3 ER_DIR + "er18n","north",0,1
#define EXIT4 ER_DIR + "er18s","south",0,2
#define EXIT5 ER_DIR + "er17n","west",0,2
#define EXIT6 ER_DIR + "er20","east",0,2

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
   "proper lies north and south of Eastroad. The northern end of "+
   "Frogmorton borders The Water, a tributary of the Brandywine "+
   "river. While to the south, far from the village, the woods "+
   "and hills of Green Hill Country can be seen.";
   
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
   add_exit(EXIT3);
   add_exit(EXIT4);
   add_exit(EXIT5);
   add_exit(EXIT6);
   
   make_the_room();
}
