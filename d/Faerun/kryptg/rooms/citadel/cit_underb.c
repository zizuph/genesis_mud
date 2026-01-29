/*
 * Citadel in the Kryptgarden
 * -- Finwe, August 2007
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_CITADEL;

object ob;

void
create_citadel()
{
    INDOORS;
    NO_STEEDS;
    set_short("A passage beneath the Citadel");
    set_extraline("The dark passageway extends deeper into the earth. " +
        "The walls are lined with stone blocks and and have empty torch " +
        "stands on them. The air is musty and smells foul. To the north " +
        "the passageway collapsed and is blocked.");

    reset_faerun_room();
    set_add_under_cit();

    add_exit(CIT_DIR + "cit_undera", "south");
}

public void
init()
{
    ::init();
}

void
reset_faerun_room()
{
    ::reset_faerun_room();
//
//    setuid(); 
//    seteuid(getuid());
//    
//    if ((ob))
//    {
//        return;
//    }
//    
//    ob = clone_object(NPC_DIR + "dwarf_ghost");
//    ob->move(this_object());

}
