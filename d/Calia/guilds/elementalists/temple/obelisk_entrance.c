
/*
 * obelisk_entrance.c
 *
 * The lower level of the obelisk in the garden of
 * the Temple for the Elemental Clerics of Calia. This is 
 * where the Guru Quest for the Cleric guild takes
 * place. 
 *
 * Copyright (C): Jaacar (Mike Phipps), August 20th, 2003
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"
 
void 
create_room() 
{
    set_short("Inside the obelisk");
    set_long("You are standing inside of the obelisk. It is a "+
        "small chamber with a set of stairs leading down into the "+
        "darkness below. You feel you could also head back 'out' to "+
        "the garden (as long as you are in your elemental form and "+
        "can walk through the wall again).\n");
    
    add_exit(ELEMENTALIST_TEMPLE+"obelisk_garden","out","@@check_spiritform",1);
    add_exit(ELEMENTALIST_TEMPLE+"obelisk_lower1","down","@@check_stairs",1);
}
 
int
check_stairs()
{
    if (TP->query_wiz_level())
    {
        write("Normally you would not be able to leave unless "+
            "you were in spirit form, but since you are a wizard, "+
            "you don't need to worry about that.\n");
        return 0;
    }

    if (!present("_skiamorfi_object_",TP))
    {
        write("You attempt to move but cannot. It is as though "+
            "your body is stuck in a solid object.\n");
        say(QCTNAME(TP)+" attempts to move but appears frozen "+
            "in "+HIS+" tracks.\n");
        return 1;
    }

    write("You proceed down the stairway, into the darkness below.\n");
    return 0;
}

int
check_spiritform()
{
    if (TP->query_wiz_level())
    {
        write("Normally you would not be able to leave unless "+
            "you were in spirit form, but since you are a wizard, "+
            "you don't need to worry about that.\n");
        return 0;
    }
    
    if (present("_skiamorfi_object_",TP))
    {
        write("You step through the wall of the obelisk and back "+
            "into the garden outside.\n");
        say(QCTNAME(TP)+" steps through the wall of the obelisk and "+
            "back into the garden outside.\n");
        return 0;
    }

    
    write("You walk into the wall with a 'thud'.\n");
    say(QCTNAME(TP)+" attempts to leave but ends up walking "+
        "into the wall with a 'thud'.\n");
    return 1;
}

