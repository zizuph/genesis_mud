/*  Dargaard Highway between VK and Kalaman
  
    road21.c - June 1998 by Kentari
*/

#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit SOLAMN_OUT;

#include "/d/Krynn/common/herbsearch.h"

#define H1 KRHERB + "breadroot"
#define H2 KRHERB + "chicory"
#define H3 KRHERB + "dandelion"
#define H4 KRHERB + "horsetail"

void
reset_solamn_room()
{
   return;
}

create_solamn_room()
{
   set_short("On the Dargaard Highway between the mountain pass and Kalaman");
   set_long("@@long_descr");
   
   add_item(({"grass","grasses","grassy weeds","weeds","lining"}),
      "Many wild varieties of weeds and grasses grow at the side of " +
      "the trail.\n");
   add_item(({"highway","old road","road"}),
      "Beaten and worn, this road has seen use dating back hundreds " +
      "of years as the main road through the mountains.\n");   

   seteuid(getuid(TO));
   set_search_places(({"grass","weeds","grasses","herbs"}));
   add_prop(OBJ_I_SEARCH_TIME,3);
   add_prop(OBJ_S_SEARCH_FUN,"herb_search");
   add_herb_file(H1);
   add_herb_file(H2);
   add_herb_file(H3);
   add_herb_file(H4);
   
   add_exit(SROOM + "road22","southwest",0);
   add_exit(SROOM + "road20","north",0);
   
   reset_solamn_room();
}

string
long_descr()
{
   return tod_descr2() + " You are on an old road with grassy weeds " +
   "lining the path. To your north the road continues " +
   "towards Kalaman, and to the southwest it curves towards " +
   "Dargaard Pass into Solamnia.\n";
}
