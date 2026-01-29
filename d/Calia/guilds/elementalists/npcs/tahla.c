
/* 
 * This is the librarian for the Temple. 
 *   
 * Coded by Jaacar July 6th, 2016.
 * Added "Introduction" Worshipper task (aka task 1)
 */ 

inherit "/lib/trade";
inherit "/std/monster";
inherit "/d/Calia/std/remember";
inherit "/d/Calia/std/intro";
inherit "/lib/guild_support";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include "defs.h"

#define EC_RACIAL_SUBLOC "_elemental_guild_racial_subloc"

#define NUM sizeof(MONEY_TYPES)

#pragma save_binary

/*
 * Function:    my_time
 * Description: Returns the time format used for logs.
 */
public string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}

public string
aeria_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: In the "+
        "days of my youth I would dance and sing with the blessing of "+
        "my Lady Aeria. I carry her joy and wisdom every day.\n");
    return "";
}

public string
library_answer()
{
	if (TP->query_prop("_i_asked_about_elemental_library"))
	{
		command("eyeroll");
		command("point plaque");
		return "";
	}
	
    write(TO->query_The_name(TP)+" telepathically says to you: All of "+
        "the information about the library can be found on the plaque.\n");
    command("point plaque");
    TP->add_prop("_i_asked_about_elemental_library",1);
    return "";
}

public string
task_one_answer()
{
	int taskone;
	
	// If they aren't a Seeker, they won't get to ask about the task
	if (!(GUILD_MANAGER->query_is_seeker(TP)))
	{
		write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
        "you speak.\n");
        return "";
    }
    
    taskone = (GUILD_MANAGER->query_can_do_wor_task_one(TP));
    
    // If they haven't been assigned task one, they won't get to ask about the task
    if (!taskone)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
        "you speak.\n");
        return "";
    }
    
    // If they've already completed task one, they should get a different answer
    if (taskone == 7)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: You've already completed "+
    	    "my task.\n");
        return "";
    }
    
    // They are indeed a Seeker and have been assigned task one and have not
    // yet completed it. Now to figure out what question they are on and ask
    // the appropriate next question.
    
    switch(taskone)
    {
    	case 1:
    		// They are on the first question of six
    		write(TO->query_The_name(TP)+" telepathically says to you: I see you have been "+
    		    "asked to come and see me about my task. Very well then, let "+
    		    "us begin then.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: This is your introductory "+
    		    "task. I have five questions for you to answer. When you think you "+
    		    "know the answer to the question I am asking, please come and "+
    		    "ask me to verify it. (ask tahla answer <your answer>)\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: Here is your first question.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: What is the name of the "+
    		    "Lord of the Flames?\n");    
    		break;
    	case 2:
    		// They are on the second question of six
    		write(TO->query_The_name(TP)+" telepathically says to you: Just a reminder, when you "+
    		    "think you know the answer to the question I am asking, please come and "+
    		    "ask me to verify it. (ask tahla answer <your answer>)\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: Here is your second question.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: What is the name of the "+
    		    "Lady of the Winds?\n"); 
    		break;
    	case 3:
    		// They are on the third question of six
    		write(TO->query_The_name(TP)+" telepathically says to you: Just a reminder, when you "+
    		    "think you know the answer to the question I am asking, please come and "+
    		    "ask me to verify it. (ask tahla answer <your answer>)\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: Here is your third question.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: What is the name of the "+
    		    "Lord of the Seas?\n"); 
    		break;
    	case 4:
    		// They are on the fourth question of six
    		write(TO->query_The_name(TP)+" telepathically says to you: Just a reminder, when you "+
    		    "think you know the answer to the question I am asking, please come and "+
    		    "ask me to verify it. (ask tahla answer <your answer>)\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: Here is your fourth question.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: What is the name of the "+
    		    "Lady of the Earth?\n"); 
    		break;
        case 5:
        	// They are on the fifth question of six
        	write(TO->query_The_name(TP)+" telepathically says to you: Just a reminder, when you "+
    		    "think you know the answer to the question I am asking, please come and "+
    		    "ask me to verify it. (ask tahla answer <your answer>)\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: Here is your fifth question.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: What is the name of the "+
    		    "Ruler of Souls and Shadows?\n"); 
    		break;
    	case 6:
    		// They are on the fifth question of six
    		write(TO->query_The_name(TP)+" telepathically says to you: Just a reminder, when you "+
    		    "think you know the answer to the question I am asking, please come and "+
    		    "ask me to verify it. (ask tahla answer <your answer>)\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: Here is your final question. "+
    		    "Please answer using ONE WORD only.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: What are the Elementals greatest "+
    		    "doing?\n"); 
    		break;
    	default:
    		// Should never get here
    		write(TO->query_The_name(TP)+" telepathically says to you: Something has gone terribly "+
    		    "wrong. Please inform a member of the council that you have asked me "+
    		    "for your task but I cannot comply for some reason.\n"); 
    		break;
    }
    
	return "";
}

public string
task_one_first_response()
{
	int taskone;
	
	// If they aren't a Seeker, they won't get to answer the task
	if (!(GUILD_MANAGER->query_is_seeker(TP)))
	{
		write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
        "you speak.\n");
        return "";
    }
    
    taskone = (GUILD_MANAGER->query_can_do_wor_task_one(TP));
    
    // If they haven't been assigned task one, they won't get to answer the task
    if (!taskone)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
        "you speak.\n");
        return "";
    }
    
    // If they've already completed task one, they should get a different answer
    if (taskone == 7)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: You've already completed "+
    	    "my task.\n");
        return "";
    }
    
    // If they've already answered question one, they should get a different answer
    if (taskone != 1)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: That is not the correct "+
    	    "answer.\n");
        return "";
    }
    
    // They are indeed a Seeker and have been assigned task one and have not
    // yet completed it and they have given a correct answer. Time to let them
    // know and ask them the next question.
    
    write(TO->query_The_name(TP)+" telepathically says to you: That is the correct answer.\n");
    GUILD_MANAGER->set_can_do_wor_task_one(TP,2);
    write(TO->query_The_name(TP)+" telepathically says to you: Here is your second question.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: What is the name of the "+
    		    "Lady of the Winds?\n"); 
    
	return "";
}

public string
task_one_second_response()
{
	int taskone;
	
	// If they aren't a Seeker, they won't get to answer the task
	if (!(GUILD_MANAGER->query_is_seeker(TP)))
	{
		write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
        "you speak.\n");
        return "";
    }
    
    taskone = (GUILD_MANAGER->query_can_do_wor_task_one(TP));
    
    // If they haven't been assigned task one, they won't get to answer the task
    if (!taskone)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
        "you speak.\n");
        return "";
    }
    
    // If they've already completed task one, they should get a different answer
    if (taskone == 7)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: You've already completed "+
    	    "my task.\n");
        return "";
    }
    
    // If they've already answered question two, they should get a different answer
    if (taskone != 2)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: That is not the correct "+
    	    "answer.\n");
        return "";
    }
    
    // They are indeed a Seeker and have been assigned task one and have not
    // yet completed it and they have given a correct answer. Time to let them
    // know and ask them the next question.
    
    write(TO->query_The_name(TP)+" telepathically says to you: That is the correct answer.\n");
    GUILD_MANAGER->set_can_do_wor_task_one(TP,3);
    write(TO->query_The_name(TP)+" telepathically says to you: Here is your third question.\n");
    write(TO->query_The_name(TP)+" telepathically says to you: What is the name of the "+
        "Lord of the Seas?\n"); 
    
	return "";
}

public string
task_one_third_response()
{
	int taskone;
	
	// If they aren't a Seeker, they won't get to answer the task
	if (!(GUILD_MANAGER->query_is_seeker(TP)))
	{
		write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
        "you speak.\n");
        return "";
    }
    
    taskone = (GUILD_MANAGER->query_can_do_wor_task_one(TP));
    
    // If they haven't been assigned task one, they won't get to answer the task
    if (!taskone)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
        "you speak.\n");
        return "";
    }
    
    // If they've already completed task one, they should get a different answer
    if (taskone == 7)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: You've already completed "+
    	    "my task.\n");
        return "";
    }
    
    // If they've already answered question three, they should get a different answer
    if (taskone != 3)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: That is not the correct "+
    	    "answer.\n");
        return "";
    }
    
    // They are indeed a Seeker and have been assigned task one and have not
    // yet completed it and they have given a correct answer. Time to let them
    // know and ask them the next question.
    
    write(TO->query_The_name(TP)+" telepathically says to you: That is the correct answer.\n");
    GUILD_MANAGER->set_can_do_wor_task_one(TP,4);
    write(TO->query_The_name(TP)+" telepathically says to you: Here is your fourth question.\n");
    write(TO->query_The_name(TP)+" telepathically says to you: What is the name of the "+
        "Lady of the Earth?\n"); 
    
	return "";
}

public string
task_one_fourth_response()
{
	int taskone;
	
	// If they aren't a Seeker, they won't get to answer the task
	if (!(GUILD_MANAGER->query_is_seeker(TP)))
	{
		write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
        "you speak.\n");
        return "";
    }
    
    taskone = (GUILD_MANAGER->query_can_do_wor_task_one(TP));
    
    // If they haven't been assigned task one, they won't get to answer the task
    if (!taskone)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
        "you speak.\n");
        return "";
    }
    
    // If they've already completed task one, they should get a different answer
    if (taskone == 7)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: You've already completed "+
    	    "my task.\n");
        return "";
    }
    
    // If they've already answered question four, they should get a different answer
    if (taskone != 4)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: That is not the correct "+
    	    "answer.\n");
        return "";
    }
    
    // They are indeed a Seeker and have been assigned task one and have not
    // yet completed it and they have given a correct answer. Time to let them
    // know and ask them the next question.
    
    write(TO->query_The_name(TP)+" telepathically says to you: That is the correct answer.\n");
    GUILD_MANAGER->set_can_do_wor_task_one(TP,5);
    write(TO->query_The_name(TP)+" telepathically says to you: Here is your fifth question.\n");
    write(TO->query_The_name(TP)+" telepathically says to you: What is the name of the "+
    		    "Ruler of Souls and Shadows?\n"); 
    
	return "";
}

public string
task_one_fifth_response()
{
	int taskone;
	
	// If they aren't a Seeker, they won't get to answer the task
	if (!(GUILD_MANAGER->query_is_seeker(TP)))
	{
		write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
        "you speak.\n");
        return "";
    }
    
    taskone = (GUILD_MANAGER->query_can_do_wor_task_one(TP));
    
    // If they haven't been assigned task one, they won't get to answer the task
    if (!taskone)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
        "you speak.\n");
        return "";
    }
    
    // If they've already completed task one, they should get a different answer
    if (taskone == 7)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: You've already completed "+
    	    "my task.\n");
        return "";
    }
    
    // If they've already answered question four, they should get a different answer
    if (taskone != 5)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: That is not the correct "+
    	    "answer.\n");
        return "";
    }
    
    // They are indeed a Seeker and have been assigned task one and have not
    // yet completed it and they have given a correct answer. Time to let them
    // know and ask them the next question.
    
    write(TO->query_The_name(TP)+" telepathically says to you: That is the correct answer.\n");
    GUILD_MANAGER->set_can_do_wor_task_one(TP,6);
    write(TO->query_The_name(TP)+" telepathically says to you: Here is your final question.\n");
    write(TO->query_The_name(TP)+" telepathically says to you: What is the Elementals greatest "+
        "doing?\n"); 
    
	return "";
}

public string
task_one_sixth_response()
{
	int taskone;
	
	// If they aren't a Seeker, they won't get to answer the task
	if (!(GUILD_MANAGER->query_is_seeker(TP)))
	{
		write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
        "you speak.\n");
        return "";
    }
    
    taskone = (GUILD_MANAGER->query_can_do_wor_task_one(TP));
    
    // If they haven't been assigned task one, they won't get to answer the task
    if (!taskone)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
        "you speak.\n");
        return "";
    }
    
    // If they've already completed task one, they should get a different answer
    if (taskone == 7)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: You've already completed "+
    	    "my task.\n");
        return "";
    }
    
    // If they've already answered question six, they should get a different answer
    if (taskone != 6)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: That is not the correct "+
    	    "answer.\n");
        return "";
    }
    
    // They are indeed a Seeker and have been assigned task one and have not
    // yet completed it and they have given a correct answer. Time to let them
    // know and tell them they are done and should notify the council.
    
    write(TO->query_The_name(TP)+" telepathically says to you: That is the correct answer.\n");
    GUILD_MANAGER->set_can_do_wor_task_one(TP,7);
    write(TO->query_The_name(TP)+" telepathically says to you: You have successfully answered "+
        "all of my questions and completed my task. Please inform the council that you have "+
        "done so.\n");
    string log_message = capitalize(TP->query_real_name()) + " has completed task 1.\n";
    COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
	return "";
}

public string
sporos_inquiry_response()
{
	object invismandala;
	int task_status;
	
	// If they aren't a Child Cleric, they won't get to answer the task	
	if (!(GUILD_MANAGER->query_is_child_cleric(TP)))
	{
		if (!(TP->query_wiz_level()))
		{
			write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
                "you speak.\n");
            return "";
        }
    }
    
    // If they already have their completed Mandala they get a different answer
    if (present("_elemental_guild_mandala",TP))
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: The Sporos is the seed "+
    	    "for your Sacred Mandala, which you already have.\n");
        return "";
    }
    
    // If they don't already have the invisible mandala object, tell them what it
    // is and direct them to Jardeth
    if (!(present("invismandala",TP)))
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: The Sporos is the seed "+
    	    "for your Sacred Mandala. In order to construct your Sacred Mandala, you shall "+
    	    "first have to get a Sporos. There are books here in the library about the "+
    	    "Sporos and Sacred Mandala, should you wish to read them. Begin your journey "+
    	    "towards this end by visiting Jardeth in the herb garden and asking him about "+
    	    "the Sporos.\n");
        return "";
    }
    
    // If they already have the invisible mandala object, find out where they are
    // in the task and point them in the proper direction
    if (present("invismandala",TP))
    {
    	invismandala=present("invismandala",TP);
    	task_status = invismandala->query_task_status();
    	switch(task_status)
    	{
    		//  0 - Just started the task, needs to pray to the Five in Obelisk Garden
			//  1 - Needs to rub dirt on Gu Obelisk
			//  2 - Needs to pour water on Diabrecho Obelisk
			//  3 - Needs to breathe on Aeria Obelisk
			//  4 - Needs to ignite Pyros Obelisk
			//  5 - Needs to stab hand with Ceremonial Dagger
    		case 0-5:
    			write(TO->query_The_name(TP)+" telepathically says to you: The Sporos is the seed "+
		    	    "for your Sacred Mandala. In order to construct your Sacred Mandala, you shall "+
		    	    "first have to get a Sporos. Begin your journey towards this end by visiting "+
		    	    "the Obelisk Garden near the cliff above the Temple. Once there, <pray to the "+
		    	    "Five>.\n");
		    	return "";
		    	break;
		    //  6 - Needs to talk to Jardeth about Seed Pod
    		case 6:
    			write(TO->query_The_name(TP)+" telepathically says to you: I see you have a Sporos "+
    			    "pod. You should take that to Jardeth and ask him about it.\n");
		    	return "";
    			break;
    		//  7 - Needs to plant sporos seed in herb garden and water with vial	
    		case 7:
    			write(TO->query_The_name(TP)+" telepathically says to you: You should plant that "+
    			    "seed in the herb garden. Once you have done so, you should pour the vial that "+
    			    "Jardeth gave you on it.\n");
	    		return "";
    			break;
    		//  71 - Planted the sporos seed and needs to water with vial	
    		case 71:
    			write(TO->query_The_name(TP)+" telepathically says to you: You should pour the vial that "+
    				"Jardeth gave you on to the seed you planted.\n");
	    		return "";
    			break;
    		//  8 - Needs to talk to Arial about Crystalline Seed (or Sporos)
    		case 8:
    			write(TO->query_The_name(TP)+" telepathically says to you: You should take that crystalline "+
	    		    "seed to Arial and ask her about it to continue.\n");
    			return "";
    			break;
    		//  9 - Needs to plant crystalline seed in Earths Behold and pour vial on it
    		case 9:
    			write(TO->query_The_name(TP)+" telepathically says to you: You should take that crystalline "+
	    		    "seed to Arial and ask her about it to continue.\n");
    			return "";
    			break;
    		//  91 - Planted crystalline seed and needs to pour vial on it
    		case 91:
    			write(TO->query_The_name(TP)+" telepathically says to you: You should take that vial that "+
	    		    "Arial gave to you and pour it on the crystalline seed you planted in Earths Beholden.\n");
	    		return "";
    			break;
    		// 10 - Needs to talk to Tahla about Seed Gem (or Sporos)
    		case 10:
    			write(TO->query_The_name(TP)+" telepathically says to you: I see you have come to me with "+
    			    "the Sporos seed shaped gem. You are well on your way to having your completed Sporos. "+
    			    "The Sporos is the heart or seed of the Sacred Mandala. It represents the place from "+
    			    "which all things begin. To continue, you should speak to Tiashe in the Refectory.\n");
    			invismandala->set_task_status(11);
	    		return "";
    			break;
    		// 11 - Needs to prepare powder for Tiashe
    		case 11:
    			write(TO->query_The_name(TP)+" telepathically says to you: You should take that seed shaped gem "+
	    		    "to Tiashe and ask her about it to continue.\n");
	    		return "";
    			break;
    		// 12 - Needs to sprinkle powder on Seed Gem
    		case 12:
    			write(TO->query_The_name(TP)+" telepathically says to you: You should take that seed shaped gem "+
	    		    "to Tiashe and ask her about it to continue.\n");
	    		return "";
    			break;
    		// 13 - Needs to talk to Sehis about Seed Gem (or Sporos or Blessing)
    		case 13:
    			write(TO->query_The_name(TP)+" telepathically says to you: You should take that seed shaped gem "+
	    		    "to Sehis and ask her about it to continue.\n");
	    		return "";
    			break;
    		// Unknown or invalid value
    		default:
    			write(TO->query_The_name(TP)+" telepathically says to you: There seems to"+
    			    "be a problem. Please report that you are having issues with your "+
    			    "Sporos to the guildmaster.\n");
		    	return "";
    			break;
    	}    	
    }
    
    write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
        "you speak.\n");
	return "";
}

/* 
 * Function name: intro_hook(object pl)
 * Arguments: object pl: the player who has introduced. 
 * Desccription: This function is called in an npc that you want to intro 
 *               after a player has introduced himself. 
 */ 
public void
intro_hook(object pl) 
{
    if (objectp(pl) && present(pl, environment(this_object())))
    {
    	TO->command("exa cloak");
    	TO->command("clturn "+OB_NAME(pl));
        this_object()->command("introduce me to " + OB_NAME(pl));
    }
         
}

public void
arm_me()
{
	clone_object(ELEMENTALIST_OBJS+"cloak")->move(TO,1);
	TO->command("wear cloak");
	TO->command("clraise");
	clone_object(ELEMENTALIST_OBJS+"alb")->move(TO,1);
	TO->command("wear alb");
	clone_object(ELEMENTALIST_OBJS+"power_tool_dagger")->move(TO,1);
	TO->command("dsheathe");
	clone_object(ELEMENTALIST_OBJS+"power_tool_wand")->move(TO,1);
	TO->command("whang");
	clone_object(ELEMENTALIST_OBJS+"air_staff")->move(TO,1);
	TO->command("wield quarterstaff");
	clone_object(ELEMENTALIST_OBJS+"air_mandala")->move(TO,1);
	TO->command("clasp mandala");
}

void
create_monster()
{
    set_name("Tahla");
    add_name("tahla");
    set_adj(({"captivating","crystalline-cloaked"}));
    set_title("Xenos-Whisperwind, Master Luminary of the Elementals, "+
        "Thundering Essence of Storms"); 
    set_race_name("elf");
    set_living_name("tahla");
    set_gender(G_FEMALE);
    set_stats(({300,300,300,300,300,300}));
    
    set_base_stat(SS_OCCUP, 300);
    set_base_stat(SS_LAYMAN, 300);
    set_appearance_offset(-50);
    set_width_desc("lean");
    set_height_desc("tall");
    set_skill(SS_DEFENCE,100);
    add_prop(LIVE_I_ALWAYSKNOWN,1);
    add_prop("_npc_primary_element","air");
        
    clone_object(EC_OCC_SHADOW)->shadow_me(TO,
        GUILD_EC_TYPE, "cleric", GUILD_EC_NAME, "");
    clone_object(EC_LAY_SHADOW)->shadow_me(TO,
        "layman", "cleric", GUILD_EC_NAME, "");
    clone_object(EC_RACE_SHADOW)->shadow_me(TO, "race", 
        "cleric", GUILD_EC_NAME, "");
    TP->add_subloc(EC_RACIAL_SUBLOC, TO);
    TO->arm_me();
    default_config_trade();

    set_alignment(1200);
    set_intro_delay(1);
    set_act_time(60);
    add_act("clasp mandala");
    add_act("clbow");
    add_act("clshake dirt");
    add_act("clpull");
    add_act("emote chews thoughtfully on her quill, while double-checking "+
        "the scrolls on the shelves.");

    set_default_answer(VBFC_ME("default_answer"));

    add_ask(({"aeria","lady aeria","winds","air"}),&aeria_answer());
    add_ask(({"scrolls","scroll","books","book","library"}),&library_answer());
    add_ask(({"task one","one","introduction task","introduction","first task",
    	"task 1","1st task","1","task"}),&task_one_answer());
    add_ask(({"answer pyros","answer Pyros","answer lord pyros","answer Lord Pyros"}),
    	&task_one_first_response());
    add_ask(({"answer aeria","answer Aeria","answer lady aeria","answer Lady Aeria"}),
        &task_one_second_response());
    add_ask(({"answer diabrecho","answer Diabrecho","answer lord diabrecho","answer Lord Diabrecho"}),
        &task_one_third_response());
    add_ask(({"answer gu","answer Gu","answer lady gu","answer Lady Gu"}),&task_one_fourth_response());
    add_ask(({"answer psuchae","answer Psuchae"}),&task_one_fifth_response());
    add_ask(({"answer creation","answer world","answer genesis","answer everything","answer life",
    	"answer Creation","answer World","answer Genesis","answer Everything","answer Life"}),
    	&task_one_sixth_response());
    add_ask(({"sporos","Sporos","Sporos seed","sporos seed",
    	"sporos seed shaped gem","Sporos seed shaped gem",
    	"sporos gem","gem","seed"}),&sporos_inquiry_response());

}

public string
default_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
        "you speak.\n");
    return "";
}

void
init_living()
{
    if (TP->query_guild_name_occ() == GUILD_EC_NAME)
		TP->add_introduced(query_real_name());
    ::init_living();
    add_action("do_buy","buy");
}

int
do_buy(string str)
{
    object item;
    string str2,str3;
    int *arr, price, num,iprice;
    
    if (!str)
    {
        notify_fail("Buy what? Read the sign perhaps?\n");
        return 0;
    }
    
    switch(str)
    {
        case "gloves":
            item = clone_object("/d/Calia/sea/objects/herb_gloves");
            iprice = 24;
            break;
        case "herb gloves":
            item = clone_object("/d/Calia/sea/objects/herb_gloves");
            iprice = 24;
            break;
        case "ingot":
            item = clone_object("/d/Calia/sea/objects/corpse_cleaner");
            iprice = 4000;
            break;
        case "silver ingot":
            item = clone_object("/d/Calia/sea/objects/corpse_cleaner");
            iprice = 4000;
            break;
        case "componentpouch":
            item = clone_object("/d/Calia/sea/objects/herbpouch");
            iprice = 24;
            break;
        case "component pouch":
            item = clone_object("/d/Calia/sea/objects/herbpouch");
            iprice = 24;
            break;
        case "herbpouch":
            item = clone_object("/d/Calia/sea/objects/herbpouch");
            iprice = 24;
            break;
        case "herb pouch":
            item = clone_object("/d/Calia/sea/objects/herbpouch");
            iprice = 24;
            break;
        case "pouch":
            item = clone_object("/d/Calia/sea/objects/herbpouch");
            iprice = 24;
            break;
        case "herbjar":
            item = clone_object("/d/Gondor/common/guild/obj/herbjar");
            iprice = 24;
            break;
        case "herb jar":
            item = clone_object("/d/Gondor/common/guild/obj/herbjar");
            iprice = 24;
            break;
        case "jar":
            item = clone_object("/d/Gondor/common/guild/obj/herbjar");
            iprice = 24;
            break;
        case "sheath":
            item = clone_object(ELEMENTALIST_OBJS+"arm_sheath");
            iprice = 450;
            break;
        case "sheathe":
            item = clone_object(ELEMENTALIST_OBJS+"arm_sheath");
            iprice = 450;
            break;
        case "lantern":
		case "lamp":
            item = clone_object(ELEMENTALIST_OBJS+"sturdy_lantern");
            iprice = 201;
            break;
	    case "oil":
		case "flask of oil":
		case "lantern-oil":
		case "lantern oil":
		case "lamp-oil":
		case "lamp oil":
            item = clone_object(ELEMENTALIST_OBJS+"large_oil_flask");
            iprice = 173;
            break;

        default: 
            NF("I don't have any items named "+str+".\n");
            return 0;
    }
    price = iprice;
    if (sizeof(arr = pay(price, this_player(), str2, 0, 0, str3)) == 1)
       return 0;  /* pay() handles notify_fail() call */
    write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM-1)))
       write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
    write("You get a "+item->short()+".\n");
    say(QCTNAME(TP)+" gets a "+item->short()+".\n");
    if(item->move(TP))
    {
        write("Its too heavy, and you drop it.\n");
        item->move(environment(TP));
    }
    return 1;
}