/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * knight6.c
 *
 * Vader
 * Recoded by Sorgum 950712
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit CASTLE_DIR + "knight_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    clone_object(DOOR_DIR + "knight6_out")->move(TO);
}
