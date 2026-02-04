/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * g_quart_2.c
 *
 * Ribos Castle quards quarters
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit CASTLE_DIR + "g_quart_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_exit(CASTLE_DIR + "cas_ent", "east", 0);
    reset_room();
}
