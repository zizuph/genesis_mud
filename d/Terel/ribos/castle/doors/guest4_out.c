/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * guest4_out.c
 *
 * Guest room door.
 *
 * Sorgum 950711
 */

#include "/d/Terel/include/Terel.h"
inherit RIBOS_DIR + "castle/doors/guest_door";
 
/*
 * Function name: create_door
 * Description:   Sets default names and id
 */
public void
create_door()
{
    ::create_door();
    set_pass_command(({"e", "east"}));    
    set_other_room(RIBOS_DIR + "castle/l_hall1_4");
}
 
