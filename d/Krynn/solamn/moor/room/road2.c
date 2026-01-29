/* created by Aridor 09/14/93 
*  Modified by Mirandus to add connecting road 08/26/2015*/

#include "../local.h"

#define GULLY "/d/Krynn/solamn/pal_gully/rooms/"
inherit ROOM_BASE

object farm;

void
reset_moor_room()
{
    if (farm)
      return;
    farm = clone_object(LIV + "farmer");
    farm->move(TO);
}

void
create_moor_room()
{

    set_short("A bend in the road");
    set_long(BS("The road continues west uphill along a ridge "
         +   "and southeast down into Palanthas. You can see "
         +   "the city spreading out to the east and beyond that the "
         +   "Vingaard Mountains towering above in the east and south. "
         +   "Fields accompany the road on both sides.",SL));

    add_exit(GULLY + "sp5","north",0,1);
    add_exit(ROOM + "road1","southeast",0,1);
    add_exit(ROOM + "road3","west",0,3);

    reset_room();
}



