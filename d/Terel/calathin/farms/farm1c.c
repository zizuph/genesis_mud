/*
 * farm1c.c
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
    set_short("farm");
    set_long("You stand before a large two story red barn. The farmhouse " +
      "is to your north. A buckboard style wagon rests to the side of the " +
      "barn.\n");

    add_item(("wagon"),"The flat bedded wagon sits to the side of the barn.\n");

    add_item(("barn"),"The two story red barn stands to the side of the small " +
      "house. A hayloft door can be seen at the top level of the barn.\n");

    add_item(({"dirt road","road"}),
      "The dirt road leads from the fenceline to the farmhouse.\n");

    add_item(("field"),"The field looks like it is used to harvest " +
      "crops in the summertime. Its covered in snow at the moment.\n");

    add_item(("house"),"A typical single level range type house.\n");

    add_item(("livestock"),"You dont see any, Yet..\n");

    add_exit(CFARMS + "farm1b","north",0,1);

    room_add_object(CFARMS + "obj/farm1_barn_door");
}
