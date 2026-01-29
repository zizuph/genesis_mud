// 1998/09/04 Last update
// 2011/08/05 Lavellan - Removed bad duplicate hobbit spawn to void

#pragma save_binary
#pragma strict_types

#include "local.h"
#include H_MAKER

inherit EAST_ROAD;

#define MAX_CITIZENS 3
 
static object *hobbits = allocate(MAX_CITIZENS);

void
create_er_room()
{
   
   area = "not far"; /* Distance from areaname */
   areaname = "Greenholm";
   land = "Shire";
   areatype = 10;
   areadesc = "tiny hamlet";
   grass = "green";
   
   extraline = "The Bounds are just to the west of this tiny village "+
   "called Greenholm.  This hamlet is situated on the western edge "+
   "of the Far Downs, also known as the Fox Downs.  Few hobbit holes "+
   "are visible from this vantage point as most face east, toward the "+
   "main part of the Shire.  The Great East Road leads west, out of "+
   "the Shire or east, to the heart of the Shire.";

   add_item(({"hole","holes","hobbit holes"}),
   "The few hobbit holes that are on this side seem to consist mostly "+
   "of windows, barred against Outsiders.\n");

   add_item(({"window","windows","barred windows"}),
   "They are round in hobbit fashion, but barred to prevent entrance.\n");

   add_item(({"village","hamlet","greenholm","edge","western edge"}),
   "This village is located on the western part of the Far Downs. Greenholm "+
   "does not seem to be very big as there is little movement as you observe "+
   "it now.  Perhaps further along you might find some activity?\n");

   add_item(({"vantage point","point","part","shire"}),
   "You stand just inside The Bounds which separate the Shire from "+
   "the rest of Eriador.\n");

   add_item(({"bounds","the bounds"}),
   "The Bounds separate the Shire from the rest of Eriador and Arnor. "+
   "It has been the gift of Argeleb II of Arnor for many hundreds of years "+
   "now.  The Shire was founded by Marco and Blancho in the year 1 of the "+
   "Shire reckoning.\n");

    add_item(({"far downs","downs","fox downs"}), "The Far Downs stretch several "+
    "leagues from north to south, though they are very narrow from east to west, "+
    "perfect for a hobbit's hole.\n");

    reset_shire_room();

   add_exit(EAST_R_DIR + "er5","west");
   add_exit(EAST_R_DIR + "er7","east");
   add_exit(EAST_R_DIR + "er6n","north",0,2);
   add_exit(EAST_R_DIR + "er6s","south",0,2);
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
            hobbits[index]->set_monster_home(EAST_R_DIR + "er6");
            hobbits[index]->move(TO);
 
        }
    }
}
