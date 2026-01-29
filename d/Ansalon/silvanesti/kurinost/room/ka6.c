#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/kurinost/local.h"
#include <ss_types.h>
#include <macros.h>
inherit KURINOST_OUT;

void
init()
{
    ::init();
    ADA("climb");
}

void
reset_kurinost_room()
{
    return;
}

create_kurinost_room()
{
    set_short("Kurinost-Alinost road");
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
    add_item("rock","A large rock lies in the path of the road and "+
         "forces the road to fork around it.  Climbing over it would "+
        "be possible, but it is simply easier to walk around.\n");

    add_exit(KROOM + "ka8","southwest",0);
    add_exit(KROOM + "ka5","southeast",0);

    reset_kurinost_room();
}

string
long_descr()
{
    return "You are travelling on the Kurinost-Alinost road.  It "+
        "hasn't been used much recently and you assume it is a "+
        "direct result of the appearance of the forest.  Something "+
        "sinister has turned this once beautiful forest into "+
        "a nightmarish woodland full of twisted and deformed "+
        "trees.  Even the underbrush is affected and unwelcoming.  "+
        "There is a large rock blocking the way south which the road "+
        "is forced to fork around.\n";
}

int climb(string str)
{
  if(str != "rock")
  {
    NF("Climb what?\n");
    return 0;
  }
  if((TP->query_skill(SS_CLIMB))<10)
  {
    say(QCTNAME(TP) + " tries to climb the rock but doesn't seem to be " +
       "able to find a proper foothold.\n");
    write("You try to climb the rock but aren't quite sure how to "+
       "attack it.\n");
    return 0;
  }
  write("Placing your foot in a nice foothold you spring yourself upon the "+
     "rock.\n");
  TP->move_living("up as he climbs the rock",KROOM+"rock.c");
  return 1;
}
