/*
 * p6.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <ss_types.h>

object dragon;

string
sign()
{
    return "The sign says: The Kaheda Order.\n";
}

void
reset_room()
{
    if (!dragon)
        dragon = clone_object(ROKEDIR + "npc/dragon");

    dragon->move_living("X", TO);
}

void
create_room()
{
    set_short("Outside a house");
    set_long("You are outside the entrance to a stone building that resides " +
             "on the top of the mountain. The view is stunning from here, " +
             "and it is possible to look over almost all of Nyreese. " +
             "A large oak dominates the west side of the building. " +
             "A small sign hangs on the house, and close to the wall are " +
             "some wild-grown bushes. You also notice a narrow path " +
             "leading east.\n");

    add_my_desc("There are two obvious exits: south, in.\n");
    set_noshow_obvious(1);

    add_exit("p5", "south");
    add_exit("monk_entr", "in");
    add_exit("q1", "east");

    add_cmd_item(({"up", "tree"}), "climb", "@@climb");

    add_item(({"oak", "tree"}), "It is a magnificent tree, " +
             "its branches streatch far above.\n");
    add_item("sign", "@@sign");
    add_item("view", "Before your eyes a spectacular view unravels. " +
             "Far to the south you see the prosperious porttown of " +
             "Cadu, while to the east and west you spot a vast ocean.\n");
    add_item("house",
             "It is a rather large house, built from finest stone.\n");
    add_item(({"bush", "bushes"}), "@@bushes");
    add_cmd_item(({"bush", "bushes"}), "enter", "@@enter");
    add_cmd_item(({"hole"}), "enter", "@@enter");
    add_cmd_item("sign", "read", "@@sign");
    reset_room();
}

string
bushes()
{
    if (TP->query_skill(SS_AWARENESS) > 35 || TP->query_skill(SS_TRACKING) > 45)
        return "Among the bushes you discover a small hole you can enter.\n";

    return "Some thick bushes.\n";
}

string
enter()
{
    if (TP->query_skill(SS_AWARENESS) > 25 || TP->query_skill(SS_TRACKING) > 35)
    {
        if (TP->query_skill(SS_AWARENESS) <= 35 &&
            TP->query_skill(SS_TRACKING) <= 45)
            write("When you try to enter the bushes, you discover a small hole through " +
                  "which you can pass.\n");
        else
            write("You enter the hole in the bushes.\n");
        TP->move_living("into the bushes", WILDDIR + "monk_herbg_se", 1);
        return "";
    }
    return "You try to enter the bush but it's too thick.\n";
}

int
climb()
{
    TP->move_living("climbing up the tree", WILDDIR + "monk_tree");
    return 1;
}
