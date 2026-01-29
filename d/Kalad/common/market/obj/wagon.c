#include "/d/Kalad/defs.h"
inherit "/std/object";

void create_object()
{

    set_name("wagon");
    set_adj("rickity");
    add_prop(OBJ_I_WEIGHT, 250000);
    add_prop(OBJ_I_VOLUME, 400000);
    add_prop(OBJ_I_VALUE, 432);
    add_prop(OBJ_I_NO_GET, 1);

    set_long(BS("An old, rickity wagon is stuck in the mud. "+
      "From the amount of rust and decay, it appears to have "+
      "been stuck here for quite some time.  You can see at "+
      "least one more shop beyond the wagon.\n"));
}


void init()
{

    ::init();
    add_action("board","mount");
    add_action("board","board");
    add_action("board","climb");
    add_action("board","enter");
    add_action("board","go");
    add_action("crawl","crawl");
}


int board(string str)
{

    if ((str != "wagon") && (str != "on wagon") &&
        (str != "over wagon")) {
    write("What do you want to do that to?\n");
      return 0;
    }

    TP->move_living("by entering the wagon.",MRKT_PATH(onWagon));
    return 1;
}


int crawl(string str)
{

    if ((str != "wagon") && (str != "under wagon")) {
        write("What do you want to crawl under?\n");
      return 0;
    }

  TP->move_living("by going beneath the wagon.",MRKT_PATH(underWagon));
    return 1;
}
