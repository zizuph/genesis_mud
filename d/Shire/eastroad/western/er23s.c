#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

#define MAX_RABBITS 2
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
       "penetrate. West is of you is the Brandywine river.";
   
   add_item(({"river","bradywine river","brandywine"}),
	    "West of you is the Brandywine river. Looking north from "+
	    "the rivers side you can see the Brandywine Bridge.\n");
   
   add_item(({"bridge","brandywine bridge"}),
	    "The bridge is to your northwest. It looks strong and "+
	    "sturdy. Which is good for a bridge which gets a lot of "+
	    "use.\n");
   
   add_item(({"surroundings","forest"}),
	    "Trees and bushes are all over the place. They make it "+
	    "difficult to navigate through the forest. Most of the "+
	    "trees are willows.\n");
   
   add_item(({"bushes","bush"}),
	    "The bushes are in clumps all over this small clearing.\n");
   reset_shire_room();
   
   set_noshow_obvious(1);
   add_exit(EAST_R_DIR + "er23","north",0,2);
   add_exit(EAST_R_DIR + "er24s","east",0,2);
   
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
