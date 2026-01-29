/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_OUTSIDE;

object human1, human2, human3;

create_tantallon_room()
{
    set_short("South outpost of Tantallon");
    set_long("This is the south outpost of Tantallon. You sense something " +
         "evil in the air. There is a small tent east from here. " +
         /* "South is a bridge crossing a river. " + */
         "North goes a small road into the heart of Tantallon.\n");

    add_item(({"city", "village", "tantallon"}), BS(
    "There is not much to see from here, why not enter it and get a " +
        "closer look.", SL));
    /*add_item("bridge",
        "It's an old fashioned stone bridge, it looks quite safe.\n");
    add_item("river", BS(
        "The river runs from east to west. The only way to cross it is " +
        "walking that bridge.", SL));*/
    add_item("tent", BS(
        "It's a small grey tent. You hear some sounds from it. You can't " +
        "enter it from this side.", SL));
    add_item("road",
        "It leads off north. It's made out of small stones.\n");
    add_item(({"stone","stones"}), BS(
        "The stones are small and round but they stick to the ground so you " +
        "can't pick them up.", SL));

    add_exit(TDIR + "city22", "north", 0);
    /*add_exit(TDIR + "bridges", "south", 0);*/
    add_exit("/d/Krynn/tant/room/road16", "southwest");
    add_exit(TDIR + "city25", "east", 0);

    reset_room();
}

reset_tantallon_room()
{
    if (!human1)
      set_alarm(1.0,0.0,"load_first");
    if (!human2)
      set_alarm(10.0,0.0,"load_second");
    if (!human3)
      set_alarm(12.0,0.0,"load_third");

}

load_first()
{
    human1 = clone_object(MON + "ne_hum_g");
    human1->move_living("xxx", TO);
}

load_second()
{
    human2 = clone_object(MON + "ne_hum_g");
    human2->move_living("xxx", TO);
}

load_third()
{
    int i;

    human3 = clone_object(MON + "ne_hum_g");

    human3->add_adj("huge");
    human3->set_short("huge evil human guard");

    human3->move_living("xxx", TO);

    for (i = 0; i < 6; i++)
        human3->set_base_stat(i, 55 + random(10));
}

void
init()
{
    object ob;
    if (ob = present("tour2", TP))
      ob->set_arr("dragon");
    ::init();
}

