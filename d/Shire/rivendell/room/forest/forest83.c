/*
 * Forest near Rivendell
 * By Finwe, August 1998
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit FOREST_BASE;
 
void
create_forest_room()
{
    set_vbfc_extra(forest_desc2);
    set_extraline("The river Bruinen flows along here lazily. ");
    reset_shire_room();
    add_forest_herbs();

    add_item(({"river", "river bruinen", "bruinen"}),
        "The river flows lazily to the west from the mountains. " +
        "It looks clear and fresh.\n");

    add_exit(FOREST_DIR + "forest79", "north",0,4, check_person);
    add_exit(FOREST_DIR + "forest82", "west",0,4, check_person);
 
}

void reset_shire_room()
{
    set_searched(0);

}
