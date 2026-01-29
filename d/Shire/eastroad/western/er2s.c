#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

int rockmax = 2 + random(4); /* 2-5 rocks here */

void
create_er_room()
{
   area = "not far from";
   areaname = "Grey Havens";
   land = "Eriador";
   areatype = 1;
   areadesc = "field";
   grass = "green";

   extraline = "Above you tower the Tower Hills, upon which stand "+
   "the three White Towers. The sides of the hills are covered "+
   "in green and only a few bushes dot them. To the east "+
   "and west are more fields; north is the East Road, and "+
   "south a path leads towards the Ered Luin.";
   
   add_item(({"white towers","towers","tower"}),
   "These towers are the White Towers built by the elves of "+
   "Mithlond. They were made to look over the sea to the Forbidden "+
   "Land, Tol Eressea.\n");

   add_item(({"surroundings","expanse","fields","shire"}),
   "They stretch out in all directions north, south, east and west. "+
   "In the middle, to your south, runs the East Road, a brown strip "+
   "in the middle of all this green.\n");

   add_item(({"hills","hill","bushes","bush"}),
   "The hills themselves, while steep, look very rich and full of life.\n");

   set_noshow_obvious(1);
   add_exit(GREY_H_DIR + "dwarf2","south");
   add_exit(EAST_R_DIR + "er2","north");
   add_exit(EAST_R_DIR + "er1s","west");
   add_exit(EAST_R_DIR + "er3s","east");
   reset_shire_room();
}

void
reset_shire_room()
{
    object rock = present("rock");
    
    if (!objectp(rock) || rock->num_heap() < rockmax)
    {
        clone_object(ROCK_DIR + "rock")->move(TO);
    }
}

