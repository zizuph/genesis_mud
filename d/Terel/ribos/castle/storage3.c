/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * storage0.c
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

    add_exit(CASTLE_DIR + "storage5", "north", 0);
    add_exit(CASTLE_DIR + "storage0", "west",  0);
}

void
reset_room()
{
    ::reset_room();
}