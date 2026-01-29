/*
 * Racial Command Soul for the Elemental Clerics of Calia
 *
 * This is the command soul that every Elemental Cleric will
 * have. It includes emotes as well as the abilities/spells that they
 * possess.
 *
 * Created by Petros, April 2010
 */

#pragma strict_types

#include <cmdparse.h>
#include <macros.h>
#include <files.h>
#include <ss_types.h>
#include <composite.h>
#include <filter_funs.h>
#include "../defs.h"

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";
inherit "/d/Genesis/specials/guilds/lib/utility_functions";

#define MEMBER_LIST_UTILITY ("/d/Calia/guilds/elementalists/lib/member_list_utility")
#define RACIAL_TITLE_HANDLER  (ELEMENTALIST_SPECIALS + "title_handler")

static string * FIRE_MESSENGERS   = ({"flame","salamander","beetle","spider"});
static string * FIRE_MOUNTS       = ({"djini"});
static string * AIR_MESSENGERS    = ({"cloud","stalker","beetle","spider"});
static string * AIR_MOUNTS        = ({"spirit"});
static string * WATER_MESSENGERS  = ({"globe","strider","beetle","spider"});
static string * WATER_MOUNTS      = ({"weird"});
static string * EARTH_MESSENGERS  = ({"cloud","basilisk","beetle","spider"});
static string * EARTH_MOUNTS      = ({"golem"});
static string * SPIRIT_MESSENGERS = ({"ball","crab","beetle","spider"});
static string * SPIRIT_MOUNTS     = ({"wisp"});

/* 
 * Function name: get_soul_id
 * Description:   Give a name for this soul
 * Returns:       string - the soul's id
 */
public string
get_soul_id() 
{ 
    return GUILD_EC_NAME + " Racial Soul"; 
}

/*
 * Function name: query_cmd_soul
 * Description:   identify this as a valid cmdsoul
 * Returns:       1
 */
public int 
query_cmd_soul() 
{
    return 1; 
}
  
public mapping
query_cmdlist()
{ 
    return ([
        /* Command name : Function name */
        // Spells
        	
        // Guild Abilities            
        "emessenger"    : "emessenger",
        "kyrullians"    : "ekyrullians",
        "ekyrullians"   : "ekyrullians",
        "esurname"      : "esurname",
        "eoptions"      : "eoptions",	
        // Emotes

        // Help and Options
        "help"          : "help", 

    ]);
}

public mapping
query_ability_map()
{
    return ([

    ]);
}

public int
emessenger()
{
    object messenger;
    string pelem, diety, mess_desc, mess_arrives, mess_departs;
    string emessenger_option;
    
    pelem = GUILD_MANAGER->query_primary_element(TP);
    emessenger_option = GUILD_MANAGER->query_emessenger_option(TP);

    if(!pelem)
    	return 0;    	    	
    
    setuid(); 
    seteuid(getuid());
    messenger = clone_object(ELEMENTALIST_OBJS + "racial_messenger");
    switch(pelem)
    {
    	case "fire":
    		switch(emessenger_option)
    		{
    			case "salamander":
    				messenger->set_adj1("red");
		    		messenger->set_mess_desc("salamander");
		    		messenger->set_mess_departs("scurries away");
		    		messenger->set_mess_arrives("jumps up and sits");
		    		mess_desc = "small red salamander";
		    		break;
		    	case "beetle":
    				messenger->set_adj1("red");
		    		messenger->set_mess_desc("beetle");
		    		messenger->set_mess_departs("flies away");
		    		messenger->set_mess_arrives("flies up and lands");
		    		mess_desc = "small red beetle";
		    		break;
		    	case "spider":
    				messenger->set_adj1("red");
		    		messenger->set_mess_desc("spider");
		    		messenger->set_mess_departs("skitters away");
		    		messenger->set_mess_arrives("skitters up and sits");
		    		mess_desc = "small red fire spider";
		    		break;
    			default:
		    		messenger->set_adj1("red");
		    		messenger->set_mess_desc("flame");
		    		messenger->set_mess_departs("floats up slowly until you can no "+
		    			"longer see it");
		    		messenger->set_mess_arrives("descends from the sky and lands");
		    		mess_desc = "small red flame";
		    		break;
		    }
    		diety = "Lord Pyros";
    		break;
    	case "air":
    		switch(emessenger_option)
    		{
    			case "stalker":
    				messenger->set_adj1("warp");
		    		messenger->set_mess_desc("stalker");
		    		messenger->set_mess_departs("blinks away");
		    		messenger->set_mess_arrives("blinks into view and sits");
		    		mess_desc = "small warp stalker";
		    		break;
		    	case "beetle":
    				messenger->set_adj1("white");
		    		messenger->set_mess_desc("beetle");
		    		messenger->set_mess_departs("flies away");
		    		messenger->set_mess_arrives("flies up and lands");
		    		mess_desc = "small white beetle";
		    		break;
		    	case "spider":
    				messenger->set_adj1("white");
		    		messenger->set_mess_desc("spider");
		    		messenger->set_mess_departs("skitters away");
		    		messenger->set_mess_arrives("skitters up and sits");
		    		mess_desc = "small white spider";
		    		break;
    			default:
		    		messenger->set_adj1("white");
		    		messenger->set_mess_desc("cloud");
		    		messenger->set_mess_departs("floats up slowly until you can no "+
		    			"longer see it");
		    		messenger->set_mess_arrives("descends from the sky and lands");
		    		mess_desc = "small white cloud";
		    		break;
		    }
    		diety = "Lady Aeria";    		
    		break;
    	case "water":
    		switch(emessenger_option)
    		{
    			case "strider":
    				messenger->set_adj1("water");
		    		messenger->set_mess_desc("strider");
		    		messenger->set_mess_departs("skitters away");
		    		messenger->set_mess_arrives("skitters up and sits");
		    		mess_desc = "small water strider";
		    		break;
		    	case "beetle":
    				messenger->set_adj1("blue");
		    		messenger->set_mess_desc("beetle");
		    		messenger->set_mess_departs("flies away");
		    		messenger->set_mess_arrives("flies up and lands");
		    		mess_desc = "small blue beetle";
		    		break;
		    	case "spider":
    				messenger->set_adj1("blue");
		    		messenger->set_mess_desc("spider");
		    		messenger->set_mess_departs("skitters away");
		    		messenger->set_mess_arrives("skitters up and sits");
		    		mess_desc = "small blue spider";
		    		break;
    			default:
		    		messenger->set_adj1("watery");
		    		messenger->set_mess_desc("globe");
		    		messenger->set_mess_departs("floats up slowly until you can no "+
		    			"longer see it");
		    		messenger->set_mess_arrives("descends from the sky and lands");
		    		mess_desc = "small watery globe";
		    		break;
		    }
    		diety = "Lord Diabrecho";    		
    		break;
    	case "earth":
    		switch(emessenger_option)
    		{
    			case "basilisk":
    				messenger->set_adj1("green");
		    		messenger->set_mess_desc("basilisk");
		    		messenger->set_mess_departs("runs away");
		    		messenger->set_mess_arrives("runs up and sits");
		    		mess_desc = "small green basilisk";
		    		break;
		    	case "beetle":
    				messenger->set_adj1("green");
		    		messenger->set_mess_desc("beetle");
		    		messenger->set_mess_departs("flies away");
		    		messenger->set_mess_arrives("flies up and lands");
		    		mess_desc = "small green beetle";
		    		break;
		    	case "spider":
    				messenger->set_adj1("crystalline");
		    		messenger->set_mess_desc("spider");
		    		messenger->set_mess_departs("skitters away");
		    		messenger->set_mess_arrives("skitters up and sits");
		    		mess_desc = "small crystalline spider";
		    		break;
    			default:
		    		messenger->set_adj1("dust");
		    		messenger->set_mess_desc("cloud");
		    		messenger->set_mess_departs("floats up slowly until you can no "+
		    			"longer see it");
		    		messenger->set_mess_arrives("descends from the sky and lands");
		    		mess_desc = "small dust cloud";
		    		break;
		    }
    		diety = "Lady Gu";    		
    		break;
    	default:
    		switch(emessenger_option)
    		{
    			case "crab":
    				messenger->set_adj1("spectral");
		    		messenger->set_mess_desc("crab");
		    		messenger->set_mess_departs("scurries away");
		    		messenger->set_mess_arrives("scurries up and sits");
		    		mess_desc = "small spectral crab";
		    		break;
		    	case "beetle":
    				messenger->set_adj1("black");
		    		messenger->set_mess_desc("beetle");
		    		messenger->set_mess_departs("flies away");
		    		messenger->set_mess_arrives("flies up and lands");
		    		mess_desc = "small black beetle";
		    		break;
		    	case "spider":
    				messenger->set_adj1("purple");
		    		messenger->set_mess_desc("spider");
		    		messenger->set_mess_departs("skitters away");
		    		messenger->set_mess_arrives("skitters up and sits");
		    		mess_desc = "small purple spider";
		    		break;
    			default:
		    		messenger->set_adj1("shadowy");
		    		messenger->set_mess_desc("ball");
		    		messenger->set_mess_departs("floats up slowly until you can no "+
		    			"longer see it");
		    		messenger->set_mess_arrives("descends from the sky and lands");
    				mess_desc = "small shadowy ball";
    				break;
    		}
    		diety = "Psuchae";    		
    		break;
    }
    messenger->move(TP,1);
    write("Concentrating on the powers granted to you by " + diety + 
        ", you summon a " + mess_desc + " from the Elemental Plane.\n");
    say(QCTNAME(TP)+" appears to concentrate for a brief moment. Suddenly "+
        "a " + mess_desc + " appears in " + TP->query_possessive() +
        " hands.\n");
    return 1;
}

public int
ekyrullians(string str)
{
    setuid();
    seteuid(getuid());
    
    MEMBER_LIST_UTILITY->list_racials();
    
    return 1;
}

/*
 * Function:    help
 * Description: Handler for the help system for Elemental Guilds
 */
public int
help(string str)
{
    // Access help files
    string content, *files; 
    setuid(); 
    seteuid(getuid()); 

    if (!stringp(str) || !strlen(str))
    { 
        return 0; 
    }
    
    if (str == "kyrullian" || str == "kyrullians") 
    {         
        if (!pointerp(files = get_dir(ELEMENTALIST_RACIAL_HELP)) || 
        	!sizeof(files))
        {
            return 0; 
        }
        
        if (!stringp(content = read_file(ELEMENTALIST_RACIAL_HELP +
        	"general")))
        {
            notify_fail("Something is terribly wrong! Please contact " +
                "the guildmaster and let them know that the kyrullian "+
                "help files for the Clerics are not working property.\n");
            return 0;
        }
        
        write("You fuss around with your notes and read the scroll "
            + "introducing the Elemental Kyrullians of Calia.\n");
        this_player()->more(generate_scroll_text(content, "Property of the "+
            "Elemental Guilds of Calia"));
        return 1;
    } 

    if (sscanf(str, "kyrullians %s", str) != 1)
    {
        if (sscanf(str, "kyrullian %s", str) !=1)
            return 0;
    }
    
    str = lower_case(str); // set everything to lowercase
    // Players can get information about spells that they know        
    
    if (stringp(content = read_file(ELEMENTALIST_RACIAL_HELP + str)))
    {        
        write("You flip through your guild scrolls and read the scroll "
            + "pertaining to " + capitalize(str) + ".\n");
        this_player()->more(generate_scroll_text(content, "Property of the "+
            "Elemental Guilds of Calia")); 
        return 1;         
    }

    notify_fail("You can't seem to find any scrolls on that topic "
        + "among the notes that you received upon joining the "
        + "kyrullians.\n"); 
    return 0;     
}

public int
esurname(string str)
{
	string command, option1, option2;
	string * prefixes;
	string * suffixes;
	string title;
	int index;
   
	if (!str)
	{
		notify_fail("Ksurname valid commands: current, options prefixes, "+
		    "options suffixes, set <prefix> <suffix>, hide, unhide\n");
		return 0;
	}
	
	// They gave four parameters (this should be the set command)
	if (sscanf(str, "%s %s %s", command, option1, option2) == 3)
	{
		if (command == "set")
		{
			prefixes = TP->query_title_prefix();
			suffixes = TP->query_title_suffix();					

			
			// check if option1 is a valid prefix - if not
			// then tell them
			option1 = capitalize(option1);
			option2 = lower_case(option2);
			if (!IN_ARRAY(option1,prefixes))
			{
				notify_fail("The option "+option1+" is not a "+
					"valid prefix.\n");
				return 0;
			}
			
			// check if option2 is a valid suffix - if not
			// then tell them
			if (!IN_ARRAY(option2,suffixes))
			{
				notify_fail("The option "+option2+" is not a "+
					"valid suffix.\n");
				return 0;
			}
			
			// Both options are valid, put the title
			// together and record it
				
			title = option1 + option2;
				
			GUILD_MANAGER->set_racial_chosen_surname(TP,title);
			write("Your new chosen Kyrullian surname has been set as:\n"+
			    title+"\n\n");
			return 1;			
		}	
		notify_fail("The option "+str+" is not valid.\n");
		return 0;
	}
	
	// They gave two parameters (this should be the options command)
	if (sscanf(str, "%s %s", command, option1) == 2)
	{
		if (command == "options")
		{
			if (option1 == "prefixes")
			{
				prefixes = TP->query_title_prefix();
				
				write("You can select one of the following prefixes:\n");
				for (index = 0; index < sizeof (prefixes); index++)
				{
				    write(prefixes[index]);
				    if (index == sizeof (prefixes)- 1)
				    	write(".");
				    else
				    	write(", ");
				}
				write("\n\n");
				return 1;
			}
			if (option1 == "suffixes")
			{
				suffixes = TP->query_title_suffix();
				
				write("You can select one of the following suffixes:\n");
				for (index = 0; index < sizeof (suffixes); index++)
				{
				    write(suffixes[index]);
				    if (index == sizeof (suffixes)- 1)
				    	write(".");
				    else
				    	write(", ");
				}
				write("\n\n");
				return 1;
			}					
		}
		notify_fail("The option "+str+" is not valid with the options "+
		    "command. Valid options are: prefixes, suffixes.\n");
		return 0;
	}
	
	// They gave one command (this should be current, hide or unhide)
	if (sscanf(str, "%s", command) == 1)
	{
		if (command == "current")
		{
		    if (GUILD_MANAGER->query_racial_spirit_surname(TP))
		    {
		        title = (GUILD_MANAGER->query_racial_spirit_surname(TP));
		        title += "-";
		        title += (GUILD_MANAGER->query_racial_chosen_surname(TP));
		    }
		    
		    if (title)
		        write("Your current Kyrullian surname is: "+title+"\n");
		    else
		        write("You don't have a Kyrullian surname yet.\n");
		        
		    if (GUILD_MANAGER->query_racial_hide_title(TP))
		        write("(Currently you are hiding your Kyrullian surname.)\n");
			return 1;
		}
		
		if (command == "hide")
		{
			write("You are now hiding your Kyrullian surname.\n");
			GUILD_MANAGER->set_racial_hide_title(TP,1);
			return 1;
		}
		
		if (command == "unhide")
		{
			write("You are now not hiding your Kyrullian surname.\n");
			GUILD_MANAGER->set_racial_hide_title(TP,0);
			return 1;
		}
		
		if (command == "options")
		{
			write("Valid options are: prefixes, suffixes.\n");
			return 1;
		}
		
		notify_fail("The option "+command+" is not valid.\n");
		return 0;
	}
	notify_fail("Ksurname valid commands: current, options prefixes, "+
		"options suffixes, set <prefix> <suffix>, hide, unhide\n");
	return 0;
}

public int
eoptions(string str)
{
	string command, option1, option2;
	string pelem;
	string current_messenger;
	string current_mount;
	string * messengers;
	string * mounts;

	int index;
   
	if (!str)
	{
		notify_fail("Eoptions valid commands: current, options messengers, "+
		    "options mounts, set messenger <option>, set mount <option>\n");
		return 0;
	}
	
	pelem = GUILD_MANAGER->query_primary_element(TP);
	switch(pelem)
	{
		case "fire":
			messengers = FIRE_MESSENGERS;
			mounts = FIRE_MOUNTS;
			break;
		case "air":
			messengers = AIR_MESSENGERS;
			mounts = AIR_MOUNTS;
			break;
		case "water":
			messengers = WATER_MESSENGERS;
			mounts = WATER_MOUNTS;
			break;
		case "earth":
			messengers = EARTH_MESSENGERS;
			mounts = EARTH_MOUNTS;
			break;
		default:
			messengers = SPIRIT_MESSENGERS;
			mounts = SPIRIT_MOUNTS;
			break;
	}
	
	// They gave four parameters (this should be the set command)
	if (sscanf(str, "%s %s %s", command, option1, option2) == 3)
	{
		if (command == "set")
		{
			// check if option1 is a valid command - if not
			// then tell them
			option1 = lower_case(option1);
			if (option1 != "messenger")
			{
				if (option1 != "mount")
				{
					notify_fail("The command "+option1+" is not valid.\n");
					return 0;
				}
			}
			
			option2 = lower_case(option2);
			if (!IN_ARRAY(option2,messengers))
			{
				if (!IN_ARRAY(option2,mounts))
				{
					notify_fail("The option "+option2+" is not a "+
						"valid option.\n");
					return 0;
				}
			}
				
			if (option1 == "messenger")
			{
				// check if option2 is a valid messenger - if not
				// then tell them
				if (!IN_ARRAY(option2,messengers))
				{
					notify_fail("The option "+option2+" is not a "+
						"valid option for messengers.\n");
					return 0;
				}
				GUILD_MANAGER->set_emessenger_option(TP,option2);
				write("Your have selected your new Elemental messenger as "+
					"a "+option2+".\n\n");
				return 1;
			}
			else
			{
				// check if option2 is a valid mount - if not
				// then tell them
				if (!IN_ARRAY(option2,mounts))
				{
					notify_fail("The option "+option2+" is not a "+
						"valid option for mounts.\n");
					return 0;
				}
				GUILD_MANAGER->set_emount_option(TP,option2);
				write("Your have selected your new Elemental mount as "+
					"a "+option2+".\n\n");
				return 1;
			}						
		}	
		notify_fail("The option "+str+" is not valid.\n");
		return 0;
	}
	
	// They gave two parameters (this should be the options command)
	if (sscanf(str, "%s %s", command, option1) == 2)
	{
		if (command == "options")
		{
			if (option1 == "messengers")
			{
				write("You can select one of the following messengers:\n");
				for (index = 0; index < sizeof (messengers); index++)
				{
				    write(messengers[index]);
				    if (index == sizeof (messengers)- 1)
				    	write(".");
				    else
				    	write(", ");
				}
				write("\n\n");
				return 1;
			}
			if (option1 == "messenger")
			{
				write("You can select one of the following messengers:\n");
				for (index = 0; index < sizeof (messengers); index++)
				{
				    write(messengers[index]);
				    if (index == sizeof (messengers)- 1)
				    	write(".");
				    else
				    	write(", ");
				}
				write("\n\n");
				return 1;
			}
			if (option1 == "mounts")
			{
				write("You can select one of the following mounts:\n");
				for (index = 0; index < sizeof (mounts); index++)
				{
				    write(mounts[index]);
				    if (index == sizeof (mounts)- 1)
				    	write(".");
				    else
				    	write(", ");
				}
				write("\n\n");
				return 1;
			}
			if (option1 == "mount")
			{
				write("You can select one of the following mounts:\n");
				for (index = 0; index < sizeof (mounts); index++)
				{
				    write(mounts[index]);
				    if (index == sizeof (mounts)- 1)
				    	write(".");
				    else
				    	write(", ");
				}
				write("\n\n");
				return 1;
			}					
		}
		notify_fail("The option "+str+" is not valid with the options "+
		    "command. Valid options are: messengers, mounts.\n");
		return 0;
	}
	
	// They gave one command (this should be current)
	if (sscanf(str, "%s", command) == 1)
	{
		if (command == "current")
		{
		    current_messenger = (GUILD_MANAGER->query_emessenger_option(TP));
		    current_mount = (GUILD_MANAGER->query_emount_option(TP));
		    
		    if (current_messenger)
		        write("Your current Elemental messenger is set as a "+
		        	current_messenger+".\n");
		    else
		    {
		    	switch(pelem)
				{
					case("fire"):
						current_messenger = "flame";
						break;
					case("air"):
						current_messenger = "cloud";
						break;
					case("water"):
						current_messenger = "globe";
						break;
					case("earth"):
						current_messenger = "cloud";
						break;
					default:
						current_messenger = "ball";
						break;
				}	
		        write("Your current Elemental messenger is set as a "+
		        	current_messenger+".\n");
		    }
		    
		    if (current_mount)
		        write("Your current Elemental mount is set as a "+
		        	current_mount+".\n");
		    else
		    {
		    	switch(pelem)
				{
					case("fire"):
						current_mount = "djini";
						break;
					case("air"):
						current_messenger = "spirit";
						break;
					case("water"):
						current_messenger = "weird";
						break;
					case("earth"):
						current_messenger = "golem";
						break;
					default:
						current_messenger = "wisp";
						break;
				}	
		        write("Your current Elemental mount is set as a "+
		        	current_mount+".\n");
		    }    
		    return 1;
		}
		
		notify_fail("The option "+command+" is not valid.\n");
		return 0;
	}
	notify_fail("Eoptions valid commands: current, options messengers, "+
		"options mounts, set messenger <option>, set mount <option>\n");
	return 0;
}
