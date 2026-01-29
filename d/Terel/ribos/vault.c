/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * vault.c
 *
 * The Ribos bank vault
 *
 * Vader
 * Recoded by Sorgum 950707
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Bank vault");
    set_long("You are in the Ribos bank vault.  It's empty.\n");

    add_exit(RIBOS_DIR + "road11", "southeast", 0);

    FIX_EUID;
    clone_object(RIBOS_DIR + "doors/v_door_out")->move(TO);        
}

