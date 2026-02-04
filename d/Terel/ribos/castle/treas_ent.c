/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * treas_ent.c
 *
 * Vader
 * Recoded by Sorgum 950712
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit STDROOM;

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("A small room");
    set_long("This is a small room.  The exit is to the south.\n");
    
    add_exit(CASTLE_DIR + "r_hall2_2", "south", 0);
 
    INSIDE;

    FIX_EUID;
    clone_object(DOOR_DIR + "t_in")->move(TO);
}
 
