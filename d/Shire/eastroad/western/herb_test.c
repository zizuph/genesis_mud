#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void
create_er_room()
{
    area = "not far from";
    areaname = "the Great East Road";
    land = "the Shire";
    areatype = 7;
    areadesc = "small clearing";
    treetype = "willow";

    extraline = "The forest is very dense and very hard to "+
    "find your way in. South of here is too thick for you to "+
    "penetrate. You cannot penetrate the forest to the east "+
    "either.";

    add_item(({"surroundings","forest"}),
      "Trees and bushes are all over the place. They make it "+
      "hard to navigate through the forest. Most of the trees "+
      "are willows.\n");

    add_item(({"bushes","bush"}),
      "What kind of forest would this be without bushes?\n");

    set_noshow_obvious(1);
    add_exit(EAST_R_DIR + "er29","north",0,2);
    add_exit(EAST_R_DIR + "er28s","west",0,2);   
    add_std_herbs("forest", file_size(file_name(TO)));
}
