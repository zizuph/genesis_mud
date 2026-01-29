#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

int rockmax = 2 + random(4); /* 2-5 rocks here */

void
create_er_room()
{
   area = "a little distance from"; /* Distance from areaname */
   areaname = "Michel Delving";
   land = "the Shire";
   areatype = 4;
   areadesc = "field of wheat";
   grass = "green";
   
   extraline = "The long rows of golden wheat move like waves in the "
   +"wind that blows from the west.  The field is carefully kept by "
   +"the hobbit farmers who export the wheat to Hobbiton.  Here "
   +"and there amongst the furrows are stacks of cut wheat, "
   +"ready to be taken to market.";
   
   add_item(({"golden wheat","rows","wheat","furrows"}),
      "The rows of wheat are lovingly tended by hobbit farmers, "
      +"who spend much of their time chasing off animals.\n");
   
   add_item(({"cut wheat","stacks","haystacks"}),
      "These stacks of wheat are left to dry, at which stage "
      +"they can be taken to the mill in Hobbiton or used as "
      +"fodder for horses.\n");
   
   add_item(({"surroundings","expanse","fields","shire"}),
      "The fields stretch out to the north, south, and east. "
      +"In the middle of the fields to the north runs the Great East Road, "
      +"a brown strip against the expanse of gold and green.\n");
   
   set_noshow_obvious(1);
   add_exit(EAST_R_DIR + "er9","north");
   add_exit(EAST_R_DIR + "er10s","east");
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

