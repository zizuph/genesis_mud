
/*
 * obelisk_aeria.c
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
 
void 
create_room() 
{
    set_short("Inside the obelisk");
    set_long("@@can_see@@\n");
    
    add_item(({"walls","wall","ceiling","roof","floor"}),"The walls, "+
        "floor and ceiling of this chamber seem to absorb all light in "+
        "the area and beyond. The walls are smooth to the touch, and "+
        "constructed from some type of black material.\n");

    add_item("passage","The passage leads off to the southeast, into the "+
        "darkness.\n");
        
    add_item(({"notch","small notch"}),"@@notch_desc\n");
    
    add_item("statue","@@statue_desc@@\n");
    
    IN;
    
    add_exit(ELEMENTALIST_TEMPLE+"obelisk_ante","southeast","@@check_spiritform",1,1);
    
}
 
void
reset_room()
{
    notch = 1;
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

    notch_desc = "The small notch is located in the base of "+
        "the statue. It appears to be triangle shaped. "+
        "You could probably insert something into it.";
    return notch_desc;
}

string
statue_desc()
{
    string statue_desc;
    
    statue_desc = "It is a small statue of Lady Aeria. It seems "+
        "strange to see it in this place.";
    
    if (notch)
        statue_desc += " There is a small notch in the base of the statue.";
    return statue_desc;
}

string
can_see()
{
    string desc;

    desc = "The walls, floor and ceiling of this chamber seem to ";
    desc += "absorb all light in the area and beyond. There is a ";
    desc += "passage leading to the southeast into the darkness. ";
    desc += "There is a statue in this chamber.";
    if (notch)
        desc += " A small notch can be seen in the statue.";
        
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
    object triangle;

    if (!notch)
        return 0;
    
    if (!str)
    {
    	notify_fail("Insert what?\n");
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

    if (!parse_command(str, TP, " [the] [crystal] 'triangle' [in] [into] [the] [notch] "))
    {
        write("The "+str+" does not fit in the notch.\n");
        return 1;
    }

    triangle = present("_aeria_triangle_",TP);
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

    write("You place the crystal triangle into the notch. The triangle "+
        "quickly changes colour to match the statue, sealing the notch.\n");
    say(QCTNAME(TP)+" does something to the statue.\n");
    notch = 0;
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
}
