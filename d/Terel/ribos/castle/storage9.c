/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * storage9.c
 *
 * A storage room in the Ribos castle.
 *
 * Vader
 * Recoded by Sorgum 950716
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit CASTLE_DIR + "storage_room";

create_room()
{
    ::create_room();

    add_exit(CASTLE_DIR + "storage1", "northeast", 0);
    add_exit(CASTLE_DIR + "storage2", "east",     0);
}

void
reset_room()
{
    ::reset_room();
}