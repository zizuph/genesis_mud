
/* 
 * This is the lapidarist for the Temple. 
 *   
 * Coded by Jaacar July 6th, 2016.
 * Added "Family" Worshipper task (aka task 3)
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
gems_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: Born of "+
        "fire deep in the bowels of the earth, gems are an untapped "+
        "resource of tremendous spiritual power.\n");
    return "";
}

public string
power_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: Though "+
        "it may sound unreal, gems are formed by an unfathomable "+
        "liquid fire! The memory of this feat remains imprinted on "+
        "the gem's residual energy, which can be harnessed in the service "+
        "of the Elementals.\n");
    return "";
}

public string
pyros_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: My passions "+
        "burn with great fury in my service to Lord Pyros. His blessing "+
        "will remain with me always.\n");
    return "";
}

public string
library_answer()
{
    write(TO->query_The_name(TP)+" telepathically says to you: As the "+
        "most studious founder, I did indeed write many books for the "+
        "Temple library to prepare the way for those who would follow. "+
        "After some time I was granted retirement, and now work in the "+
        "Temple's gem garden.\n");
    return "";
}

public string
task_three_answer()
{
	int taskthree;
	
	// If they aren't a Seeker, they won't get to ask about the task
	if (!(GUILD_MANAGER->query_is_seeker(TP)))
	{
		write(TO->query_The_name(TP)+" telepathically says to you: I do "+
			"not know of what you speak.\n");
        return "";
    }
    
    taskthree = (GUILD_MANAGER->query_can_do_wor_task_three(TP));
    
    // If they haven't been assigned task three, they won't get to ask about 
    // the task
    if (!taskthree)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: I do not "+
    		"know of what you speak.\n");
        return "";
    }
    
    // If they've already completed task three, they should get a different 
    // answer
    if (taskthree == 3)
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: You've "+
    		"already completed my task.\n");
        return "";
    }
    
    // They are indeed a Seeker and have been assigned task three and have not
    // yet completed it. Now to figure out what question they are on and ask
    // the appropriate next question.
    
    switch(taskthree)
    {
    	case 1:
    		// They are on the first question of two
    		write(TO->query_The_name(TP)+" telepathically says to you: I see "+
    			"you have been "+
    		    "asked to come and see me about my task. Very well then, let "+
    		    "us begin then.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: "+
    			"This is your family "+
    		    "task. I have two questions for you to answer. When you "+
    		    "are ready to "+
    		    "respond to the question, you may do so by stating you "+
    		    "are ready to "+
    		    "answer the question. You will be given a magical form "+
    		    "that you can "+
    		    "write your answer on. You only get to submit each "+
    		    "answer once, so "+
    		    "make sure you are happy with your response before "+
    		    "submitting it. You "+
    		    "may abort your submittal at any time just like you "+
    		    "would if you were "+
    		    "sending a mail message (~q).\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: "+
    			"Here is your first question.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: "+
    			"Define family for me and what "+
    		    "it means to you.\n");    
    		break;
    	case 2:
    		// They are on the second question of two
    		write(TO->query_The_name(TP)+" telepathically says to you: "+
    			"Just a reminder, "+
    		    "when you are ready to respond to the question, you may "+
    		    "do so by stating "+
    		    "you are ready to answer the question. You will be given "+
    		    "a magical form "+
    		    "that you can write your answer on. You only get to "+
    		    "submit each answer "+
    		    "once, so make sure you are happy with your response "+
    		    "before submitting it. "+
    		    "You may abort your submittal at any time just like "+
    		    "you would if you were "+
    		    "sending a mail message (~q).\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: "+
    			"Here is your final question.\n");
    		write(TO->query_The_name(TP)+" telepathically says to you: "+
    			"Why do we ask for this "+
    		    "definition of family and why is it so vital?\n");  
    		break;
    	default:
    		// Should never get here
    		write(TO->query_The_name(TP)+" telepathically says to you: "+
    			"Something has gone terribly "+
    		    "wrong. Please inform a member of the council that you "+
    		    "have asked me "+
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
			write(TO->query_The_name(TP)+" telepathically says to you: I "+
				"do not know of what you speak.\n");
            return "";
        }
    }
    
    // If they already have their completed Mandala they get a different answer
    if (present("_elemental_guild_mandala",TP))
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: The "+
    		"Sporos is the seed "+
    	    "for your Sacred Mandala, which you already have.\n");
        return "";
    }
    
    // If they don't already have the invisible mandala object, tell them 
    // what it is and direct them to Jardeth
    if (!(present("invismandala",TP)))
    {
    	write(TO->query_The_name(TP)+" telepathically says to you: The "+
    		"Sporos is the seed "+
    	    "for your Sacred Mandala. In order to construct your Sacred "+
    	    "Mandala, you shall "+
    	    "first have to get a Sporos. Begin your journey towards this "+
    	    "end by visiting "+
    	    "Jardeth in the herb garden and asking him about the Sporos.\n");
        return "";
    }
    
    // If they already have the invisible mandala object, find out where 
    // they are
    // in the task and point them in the proper direction
    if (present("invismandala",TP))
    {
    	invismandala=present("invismandala",TP);
    	task_status = invismandala->query_task_status();
    	switch(task_status)
    	{
    		//  0 - Just started the task, needs to pray to the Five in 
    		//      Obelisk Garden
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
		    	    "first have to get a Sporos. Begin your journey towards "+
		    	    "this end by visiting "+
		    	    "the Obelisk Garden near the cliff above the Temple. "+
		    	    "Once there, <pray to the "+
		    	    "Five>.\n");
		    	return "";
		    	break;
		    //  6 - Needs to talk to Jardeth about Seed Pod
    		case 6:
    			write(TO->query_The_name(TP)+" telepathically says to you: "+
    				"I see you have a Sporos "+
    			    "pod. You should take that to Jardeth and ask him "+
    			    "about it.\n");
		    	return "";
    			break;
    		//  7 - Needs to plant sporos seed in herb garden and water 
    		//      with vial	
    		case 7:
    			write(TO->query_The_name(TP)+" telepathically says to you: "+
    				"You should plant that "+
    			    "seed in the herb garden. Once you have done so, you "+
    			    "should pour the vial that "+
    			    "Jardeth gave you on it.\n");
	    		return "";
    			break;
    		//  71 - Planted the sporos seed and needs to water with vial	
    		case 71:
    			write(TO->query_The_name(TP)+" telepathically says to you: "+
    				"You should pour the vial that "+
    				"Jardeth gave you on to the seed you planted.\n");
	    		return "";
    			break;
    		//  8 - Needs to talk to Arial about Crystalline Seed (or Sporos)
    		case 8:
    			write(TO->query_The_name(TP)+" telepathically says to you: "+
    				"I see you have returned "+
    			    "from the herb garden with your Sporos crystalline seed. "+
    			    "You should now plant that "+
    			    "seed here in Earths Beholden. Once you have done so, "+
    			    "you should pour this vial "+
    			    "on it.\n");
    			clone_object(ELEMENTALIST_OBJS+
    				"sporos_crystalline_seed_vial")->move(TP,1);
    			write(TO->query_The_name(TP)+" hands you a vial.\n");
    			say(QCTNAME(TO)+" hands a vial to "+QTNAME(TO)+".\n");
    			invismandala->set_task_status(9);
    			return "";
    			break;
    		//  9 - Needs to plant crystalline seed in Earths Behold and 
    		//      pour vial on it
    		case 9:
    			write(TO->query_The_name(TP)+" telepathically says to you: "+
    				"You should now plant that "+
    			    "crystalline seed here in Earths Beholden. Once you "+
    			    "have done so, you should pour "+
    			    "the vial I gave you on it.\n");
    			return "";
    			break;
    		//  91 - Planted crystalline seed and needs to pour vial on it
    		case 91:
    			if (!present("seed shaped gem",TP))
    			{
    				write(TO->query_The_name(TP)+" telepathically says "+
    					"to you: You should now pour the vial I gave "+
	    			    "you on to the seed you planted.\n");
	    			return "";
	    		}
	    		write(TO->query_The_name(TP)+" telepathically says to "+
	    			"you: You should take that seed shaped "+
	    		    "gem to Tahla and ask her about it to continue.\n");
	    		return "";
    			break;
    		// 10 - Needs to talk to Tahla about Seed Gem (or Sporos)
    		case 10:
    			write(TO->query_The_name(TP)+" telepathically says to "+
    				"you: You should take that seed shaped gem "+
	    		    "to Tahla and ask her about it to continue.\n");
	    		return "";
    			break;
    		// 11 - Needs to prepare powder for Tiashe
    		case 11:
    			write(TO->query_The_name(TP)+" telepathically says to "+
    				"you: You should take that seed shaped gem "+
	    		    "to Tiashe and ask her about it to continue.\n");
	    		return "";
    			break;
    		// 12 - Needs to sprinkle powder on Seed Gem
    		case 12:
    			write(TO->query_The_name(TP)+" telepathically says to "+
    				"you: You should take that seed shaped gem "+
	    		    "to Tiashe and ask her about it to continue.\n");
	    		return "";
    			break;
    		// 13 - Needs to talk to Sehis about Seed Gem (or Sporos 
    		//      or Blessing)
    		case 13:
    			write(TO->query_The_name(TP)+" telepathically says "+
    				"to you: You should take that seed shaped gem "+
	    		    "to Sehis and ask her about it to continue.\n");
	    		return "";
    			break;
    		// Unknown or invalid value
    		default:
    			write(TO->query_The_name(TP)+" telepathically says "+
    				"to you: There seems to"+
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
	clone_object(ELEMENTALIST_OBJS+"fire_staff")->move(TO,1);
	TO->command("wield quarterstaff");
	clone_object(ELEMENTALIST_OBJS+"fire_mandala")->move(TO,1);
	TO->command("clasp mandala");
}

void
create_monster()
{
    set_name("Arial");
    add_name("arial");
    set_title("Luna-Diamondheart, the Master Lapidarist of the Elementals, "+
        "Glorious Erudite of Flame");
    set_adj(({"beautiful","white-cloaked"}));
    set_race_name("elf");
    set_living_name("arial");
    set_gender(G_FEMALE);

    set_stats(({300,300,300,300,300,300}));
    set_alignment(1200);
    set_skill(SS_DEFENCE,100);
    set_base_stat(SS_OCCUP, 300);
    set_base_stat(SS_LAYMAN, 300);
    set_appearance_offset(-50);
    set_width_desc("lean");
    set_height_desc("tall");

    add_prop(LIVE_I_ALWAYSKNOWN,1);
    add_prop("_npc_primary_element","fire");
    
    clone_object(EC_OCC_SHADOW)->shadow_me(TO,
        GUILD_EC_TYPE, "cleric", GUILD_EC_NAME, "");
    clone_object(EC_LAY_SHADOW)->shadow_me(TO,
        "layman", "cleric", GUILD_EC_NAME, "");
    clone_object(EC_RACE_SHADOW)->shadow_me(TO, "race", 
        "cleric", GUILD_EC_NAME, "");
    TP->add_subloc(EC_RACIAL_SUBLOC, TO);
    TO->arm_me();

    set_intro_delay(1);
    set_act_time(15);
    add_act("clasp mandala");
    add_act("clbow");
    add_act("clshake dirt");
    add_act("clpull");
    add_act("emote polishes her gemstones and you can't help but "+
        "notice her hands are yet stained with the ink she devoted "+
        "to writing the books in the library.");
    add_act("emote breathes deeply as a fresh breeze wafts in from the "+
        "garden.");
    add_act("emote telepathically says: It is not for me to reveal the "+
        "spiritual properties of gems. It is something you must discover "+
        "for yourself.");
    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"gem","gems","gemstone","gemstones"}),&gems_answer());
    add_ask(({"power","spiritual power"}),&power_answer());
    add_ask(({"flames","fire","pyros","lord pyros"}),&pyros_answer());
    add_ask(({"library","book","books"}),&library_answer());
    add_ask(({"task three","three","family task","family","third task",
    	"task 3","3rd task","3","task"}),&task_three_answer());
    add_ask(({"sporos","Sporos","Sporos seed","sporos seed",
    	"sporos crystalline seed","Sporos crystalline seed",
    	"crystalline seed","seed"}),&sporos_inquiry_response());
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
