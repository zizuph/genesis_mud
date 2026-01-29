/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_OUTSIDE;

object goblin, human;

create_tantallon_room()
{
    set_short("On small road");
    set_long(BS(
        "You are standing on a small road between two tents. A road crossing " +
    "is south and north you can see a rather large opening. It might be " +
    "the centre of Tantallon. The evil in the air is rather strong here." +
    "", SL));

    add_item("tent",
        "Wich tent do you mean, the west tent or the east tent?\n");
    add_item("east tent", BS(
        "It's grey and rather big. Ten people could at least stand up in it. " +
        "There is a big sign on it and you can hear a lot of noice from the " +
        "inside.", SL));
    add_item("west tent",
        "It's a small black tent. There is no entrance on this side.\n");
    add_item("sign",
        "It's a small sign made out of wood with some words painted on it.\n");
    add_item("words",
        "They look readable.\n");
    add_item("road",
        "It leads off north and south. It's made out of small stones.\n");
    add_item(({"stone","stones"}), BS(
        "The stones are small and round but they stick to the ground so you " +
        "can't pick them up.", SL));
    add_item("crossing",
        "Just a normal four way road crossing.\n");

    add_cmd_item("sign", "read", "You read: THE DRACO INN\n");

    add_exit(TDIR + "city22", "south", 0);
    add_exit(TDIR + "tent2", "east", 0);
    add_exit(TDIR + "city15", "north", 0);

    set_alarm(1.0,0.0,"reset_room");
}

reset_tantallon_room()
{
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
