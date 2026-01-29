#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

/* Put something here like Mithlond defs or Bree defs that describe that area. */

void
create_er_room()
{

    area = "a good distance from"; /* Distance from areaname */
    areaname = "Mithlond";
    land = "Eriador";
    areatype = 8;
    areadesc = "harbour-area";
    grass = "green";

    extraline = "To the west are the piers of Mithlond, while to the east lies "+
    "the great unknown.  The fields of the Shire stretch out as you look east, "+
    "while to the west and south rise the Ered Luin, or Blue Mountains. Looking "+
    "up, the Tower Hills begin to really tower above. A road "+
    "leads south towards the Blue Mountains, and north is a green field.";

    add_item(({"ered luin","blue mountains","mountains","mountain"}),
      "At this distance it is difficult to distinguish one peak from all the rest, but "+
      "you can see them hovering above the plains to the south, even above what "+
      "must be the Tower Hills.\n");

    add_item(({"tower hills","hills","fields","field","towers","tower","white towers"}),
      "The tower hills stretch out to the south above the fields, the towers built on them "+
      "spiraling up into the sky. The towers are very old, you guess, but the hills they "+
      "are built atop are even older.\n");

    add_item(({"piers","mithlond","pier","wall","city","walls","city walls","lighthouse"}),
      "The piers of Mithlond are hidden behind the walls that enclose the city.  The "+
      "Lighthouse of Mithlond climbs high into the sky, nearly as high as the White "+
      "Towers.  Many a sailor has been saved by the brilliant lighthouse at Mithlond.\n"); 
    add_exit(EAST_R_DIR + "er1","west");
    add_exit(EAST_R_DIR + "er3","east");
    add_exit(EAST_R_DIR + "er2n","north",0,2,1);
    add_exit(EAST_R_DIR + "er2s","south",0,2,1);
}
