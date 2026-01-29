/*
 * Common Board Room for the Academy of Elemental Arts in Gelan
 * 
 * Created by Petros, September 2009
 */

#pragma strict_types

#include "defs.h"

inherit SCHOOL_ROOM_BASE;

public void
create_school_room()
{
    set_short("Common Board Room");
    set_long("You find yourself in a strange place unlike any other in "
        + "the Academy. Inside this room, you find that a single board "
        + "that contains the Common Board notices for all of Genesis "
        + "to see. You notice that you can go <back> from where you "
        + "came from.\n\n");
                   
    add_exit(ACADEMIC_SCHOOL + "boardroom", "back");

    clone_object("/d/Genesis/obj/board")->move(this_object()); 
}

