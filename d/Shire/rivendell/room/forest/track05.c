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
        add_my_desc("A white stone lays hidden in the leaves and bushes.\n");
    }

    set_add_white_stone("top", "bottom");

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

    add_exit(FOREST_DIR + "track06", "north", 0,4, check_person);
    add_exit(FOREST_DIR + "track04", "south", 0,4, check_person);
    add_exit(FOREST_DIR + "forest24","west","@@bush_exit@@", 4, check_person);

 
}

int bush_exit()
{
    write ("You head west and crash through the bushes.\n");
    say(QCTNAME(TP) + " goes west and crashes through the bushes.\n");
    tell_room(FOREST_DIR + "forest24",
              QCTNAME(TP)+" comes crashing through the forest and startles you.\n",
              TP);
}

void reset_shire_room()
{
    set_searched(0);

}
