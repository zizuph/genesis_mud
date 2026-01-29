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

    if(check_person)
    {
        add_my_desc("A white stone lays hidden in the leaves.\n");
    }
    
    set_add_white_stone("upper end", "lower left-hand corner");

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
 
    add_exit(FOREST_DIR + "track05", "north",0,4, check_person);
    add_exit(FOREST_DIR + "track03", "southwest",0,4, check_person);
 
}

void reset_shire_room()
{
}
