#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;
#define MAX_RABBITS 1
#define RABBIT "/d/Gondor/common/npc/rabbit"

static object *rabbit = allocate(MAX_RABBITS);
 
void
create_er_room()
{
   area = "not far from";
   areaname = "the Great East Road";
   land = "Eriador";
   areatype = 7;
   areadesc = "small clearing";
   treetype = "willow";
   
   extraline = "The forest is very dense and very hard to "+
     "find your way in. South of here is too thick for you to "+
       "penetrate.";
   
   add_item(({"surroundings","forest"}),
	    "Trees and bushes are all over the place. They make it "+
	    "hard to navigate through the forest. Most of the trees "+
	    "are willows.\n");
   
   add_item(({"bushes","bush"}),
	    "Bushes are clumped all over the place. Nothing about "+
	    "them is out of the ordinary.\n");
   
   reset_shire_room();
   room_add_object("/d/Shire/eastroad/western/under_leaves");
   set_noshow_obvious(1);
   add_exit(EAST_R_DIR + "er28","north",0,2);
   add_exit(EAST_R_DIR + "er27s","west",0,2);   
   add_exit(EAST_R_DIR + "er29s","east",0,2);

}

void reset_shire_room()
{
    int index;

    setuid();
    seteuid(getuid());

    for(index = 0; index < MAX_RABBITS; index++)
    {
        if (!objectp(rabbit[index]))
        {
            rabbit[index] = clone_object(RABBIT);
            rabbit[index]->set_random_move(3);
            rabbit[index]->move(TO);
        }
    }
}
