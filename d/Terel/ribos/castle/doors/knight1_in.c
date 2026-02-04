/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * knight1_in.c
 *
 * Knight room door.
 *
 * Sorgum 950711
 *
 * Modified: Bleys, 25 Apr 2003:
 *   - altered filename string in file header to be accurate
 *   - guest_door inherit was erroneously inheriting a nonexistent
 *       file 'guest_door1'
 *   - set_other_room() referred to the room that clones and
 *       contains this door, creating an incessant loop.
 *   - the necessary set_pass_command() call was missing.
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
    set_other_room(RIBOS_DIR + "castle/knight1");
}
 
