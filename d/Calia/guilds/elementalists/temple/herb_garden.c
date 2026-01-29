/*
 * Herb Garden of the Elemental Temple of Calia
 * 
 * Created by Jaacar, June 2016
 */

#pragma strict_types

#include <macros.h>
#include "defs.h"

inherit TEMPLE_ROOM_BASE;

// Defines

// Prototypes
object jardeth;

void
reset_room()
{
     if (!objectp(jardeth)) { 
         jardeth = clone_object(ELEMENTALIST_NPCS +"jardeth");
         jardeth->set_width_desc("lean");
         jardeth->set_height_desc("tall"); 
         jardeth->move_living("steps out from behind a some bushes", TO); 
     } 
}

public int
query_valid_kalliergo_room()
{
    return 1;
}

public int
do_pick(string str)
{
    write("You dare not pick anything for fear of angering Lady Gu.\n");
    return 1;
}

public void
create_temple_room()
{
    set_short("Herb garden");
    set_long("Outlined by marble walls on all sides and a transparent crystalline roof this is "
		+ "the herb garden of the Elemental Temple. The floor and foundation "
		+ "is the same as elsewhere in the temple, however, three large rows have been cut into "
		+ "the floor and are home to various plants and bushes. A small amount of light streams "
		+ "in from the windows on the south wall. There is a small table with some "
		+ "garden tools near the western wall.\n\n");
	
	try_item( ({"windows"}),
		"Made from smoked glass the windows on the south wall would not be noticable "
		+ "to outsiders as they are part of the secluded garden within the temple "
		+ "proper and not the larger garden that surrounds the temple. Due to the smoked glass it is hard "
		+ "to tell the details on the other side.\n");
	
	try_item( ({"smoked glass", "glass"}),
		"The smoked glass allows a sombre light to filter in but it is not possible to make "
		+ "out the details of what lies on the other side. \n");
	
	try_item( ({"roof", "crystalline roof"}),
		" The roof is made from transparent crystalline. Sunlight shimmers through giving "
		+ "nourishment to the plants in the garden here. \n");

	try_item( ({"plants", "bushes" }),
		"There are various plants and bushes growing here. All of the different herbs "
		+ "that grown here are used by the herbalist shop to the southeast.\n");

	try_item( ({"garden tools"}),
		"The usual watering cans, small shovels, rakes and other tools to keep the garden well tended .\n");
		
	try_item( ({"button","small button"}),"You notice a small button on the underside of the "+
        "table. You might be able to press it.\n");
	
	add_exit(ELEMENTALIST_TEMPLE + "herbalist", "southeast","@@cannot_enter_restrict_resource_banned", 1, "@@cannot_see_restrict_resource_banned");
	add_exit(ELEMENTALIST_TEMPLE + "refectory", "west");
	reset_room();	
}

int
do_press(string str)
{
	int taskone, tasktwo, taskthree, taskfour;
	
	if (!str)
        return 0;
	
	if (parse_command(str, ({}),"[the] [small] 'button'"))
    {
		// If they aren't a Seeker, nothing will happen.
		if (!(GUILD_MANAGER->query_is_seeker(TP)))
		{
			write("Nothing happens.\n");
	        return 1;
	    }
	    taskone = (GUILD_MANAGER->query_can_do_wor_task_one(TP));
	    tasktwo = (GUILD_MANAGER->query_can_do_wor_task_two(TP));
	    taskthree = (GUILD_MANAGER->query_can_do_wor_task_three(TP));
	    taskfour = (GUILD_MANAGER->query_can_do_wor_task_four(TP));
	    
	    // If they haven't been assigned task one, nothing will happen.
	    if (!taskone)
	    {
	    	write("Nothing happens.\n");
	        return 1;
	    }
	    
	    // If they haven't been assigned task two, nothing will happen.
	    if (!tasktwo)
	    {
	    	write("Nothing happens.\n");
	        return 1;
	    }
	    
	    // If they haven't been assigned task three, nothing will happen.
	    if (!taskthree)
	    {
	    	write("Nothing happens.\n");
	        return 1;
	    }
	    
	    // If they haven't been assigned task four, nothing will happen.
	    if (!taskfour)
	    {
	    	write("Nothing happens.\n");
	        return 1;
	    }
	    
	    /// If they haven't already completed the pool part of task four, nothing will happen.
	    if (taskfour < 4)
	    {
	    	write("Nothing happens.\n");
	        return 1;
	    }
	    
	    // If they've already completed a further part of task four, nothing will happen.
	    if (taskfour > 4)
	    {
	    	write("Nothing happens.\n");
	        return 1;
	    }
	    
	    // They are indeed a Seeker and have been assigned task four and have not
	    // yet completed it.
	    GUILD_MANAGER->set_can_do_wor_task_four(TP, 5);
	    write("Jardeth smiles knowingly at you as you quickly press the button. An image "+
	        "of a hand reaching out and touching a plaque quickly fills your mind. You "+
	        "notice the plaque is in a room with many statues. You feel "+
	        "compelled to find this plaque and touch it.\n");
	    return 1; 
	} 
	return 0;
}

public int
do_plant(string str)
{
	object invismandala;
	int task_status;
	
	invismandala=present("invismandala",TP);
    task_status = invismandala->query_task_status();
    
    // They are on the child mandala task and should plant the sporos seed
    if (invismandala && task_status == 7)
    {
    	present("sporos seed",TP)->remove_object();
    	write("You plant the Sporos seed in the herb garden. It is ready for you "+
    	    "to pour the vial onto.\n");
    	say(QCTNAME(TP)+" plants something in the herb garden.\n");
    	invismandala->set_task_status(71);    		
    	return 1;
    }
    
    // Check to see if they are a member
    if (!IS_MEMBER(TP))
    {
    	NF("You wouldn't dare attempt to plant anything here as you "+
    	    "don't reside here.\n");
    	return 0;
    }
    
    // Fill in the planting task stuff here 
    write("You aren't quite sure you are authorized to plant anything "+
        "here so you decide not to.\n");
    return 1;
}

public int
do_water(string str)
{
	object invismandala;
	int task_status;
	
	invismandala=present("invismandala",TP);
    task_status = invismandala->query_task_status();
    
	// They are on the child mandala task and should plant the sporos seed
    if (invismandala && task_status == 71)
    {
    	present("Sporos seed vial",TP)->remove_object();
    	write("You pour the contents of the vial onto the location you planted "+
    	    "the seed.\nThe vial disappears out of your hands.\nThe dirt begins "+
    	    "to move slightly and some type of crystalline object rises out of "+
    	    "it. You reach down and grab the object, realizing quickly it is "+
    	    "a crystalline seed.\nJardeth smiles at you.\nJardeth telepathically "+
    	    "says to you: You should take that crystalline seed to Arial and "+
    	    "ask her about it to continue.\n");
    	say(QCTNAME(TP)+" pours some kind of liquid out of a vial onto the herb "+
    	    "garden.\nThe dirt begins to move slightly and some type of crystalline "+
    	    "object rises out of it. "+QCTNAME(TP)+" reaches down and grabs the "+
    	    "object.\n");
    	clone_object(ELEMENTALIST_OBJS+"sporos_crystalline_seed")->move(TP,1);
    	invismandala->set_task_status(8);    		
    	return 1;
    }
    
    // Check to see if they are a member
    if (!IS_MEMBER(TP))
    {
    	NF("You wouldn't dare attempt to "+query_verb()+" anything here as you "+
    	    "don't reside here.\n");
    	return 0;
    }
    
    // Fill in the planting task stuff here 
    write("You aren't quite sure you are authorized to "+query_verb()+" anything "+
        "here so you decide not to.\n");
    return 1;
}

public void
init()
{
    ::init();
    add_action("do_pick", "pick");
    add_action(do_press,"press");
    add_action(do_plant,"plant");
    add_action(do_water,"water");
    add_action(do_water,"pour");
}