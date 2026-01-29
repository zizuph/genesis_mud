
/* 
 * This is the greeter NPC for the Temple. 
 *   
 * Coded by Jaacar July 6th, 2016.
 * 
*/ 

#include <ss_types.h>
#include <macros.h> 
#include <stdproperties.h>
#include <cmdparse.h>
#include "defs.h"


inherit "/std/monster"; 
inherit "/d/Calia/std/intro";
inherit "/d/Calia/std/remember";
inherit "/lib/guild_support";

#define EC_RACIAL_SUBLOC "_elemental_guild_racial_subloc"

#define DROPROOM "/d/Calia/guilds/elementalists/temple/ec_rack"
#define DONATION_LOG "elementalists/donation_log"

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
task_five_answer()
{
	int taskone, tasktwo, taskthree, taskfour, taskfive;
	
	// If they aren't a Seeker, they won't get to ask about the task
	if (!(GUILD_MANAGER->query_is_seeker(TP)))
	{
	    if (!GUILD_MANAGER->query_is_worshipper(TP))
	    {
    		write(TO->query_The_name(TP)+" telepathically says to you: I do "+
    			"not know of what you speak.\n");
            return "";
        }
    }
    taskone = (GUILD_MANAGER->query_can_do_wor_task_one(TP));
    tasktwo = (GUILD_MANAGER->query_can_do_wor_task_two(TP));
    taskthree = (GUILD_MANAGER->query_can_do_wor_task_three(TP));
    taskfour = (GUILD_MANAGER->query_can_do_wor_task_four(TP));
    taskfive = (GUILD_MANAGER->query_can_do_ec_task_five(TP));
    
    if (!GUILD_MANAGER->query_is_worshipper(TP))
    {        
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
    }
    
    // If they haven't been assigned task five, they won't get to ask 
    // about the task
    if (!taskfive)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: I do "+
    		"not know of what you speak.\n");
        return "";
    }
    
    // If they've already completed task five, they should get a 
    // different answer
    if (taskfive == 3)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: "+
    		"You've already completed my task.\n");
        return "";
    }
    
    // They are indeed a Seeker and have been assigned task five and have not
    // yet completed it. Now to figure out what question they are on and ask
    // the appropriate next question.
    
    switch(taskfive)
    {
    	case 1:
    		// They are on the first question of two
    		write(TO->query_The_name(TP)+" telepathically says to you: I see you have been "+
    		    "asked to come and see me about my task. Very well then, let "+
    		    "us begin then.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: This is your Spirit "+
    		    "and Soul task. An Elder has deemed you fit to continue to learn of the "+
    		    "more esoteric lore surrounding our Way. Let us see if you have been "+
    		    "attentive in these matters. I have two questions for you to answer. "+
    		    "When you think you "+
    		    "know the answer to the question I am asking, please come and "+
    		    "ask me to verify it. (ask sehis answer <your answer>)\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: Here is your first question.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: The Elements work "+
    		    "together constantly in Creation. Creation is not a singular event, it "+
    		    "happens in every second and in every moment of our lives. An Elder has "+
    		    "spoken to you about a part of Creation relating to Spirit as the catalyst "+
    		    "and binder. What do we call this part?\n");    
    		break;
    	case 2:
    		// They are on the second question of two
    		write(TO->query_The_name(TP)+" telepathically says to you: Just a reminder, when you "+
    		    "think you know the answer to the question I am asking, please come and "+
    		    "ask me to verify it. (ask sehis answer <your answer>)\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: Here is your second question.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: An Elder also would "+
    		    "have mentioned another role; that of Soul. The continued existence of "+
    		    "the eternal component that is truly you.\n");
    		write(TO->query_The_name(TP)+" holds her finger in the air and says: Birth.\n");
    		say(TO->query_The_name(TP)+" holds her finger in the air and says: Birth.\n");
    		write(TO->query_The_name(TP)+" smiles reverently, draws a half-circle in "+
    		    "the air and says: Life.\n");
    		say(TO->query_The_name(TP)+" smiles reverently, draws a half-circle in "+
    		    "the air and says: Life.\n");
    		write(TO->query_The_name(TP)+" completes drawing the circle in the air "+
    		    "and solemnly says: Death.\n");
    		say(TO->query_The_name(TP)+" completes drawing the circle in the air "+
    		    "and solemnly says: Death.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: All phases of "+
    		    "our existence.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: What do we call "+
    		    "this journey of our Soul?\n");
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
task_five_first_response()
{
	int taskone, tasktwo, taskthree, taskfour, taskfive;
	
	// If they aren't a Seeker, they won't get to answer the task
	if (!(GUILD_MANAGER->query_is_seeker(TP)))
	{
	    if (!GUILD_MANAGER->query_is_worshipper(TP))
	    {
    		write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
            "you speak.\n");
            return "";
        }
    }
    
    taskone = (GUILD_MANAGER->query_can_do_wor_task_one(TP));
    tasktwo = (GUILD_MANAGER->query_can_do_wor_task_two(TP));
    taskthree = (GUILD_MANAGER->query_can_do_wor_task_three(TP));
    taskfour = (GUILD_MANAGER->query_can_do_wor_task_four(TP));
    taskfive = (GUILD_MANAGER->query_can_do_ec_task_five(TP));
    
    if (!GUILD_MANAGER->query_is_worshipper(TP))
    {
        // If they haven't been assigned task one, they won't get to answer the task
        if (!taskone)
        {
        	write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
            "you speak.\n");
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
    }
    
    // If they've already completed task five, they should get a different answer
    if (taskfive == 3)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: You've already completed "+
    	    "my task.\n");
        return "";
    }
    
    // If they've already answered question one, they should get a different answer
    if (taskfive != 1)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: That is not the correct "+
    	    "answer.\n");
        return "";
    }
    
    // They are indeed a Seeker and have been assigned task five and have not
    // yet completed it and they have given a correct answer. Time to let them
    // know and ask them the next question.
    
    write(TO->query_The_name(TP)+" telepathically says to you: That is the correct answer.\n");
    GUILD_MANAGER->set_can_do_ec_task_five(TP,2);
    write(TO->query_The_name(TP)+" telepathically says to you: Here is your final question.\n");
    write(TO->query_The_name(TP)+" telepathically says to you: An Elder also would "+
	    "have mentioned another role; that of Soul. The continued existence of "+
	    "the eternal component that is truly you.\n");
	write(TO->query_The_name(TP)+" holds her finger in the air and says: Birth.\n");
	say(TO->query_The_name(TP)+" holds her finger in the air and says: Birth.\n");
	write(TO->query_The_name(TP)+" smiles reverently, draws a half-circle in "+
	    "the air and says: Life.\n");
	say(TO->query_The_name(TP)+" smiles reverently, draws a half-circle in "+
	    "the air and says: Life.\n");
	write(TO->query_The_name(TP)+" completes drawing the circle in the air "+
	    "and solemnly says: Death.\n");
	say(TO->query_The_name(TP)+" completes drawing the circle in the air "+
	    "and solemnly says: Death.\n");
	write(TO->query_The_name(TP)+" telepathically says to you: All phases of "+
	    "our existence.\n");
	write(TO->query_The_name(TP)+" telepathically says to you: What do we call "+
	    "this journey of our Soul?\n"); 
    
	return "";
}

public string
task_five_second_response()
{
	int taskone, tasktwo, taskthree, taskfour, taskfive;
	
	// If they aren't a Seeker, they won't get to answer the task
	if (!(GUILD_MANAGER->query_is_seeker(TP)))
	{
	    if (!GUILD_MANAGER->query_is_worshipper(TP))
	    {
    		write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
            "you speak.\n");
            return "";
        }
    }
    
    taskone = (GUILD_MANAGER->query_can_do_wor_task_one(TP));
    tasktwo = (GUILD_MANAGER->query_can_do_wor_task_two(TP));
    taskthree = (GUILD_MANAGER->query_can_do_wor_task_three(TP));
    taskfour = (GUILD_MANAGER->query_can_do_wor_task_four(TP));
    taskfive = (GUILD_MANAGER->query_can_do_ec_task_five(TP));
    
    if (!GUILD_MANAGER->query_is_worshipper(TP))
    {
        // If they haven't been assigned task one, they won't get to answer the task
        if (!taskone)
        {
        	write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
            "you speak.\n");
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
    }
    
    // If they've already completed task five, they should get a different answer
    if (taskfive == 3)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: You've already completed "+
    	    "my task.\n");
        return "";
    }
    
    // If they've already answered question two, they should get a different answer
    if (taskfive != 2)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: That is not the correct "+
    	    "answer.\n");
        return "";
    }
    
    // They are indeed a Seeker and have been assigned task five and have not
    // yet completed it and they have given a correct answer. Time to let them
    // know and ask them the next question.
    
    write(TO->query_The_name(TP)+" telepathically says to you: That is the correct answer.\n");
    GUILD_MANAGER->set_can_do_ec_task_five(TP,3);
    write(TO->query_The_name(TP)+" telepathically says to you: You have successfully answered "+
        "all of my questions and completed my task. Now search the Temple for two places, "+
        "one where you will see the Quickening and one where you will see the Cycle of Soul. "+
        "Once you have found both of these places, call upon your Elder and show them what "+
        "you have found.\n");
    string log_message = capitalize(TP->query_real_name()) + " has completed task 5.\n";
    COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
	return "";
}

public string
job_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: My "+
        "job is to answer the questions of those who come to this "+
        "Temple.\n");
    return "";
}

public string
temple_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: This "+
        "is the Temple of the Elementals. Those who are members of the "+
        "Elementalists reside here.\n");
    return "";
}

public string
member_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: I "+
        "cannot divulge the identities of the members. I am sorry.\n");
    return "";
}

public string
join_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: You "+
        "should find the information you seek in the library to the "+
        "east.\n");
    return "";
}

public string
apply_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: I "+
        "am sorry, I do not accept applications. You should find "+
        "the information you seek about joining in the library "+
        "to the east.\n");
    return "";
}

public string
elementals_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: "+
        "The Elemental Worshippers can be found here in the Temple.\n");
    return "";
}

public string
donation_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: You "+
        "can donate items to the Elemental Clerics if you wish. Simply "+
        "notify me which item you wish to donate. (donate <item>)\n");
    return "";
}

public string
question_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: Ah! "+
        "A question I do not get asked very many times. I can tell "+
        "you about Elementals, applying, joining, members, temple, "+
        "donations and position.\n");
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
    
    // If they already have their completed Sporos they get a different answer
    if (present("_completed_sporos_",TP))
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: The Sporos is the seed "+
    	    "for your Sacred Mandala, which you already have. Go find the book titled Sacred "+
    	    "Madala in the library.\n");
        return "";
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
    	    "first have to get a Sporos. Begin your journey towards this end by visiting "+
    	    "Jardeth in the herb garden and asking him about the Sporos.\n");
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
    			write(TO->query_The_name(TP)+" telepathically says to you: You should take that seed shaped gem "+
	    		    "to Tahla and ask her about it to continue.\n");
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
    			present("raw Sporos",TP)->remove_object();
    			write(TO->query_The_name(TP)+" telepathically says to you: Ah, the Sporos. Allow me "+
    			    "to finalize it and prepare it to bind with you.\nYou hand "+TO->query_The_name(TP)+
    			    " the dark seed.\n"+TO->query_The_name(TP)+" firmly grasps it in her hands, closes "+
    			    "her eyes and begins to hum rhythmically. A light surrounds her hands, the dark "+
    			    "seed begins to absorb the light and glow. The light fades from her hands and from "+
    			    "the seed. "+TO->query_The_name(TP)+" smiles brightly and hands you the seed.\nThe "+
    			    "instant it touches your hands, it begins to grow and shrink in a constant pattern, "+
    			    "almost as if it was mimicking your own heartbeat.\n"+TO->query_The_name(TP)+
    			    " telepathically says to you: Now that you have completed the Sporos, you are ready "+
    			    "to begin constructions of your Sacred Mandala. Seek out the book in the library of "+
    			    "the same title and follow the instructions provided.\n");
    			say(QCTNAME(TO)+" takes something from "+QTNAME(TP)+".\n");
    			say(QCTNAME(TO)+" firmly grasps she she took in her hands, closes her eyes and begins "+
    			    "to hum rhythmically. A light surrounds her hands, the object begins to absorb the "+
    			    "light and glow. The light fades from her hands and from the object.\n");
    			say(QCTNAME(TO)+" smiles brightly and hands the object back to "+QTNAME(TP)+".\n");
    			clone_object(ELEMENTALIST_OBJS+"sporos")->move(TP,1);
    			invismandala->remove_object();
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
	clone_object(ELEMENTALIST_OBJS+"spirit_staff")->move(TO,1);
	TO->command("wield quarterstaff");
	clone_object(ELEMENTALIST_OBJS+"spirit_mandala")->move(TO,1);
	TO->command("clasp mandala");
}

public void
create_monster()
{
    set_name("Sehis");
    add_name("elf");
    add_name("greeter");
    add_name("sehis");
    set_living_name("sehis");
    set_title("Petros-Spirithammer, the Greeter of the Elemental "+
        "Temple, Divine Synthesis of Eternity");
    
    set_adj(({"smiling", "silver-cloaked"}));  
   
    set_race_name("elf");
    set_gender(G_FEMALE);
    
    set_stats(({300,300,300,300,300,300}));
    set_alignment(1200); 

    set_skill(SS_UNARM_COMBAT, 100); 
    set_skill(SS_DEFENCE, 100);
    set_base_stat(SS_OCCUP, 300);
    set_base_stat(SS_LAYMAN, 300);
    set_appearance_offset(-50);
    set_width_desc("lean");
    set_height_desc("tall");

    set_intro_delay(1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(CONT_I_WEIGHT, 65000); 
    add_prop(CONT_I_VOLUME, 65000);
    add_prop(LIVE_I_ALWAYSKNOWN, 1);
    add_prop("_npc_primary_element","life");

    clone_object(EC_OCC_SHADOW)->shadow_me(TO, GUILD_EC_TYPE,
        "cleric", GUILD_EC_NAME, "");
    clone_object(EC_LAY_SHADOW)->shadow_me(TO, "layman",
        "cleric", GUILD_EC_NAME, "");
    clone_object(EC_RACE_SHADOW)->shadow_me(TO, "race", 
        "cleric", GUILD_EC_NAME, "");
    TP->add_subloc(EC_RACIAL_SUBLOC, TO);
    
    TO->arm_me();
	
	set_act_time(15);
    add_act("clasp mandala");
    add_act("clbow");
    add_act("clshake dirt");
    add_act("clpull");
    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"job","position"}),&job_answer());
    add_ask(({"temple","holy temple"}),&temple_answer());
    add_ask(({"member","members"}),&member_answer());
    add_ask(({"join","joining"}),&join_answer());
    add_ask(({"apply","application","applying"}),&apply_answer());
    add_ask(({"elements","elementals"}),&elementals_answer());
    add_ask(({"question","questions"}),&question_answer());
    add_ask(({"donate","donation","donating","donations"}),&donation_answer());
    add_ask(({"sporos","Sporos","Sporos seed","sporos seed",
    	"sporos dark seed","Sporos dark seed","seed",
    	"dark seed"}),&sporos_inquiry_response());
    add_ask(({"task five","five","spirit task","spirit","soul task",
        "soul","spirit and soul task","soul and spirit task",
        "spirit & soul task","soul & spirit task","fifth task",
    	"task 5","5th task","5","task"}),&task_five_answer());
    add_ask(({"answer quickening","answer Quickening","answer the quickening",
        "answer the Quickening"}),
    	&task_five_first_response());
    add_ask(({"answer cycle","answer Cycle","answer cycle of soul",
        "answer Cycle of Soul","answer the cycle of soul","answer the Cycle of Soul",
        "answer the cycle of the soul","answer the Cycle of the Soul","answer the cycle",
        "answer the Cycle"}),
    	&task_five_second_response());
}

public string
default_answer()
{
    command("emote telepathically says to you: I do not know of what "+
        "you speak.");
    return "";
}

/* 
 * Function:     do_donate 
 * Description:  Donate an item to the cadet racks. 
 * Original code by Maniac for Cadets
 *
 */

int 
do_donate(string str) 
{ 
    object *oblist, donation; 
    string sh; 
    int v; 

    if (!stringp(str) || !strlen(str) || 
        !sizeof(oblist = FIND_STR_IN_ARR(str, all_inventory(TP)))) 
    { 
        NF("Donate what to the Elemental Clerics?\n"); 
        return 0; 
    } 

    if (sizeof(oblist) > 1) 
    { 
        NF("You may only donate one item at a time to " + 
            "the Elemental Clerics.\n"); 
        return 0; 
    } 

    donation = oblist[0]; 
    sh = LANG_ASHORT(donation); 
    write("You offer " + sh + " as a donation to " + 
          "the Elemental Clerics.\n"); 
    say(QCTNAME(TP) + " offers " + sh + 
        " as a donation to the Elemental Clerics.\n"); 

    if (IS_COINS_OBJECT(donation)) 
    { 
        v = donation->query_prop(OBJ_I_VALUE); 
        if (v > 500) 
            command("$emote smiles thankfully"); 
        else if (v > 1000) 
            command("$emote smiles appreciatively"); 
        else if (v > 4000) 
            command("$emote smiles very appreciatively"); 

        write(TO->query_The_name(TP)+" telepathically says to you: "+
            "Very generous of you, but there is no fund to add that "+
            "to currently.\n"); 
        return 1; 
    } 

    if (living(donation)) 
    { 
        command("boggle"); 
        write(TO->query_The_name(TP)+" telepathically says to you: "+
            "Thanks for the thought but we don't accept " + 
            "living animals!\n"); 
        return 1; 
    } 

    if (donation->query_prop(OBJ_I_BROKEN)) 
    { 
        command("chuckle"); 
        write(TO->query_The_name(TP)+" telepathically says to you: "+
            "Good of you to think of us, but " + 
            "that " + donation->query_name() + " doesn't " + 
            "look much use at the moment.\n"); 
        return 1; 
    } 

    if (donation->query_keep()) 
    { 
        write(TO->query_The_name(TP)+" telepathically says to you: "+
            "Are you sure you want to " + 
            "donate " + LANG_THESHORT(donation) + 
            "? If so, please unkeep the "+LANG_THESHORT(donation) + 
            " and try again.\n"); 
        return 1; 
    }

    if (donation->query_prop(OBJ_M_NO_DROP))
    {
        write(TO->query_The_name(TP)+" telepathically says to you: "+
            "You cannot seem to release " + LANG_THESHORT(donation) +".\n"); 
        return 1;
    }

    if (donation->query_prop(OBJ_M_NO_GIVE))
    {
        write(TO->query_The_name(TP)+" telepathically says to you: "+
            "You cannot seem to release " + LANG_THESHORT(donation) +".\n"); 
        return 1;
    }

    DROPROOM->teleledningsanka(); // load the room if it's not already loaded.
    donation->move(DROPROOM,1);
    
    sh = LANG_THESHORT(donation); 

    tell_room(DROPROOM,capitalize(LANG_ASHORT(donation))+" suddenly "+
        "appears on the ground.\n");
    tell_room(environment(this_object()),QCTNAME(this_object()) + 
        " puts " + sh + " into a magical bag.\n"); 
    command("$thank " + OB_NAME(TP));
    log_file(DONATION_LOG, ctime(time())+" "+capitalize(LANG_ASHORT(donation))+
        " was donated by "+TP->query_name() +".\n",-1);
    return 1; 
} 

void
init_living()
{   
	if (TP->query_guild_name_occ() == GUILD_EC_NAME)
		TP->add_introduced(query_real_name());

    add_action(do_donate,"donate");
	::init_living();
}
