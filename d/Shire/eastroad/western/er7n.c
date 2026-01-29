#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void add_stuff();

void
create_er_room()
{
   area = "near";
   areaname = "Greenholm";
   land = "the Shire";
   areatype = 1;
   areadesc = "meadow";
   grass = "green";

   extraline = "This meadow, just outside the center of the village "+
   "Greenholm has a few small hills with hobbit holes dug out of them. "+
   "A slight path leads north towards an opening in the trees.  "+
   "West is Greenholm proper, and south will take you back to the East Road.";

   add_item(({"center","hills","hill","village","greenholm"}),
   "The center of the village Greenholm is somewhat to the west, "+
   "but there are some hobbit holes built into the low hills here.\n");

   add_item(({"hobbit hole","hobbit holes","burrows","smials"}),
   "The hobbit holes here seem closed tight, no way to enter them.\n");

   set_noshow_obvious(1);
   add_exit(EAST_R_DIR + "er7","south");
   add_exit(EAST_R_DIR + "er6n","west");
   add_exit(VILLAGE_DIR + "greenholm/viln1","north");

   add_stuff();
}


void
reset_shire_room()
{
   add_stuff();
}


void
add_stuff()
{
   object line;

    if(!present("string"))
   {
   line = clone_object(ER_OBJ + "string");
   line->move(TO);
   }

}
