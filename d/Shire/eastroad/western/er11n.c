#pragma save_binary
#pragma strict_types

#include "local.h"
//#define RABBIT "/d/Gondor/common/npc/rabbit"

inherit EAST_ROAD;

#define MAX_RABBITS 1
#define RABBIT "/d/Gondor/common/npc/rabbit"

static object *rabbit = allocate(MAX_RABBITS);

//void reset_shire_room();

void create_er_room()
{

    area = "some distance from"; /* Distance from areaname */
    areaname = "Waymeet";
    land = "the Shire";
    areatype = 1;
    areadesc = "rolling plain";
    grass = "long";

    extraline = "To the north, you can see a road running from the village "
    +"of Waymeet to the east to the hamlets of Nobottle and Hardneedle "
    +"to the northwest. Apart from this road, and the Great East Road "
    +"to the south, you can see little but the ever present grassy plains.";

    add_item(({"village","waymeet"}),
      "Situated on a cross-road near here to the east, Waymeet "
      +"is a popular stopping place for travellers along the Great "
      +"East Road.\n");

    add_item(({"hamlet","hamlets","nobottle","hardneedle"}),
      "Far to the north of here, the hamlets are not visible from here.\n");

    add_item(({"surroundings","expanse","plain","shire"}),
      "The Shire is an expanse of plains, with the occasional village "
      +"or cultivated field, where the hobbits till the rich soil of the "
      +"Shire.\n");

    set_noshow_obvious(1);

    reset_shire_room();

    add_exit(EAST_R_DIR + "er11","south",0,2);
    add_exit(EAST_R_DIR + "er10n","west",0,2);
    add_exit(EAST_R_DIR + "er12", "southeast", 0, 2);
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
