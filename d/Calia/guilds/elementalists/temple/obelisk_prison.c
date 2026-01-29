
/*
 * obelisk_prison.c
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

int globe = 1;

string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}

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
    add_item("stairs","@@stairs_desc@@\n");
    add_item("globe","@@globe_desc@@\n");
    add_item("glass globe","@@glass_globe_desc@@\n");
    
    IN;
    
    add_exit(ELEMENTALIST_TEMPLE+"obelisk_ante","down","@@check_spiritform",1,1);
    
}
 
void
reset_room()
{
    globe = 1;
}

string
globe_desc()
{
    string globe_desc;

    if (globe)
    {
        globe_desc = "There is a glass globe hovering in the centre ";
        globe_desc += "of the chamber. It is perfectly smooth to the ";
        globe_desc += "touch. In the globe you see a dark shadowy ";
        globe_desc += "figure swirling around. You could probably ";
        globe_desc += "break the globe if you wanted.";
        return globe_desc;
    }
    else
    {
        globe_desc = "There is the remains of a broken glass globe ";
        globe_desc += "on the floor here.";
        return globe_desc;
    }
}

string
stairs_desc()
{
    string stairs_desc;

    stairs_desc = "The stairs lead down into the darkness.";
    return stairs_desc;
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
    desc += "absorb all light in the area and beyond. There are ";
    desc += "stairs leading down into the darkness. ";
    if (globe)
    {
        desc += "Hovering in the centre of the chamber you see ";
        desc += "a glass globe.";
    }
    else
    {
        desc += "On the ground you see the remains of a broken glass ";
        desc += "globe.";
    }
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
do_break(string str)
{
	if (!str)
    {
    	notify_fail("Break what?\n");
    	return 0;
    }
    
    if (TP->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT))
    {
        write("You have already completed the quest!\n");
        return 1;
    }

    if (!present("_skiamorfi_object_",TP))
    {
        write("You attempt to move but cannot. It is as though "+
            "your body is stuck in a solid object.\n");
        say(QCTNAME(TP)+" attempts to move but appears frozen "+
            "in "+HIS+" tracks.\n");
        return 1;
    }

    if (!globe)
    {
        write("Break what? The globe is already broken.\n");
        return 1;
    }

    if (!parse_command(str, TP, " [the] [glass] 'globe' "))
    {
        write("Break what? The glass globe?\n");
        return 1;
    }
    
    string *completed_messages = ({"You reach out and grab the glass "+
    	"globe that is hovering in the centre of the chamber. Taking "+
    	"a firm hold of it in one hand you throw it forcefully at the g"+
    	"round. As it hits the ground, the glass globe shatters into "+
    	"pieces, releasing the shadowy figure from inside of it.\n\n",
    	"The shadowy figure grows to exactly your size and shape, then "+
    	"stands before you. It reaches out and touches your shoulder. "+
    	"The shadowy hand feels cold, but familiar all the same.\n\n",
    	"The figure telepathically speaks to you in your own voice"+
    	": \"At last! At last you have freed me! I am a part of your "+
    	"own soul. A part that was taken by Psuchae from you when you "+
    	"joined the Circle. Do not be angered by this. Psuchae has done "+
    	"this as a test of devotion for you.\n\n",
    	"You have done well and passed this test. As a reward, you shall "+
    	"be granted the ability to train fully in the art of Spellcraft "+
    	"as you will have your entire soul to absorb this knowledge. "+
    	"Other gifts that have been granted to you shall be more powerful "+
    	"than they were before. Thank you for freeing me from this prison. "+
    	"We shall journey together once more, and you shall finally feel "+
        "complete.\n\n",
        "With that, the figure turns to face away from you and backs into "+
        "you. Your body absorbs the figure into it as it moves further and "+
        "further back into you. The last bit of the shadowy figure disappears "+
        "into your body and you feel absolutely complete, and a small bit more "+
    	"experienced.\n\n",
    	"You feel your sacred mandala vibrate rapidly.\n\n"});
    for (int i=0; i < sizeof(completed_messages); i++)
		set_alarm((10.0*itof(i)), 0.0, &tell_object(TP, completed_messages[i]));
    say(QCTNAME(TP)+" reaches out and grabs the glass globe that is "+
        "hovering in the centre of the chamber. Taking a firm hold on it "+
        "in one hand, "+HE+" throws it forcefully at the ground. As it hits "+
        "the ground, the glass globe shatters into pieces, releasing the "+
        "shadowy figure from inside of it. The shadowy figure places its "+
        "hand on "+QNAME(TP)+"'s shoulder for a brief moment. It turns "+
        "around and begins to walk backwards into "+QNAME(TP)+". The figure "+
        "seems to be absored right into "+QNAME(TP)+" completely.\n");
    
    globe = 0;

    TP->remove_prop(LIVE_I_PLACED_CLERIC_TRIANGLE);
    TP->remove_prop(LIVE_I_PLACED_CLERIC_CYLINDER);
    TP->remove_prop(LIVE_I_PLACED_CLERIC_SYMBOL);
    TP->remove_prop(LIVE_I_ON_CLERIC_GURU_QUEST);
    TP->set_bit(EC_GURU_GROUP,EC_GURU_BIT);
    TP->add_exp_quest(EC_GURU_EXP); 
    TP->command("save");
    
    setuid(); 
    seteuid(getuid());
    log_file("elemental_clerics/ec_guru_quest",
        capitalize(TP->query_real_name()) + " gets "+EC_GURU_EXP+
        " experience, " + ctime(time()) + ".\n");
    COUNCIL_LOG_BOOK->update_log_book(my_time() + 
        capitalize(TP->query_real_name()) + " has completed the guru "+
        "quest.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_break,"break");
}
