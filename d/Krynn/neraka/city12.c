/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_OUTSIDE;

object goblin, human, baaz1, kapak;

create_tantallon_room()
{
    set_short("Center of Tantallon");
    set_long(BS(
        "You are in the middle of Tantallon. You stand in the northeast corner " +
        "of an opening. A lot of people are running around in what appears " +
    "to be circles. The evil in the air is rather strong now. One tent " +
    "is east from you. A small road goes off north.", SL));

    add_item(({"tent", "east tent"}), BS(
        "It's a grey tent and it's very high. High enough for a giant to " +
        "enter it. The tent smells of beer. There is a small window on the " +
    "tent.", SL));
    add_item("window", BS(
        "The window is an open hole. Through it you can see the back room of " +
        "the Giants Inn, where all the beer is kept.", SL));
    add_item("people", BS(
        "At a closer look you see that some are talking to each other and " +
    "others are walking quickly cross this place.", SL));
    add_item("road",
        "It leads off north. It's made out of small stones.\n");
    add_item(({"stone", "stones"}), BS(
        "The stones are small and round but they stick to the ground so you " +
        "can't pick them up.", SL));

    add_exit(TDIR + "city11", "west", 0);
    add_exit(TDIR + "city16", "south", 0);
    add_exit(TDIR + "city9", "north", 0);

    set_alarm(1.0,0.0,"reset_room");
}

init()
{
    ::init();
    ADA("enter");
    ADD("enter", "go");
    ADD("enter", "climb");
}

enter(str)
{
    NF(C(query_verb()) + " what?\n");
    if (str != "window" && str != "through window")
    return 0;

    TP->move_living("into the tent", TDIR + "back5");
    return 1;
}

reset_tantallon_room()
{
    if(!objectp(baaz1))
        {
         baaz1 = clone_object("/d/Krynn/std/baaz");
         baaz1->set_color("red");
         BAAZ_COIN1->move(baaz1);
         BAAZ_COIN2->move(baaz1);
         baaz1->move(TO);
    }

    if(!objectp(kapak))
        {
         kapak = clone_object("/d/Krynn/std/kapak");
         kapak->set_color("red");
         KAPAK_COIN1->move(kapak);
         KAPAK_COIN2->move(kapak);
         kapak->move(TO);
    }

    if (!goblin)
    {
        goblin = clone_object(MON + "ne_goblin");
        goblin->move_living("xxx", TO);
    }

    if (!human)
      set_alarm(6.0,0.0,"load_human");
}

load_human()
{
    int i;

    human = clone_object(MON + "ne_hum_g");
    human->move_living("xxx", TO);

    if (random(3))
        human->set_random_move(random(100));

}