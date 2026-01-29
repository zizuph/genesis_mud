/*
 * Gem Garden of the Elemental Temple of Calia
 * 
 * Created by Jaacar, June 2016
 */

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <mail.h>
#include "defs.h"

inherit TEMPLE_ROOM_BASE;
inherit "/d/Sparkle/area/city/library/room/library_lib";

// Defines

// Prototypes
object arial;
string task, summary;
int question;

/*
 * Function:    my_time
 * Description: Returns the time format used for logs.
 */
public string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}

void
reset_room()
{
     if (!objectp(arial)) { 
         arial = clone_object(ELEMENTALIST_NPCS +"arial");
         arial->set_width_desc("lean");
         arial->set_height_desc("tall"); 
         arial->move_living("steps out from behind a some bushes", TO); 
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
    set_short("'Earths Beholden'");
    set_long("Outlined by marble walls on all sides and a transparent crystalline roof this is "
		+ "'Earths beholden' - the gem garden of the Elemental Temple. The floor and foundation "
		+ "is the same as elsewhere in the temple, however, three large rows have been cut into "
		+ "the floor and are home to some very bright bushes. A small amount of light streams "
		+ "in from the windows on the south wall. There is a small table with some "
		+ "garden tools near the western wall.\n");
	
	try_item( ({"windows"}),
		"Made from smoked glass the windows on the south wall would not be noticable "
		+ "to outsiders as they are part of the secluded garden within the temple "
		+ "proper and not the larger garden that surrounds the temple. Due to the smoked glass it is hard "
		+ "to tell the details on the other side.\n");
	
	try_item( ({"smoked glass", "glass"}),
		"The smoked glass allows a sombre light to filter in but it is not possible to make "
		+ "out the details of what lies on the other side.\n");
	
	try_item( ({"roof", "crystalline roof"}),
		" The roof is made from transparent crystalline. Sunlight shimmers through giving "
		+ "nourishment to the plants in the garden here.\n");

	try_item( ({"plants", "bushes" }),
		"The dark green bushes stand about seven to eight feet tall and are home to a host "
		+ "of massive broad leaves. Purple and bluish vines criss cross the branches and leaves. "
		+ "Several of the veined branches have smaller branches holding flower buds that droop "
		+ "heavily towards the ground. None of the buds are flowering though.\n");

	try_item( ({"leaves", "bush leaves"}),
		"The leaves are dark-green and flat. Oddly-looking veins run through the leaves.\n");
	
	try_item( ({"veins", "purple veins", "bluish veins"}),
		"The purple and bluish vines pulsate very slowly and appear to be crystalline in texture. "
		+ "They run through the bushes from top to bottom but appear to be somewhat thicker near. "
		+ " the roots.\n");

	try_item( ({"buds"}), 
		"What looks to be fruit or flower buds are essentially small drop-shaped bags of plant and "
		+ "blue vein. Whatever they contain must be heavy, because the biggest ones hang so low that "
		+ "they strain the branches they grow from.\n");

	try_item( ({"garden tools"}),
		"The usual watering cans, small shovels, rakes and other tools to keep the garden well tended.\n");
    
    try_item( ({"switch","small switch"}),"You notice a small switch on the underside of the "+
        "table. You might be able to switch it.\n");
	
	add_exit(ELEMENTALIST_TEMPLE + "lapidary", "southwest", "@@cannot_enter_restrict_resource_banned",1, "@@cannot_see_restrict_resource_banned");
	reset_room();	
}

int
do_switch(string str)
{
	int taskone, tasktwo, taskthree, taskfour;
	
	if (!str)
        return 0;
	
	if (parse_command(str, ({}),"[the] [small] 'switch'"))
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
	    
	    // If they haven't already completed the pool part of task four, nothing will happen.
	    if (taskfour < 3)
	    {
	    	write("Nothing happens.\n");
	        return 1;
	    }
	    
	    // If they've already completed a further part of task four, nothing will happen.
	    if (taskfour > 3)
	    {
	    	write("Nothing happens.\n");
	        return 1;
	    }
	    
	    // They are indeed a Seeker and have been assigned task four and have not
	    // yet completed it.
	    GUILD_MANAGER->set_can_do_wor_task_four(TP, 4);
	    write("When nobody is watching, you quickly switch the switch. An image "+
	        "of a small button quickly fills your mind. You notice the button is "+
	        "on the underside of a table. Standing next to the table, you recognize "+
	        "Jardeth. You feel compelled to find this button.\n");
	    return 1; 
	} 
	return 0;
}


public int
library_write_access()
{
	if (!GUILD_MANAGER->query_can_do_wor_task_three(TP))
	{
		notify_fail("What?\n");	
		return 0;
	}
	if (GUILD_MANAGER->query_can_do_wor_task_three(TP) > 3)
	{
		notify_fail("You have already completed this task.\n");
		return 0;
	}
	return 1;
}

public int
library_write(string str)
{
	string input, task_question;
    if (!library_write_access())
    {
        return 0;
    }
    task = "Task three";
    question = (GUILD_MANAGER->query_can_do_wor_task_three(TP));    
    setuid();
    seteuid(getuid());
    switch(question)
    {
    	case 1:
    		task_question="Define family for me and what it means to you.";
    		break;
    	case 2:
    		task_question="Why do we ask for this definition of family and "+
    		    "why is it so vital?";
    		break;
    	default:
    		task_question="There is a problem. Please inform the council.";
    		break;
    }
    write(task_question+"\n");
    clone_object(EDITOR_OBJECT)->edit(&done_writing(task,input));
    return 1;
}

public int
done_writing(string task, string summary, string input)
{
    if (!strlen(input))
    {
        library_write_abort_hook();
        return 0;
    }
    
    switch(question)
    {
    	case 1:
    		write("You finish your submission and hand it to Arial.\n"+
    		    "When you are ready, you can ask Arial for the next "+
    		    "question.\n");
    		GUILD_MANAGER->set_can_do_wor_task_three(TP,2);
    		GUILD_MANAGER->set_task_three_answer_one(TP, input);
    		return 1;
    		break;
    	case 2:
    		write("You finish your submission and hand it to Arial.\n"+
    		    "Arial nods at you.\nArial telepathically says to you: "+
    		    "You have answered all of my questions and completed my "+
    		    "task. Please inform the council that you have done so.\n");
    		string log_message = capitalize(TP->query_real_name()) + " has completed task 3.\n";
    		COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);    
    		GUILD_MANAGER->set_can_do_wor_task_three(TP,3);
    		GUILD_MANAGER->set_task_three_answer_two(TP, input);
    		return 1;
    		break;
    	default:
    		write("You finish your submission but there is a problem. "+
    		    "please notify the council.\n");
    		return 1;
    		break;
    }
}

public int
do_plant(string str)
{
	object invismandala;
	int task_status;
	
	invismandala=present("invismandala",TP);
    task_status = invismandala->query_task_status();
    
    // They are on the child mandala task and should plant the sporos seed
    if (invismandala && task_status == 9)
    {
    	present("Sporos crystalline seed",TP)->remove_object();
    	write("You plant the Sporos crystalline seed in Earths Beholden. It is ready "+
    	    "for you to pour the vial onto.\n");
    	say(QCTNAME(TP)+" plants something in Earths Beholden.\n");
    	invismandala->set_task_status(91);    		
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
    if (invismandala && task_status == 91)
    {
    	present("Sporos crystalline seed vial",TP)->remove_object();
    	write("You pour the contents of the vial onto the location you planted "+
    	    "the seed.\nThe vial disappears out of your hands.\nThe dirt begins "+
    	    "to move slightly and some type of gem rises out of it. You quickly "+
    	    "reach down and grab the gem, realizing quickly it is shaped like a "+
    	    "seed.\nArial telepathically says to you: You should take that seed "+
    	    "shaped gem seed to Tahla and ask her about it to continue.\n");
    	say(QCTNAME(TP)+" pours some kind of liquid out of a vial onto one of the "+
    	    "rows.\nThe dirt begins to move slightly and some type of gem rises "+
    	    "out of it. "+QCTNAME(TP)+" reaches down and grabs the gem.\n");
    	clone_object(ELEMENTALIST_OBJS+"sporos_seed_shaped_gem")->move(TP,1);
    	invismandala->set_task_status(10);    		
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
    init_genesis_library();
    add_action(library_write, "answer");
    add_action("do_pick", "pick");
    add_action(do_switch, "switch");
    add_action(do_plant,"plant");
    add_action(do_water,"water");
    add_action(do_water,"pour");    
}