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
    set_vbfc_extra(forest_desc5);
    reset_shire_room();
    add_forest_herbs();

    add_exit(FOREST_DIR + "forest14", "north",0,4, check_person);
    add_exit(FOREST_DIR + "forest21", "west","@@bush_exit@@",4, check_person);
    add_exit(FOREST_DIR + "forest30", "southwest",0,4, check_person);
}



int bush_exit()
{
    write ("You go west and crash through the bushes.\n");
    say(QCTNAME(TP) + " goes west and crashes through the bushes.\n");
    tell_room(FOREST_DIR + "forest21",
              QCTNAME(TP)+" comes crashing through the forest and startles you.\n",
              TP);

}

void reset_shire_room()
{
    set_searched(0);

}
