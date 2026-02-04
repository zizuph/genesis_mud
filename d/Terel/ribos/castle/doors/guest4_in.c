/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * guest4_in.c
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
    set_other_room(RIBOS_DIR + "castle/guest4");
}
 
