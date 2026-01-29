#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void
create_er_room()
{
   
   area = "not far from"; /* Distance from areaname */
   areaname = "Michel Delving";
   land = "the Shire";
   areatype = 8;
   areadesc = "number of cultivated fields";
   grass = "freshly cut";
   
   extraline =  "You can see the village of Michel Delving a few miles to "
   +"the west, with the fields of the village surrounding the "
   +"road here.  The West Farthing of the Shire, that you are "
   +"walking through now, is a quiet and peaceful place.  "
   +"Far along the road to the east, you can make out the "
    +"hamlet of Waymeet, while closer to you a field "
   +"lies south.";
   
   add_item(({"village","michel delving"}),
      "The village of Michel Delving, not far away from here, "
      +"is the home of the Mayor of the Shire, and also the "
      +"famous Mathom house, where many treasures are kept.  "
      +"Michel Delving is the largest village in the Shire.\n");
   
   add_item("hardbottle",
      "Hardbottle is a hamlet in the South Farthing of the Shire.  "
      +"Situated well off the main road of the Shire, it is a quiet "
      +"and peaceful place.\n");
   
   add_item(({"field","fields"}),
      "These fields supply the wheat and grain for the village, "
      +"although you can also make out little patches of vegetable "
      +"and herb gardens amongst them.\n");
   
   add_item(({"hamlet","waymeet"}),
      "Off in the distance, you can make out Waymeet's inn "
      +"and the houses and hobbit holes of the hamlet.  It looks "
      +"like it would be a good place to rest for a while on your "
      +"journey through the Shire.\n");

   add_exit(EAST_R_DIR + "er8","west");
   add_exit(EAST_R_DIR + "er10","east");
   add_exit(EAST_R_DIR + "er9n","north",0,2,1);
   add_exit(EAST_R_DIR + "er9s","south",0,2,1);
   
}
