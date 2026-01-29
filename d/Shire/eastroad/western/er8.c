// 1998/09/04 Last update
// 2011/08/05 Lavellan - Removed bad duplicate hobbit spawn to void, typo

#pragma save_binary
#pragma strict_types

#include "local.h"
#include H_MAKER
 
inherit EAST_ROAD;
 
#define MAX_CITIZENS 5
 
static object *hobbits = allocate(MAX_CITIZENS);

void
create_er_room()
{
   
   area = "not far"; /* Distance from areaname */
   areaname = "Michel Delving";
   land = "the Shire";
   areatype = 10;
   areadesc = "village";
   grass = "green";
   
   extraline = "The village lies on either side of the "+
//   "East Road. The Mayor's residence and the Mathom house "+
   "East Road. The Mayor's residence and the Mathom House "+
   "are to the south, while the inn and many of the farmhouses are "+
   "to the north. Most of the houses are the traditional hobbit "+
   "design, holes dug into the earth. From what you can see of "+
   "the village, it is a happy and cheerful place, as befits a hobbit "+
   "dwelling.";

    clone_object("/d/Genesis/obj/donation/column")->move(this_object(), 1);
   
   add_item(({"mayor","residence"}),"The Mayor's residence "+
      "is a large house that lies to the south, where the Mayor "+
      "governs the Shire from.\n");
   
   add_item(({"mathom house","mathom"}),
//      "The Mathom house is the home of many wonderful treasures, "+
      "The Mathom House is the home of many wonderful treasures, "+
//      "brought back from afar. It is rumoured that wonderful swords"+
      "brought back from afar. It is rumoured that wonderful swords "+
      "lie in this hobbit museum.\n");
   
   add_item(({"house","hole","home"}),
      "These typical hobbit holes, or smials, as they are called by"+
      "hobbits, are comfortable holes dug into the ground, with "+
      "windows and doors providing light and fresh air. All of "+
      "the doors in sight seem fastened shut.\n");
   
   add_item("inn",
      "The inn is a fine place to rest after a long journey along the "+
      "East Road. It is normally full of hobbits, and is well stocked "+
      "with ales and wines.\n");
   
   add_item(({"farm","farms","farmhouses"}),
      "The farmhouses of Michel Delving supply the wheat and grain "+
      "for the village, as well as making ales and wines for the inn. "+
      "They are large, prosperous looking farms, adding to the general "+
      "air of contentment in the village.\n");

    reset_shire_room();


   add_exit(EAST_R_DIR + "er7","west");
   add_exit(EAST_R_DIR + "er9","east");
   add_exit(MD_DIR + "gamroad4","north",0,2);
   add_exit(MD_DIR + "gamroad3","south",0,2);
}

void
reset_shire_room()
{
 
    int index;
 
    /* Do this first, since we may need to clone. */
    setuid();
    seteuid(getuid());
 
    /* Loop over all elements in the array. */
    for(index = 0; index < MAX_CITIZENS; index++)
    {
        if (!objectp(hobbits[index]))
        {
//            hobbits[index] = clone_object(HOBBITMAKER);
            hobbits[index] = clone_object(HOBBITMAKER);
            hobbits[index]->set_type(CITIZEN);
            hobbits[index]->set_power(100);
            hobbits[index]->set_restrain_path(({"/d/Shire/eastroad/western", 
                "/d/Shire/eastroad/village/whit",
                "/d/Shire/common/hobbiton",
                "/d/Shire/michel" }));
            hobbits[index]->set_random_move(3);
            hobbits[index]->set_monster_home(EAST_R_DIR + "er8");
            hobbits[index]->move(TO);
 
        }
    }
}
