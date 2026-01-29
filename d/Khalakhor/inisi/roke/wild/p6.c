/*
 * p6.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <ss_types.h>

object dragon;

/*
string
sign()
{
    return "The sign says: The _Kaheda_ Order.\n";
}
*/

void
reset_room()
{
    if (!dragon)
    {
        dragon = clone_object(ROKEDIR + "npc/dragon");
        dragon->move_living("X", TO);
        return;
    }

    if (environment(dragon) != this_object())
    {
        dragon->move_living("home", TO);
    }
}

void
create_room()
{
    set_short("Outside an old building");
/*
    set_long("You are outside the entrance to a stone building that resides " +
             "on the top of the mountain. The view is stunning from here, " +
             "and it is possible to look over almost all of Nyreese. " +
             "A large oak dominates the west side of the building. " +
             "A small sign hangs on the house, and close to the wall are " +
             "some wild-grown bushes. You also notice a narrow path " +
             "leading east.\n");
*/

    set_long("You are outside the entrance of an abandoned stone building, " +
             "which extends back quite a long way and into the surrounding " +
             "mountainside. The view is stunning from here, and it is " +
             "possible to look over most of Nyreese. A large oak tree is " +
             "directly to the west of the building, whose entrance is " +
             "almost completely blocked by brambles and gorse bushes. " +
             "A narrow path leads east.\n");

    add_exit("p5",        "south");
    add_exit("monk_entr", "in");
    add_exit("q1",        "east", 0, 1, 1 /* non-obvious */);

    add_cmd_item(({"up", "tree"}), "climb", "@@climb");

    add_item(({"oak", "tree"}), "It is a magnificent tree, " +
             "its branches stretch far above.\n");
    add_item("view", "Before your eyes a spectacular view unravels. " +
             "Far to the south you see the prosperious porttown of " +
             "Cadu, while to the east and west you spot a vast ocean.\n");
/*
    add_item(({"house", "building"}),
             "It is a rather large house, built from finest stone.\n");
*/
    add_item(({"house", "building"}),
             "This building is made of faded grey stone, quarried from the " +
             "surrounding mountainside. The door is missing, and gorse " +
             "bushes now grow where once was a prestine earthen floor. " +
             "Cobwebs hang from the ceiling, and the musty damp smell of " +
             "mould irritates your nose. " +
             "There is a small, less faded, rectangular patch of stone " +
             "directly to the right of the open doorway.\n");
    add_item(({"patch", "patch of stone"}), "You think there may have been " +
             "something attached there, like a sign.\n");
    add_item(({"bush", "bushes"}), "@@bushes");
    add_cmd_item(({"bush", "bushes", "hole"}), "enter", "@@enter");
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
