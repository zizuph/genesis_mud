
/*
 * obelisk_lower2.c
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
    set_long("@@can_see@@\n");
    add_item("walls","@@walls_desc@@\n");
    add_item("wall","@@wall_desc@@\n");
    add_item("ceiling","@@ceiling_desc@@\n");
    add_item("roof","@@roof_desc@@\n");
    add_item("floor","@@floor_desc@@\n");
    add_item("passage","@@passage_desc@@\n");
    
    add_exit(ELEMENTALIST_TEMPLE+"obelisk_lower1","south","@@check_spiritform",1,1);
    add_exit(ELEMENTALIST_TEMPLE+"obelisk_ante","north","@@check_spiritform",1,1);
}
 
string
passage_desc()
{
    string pass_desc;

    pass_desc = "The passage leads off to the south, into the ";
    pass_desc += "darkness and to the north into some type of large ";
    pass_desc += "chamber.";
    return pass_desc;
}

string
walls_desc()
{
    string wall_desc;
    
    wall_desc = "The walls, floor and ceiling of this chamber seem to ";
    wall_desc += "absorb all light in the area and beyond. The walls ";
    wall_desc += "are smooth to the touch, and constructed from some ";
    wall_desc += "type of black material.";
    return wall_desc;
}

string
wall_desc()
{
    string wall_desc;
    
    wall_desc = "The walls, floor and ceiling of this chamber seem to ";
    wall_desc += "absorb all light in the area and beyond. The walls ";
    wall_desc += "are smooth to the touch, and constructed from some ";
    wall_desc += "type of black material.";
    return wall_desc;
}

string
ceiling_desc()
{
    string ceiling_desc;
    
    ceiling_desc = "The walls, floor and ceiling of this chamber seem ";
    ceiling_desc += "to absorb all light in the area and beyond. The ";
    ceiling_desc += "ceiling appears to be very smooth, and constructed ";
    ceiling_desc += "from some type of black material.";
    return ceiling_desc;
}

string
roof_desc()
{
    string ceiling_desc;
    
    ceiling_desc = "The walls, floor and ceiling of this chamber seem ";
    ceiling_desc += "to absorb all light in the area and beyond. The ";
    ceiling_desc += "ceiling appears to be very smooth, and constructed ";
    ceiling_desc += "from some type of black material.";
    return ceiling_desc;
}

string
floor_desc()
{
    string floor_desc;
    
    floor_desc = "The walls, floor and ceiling of this chamber seem to ";
    floor_desc += "absorb all light in the area and beyond. The floor ";
    floor_desc += "is smooth to the touch, and constructed from some ";
    floor_desc += "type of black material.";
    return floor_desc;
}

string
can_see()
{
    string desc;

    desc = "The walls, floor and ceiling of this chamber seem to ";
    desc += "absorb all light in the area and beyond. There is a ";
    desc += "passage leading to the south into the darkness and to ";
    desc += "north into some type of larger chamber.";
    return desc;
}

int
check_spiritform()
{
    if (TP->query_wiz_level())
    {
        write("Normally you would not be able to wander unless "+
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

    return 0;
}

