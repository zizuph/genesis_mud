/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_OUTSIDE;

object human1, human2, human3, giant;


load_human1()
{
    int i;

    human1 = clone_object(MON + "ne_hum_g");
    human1->move_living("xxx", TO);
    human1->set_random_move(random(100));
}

load_human2()
{
    int i;

    human2 = clone_object(MON + "ne_hum_g");
    human2->move_living("xxx", TO);
    human2->set_random_move(random(100));
}

load_human3()
{
    int i;

    human3 = clone_object(MON + "ne_hum_g");
    human3->move_living("xxx", TO);
    human3->set_random_move(random(100));
}

reset_tantallon_room()
{
    if(!objectp(giant))
        {
         giant = clone_object(MON + "ne_gia_g");
         giant->set_color("red");
         giant->arm_me();  
         giant->move(TO);
    }

    if (!human1)
      set_alarm(2.0,0.0,"load_human1");
    if (!human2)
      set_alarm(7.0,0.0,"load_human2");
    if (!human3)
      set_alarm(13.0,0.0,"load_human3");
}

create_tantallon_room()
{
    set_short("On east Bridge");
    set_long(BS(
        "You are standing on a stone bridge. West you see a small city. " +
        "Under the bridge you hear water running. Walking east will take " +
    "you to a rather big plain.", SL));

    add_item("city", BS(
        "From here you get a good view at the city, and you directly decide " +
        "to stop calling this place for a city. It looks much more like a " +
        "village. The first thing that strikes you is that there are no " +
    "houses. Instead there are several tents. There is also a dark evil " +
    "glow about the small village. Who knows what awaits there.", SL));
    add_item("bridge",
        "It's an old fashioned stone bridge, it looks quite safe.\n");
    add_item(({"river", "water"}), BS(
        "You lean over the bridge to get a look of it. You can see some fish " +
    "swimming around.", SL));
    add_item("fish",
        "The fish moves quickly in the water.\n");
    add_item("plain",
        "It sure is vast.\n");

    add_exit(TDIR + "city10", "west", 0);
    add_exit(TDIR + "prebe", "east", 0);

    reset_tantallon_room();
}


