
/*
 * obelisk_psuchae.c
 *
 * The lower level of the black obelisk in the garden of
 * the Temple for the Spirit Circle of Psuchae. This is 
 * where the Guru Quest for the Spirit Spells skills takes
 * place. 
 *
 * Copyright (C): Jaacar (Mike Phipps), August 21st, 2003
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"
#include SPIRIT_HEADER

void 
create_room() 
{
    set_short("Inside the black obelisk");
    set_long("@@can_see@@\n");
    add_item("walls","@@walls_desc@@\n");
    add_item("wall","@@wall_desc@@\n");
    add_item("ceiling","@@ceiling_desc@@\n");
    add_item("roof","@@roof_desc@@\n");
    add_item("floor","@@floor_desc@@\n");
    add_item("stairs","@@stairs_desc@@\n");
    add_item("depression","@@depression_desc@@\n");
    
    IN;
    
    add_exit(SPIRIT_TEMPLE+"obelisk_ante","up","@@check_spiritform",1,1);
    
}
 
string
depression_desc()
{
    string depr_desc;

    if (present("_skiamati_object_",TP))
    {
        depr_desc = "The depression is roughly circular shaped.";
        return depr_desc;
    }

    depr_desc = "You find no depression.";
    return depr_desc;
}

string
stairs_desc()
{
    string stairs_desc;

    if (present("_skiamati_object_",TP))
    {
        stairs_desc = "The stairs lead up into the darkness.";
        return stairs_desc;
    }

    stairs_desc = "You find no stairs.";
    return stairs_desc;
}

string
walls_desc()
{
    string wall_desc;
    
    if (present("_skiamati_object_",TP))
    {
        wall_desc = "The walls, floor and ceiling of this chamber seem to ";
        wall_desc += "absorb all light in the area and beyond. The walls ";
        wall_desc += "are smooth to the touch, and constructed from some ";
        wall_desc += "type of black material.";
        return wall_desc;
    }

    wall_desc = "You find no walls.";
    return wall_desc;
}

string
wall_desc()
{
    string wall_desc;
    
    if (present("_skiamati_object_",TP))
    {
        wall_desc = "The walls, floor and ceiling of this chamber seem to ";
        wall_desc += "absorb all light in the area and beyond. The walls ";
        wall_desc += "are smooth to the touch, and constructed from some ";
        wall_desc += "type of black material.";
        return wall_desc;
    }

    wall_desc = "You find no wall.";
    return wall_desc;
}

string
ceiling_desc()
{
    string ceiling_desc;
    
    if (present("_skiamati_object_",TP))
    {
        ceiling_desc = "The walls, floor and ceiling of this chamber seem ";
        ceiling_desc += "to absorb all light in the area and beyond. The ";
        ceiling_desc += "ceiling appears to be very smooth, and constructed ";
        ceiling_desc += "from some type of black material.";
        return ceiling_desc;
    }

    ceiling_desc = "You find no ceiling.";
    return ceiling_desc;
}

string
roof_desc()
{
    string ceiling_desc;
    
    if (present("_skiamati_object_",TP))
    {
        ceiling_desc = "The walls, floor and ceiling of this chamber seem ";
        ceiling_desc += "to absorb all light in the area and beyond. The ";
        ceiling_desc += "ceiling appears to be very smooth, and constructed ";
        ceiling_desc += "from some type of black material.";
        return ceiling_desc;
    }

    ceiling_desc = "You find no roof.";
    return ceiling_desc;
}

string
floor_desc()
{
    string floor_desc;
    
    if (present("_skiamati_object_",TP))
    {
        floor_desc = "The walls, floor and ceiling of this chamber seem to ";
        floor_desc += "absorb all light in the area and beyond. The floor ";
        floor_desc += "is smooth to the touch, and constructed from some ";
        floor_desc += "type of black material.";
        return floor_desc;
    }

    floor_desc = "You find no floor.";
    return floor_desc;
}

string
can_see()
{
    string desc;

    if (present("_skiamati_object_",TP))
    {
        desc = "The walls, floor and ceiling of this chamber seem to ";
        desc += "absorb all light in the area and beyond. There is a ";
        desc += "depression on the wall and some stairs leading up ";
        desc += "into the darkness.";
        return desc;
    }

    desc = "You can see absolutely nothing.";
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

int
do_insert(string str)
{
    object symbol;

    if (!present("_skiamati_object_",TP))
        return 0;

    if (!present("_skiamorfi_object_",TP))
    {
        write("You attempt to move but cannot. It is as though "+
            "your body is stuck in a solid object.\n");
        say(QCTNAME(TP)+" attempts to move but appears frozen "+
            "in "+HIS+" tracks.\n");
        return 1;
    }

    if (str != "symbol" && str != "holy symbol" && str != "mandala" &&
        str != "sacred mandala")
    {
        write("The "+str+" does not fit in the depression.\n");
        return 1;
    }

    symbol = present("spirit_holy_symbol",TP);
    if (!symbol)
    {
        write("Put what in the depression?\n");
        return 1;
    }

    if (TP->query_prop(LIVE_I_PLACED_SPIRIT_SYMBOL))
    {
        write("You have already completed this step.\n");
        return 1;
    }

    write("You place the sacred mandala into the depression. The whole "+
        "wall begins to glow brightly.\n\nYou hear a voice ringing in "+
        "your mind yelling \"Help! Help me now! You have opened the "+
        "passage to me. Free me at last!\".\n\nThe light from coming "+
        "from the depression gets brighter then narrows itself to a "+
        "single point light. Following the point of light with your "+
        "eyes, you see it travels to the centre of the room, then curves "+
        "quickly and points straight up the stairs. The light vanishes "+
        "as quickly as it appeared.\nYou take your sacred mandala back from "+
        "the depression.\n");
    say(QCTNAME(TP)+" does something to the depression. The entire wall "+
        "begins to glow very brightly and you have to cover your eyes in "+
        "fear that you will be blinded. When you finally uncover them, "+
        "the chamber is as it once was, the light is gone completely.\n");
    TP->add_prop(LIVE_I_PLACED_SPIRIT_SYMBOL,1);
    return 1;
}

void
init()
{
    ::init();
    add_action(do_insert,"insert");
}
