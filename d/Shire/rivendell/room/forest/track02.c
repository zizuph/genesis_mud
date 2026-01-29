/*
 * Path to Rivendell
 * By Finwe, November 1997
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit FOREST_BASE;
 
void
create_forest_room()
{
 
    set_vbfc_extra(forest_desc1);

    if(check_person)
    {
        add_my_desc("A white stone lays buried beneath some " +
        "fallen leaves and twigs.\n");
    }
/* 
    add_item("white stone",
        "You see a white stone. It is buried by fallen leaves " +
        "and twigs. A star is engraved on the right end of the " +
        "stone and a moon engraved on the lower left-hand end of " +
        "the stone.\n");
    add_item("moss",
        "It is a verdant green color, looking velvet in the " +
        "dappled light. The moss grows over and across the " +
        "stones, covering them in a blanket of green.\n");
    add_item("heather",
        "The heather is a rich green color with tiny yellow " +
        "bell-shaped flowers. The plant is covered with tiny " +
        "leaves and crawls all over the floor of the forest.\n");
*/
    set_add_white_stone("right", "lower left-hand");

    add_item(({"stones", "rocks"}),
        "Various rocks and stones are buried under the leaves. They " +
        "look like they have been washed down from the " +
        "mountains and are of various colors.\n");
    add_item(({"colored stones", "colored rocks"}),
        "You see some red, gray, black, white, and other " +
        "colored stones scattered about.\n");
    add_item(({"black stones", "black rocks", "red stones", "red rocks", 
            "white stones", "white rocks", "gray stones", 
            "gray rocks"}),
        "The stones are scattered about, some buried under the " +
        "leaves and forest debris.\n");
 
    reset_shire_room();
    add_forest_herbs();
 
    add_exit(FOREST_DIR + "forest32", "north","@@bush_exit@@", 4, check_person);
    add_exit(FOREST_DIR + "track03", "east", 0,4, check_person);
    add_exit(FOREST_DIR + "track01", "southwest", 0,4, check_person);
 
}

int bush_exit()
{
    write ("You go north and crash through the bushes.\n");
    say(QCTNAME(TP) + " goes north and crashes through the bushes.\n");
    tell_room(FOREST_DIR + "forest32",
              QCTNAME(TP)+" comes crashing through the forest and startles you.\n",
              TP);
}

void reset_shire_room()
{
    set_searched(0);

}
