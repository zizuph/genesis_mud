#include "/d/Gondor/defs.h"

inherit LIB_DIR + "field";

#include <macros.h>
#include <stdproperties.h>

void    add_stuff();

void
create_room()
{
    area = "southern";
    areaname = "Lebennin";
    land = "Gondor";
    areatype = 0;
    areadesc = "pier on the bank of the Anduin";
    grass = "long";

    add_exit(LEB_DIR + "sroad/sr2", "north", 0, 2);

    extraline = "The run-down pier is reaching into the Anduin. "
      + "Perhaps it is used by fishermen who do not want to use "
      + "the great harbour in Pelargir.";

    add_item(({"pier", "dock"}), BSN(
        "This pier reachs out into the river Anduin. It is in a rather "
      + "poor condition but it looks like a ship docked here not too "
      + "long ago."));
    add_item(({"river", "anduin", "river anduin", }), BSN(
        "The river is very broad here, it must be several miles to the "
      + "other bank which. Not far to the southwest are the Mouths "
      + "of the Anduin, the many smaller branches into which the "
      + "river divides before reaching the Bay of Belfalas."));
    remove_item("road");
    add_item(({"road", }), BSN(
        "The road north of here is coming from Pelargir to the "
      + "northwest and continues southwest along the bank of the Anduin."));

    make_the_room();
    add_stuff();
}

void
add_stuff()
{
   object  sign;

   FIX_EUID
   if (!present("sign", TO))
   {
      sign = clone_object(SHIP_DIR + "poros_sign");
      sign->set_file(SHIP_DIR + "poros_lebennin.txt");
      sign->move(TO);
   }
}

