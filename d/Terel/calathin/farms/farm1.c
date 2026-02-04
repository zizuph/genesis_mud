/*
 * farm1.c
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
    set_long("You stand on the edge of a split-railed fence separating " +
      "the outskirts of Calathin from a small farm. A barn and small house " +
      "can be seen in the middle of the farm separated by a frozen snow covered " +
      "field.\n");

    add_item(({"split-railed","fence"}),
      "The fence completely surrounds the farm except for the gate " +
      "before you. It looks sturdy enough to hold even the largest of " +
      "livestock from leaving the farm.\n");

    add_item(("field"),"The field looks as if it could be used to harvest " +
      "crops. Right now its a field of snow.\n");

    add_item(("barn"),"The two story red barn stands to the side of the small " +
      "house. A hayloft door can be seen at the top level of the barn.\n");

    add_item(("house"),"A Typical single level range type house.\n");

    add_item(("livestock"),"You dont see any, Yet..\n");

    add_exit(CALATHIN_DIR + "paths/path_n06","northwest",0,1);

    room_add_object(CFARMS + "obj/farm1_gate");
}
