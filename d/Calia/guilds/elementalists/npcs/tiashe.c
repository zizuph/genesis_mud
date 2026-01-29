
/* 
 * This is the caterer for the Temple. 
 *   
 * Coded by Jaacar July 6th, 2016.
 * Added "Faith" Worshipper task (aka task 2)
 * Mirandus - November 24, 2020
 * - Fixed the Task Six answering issue.
*/ 

#include <ss_types.h>
#include <macros.h> 
#include <stdproperties.h>
#include "defs.h"

inherit "/std/monster";
inherit "/d/Calia/std/remember";
inherit "/d/Calia/std/intro";
inherit "/lib/guild_support";

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
food_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: Many "+
        "think cooking is a whimsical persuit, but sustinance "+
        "of the body is just as important as sustinance of the spirit.\n");
    return "";
}

public string
spirit_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: While we "+
        "are servants of spirit, we are still bound by our physical body. "+
        "Without a nourished body, we cannot thrive in this reality.\n");
    return "";
}

public string
diabrecho_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: The depths "+
        "of Diabrecho's insights inspire my soul.\n");
    return "";
}

public string
insight_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: While the "+
        "Clergy can offer some insights to guide you along your spiritual "+
        "path, ulitmately the journey is one you walk with Elementals "+
        "beside you. I have found the garden to be a place of serenity "+
        "for contemplation.\n");
    return "";
}

public string
task_answer()
{
    if (!GUILD_MANAGER->query_can_do_wor_task_two(TP))
    {
        if(!GUILD_MANAGER->query_can_do_ec_task_six(TP))
        {
    		write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
            "you speak.\n");
            return "";
        }
    }
    write(TO->query_The_name(TP)+" telepathically says to you: Which task are you speaking "+
        "of? The faith task or the servitude task?\n");
    return "";
}

public string
task_two_answer()
{
	int tasktwo;
	
	// If they aren't a Seeker, they won't get to ask about the task
	if (!(GUILD_MANAGER->query_is_seeker(TP)))
	{
		write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
        "you speak.\n");
        return "";
    }
    
    tasktwo = (GUILD_MANAGER->query_can_do_wor_task_two(TP));
    
    // If they haven't been assigned task two, they won't get to ask about the task
    if (!tasktwo)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
        "you speak.\n");
        return "";
    }
    
    // If they've already completed task two, they should get a different answer
    if (tasktwo == 9)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: You've already completed "+
    	    "my task.\n");
        return "";
    }
    
    // They are indeed a Seeker and have been assigned task two and have not
    // yet completed it. Now to figure out what question they are on and ask
    // the appropriate next question.
    
    switch(tasktwo)
    {
    	case 1:
    		// They are on the first question of eight
    		write(TO->query_The_name(TP)+" telepathically says to you: I see you have been "+
    		    "asked to come and see me about my task. Very well then, let "+
    		    "us begin then.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: This is your faith "+
    		    "task. I have eight questions for you to answer. When you are ready to "+
    		    "respond to the question, you may do so by stating you are ready to "+
    		    "answer the question. You will be given a magical form that you can "+
    		    "write your answer on. You only get to submit each answer once, so "+
    		    "make sure you are happy with your response before submitting it. You "+
    		    "may abort your submittal at any time just like you would if you were "+
    		    "sending a mail message (~q).\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: Here is your first question.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: What does the Lord of the "+
    		    "Flames and his Element of Fire define for you?\n");    
    		break;
    	case 2:
    		// They are on the second question of eight
    		write(TO->query_The_name(TP)+" telepathically says to you: Just a reminder, "+
    		    "when you are ready to respond to the question, you may do so by stating "+
    		    "you are ready to answer the question. You will be given a magical form "+
    		    "that you can write your answer on. You only get to submit each answer "+
    		    "once, so make sure you are happy with your response before submitting it. "+
    		    "You may abort your submittal at any time just like you would if you were "+
    		    "sending a mail message (~q).\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: Here is your second question.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: What does the Lady of the "+
    		    "Winds and her Element of Air define for you?\n");  
    		break;
    	case 3:
    		// They are on the third question of eight
    		write(TO->query_The_name(TP)+" telepathically says to you: Just a reminder, "+
    		    "when you are ready to respond to the question, you may do so by stating "+
    		    "you are ready to answer the question. You will be given a magical form "+
    		    "that you can write your answer on. You only get to submit each answer "+
    		    "once, so make sure you are happy with your response before submitting it. "+
    		    "You may abort your submittal at any time just like you would if you were "+
    		    "sending a mail message (~q).\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: Here is your third question.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: What does the Lord of the "+
    		    "Seas and his Element of Water define for you?\n"); 
    		break;
    	case 4:
    		// They are on the fourth question of eight
    		write(TO->query_The_name(TP)+" telepathically says to you: Just a reminder, "+
    		    "when you are ready to respond to the question, you may do so by stating "+
    		    "you are ready to answer the question. You will be given a magical form "+
    		    "that you can write your answer on. You only get to submit each answer "+
    		    "once, so make sure you are happy with your response before submitting it. "+
    		    "You may abort your submittal at any time just like you would if you were "+
    		    "sending a mail message (~q).\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: Here is your fourth question.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: What does the Lady of the "+
    		    "Earth and her Element of Earth define for you?\n");  
    		break;
        case 5:
    		// They are on the fifth question of eight
    		write(TO->query_The_name(TP)+" telepathically says to you: Just a reminder, "+
    		    "when you are ready to respond to the question, you may do so by stating "+
    		    "you are ready to answer the question. You will be given a magical form "+
    		    "that you can write your answer on. You only get to submit each answer "+
    		    "once, so make sure you are happy with your response before submitting it. "+
    		    "You may abort your submittal at any time just like you would if you were "+
    		    "sending a mail message (~q).\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: Here is your fifth question.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: What does Psuchae and the "+
    		    "Element of Spirit define for you?\n");  
    		break;
    	case 6:
    		// They are on the sixth question of eight
    		write(TO->query_The_name(TP)+" telepathically says to you: Just a reminder, "+
    		    "when you are ready to respond to the question, you may do so by stating "+
    		    "you are ready to answer the question. You will be given a magical form "+
    		    "that you can write your answer on. You only get to submit each answer "+
    		    "once, so make sure you are happy with your response before submitting it. "+
    		    "You may abort your submittal at any time just like you would if you were "+
    		    "sending a mail message (~q).\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: Here is your sixth question.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: Name me the places in the "+
    		    "Realms where you personally, clearly perceive the Five, and why this is "+
    		    "significant for you.\n"); 
    		break;
    	case 7:
    		// They are on the seventh question of eight
    		write(TO->query_The_name(TP)+" telepathically says to you: Just a reminder, "+
    		    "when you are ready to respond to the question, you may do so by stating "+
    		    "you are ready to answer the question. You will be given a magical form "+
    		    "that you can write your answer on. You only get to submit each answer "+
    		    "once, so make sure you are happy with your response before submitting it. "+
    		    "You may abort your submittal at any time just like you would if you were "+
    		    "sending a mail message (~q).\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: Here is your seventh question.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: Explain which of the Five "+
    		    "you would dedicate yourself to, should you be accepted into the Circle, and "+
    		    "why that is so.\n"); 
    		break;
    	case 8:
    		// They are on the eighth question of eight
    		write(TO->query_The_name(TP)+" telepathically says to you: Just a reminder, "+
    		    "when you are ready to respond to the question, you may do so by stating "+
    		    "you are ready to answer the question. You will be given a magical form "+
    		    "that you can write your answer on. You only get to submit each answer "+
    		    "once, so make sure you are happy with your response before submitting it. "+
    		    "You may abort your submittal at any time just like you would if you were "+
    		    "sending a mail message (~q).\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: Here is your final question.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: What do you feel the Five want "+
    		    "from us?\n"); 
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
task_six_answer()
{
	int tasksix;
	
	// If they aren't a Seeker, they won't get to ask about the task
	if (!(GUILD_MANAGER->query_is_seeker(TP)))
	{
	    if (!GUILD_MANAGER->query_is_worshipper(TP))
	    {
    		write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
            "you speak.\n");
            return "";
        }
    }
    
    tasksix = (GUILD_MANAGER->query_can_do_ec_task_six(TP));
    
    // If they haven't been assigned task two, they won't get to ask about the task
    if (!tasksix)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: I do not know of what "+
        "you speak.\n");
        return "";
    }
    
    // If they've already completed task two and task six, they should get a different answer
    if (tasksix == 7)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: You've already completed "+
    	    "my task.\n");
        return "";
    }
    
    // They are indeed a Seeker and have been assigned task six and have not
    // yet completed it. Now to figure out what question they are on and ask
    // the appropriate next question.
    
    switch(tasksix)
    {
    	case 1:
    		// They are on the first question of six
    		write(TO->query_The_name(TP)+" telepathically says to you: I see you have been "+
    		    "asked to come and see me about my task. Very well then, let "+
    		    "us begin then.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: This is your servitude "+
    		    "task. I have six questions for you to answer. When you are ready to "+
    		    "respond to the question, you may do so by stating you are ready to "+
    		    "answer the question. You will be given a magical form that you can "+
    		    "write your answer on. You only get to submit each answer once, so "+
    		    "make sure you are happy with your response before submitting it. You "+
    		    "may abort your submittal at any time just like you would if you were "+
    		    "sending a mail message (~q).\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: Here is your first question.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: Given that we are "+
    		    "both Elemental Servants and Kyrullians, explain to me who the Clerics of "+
    		    "this Temple are.\n");    
    		break;
    	case 2:
    		// They are on the second question of six
    		write(TO->query_The_name(TP)+" telepathically says to you: Just a reminder, "+
    		    "when you are ready to respond to the question, you may do so by stating "+
    		    "you are ready to answer the question. You will be given a magical form "+
    		    "that you can write your answer on. You only get to submit each answer "+
    		    "once, so make sure you are happy with your response before submitting it. "+
    		    "You may abort your submittal at any time just like you would if you were "+
    		    "sending a mail message (~q).\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: Here is your second question.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: What behaviour would "+
    		    "you expect from such a Cleric?\n");  
    		break;
    	case 3:
    		// They are on the third question of six
    		write(TO->query_The_name(TP)+" telepathically says to you: Just a reminder, "+
    		    "when you are ready to respond to the question, you may do so by stating "+
    		    "you are ready to answer the question. You will be given a magical form "+
    		    "that you can write your answer on. You only get to submit each answer "+
    		    "once, so make sure you are happy with your response before submitting it. "+
    		    "You may abort your submittal at any time just like you would if you were "+
    		    "sending a mail message (~q).\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: Here is your third question.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: How do the Clerics "+
    		    "handle conflicts internally and externally?\n"); 
    		break;
    	case 4:
    		// They are on the fourth question of six
    		write(TO->query_The_name(TP)+" telepathically says to you: Just a reminder, "+
    		    "when you are ready to respond to the question, you may do so by stating "+
    		    "you are ready to answer the question. You will be given a magical form "+
    		    "that you can write your answer on. You only get to submit each answer "+
    		    "once, so make sure you are happy with your response before submitting it. "+
    		    "You may abort your submittal at any time just like you would if you were "+
    		    "sending a mail message (~q).\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: Here is your fourth question.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: How do the Clerics "+
    		    "approach outsiders?\n");  
    		break;
        case 5:
    		// They are on the fifth question of six
    		write(TO->query_The_name(TP)+" telepathically says to you: Just a reminder, "+
    		    "when you are ready to respond to the question, you may do so by stating "+
    		    "you are ready to answer the question. You will be given a magical form "+
    		    "that you can write your answer on. You only get to submit each answer "+
    		    "once, so make sure you are happy with your response before submitting it. "+
    		    "You may abort your submittal at any time just like you would if you were "+
    		    "sending a mail message (~q).\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: Here is your fifth question.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: How do the Clerics "+
    		    "stand in regards to the moral strifes of good and evil?\n");  
    		break;
    	case 6:
    		// They are on the sixth question of six
    		write(TO->query_The_name(TP)+" telepathically says to you: Just a reminder, "+
    		    "when you are ready to respond to the question, you may do so by stating "+
    		    "you are ready to answer the question. You will be given a magical form "+
    		    "that you can write your answer on. You only get to submit each answer "+
    		    "once, so make sure you are happy with your response before submitting it. "+
    		    "You may abort your submittal at any time just like you would if you were "+
    		    "sending a mail message (~q).\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: Here is your final question.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: How do the Clerics "+
    		    "view wars of dominion?\n"); 
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
    			write(TO->query_The_name(TP)+" telepathically says to you: You should take that seed gem "+
	    		    "seed to Tahla and ask her about it to continue.\n");
	    		return "";
    			break;
    		// 11 - Needs to prepare powder for Tiashe
    		case 11:
    			write(TO->query_The_name(TP)+" telepathically says to you: Ah, the Sporos. You will need "+
    			    "to activate that seed shaped gem by sprinkling a special powder on it. I have a "+
    			    "small bit of powder left that you can have.\n"+TO->query_The_name(TP)+
    			    " hands you a small bit of powder.\n");
    			say(QCTNAME(TO)+" hands "+QTNAME(TP)+" something.\n");
    			clone_object(ELEMENTALIST_OBJS+"sporos_powder")->move(TP,1);
    			invismandala->set_task_status(12);
	    		return "";
    			break;
    		// 12 - Needs to sprinkle powder on Seed Gem
    		case 12:
    			write(TO->query_The_name(TP)+" telepathically says to you: You need to sprinkle the powder on "+
    			    "to the seed shaped gem.\n");
	    		return "";
    			break;
    		// 13 - Needs to talk to Sehis about Seed Gem (or Sporos or Blessing)
    		case 13:
    			write(TO->query_The_name(TP)+" telepathically says to you: You should take that dark seed "+
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
	clone_object(ELEMENTALIST_OBJS+"water_staff")->move(TO,1);
	TO->command("wield quarterstaff");
	clone_object(ELEMENTALIST_OBJS+"water_mandala")->move(TO,1);
	TO->command("clasp mandala");
}

void
create_monster()
{
    set_name("Tiashe"); 
    add_name("caterer");
    add_name("tiashe");
    set_living_name("tiashe");

    set_adj(({"smiling", "blue-cloaked"}));  
   
    set_race_name("elf");
    set_gender(G_FEMALE);
    set_title("Quintas-Tranquilbrook, the Master Caterer of the "+
        "Elementals, Fathomless Apotheosis of the Deep");

    default_config_npc(300);
    
    clone_object(EC_OCC_SHADOW)->shadow_me(TO,
        GUILD_EC_TYPE, "cleric", GUILD_EC_NAME, "");
    clone_object(EC_LAY_SHADOW)->shadow_me(TO,
        "layman", "cleric", GUILD_EC_NAME, "");
    clone_object(EC_RACE_SHADOW)->shadow_me(TO, "race", 
        "cleric", GUILD_EC_NAME, "");
    TP->add_subloc(EC_RACIAL_SUBLOC, TO);
    add_prop("_npc_primary_element","water");

    set_skill(SS_UNARM_COMBAT, 100); 
    set_skill(SS_DEFENCE, 100);
    set_base_stat(SS_OCCUP, 300);
    set_base_stat(SS_LAYMAN, 300);
    set_appearance_offset(-50);
    set_width_desc("lean");
    set_height_desc("tall");
    set_alignment(1200);
    TO->arm_me();

    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_ALWAYSKNOWN,1);
    add_prop(CONT_I_WEIGHT, 65000); 
    add_prop(CONT_I_VOLUME, 65000); 
    set_intro_delay(1);
    set_act_time(15);
    add_act("clasp mandala");
    add_act("clbow");
    add_act("clshake dirt");
    add_act("clpull");
    add_act("emote smiles softly as she cleans one of the tables.");
    add_act("emote prepares a meal with a graceful motion.");
    add_act("emote peers surreptitiously around, then tastes a small bit of "+
        "cookie dough from her mixing bowl.");
    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"food"}),&food_answer());
    add_ask(({"spirit"}),&spirit_answer());
    add_ask(({"diabrecho","lord diabrecho","waves","water"}),&diabrecho_answer());
    add_ask(({"insight","insights"}),&insight_answer());
    add_ask(({"task"}),&task_answer());
    add_ask(({"task two","two","faith task","faith","second task",
    	"task 2","2nd task","2"}),&task_two_answer());
    add_ask(({"task six","six","servitude task","servitude","sixth task",
    	"task 6","6th task","6"}),&task_six_answer());
    add_ask(({"sporos","Sporos","Sporos seed","sporos seed",
    	"sporos seed shaped gem","Sporos seed shaped gem",
    	"sporos gem","gem","seed","Sporos powder","powder",
    	"sporos powder"}),&sporos_inquiry_response());
}

public string
default_answer()
{
    command("emote telepathically says to you: I do not know of what "+
        "you speak.");
    return "";
}

void
init_living()
{
    if (TP->query_guild_name_occ() == GUILD_EC_NAME)
		TP->add_introduced(query_real_name());
    ::init_living();
}
