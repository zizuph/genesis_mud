/* Khiraa Dungeon, Sarr */
#include "defs.h"
inherit DUNGEON_DIR + "dungeon_room";

int found = 0;

void
create_room()
{
    ::create_room();
    set_short("A dark dungeon");
    set_long(
      "This is a small, dingy dirty old cell. The walls are made of stone, " +
      "and in some spots you see dried blood. There is a pile of rotting " +
      "wood here, and some old shackles on the wall.\n");

    add_item(({"pile", "wood"}),
      "Looking closely at the wood pile, you can see a skeleton buried " +
      "within it.\n");
    add_item(({"shackles"}), "They are old and rusted.\n");

    add_item(({"skeleton"}), "@@my_long@@");
    clone_object(DUNGEON_OBJ_DIR + "gate_9_inner")->move(TO);
}

string
my_long()
{
    if (found)
    {
        return "Its old, crumbling, and dusty. It appears to be human, but " +
               "you can not be sure.\n";
    }
    return "Its old, crumbling and dusty. It appears to be human, but you " +
           "can not be sure. You think you see something shining underneath " +
           "it.\n";
}

void
init()
{
    ::init();
    add_action("do_search", "search");
}

int
do_search(string str)
{
    if (str != "skeleton")
    {
        NF("Search what?\n");
        return 0;
    }
    write("You search around the skeleton.\n");
    say(QCTNAME(TP) + " searches around the skeleton.\n");
    set_alarm(4.0, 0.0, "do_search2");
    return 1;
}

void
do_search2()
{
    object obj;
    if (found)
    {
        write("You find nothing.\n");
    }
    else
    {
        write("You find a dagger!\n");
        say(QCTNAME(TP) + " finds something.\n");
        obj = clone_object(QUEST_DAGGER_FILE);
        obj->move(TP, 1);
        found = 1;
    }
}

void
reset_room()
{
    found = 0;
}
