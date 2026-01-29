
/* 
 * This is the herbalist for the Temple. 
 *   
 * Coded by Jaacar July 6th, 2016.
 */ 

#pragma save_binary
#pragma strict_types

inherit "/std/monster";
inherit "/d/Calia/std/remember";
inherit "/d/Calia/std/intro";
inherit "/lib/guild_support";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include <language.h>

#include "defs.h"

#define EC_RACIAL_SUBLOC "_elemental_guild_racial_subloc"

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
task_four_answer()
{
	int taskone, tasktwo, taskthree, taskfour;
	
	// If they aren't a Seeker, they won't get to ask about the task
	if (!(GUILD_MANAGER->query_is_seeker(TP)))
	{
		write(TO->query_The_name(TP)+" telepathically says to you: I do "+
			"not know of what you speak.\n");
        return "";
    }
    taskone = (GUILD_MANAGER->query_can_do_wor_task_one(TP));
    tasktwo = (GUILD_MANAGER->query_can_do_wor_task_two(TP));
    taskthree = (GUILD_MANAGER->query_can_do_wor_task_three(TP));
    taskfour = (GUILD_MANAGER->query_can_do_wor_task_four(TP));
    
    // If they haven't been assigned task one, they won't get to ask about 
    // the task
    if (!taskone)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: I do "+
    		"not know of what you speak.\n");
        return "";
    }
    
    // If they haven't been assigned task two, they won't get to ask about 
    // the task
    if (!tasktwo)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: I do "+
    		"not know of what you speak.\n");
        return "";
    }
    
    // If they haven't been assigned task three, they won't get to ask 
    // about the task
    if (!taskthree)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: I do "+
    		"not know of what you speak.\n");
        return "";
    }
    
    // If they haven't been assigned task four, they won't get to ask 
    // about the task
    if (!taskfour)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: I do "+
    		"not know of what you speak.\n");
        return "";
    }
    
    // If they've already completed task four, they should get a 
    // different answer
    if (taskfour == 6)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: "+
    		"You've already completed my task.\n");
        return "";
    }
    
    // They are indeed a Seeker and have been assigned task four and have not
    // yet completed it. 
    
    write(TO->query_The_name(TP)+" telepathically says to you: I see "+
    	"you have been "+
        "asked to come and see me about my task. Very well then, let "+
    	"us begin then.\n");
    write(TO->query_The_name(TP)+" telepathically says to you: "+
    	"This is your most "+
    	"important task. I want you to go to the place where the "+
    	"waters lie in a "+
    	"semi-circular fashion. There you will find a small button. "+
    	"You shall go "+
    	"there and press the button. When you have finished completing "+
    	"all of the "+
    	"steps you will receive, come back to me and tell me the the "+
    	"answer I am "+
    	"seeking. (ask jardeth answer <your answer>)\n");
       
	return "";
}

public string
task_four_response()
{
	int taskone, tasktwo, taskthree, taskfour, taskfive, tasksix;
	
	// If they aren't a Seeker, they won't get to answer the task
	if (!(GUILD_MANAGER->query_is_seeker(TP)))
	{
		write(TO->query_The_name(TP)+" telepathically says to you: "+
			"I do not know of what you speak.\n");
        return "";
    }
    
    taskone = (GUILD_MANAGER->query_can_do_wor_task_one(TP));
    tasktwo = (GUILD_MANAGER->query_can_do_wor_task_two(TP));
    taskthree = (GUILD_MANAGER->query_can_do_wor_task_three(TP));
    taskfour = (GUILD_MANAGER->query_can_do_wor_task_four(TP));
    taskfive = (GUILD_MANAGER->query_can_do_ec_task_five(TP));
    tasksix = (GUILD_MANAGER->query_can_do_ec_task_six(TP));
    
    // If they haven't been assigned task one, they won't get to ask about 
    // the task
    if (!taskone)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: I "+
    		"do not know of what you speak.\n");
        return "";
    }
    
    // If they haven't been assigned task two, they won't get to ask about 
    // the task
    if (!tasktwo)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: I "+
    		"do not know of what you speak.\n");
        return "";
    }
    
    // If they haven't been assigned task three, they won't get to ask 
    // about the task
    if (!taskthree)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: I do "+
    		"not know of what you speak.\n");
        return "";
    }
    
    // If they haven't been assigned task four, they won't get to ask 
    // about the task
    if (!taskfour)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: I "+
    		"do not know of what you speak.\n");
        return "";
    }
    
    // If they've already completed task one, they should get a 
    // different answer
    if (taskfour == 2)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: "+
    		"You've already completed my task.\n");
        return "";
    }
    
    // They are indeed a Seeker and have been assigned task four and have not
    // yet completed it and they have given a correct answer. Time to let them
    // know and tell them they are done and should notify the council.
    
    write(TO->query_The_name(TP)+" telepathically says to you: That is "+
    	"the correct answer.\n");
    GUILD_MANAGER->set_can_do_wor_task_four(TP,2);
    write(TO->query_The_name(TP)+" telepathically says to you: You have "+
    	"successfully found "+
        "the answer I was looking for and completed my task. There is a "+
        "scroll in the library "+
        "that you now have access to entitled 'Secrecy'. Please go study "+
        "this scroll. When you "+
        "feel you have gained all the knowledge that it has to give, "+
        "please inform the council "+
        "that you have done so.\n");
    string log_message = capitalize(TP->query_real_name()) + 
    	" has completed task 4.\n";
    COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
    
	return "";
}

public string
herbs_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: Herbs are "+
        "a gift born of Lady Gu, and like all things, they have a "+
        "deeply powerful spiritual energy.\n");
    return "";
}

public string
energy_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: You can "+
        "harness the spiritual energy of an herb through the ritual "+
        "chamber and use of your gifts.\n");
    return "";
}

public string
gu_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: I humbly "+
    "serve Lady Gu in caring for the earth.\n");
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
			write(TO->query_The_name(TP)+" telepathically says to you: "+
				"I do not know of what you speak.\n");
            return "";
        }
    }
    
    // If they already have their completed Mandala they get a different 
    // answer
    if (present("_elemental_guild_mandala",TP))
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: The "+
    		"Sporos is the seed "+
    	    "for your Sacred Mandala, which you already have.\n");
        return "";
    }
    
    // If they don't already have the invisible mandala object, tell them 
    // what it is, give them the invis object and direct them to the 
    // obelisk garden
    if (!(present("invismandala",TP)))
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: The "+
    		"Sporos is the seed "+
    	    "for your Sacred Mandala. In order to construct your Sacred "+
    	    "Mandala, you shall "+
    	    "first have to get a Sporos. I believe there are books "+
    	    "explaining about the "+
    	    "Sporos and Sacred Mandala in the library, should you wish "+
    	    "to read them. "+
    	    "Begin your journey towards this end by visiting the "+
    	    "Obelisk Garden near "+
    	    "the cliff above the Temple. Once there, <pray to the Five>.\n");
    	invismandala=clone_object(ELEMENTALIST_OBJS+
    		"child_mandala_invis_object");
    	invismandala->move(TP,1);
        return "";
    }
    
    // If they already have the invisible mandala object, find out where 
    // they are in the task and point them in the proper direction
    if (present("invismandala",TP))
    {
    	invismandala=present("invismandala",TP);
    	task_status = invismandala->query_task_status();
    	switch(task_status)
    	{
    		//  0 - Just started the task, needs to pray to the Five 
    		//      in Obelisk Garden
			//  1 - Needs to rub dirt on Gu Obelisk
			//  2 - Needs to pour water on Diabrecho Obelisk
			//  3 - Needs to breathe on Aeria Obelisk
			//  4 - Needs to ignite Pyros Obelisk
			//  5 - Needs to stab hand with Ceremonial Dagger
    		case 0-5:
    			write(TO->query_The_name(TP)+" telepathically says to you: "+
    				"The Sporos is the seed "+
		    	    "for your Sacred Mandala. In order to construct your "+
		    	    "Sacred Mandala, you shall "+
		    	    "first have to get a Sporos. I believe there are "+
		    	    "books explaining about the "+
    	            "Sporos and Sacred Mandala in the library, should "+
    	            "you wish to read them. Begin "+
    	            "your journey towards this end by visiting the "+
    	            "Obelisk Garden near the cliff "+
    	            "above the Temple. Once there, <pray to the Five>.\n");
		    	return "";
		    	break;
		    //  6 - Needs to talk to Jardeth about Seed Pod
    		case 6:
    			write(TO->query_The_name(TP)+" telepathically says to "+
    				"you: I see you have returned "+
    			    "from the Obelisk Garden with your Sporos pod. If "+
    			    "you would be so kind as to "+
    			    "hand that to me, I shall see what I can do "+
    			    "about opening that for you.\n");
    			write("You hand the Sporos pod to Jardeth.\n");
    			present("Sporos pod",TP)->remove_object();
    			say(QCTNAME(TP)+" hands something to "+QTNAME(TO)+".\n");
    			write(TO->query_The_name(TP)+" clasps the Sporos pod "+
    				"in his hands and closes his "+
    			    "eyes briefly. He takes a tool from the table "+
    			    "and gently prys the pod open, "+
    			    "revealing a small seed. He puts the tool back on "+
    			    "the table.\n");
    			say(QCTNAME(TO)+" clasps something in his hands and "+
    				"closes his eyes briefly. He "+
    			    "takes a tool from the table and gently prys "+
    			    "the object open, revealing a "+
    			    "small seed. He puts the tool back on the table.\n");
    			clone_object(ELEMENTALIST_OBJS+"sporos_seed")->move(TP,1);
    			write(TO->query_The_name(TP)+" hands you the seed.\n");
    			say(QCTNAME(TO)+" hands the seed to "+QTNAME(TO)+".\n");
    			write(TO->query_The_name(TP)+" telepathically says "+
    				"to you: You should now plant that "+
    			    "seed here in the herb garden. Once you have "+
    			    "done so, you should pour this vial "+
    			    "on it.\n");
    			clone_object(ELEMENTALIST_OBJS+"sporos_seed_vial")->move(TP,1);
    			write(TO->query_The_name(TP)+" hands you a vial.\n");
    			say(QCTNAME(TO)+" hands a vial to "+QTNAME(TO)+".\n");
    			invismandala->set_task_status(7);
		    	return "";
    			break;
    		//  7 - Needs to plant sporos seed in herb garden and water 
    		//       with vial	
    		case 7:
    			write(TO->query_The_name(TP)+" telepathically says to you: "+
    				"You should now plant that "+
    			    "seed here in the herb garden. Once you have done so, "+
    			    "you should pour the vial I gave "+
    			    "you on it.\n");
	    		return "";
    			break;
    		//  71 - Planted the sporos seed and needs to water with vial	
    		case 71:
    			if (!present("crystalline seed",TP))
    			{
    				write(TO->query_The_name(TP)+" telepathically says "+
    					"to you: You should now pour the vial I gave "+
	    			    "you on to the seed you planted.\n");
	    			return "";
	    		}
	    		write(TO->query_The_name(TP)+" telepathically says to you: "+
	    			"You should take that crystalline "+
	    		    "seed to Arial and ask her about it to continue.\n");
	    		return "";
    			break;
    		//  8 - Needs to talk to Arial about Crystalline Seed (or Sporos)
    		case 8:
    			write(TO->query_The_name(TP)+" telepathically says to you: "+
    				"You should take that crystalline "+
	    		    "seed to Arial and ask her about it to continue.\n");
    			return "";
    			break;
    		//  9 - Needs to plant crystalline seed in Earth's Behold and 
    		//      pour vial on it
    		case 9:
    			write(TO->query_The_name(TP)+" telepathically says to you: "+
    				"You should take that crystalline "+
	    		    "seed to Arial and ask her about it to continue.\n");
	    		return "";
    			break;
    		//  91 - Planted crystalline seed and needs to pour vial on it
    		case 91:
    			write(TO->query_The_name(TP)+" telepathically says to you: "+
    				"You should take that vial that "+
	    		    "Arial gave to you and pour it on the crystalline "+
	    		    "seed you planted in Earths Beholden.\n");
	    		return "";
    			break;
    		// 10 - Needs to talk to Tahla about Seed Gem (or Sporos)
    		case 10:
    			write(TO->query_The_name(TP)+" telepathically says to you: "+
    				"You should take that seed shaped gem "+
	    		    "to Tahla and ask her about it to continue.\n");
	    		return "";
    			break;
    		// 11 - Needs to prepare powder for Tiashe
    		case 11:
    			write(TO->query_The_name(TP)+" telepathically says to you: "+
    				"You should take that seed shaped gem "+
	    		    "to Tiashe and ask her about it to continue.\n");
	    		return "";
    			break;
    		// 12 - Needs to sprinkle powder on Seed Gem
    		case 12:
    			write(TO->query_The_name(TP)+" telepathically says to you: "+
    				"You should take that seed shaped gem "+
	    		    "to Tiashe and ask her about it to continue.\n");
	    		return "";
    			break;
    		// 13 - Needs to talk to Sehis about Seed Gem (or Sporos or 
    		//      Blessing)
    		case 13:
    			write(TO->query_The_name(TP)+" telepathically says to you: "+
    				"You should take that seed shaped gem "+
	    		    "to Sehis and ask her about it to continue.\n");
	    		return "";
    			break;
    		// Unknown or invalid value
    		default:
    			write(TO->query_The_name(TP)+" telepathically says to you: "+
    				"There seems to "+
    			    "be a problem. Please report that you are having "+
    			    "issues with your "+
    			    "Sporos to the guildmaster.\n");
		    	return "";
    			break;
    	}    	
    }
    
    write(TO->query_The_name(TP)+" telepathically says to you: I do not "+
    	"know of what you speak.\n");
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
	clone_object(ELEMENTALIST_OBJS+"earth_staff")->move(TO,1);
	TO->command("wield quarterstaff");
	clone_object(ELEMENTALIST_OBJS+"earth_mandala")->move(TO,1);
	TO->command("clasp mandala");
}

void
create_monster()
{
    set_name("Jardeth");
    add_name("jardeth");
    set_title("Elias-Leafhunter, the Master Herbalist of the Elementals, "+
        "Eternal Sage of Tremors");
    set_adj(({"ancient","sparkling-cloaked"}));
    set_race_name("elf");
    set_living_name("jardeth");
    set_stats(({300,300,300,300,300,300}));
    set_alignment(1200);
    set_base_stat(SS_OCCUP, 300);
    set_base_stat(SS_LAYMAN, 300);
    set_appearance_offset(-50);
    set_width_desc("lean");
    set_height_desc("tall");
    set_skill(SS_DEFENCE,100);
    set_intro_delay(1);
    set_act_time(15);
    add_act("clasp mandala");
    add_act("clbow");
    add_act("clshake dirt");
    add_act("clpull");
    add_act("emote absentmindedly brushes a bit of the soil "+
        "from the front of his robes.");
    add_act("emote frowns slightly and squints as he makes out a "+
        "label for one of his herb pouches.");
    add_act("emote waters some of the herbs in the garden.");
    add_act("emote plants some herbs in the garden.");
    add_prop(NPC_M_NO_ACCEPT_GIVE,1);
    add_prop(LIVE_I_ALWAYSKNOWN,1);
    add_prop("_npc_primary_element","earth");
    
    clone_object(EC_OCC_SHADOW)->shadow_me(TO,
        GUILD_EC_TYPE, "cleric", GUILD_EC_NAME, "");
    clone_object(EC_LAY_SHADOW)->shadow_me(TO,
        "layman", "cleric", GUILD_EC_NAME, "");
    clone_object(EC_RACE_SHADOW)->shadow_me(TO, "race", 
        "cleric", GUILD_EC_NAME, "");
    TP->add_subloc(EC_RACIAL_SUBLOC, TO);
    TO->arm_me();

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"herb","herbs"}),&herbs_answer());
    add_ask(({"energy","spiritual energy"}),&energy_answer());
    add_ask(({"stones","earth","gu","lady gu"}),&gu_answer());
    add_ask(({"task four","four","fourth task","task 4","4th task",
    	"4","task"}),&task_four_answer());
    add_ask(({"answer secrecy"}),&task_four_response());
    add_ask(({"sporos","Sporos","pod","sporos pod","Sporos pod",
    	"Sporos seed","sporos seed","sporos crystalline seed",
    	"Sporos crysalline seed","crystalline seed","seed"}),
    	&sporos_inquiry_response());

}

public string
default_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: I do not "+
    	"know of what you speak.\n");
    return "";
}

void
init_living()
{
    if (TP->query_guild_name_occ() == GUILD_EC_NAME)
		TP->add_introduced(query_real_name());
    ::init_living();
}
