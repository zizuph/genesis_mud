#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/kurinost/local.h"
#include <ss_types.h>
#include <macros.h>
inherit KURINOST_OUT;

void
init()
{
  ADA("climb");
  ADA("enter");
}

void
reset_kurinost_room()
{
    return;
}

create_kurinost_room()
{
    set_short("On a rock in the Kurinost road");
    set_long("@@long_descr");

    add_item(({"forest","tree","trees"}), "The trees here look "+
        "gnarled and ugly.  You are not sure why the forest "+
        "suddenly changes from gorgeous to grotesque, but you "+
        "are very certain that it is not natural.\n");
    add_item("road","Little more than a dirt path through the "+
        "forest, the road connects the Silvanesti towns of "+
        "Alinost to the southwest, and Kurinost to the "+
        "northeast.\n");
    add_item(({"underbrush","brush"}), "The underbrush seems to "+
        "have changed from bushes to brambles, making travel off "+
        "of the path dangerous, if not impossible.\n");
    add_item("rock","You are on the rock that lies in the path of the " +
        "road.  You notice a wedge in the rock that you might be able " +
        "to fit through, but it is very dark and you can't tell if anything "+
        "is inside.\n");

    reset_kurinost_room();
}

string
long_descr()
{
    return "You stand upon a large rock that blocks the Kurinost - "+
        "Alinost road.  The rock appears to be made of granite and " +
        "because of its size, you understand why the elves chose to " +
        "build the road around it rather than moving the rock.  From " +
        "this height you feel you would have had a beautiful view of " +
        "the forest if it wasn't so disfigured.\n";
}

int climb(string str)
{
  if (str == "east")
  {
    write("You climb down east, and make it back to the road safely.\n");
    TP->move_living("descends the rock to the east.",KROOM+"ka5.c");
    return 1;
  }
  if (str == "west")
  {
    write("You climb down west, and make it back to the road safely.\n");
    TP->move_living("descends the rock to the west.",KROOM+"ka8.c");
    return 1;
  }
  if (str == "north")
  {
    write("You climb down north, and make it back to the road safely.\n");
    TP->move_living("descends the rock to the north.",KROOM+"ka6.c");
    return 1;
  }
  if (str == "south")
  {
    write("You climb down south, and make it back to the road safely.\n");
    TP->move_living("descends the rock to the south.",KROOM+"ka7.c");
    return 1;
  }
  NF("Climb down in which direction?\n");
  return 0;
}

int enter(string str)
{
  if ((str != "wedge") && (str != "rock"))
  {
     NF("Enter what?\n");
     return 0;
  }
  write("You manage to squeeze yourself through the entrance.\n");
  TP->move_living("slips into the rock.", "/d/Ansalon/silvanesti/shadow/room/entrance.c");
  return 1;
}
