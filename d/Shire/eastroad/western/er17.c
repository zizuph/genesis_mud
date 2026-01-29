#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void
create_er_room()
{
   area = "not far from";
   areaname = "Frogmorton";
   land = "the Shire";
   areatype = 8;
   areadesc = "rolling plain";
   grass = "green";
   
   extraline = "You are standing on the East Road, somewhere between "+
   "Frogmorton and Bywater in the East Farthing. A thin creek runs below "+
   "the old wooden bridge here; winding its way across the plains to "+
   "meld with 'The Water' which is just visible to the north. 'The Water' "+
   "is a tributary of the great river Baranduin, and it is one of the "+
   "most notable features of the Shire, hosting many of the small Hobbit "+
   "villages.";
   add_item(({"frogmorton"}),"   The small Hobbit village of Frogmorton lies "+
   "about eight miles east of here. The village seems to be no "+
   "more than a smudge on the horizon where the East Road and The "+
   "Water seem to brush togeather.\n");
   add_item(({"bywater"}),"The Hobbit village of Bywater is just off to the "+
      "west, past the Three Farthing Stone. Set on the junction of the East Road "+
      "and the road to Hobbiton, Bywater still maintains the appearance of a "+
      "peaceful Hobbit village.\n");
   
   add_item(({"water","the water","baranduin","river"}),"At this distance, "+
      "'The Water' only appears as a thin, narrow river, running across the "+
      "gentle hills of the Shire.\n");
   
   add_item(({"creek"}),"This small creek seems to wind its way into "+
	    "the heart of the Shire, joining 'The Water' just over the "+
	    "fields to the north.\n");
   add_item(({"bridge"}),"You seem to be standing on an old wooden bridge "+
	    "which passes over a tiny creek running off to the north.\n");
   
   add_exit(EAST_R_DIR + "er16","northwest",0,2);
   add_exit(EAST_R_DIR + "er18","northeast",0,2);
   add_exit(EAST_R_DIR + "er16s","west",0,2,1);
   add_exit(EAST_R_DIR + "er17n","north",0,2,1);

}
