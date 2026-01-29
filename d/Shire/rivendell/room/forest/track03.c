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
 
    set_vbfc_extra(forest_desc3);
    extraline="Some broken branches hang down from the trees, " +
        "blocking the light. ";

    if(check_person)
    {
        add_my_desc("A white stone lays buried beneath some " +
        "fallen leaves and twigs.\n");
    }

    add_item(({"broken branch", "broken branches"}),
        "Some broken branches hang down from the trees. Their " +
        "ends look like they were broken off during a strong " +
        "wind or from old age.\n");
    
    set_add_white_stone("upper right-hand corner", "left end");

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
 
    add_exit(TREES_DIR  + "track03_01", "up",0,4,1);
    add_exit(FOREST_DIR + "forest46", "south","@@bush_exit@@",4, check_person);
    add_exit(FOREST_DIR + "track02", "west",0,4, check_person);
    add_exit(FOREST_DIR + "track04", "northeast",0,4, check_person);
 
}

int bush_exit()
{
    write ("You go south and crash through the bushes.\n");
    say(QCTNAME(TP) + " goes south and crashes through the bushes.\n");
    tell_room(FOREST_DIR + "forest46",
              QCTNAME(TP)+" comes crashing through the forest and startles you.\n",
              TP);
}

void reset_shire_room()
{
    set_searched(0);

}
