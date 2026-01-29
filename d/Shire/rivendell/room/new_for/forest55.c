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
    set_vbfc_extra(forest_desc4);
    reset_shire_room();

    add_exit(FOREST_DIR + "forest45", "north",0,4, check_person);
    add_exit(FOREST_DIR + "forest64", "south","@@bush_exit_s@@",4, 1);
    add_exit(FOREST_DIR + "forest56", "east",0,4, check_person);
    add_exit(FOREST_DIR + "forest54", "west","@@bush_exit@@",4, 1);
}

int bush_exit()
{
    write ("You go west and crash through the bushes.\n");
    say(QCTNAME(TP) + " goes west and crashes through the bushes.\n");
    tell_room(FOREST_DIR + "forest54",
              QCTNAME(TP)+" comes crashing through the forest and startles you.\n",
              TP);
}

int bush_exit_s()
{
    write ("You go south and crash through the bushes.\n");
    say(QCTNAME(TP) + " goes south and crashes through the bushes.\n");
    tell_room(FOREST_DIR + "forest64",
              QCTNAME(TP)+" comes crashing through the forest and startles you.\n",
              TP);
}

void reset_shire_room()
{
}
