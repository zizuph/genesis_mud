/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * v_door_out.c
 *
 * The door to the vault in the ribos bank
 *
 * Vader
 * Recoded by Sorgum 950707
 */

#include "/d/Terel/include/Terel.h"
inherit "/std/door";

/*
 * Function name: create_door
 * Description:   Sets default names and id
 */
public void
create_door()
{
    ::create_door();
    set_door_id("vault_door");

    set_pass_command(({"e","east"}));
    set_door_desc("A bank vault made of thick steel.\n");

    set_open_desc("A bank vault door that someone has left open.\n");
    set_closed_desc("A bank vault door that has been left closed.\n");
    
    set_other_room(RIBOS_DIR + "bank");

    set_open(0);
    set_locked(0);    
}
