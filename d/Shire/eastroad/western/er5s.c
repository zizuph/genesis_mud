#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

int rockmax = 2 + random(4); /* 2-5 rocks here */

void
create_er_room()
{
   area = "just south of";
   areaname = "Greenholm";
   land = "Eriador";
   areatype = 10;
   areadesc = "meadow";
   grass = "green";

   extraline = "The flat green meadows of Eriador stretch "+
   "before your eyes in all directions.  The Bounds of the Shire "+
   "lie to the east; western Eriador and Mithlond are west.";

   add_item(({"meadow","meadows","flat green meadows"}),
   "The green meadows are rich in vegetation and herb-life.\n");

   add_item(({"bounds","bounds of the Shire"}),
   "The Bounds of the Shire are to the east, given "+
   "to the hobbits of the Shire by King Argeleb II of "+
   "Arnor, when the Dunedain still ruled the North.\n");

   add_item(({"eriador","mithlond"}),
   "Eriador surrounds the Shire, which is technically a part of "+
   "it, just as Eriador is a part of Arnor, the former north Kingdom "+
   "of Middle Earth.  Mithlond, where Cirdan keeps his fleet, is "+
   "also part of Eriador, and also known as Grey Havens.\n");

   set_noshow_obvious(1);
   add_exit(EAST_R_DIR + "er5","north");
   add_exit(EAST_R_DIR + "er6s","east");
   add_exit(EAST_R_DIR + "er4s","west");

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
