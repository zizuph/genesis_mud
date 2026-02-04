/*
 * farm1b.c
 *
 * Calathin external house.
 * 11/21/1999 -- Tomas
 *
 * Lucius - Feb 2021
 *    Cleaned and modernized.
 */
#include "farm.h"
inherit FARMRM;

public void
create_terel_room()
{
    set_short("farmhouse");
    set_long("Before you stands a small farmhouse. The windows are shuttered " +
      "tight to keep the adverse weather out. A covered porch wraps completely " +
      "around the farmhouse providing a clear walkway to the " +
      "door. A covered well sits in the middle of the frost covered yard. " +
      "to the south is the barn.\n");

    add_item(("barn"),"is to the south. The two story red barn stands to " +
      "the side of the small " +
      "house. A hayloft door can be seen at the top level of the barn.\n");

    add_item(({"dirt road","road"}),
      "The dirt road leads from the fenceline to the farmhouse.\n");

    add_item(({"covered well","well"}),
      "Brick and mortar well, used to collect water from the ground.\n");

    add_item(("field"),"The field looks like it is used to harvest " +
      "crops in the summertime. Its covered in snow at the moment.\n");

    add_item(({"farmhouse","house"}),"A typical single level range type house.\n");

    add_item(("livestock"),"You dont see any, Yet..\n");

    add_exit(CFARMS + "farm1a","northwest",0,1);
    add_exit(CFARMS + "farm1c","south",0,1);

    room_add_object(CFARMS + "obj/farm1_door");

    add_field_herbs();
    add_pebbles();
}
