#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

#define BOMB_DIR "/d/Shire/bombadil/npc/"
static object pheasant;

void
create_er_room()
{
   
    area = "far away to"; /* Distance from areaname */
    areaname = "Hardbottle";
    land = "the Shire";
    areatype = 8;
    areadesc = "undulating plain";
    grass = "lush and green";
   
    extraline =  "This road leads south from the Great East Road, "
    +"en route to the hamlet of Hardbottle in the "
    +"South Farthing. To the west are fields of wheat, while "
    +"to the east of the road is a grassy hill.";
   
    add_item("hill",
        "This grassy hill rises gently from the surrounding plains.\n");
   
    add_item(({"fields","wheat"}),
        "These fields are kept by the hobbits of Michel Delving, "
        +"a village to the west of here. They supply food and "
        +"grain for the surrounding area.\n");
   
    add_item(({"plains","grass","grassy plains"}),
        "Most of the Shire is made up of sweeping plains, with "
        +"lush green grass rippling in the ever present breeze.\n");
   
    add_item("hardbottle",
        "Far to the south of here, the hamlet of Hardbottle is barely "
        +"visible at this distance. From what you can see, it looks like  "
        +"a rustic little hamlet surrounded by fields.\n");
   
    add_item(({"white downs","downs"}),
        "The White Downs extend from the northwest to the "
        +"southwest in a line.  The Great East Road cuts through "
        +"the middle of them, on its way to Mithlond.\n");
    reset_shire_room();

    add_exit(EAST_R_DIR + "er10","north",0,2);
    add_exit(EAST_R_DIR + "er11s","east",0,2,1);
    add_exit(EAST_R_DIR + "er9s","west",0,2,1);
}

void
reset_shire_room()
{
    setuid();
    seteuid(getuid());

    if(!objectp(pheasant))
    {
        pheasant = clone_object(BOMB_DIR + "pheasant");
        pheasant->set_restrain_path("/d/Shire/eastroad/western");
        pheasant->set_random_move(2);
        pheasant->move(TO);
    }
}

