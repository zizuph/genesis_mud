/*
 * Farm2f.c   Tomas  -- Jan 2000
 *
 * Lucius - Feb 2021
 *    Cleaned and modernized.
 */
#include "farm.h"
inherit FARMRM;

public void
create_terel_room()
{
    INSIDE;
    set_short("farmhouse");
    set_long("The interior of the house is sparten at best. " +
      "Rustic furnishings fill what little space the house has " +
      "to offer. A fireplace provides heat and a convenient place " +
      "to cook ones meals. A small cast iron pot hangs from a rod " +
      "within the fireplace.\n");

    add_item(("furnishings"),"A small unmade pallet rests before " +
      "the far wall while a table and stool sits in the middle of the room.\n");

    add_item(("table"),"Dirty dishes and mug sits on the table.\n");

    add_item(({"dishes","mug"}),"The dishes and mug look largely uninteresting.\n");

    add_item(("stool"),"A small rickey stool rests before the table.\n");

    add_item(({"fireplace"}),
      "The fireplace looks like it is used to heat the room of the house. " +
      "A small pot hangs from a metal rod within the fireplace.\n");

    add_item(({"metal rod","rod","pot"}),
      "A small pot used for cooking hangs within the fireplace by a metal " +
      "rod. It looks well used. You decide it isn't worth getting dirty " +
      "by exploring the pot further.\n");

    add_cmd_item(({"stool"}),({"sit","sit on"}), "You decide not to chance " +
      "breaking the stool by sitting on it.\n");

    add_cmd_item(({"pallet"}),({"sleep","sleep in","sit on","sit"}),
      "You decide that the pallet is far to smelly for you to get a good " +
      "nights rest in.\n");

    room_add_object(CFARMS + "obj/farm2f_door1");
}
