
/*
 * obelisk_ante.c
 *
 * The lower level of the obelisk in the garden of
 * the Temple for the Elemental Clerics of Calia. This is 
 * where the Guru Quest for the Cleric guild takes
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

int notch = 1;
int depression = 1;
 
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
    add_item("passages","@@passages_desc@@\n");
    add_item("notch","@@notch_desc@@\n");
    add_item("small notch","@@notch_desc@@\n");
    add_item("depression","@@depression_desc@@\n");
    
    IN;
    
    add_exit(ELEMENTALIST_TEMPLE+"obelisk_lower2","south","@@check_spiritform",1,1);
    add_exit(ELEMENTALIST_TEMPLE+"obelisk_psuchae_triangle","north","@@check_spiritform",1,1);
    add_exit(ELEMENTALIST_TEMPLE+"obelisk_aeria","northwest","@@check_spiritform",1,1);
    add_exit(ELEMENTALIST_TEMPLE+"obelisk_gu","southwest","@@check_spiritform",1,1);
    add_exit(ELEMENTALIST_TEMPLE+"obelisk_diabrecho","northeast","@@check_spiritform",1,1);
    add_exit(ELEMENTALIST_TEMPLE+"obelisk_pyros","southeast","@@check_spiritform",1,1);
    add_exit(ELEMENTALIST_TEMPLE+"obelisk_psuchae","down","@@check_step_two@@",1,1);
    add_exit(ELEMENTALIST_TEMPLE+"obelisk_prison","up","@@check_step_three@@",1,1);
}
 
void
reset_room()
{
    notch = 1;
    depression = 1;
}

string
depression_desc()
{
    string depr_desc;

    if (!depression)
    {
        depr_desc = "You find no depression.";
        return depr_desc;
    }

    depr_desc = "There is a depression located in the west wall, ";
    depr_desc += "right below the small notch. It appears to be ";
    depr_desc += "triangular shaped. You could probably place ";
    depr_desc += "something into it.";
    return depr_desc;
}

string
small_notch_desc()
{
    string notch_desc;

    if (!notch)
    {
        notch_desc = "You find no small notch.";
        return notch_desc;
    }

    notch_desc = "The small notch is located in the west wall. ";
    notch_desc += "It appears to be cylinder shaped. You could ";
    notch_desc += "probably insert something into it.";
    return notch_desc;
}

string
notch_desc()
{
    string notch_desc;

    if (!notch)
    {
        notch_desc = "You find no notch.";
        return notch_desc;
    }

    notch_desc = "The small notch is located in the west wall. ";
    notch_desc += "It appears to be cylinder shaped. You could ";
    notch_desc += "probably insert something into it.";
    return notch_desc;
}

string
passages_desc()
{
    string pass_desc;

    pass_desc = "There are passages leading off to the north, ";
    pass_desc += "northwest, northeast, southwest, south and southeast ";
    pass_desc += "into the darkness.";
    return pass_desc;
}

string
walls_desc()
{
    string wall_desc;
    
    wall_desc = "The walls, floor and ceiling of this chamber seem to ";
    wall_desc += "absorb all light in the area and beyond. The walls ";
    wall_desc += "are smooth to the touch, and constructed from some ";
    wall_desc += "type of black material. ";
        
    if (depression)
    {
        wall_desc += "There is a depression in the west wall.";
    }
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
    desc += "absorb all light in the area and beyond. There are ";
    desc += "passages leading to the north, northwest, northeast, ";
    desc += "southwest, south and southeast into the darkness.";
    
    if (notch)
        desc += " A small notch can be seen on the western wall.";
        
    if (TP->query_prop(LIVE_I_PLACED_CLERIC_CYLINDER))
        desc += " A hidden stairway leads down into the darkness.";
        
    if (TP->query_prop(LIVE_I_PLACED_CLERIC_SYMBOL))
        desc += " You see another hidden stairway leading up.";
        
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
check_step_two()
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

    if (TP->query_prop(LIVE_I_PLACED_CLERIC_CYLINDER))
    {
        write("You make your way down the hidden stairway to the "+
            "north.\n");
        return 0;
    }

    return 1;
}

int
check_step_three()
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

    if (TP->query_prop(LIVE_I_PLACED_CLERIC_SYMBOL))
    {
        write("You make your way up the second hidden stairway.\n");
        return 0;
    }

    return 1;
}

int
do_insert(string str)
{
    object cylinder;
    
    if (!str)
    {
    	notify_fail("Insert what?\n");
    	return 0;
    }

    if (!notch)
        return 0;

    if (!present("_skiamorfi_object_",TP))
    {
        write("You attempt to move but cannot. It is as though "+
            "your body is stuck in a solid object.\n");
        say(QCTNAME(TP)+" attempts to move but appears frozen "+
            "in "+HIS+" tracks.\n");
        return 1;
    }

    if (!parse_command(str, TP, " [the] [glowing] 'cylinder' [in] [into] [the] [notch] "))
    {
        write("The "+str+" does not fit in the notch.\n");
        return 1;
    }

    cylinder = present("_psuchae_cylinder_",TP);
    if (!cylinder)
    {
        write("Put what in the notch?\n");
        return 1;
    }

    if (TP->query_prop(LIVE_I_PLACED_CLERIC_CYLINDER))
    {
        write("You have already completed this step.\n");
        return 1;
    }

    if (!TP->query_prop(LIVE_I_PLACED_CLERIC_TRIANGLE))
    {
        write("You feel you are not yet ready to complete this step.\n");
        return 1;
    }

    if (TP->query_prop(LIVE_I_PLACED_CLERIC_SYMBOL))
    {
        write("You have already completed this step.\n");
        return 1;
    }

    write("You place the glowing cylinder into the notch. The cylinder "+
        "quickly changes colour to match the wall, sealing the notch.\n");
    say(QCTNAME(TP)+" does something to the western wall.\n");
    notch = 0;
    cylinder->remove_object();
    TP->add_prop(LIVE_I_PLACED_CLERIC_CYLINDER,1);
    write("You feel as though you are one step closer to freeing "+
        "the trapped spirit. A stairway leading down to the north "+
        "has been revealed to you.\n");
    return 1;
}

int
do_place(string str)
{
    object triangle;
    
    if (!str)
    {
    	notify_fail("Place what?\n");
    	return 0;
    }

    if (!notch)
        return 0;

    if (!present("_skiamorfi_object_",TP))
    {
        write("You attempt to move but cannot. It is as though "+
            "your body is stuck in a solid object.\n");
        say(QCTNAME(TP)+" attempts to move but appears frozen "+
            "in "+HIS+" tracks.\n");
        return 1;
    }

    if (!parse_command(str, TP, " [the] [black] 'triangle' [in] [into] [the] [notch] "))
    {
        write("The "+str+" does not fit in the notch.\n");
        return 1;
    }

    triangle = present("_psuchae_triangle_",TP);
    if (!triangle)
    {
        write("Put what in the notch?\n");
        return 1;
    }

    if (TP->query_prop(LIVE_I_PLACED_CLERIC_TRIANGLE))
    {
        write("You have already completed this step.\n");
        return 1;
    }

    if (TP->query_prop(LIVE_I_PLACED_CLERIC_CYLINDER))
    {
        write("You have already completed this step.\n");
        return 1;
    }

    if (TP->query_prop(LIVE_I_PLACED_CLERIC_SYMBOL))
    {
        write("You have already completed this step.\n");
        return 1;
    }

    write("You place the black triangle into the depression. The triangle "+
        "quickly changes colour to match the wall, sealing the depression.\n");
    say(QCTNAME(TP)+" does something to the statue.\n");
    depression = 0;
    triangle->remove_object();
    TP->add_prop(LIVE_I_PLACED_CLERIC_TRIANGLE,1);
    write("You feel as though you are one step closer to freeing "+
        "the trapped spirit.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_insert,"insert");
    add_action(do_place,"place");
}
