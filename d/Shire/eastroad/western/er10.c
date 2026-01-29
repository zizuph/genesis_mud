#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void
create_er_room()
{
   area = "some distance from"; /* Distance from areaname */
   areaname = "Michel Delving";
   land = "the Shire";
   areatype = 8;
   areadesc = "undulating plain";
   grass = "lush and green";
   
   extraline =  "The Great East Road winds and bounds here"
   +" through small hills echoing the Green Hill Country farther east in the "
   +"South Farthing. To the west lies the village of Michel "
   +"Delving, the unofficial capital of the Shire, while the "
   +"road continues far to the east, past Hobbiton to Bree. "
   +"To the west you can see the White Downs, while the "
   +"Took Hills can be seen in the distance to the southeast.";
   
   add_item(({"village","michel delving"}),
      "Situated near the White Downs, Michel Delving is the "
      +"largest village in the Shire, and is the home of a museum "
      +"and also a fine pub.\n");
   
   add_item("hobbiton",
      "The former capital of the Shire lies along the Great "
      +"East Road far to the east. Hobbiton is one of the "
      +"largest villages in the Shire.\n");
   
   add_item("bree",
      "Situated far to the east of here, Bree is a strange "
      +"place, where hobbits live with humans. There is a "
      +"famous inn there, the Prancing Pony.\n");
   
   add_item("hardbottle",
      "Far to the south of here, Hardbottle is only a smudge "
      +"on the horizon.  It looks like a peaceful and small "
      +"hamlet, like many others in the Shire.\n");
   
   add_item(({"white downs","downs"}),
      "The White Downs extend from the northwest to the "
      +"southwest in a line. The Great East Road cuts through "
      +"the middle of them, on its way to Mithlond.\n");
   
   add_item(({"took hills","hills"}),
      "The hills of Tookland lie to the east and southeast of here, "
      +"home to the family of hobbits known as Tooks.\n");

   add_exit(EAST_R_DIR + "er9","west");
   add_exit(EAST_R_DIR + "er11","east");
   add_exit(EAST_R_DIR + "er10n","north",0,2,1);
   add_exit(EAST_R_DIR + "er10s","south",0,2);
   
}
