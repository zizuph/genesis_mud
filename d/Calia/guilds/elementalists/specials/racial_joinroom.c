
/*
 * racial_joinroom.c
 *
 * This is the joinroom for the Elemental Clerics racial
 * guild. After becoming a Full Master Cleric, players 
 * can come to this room to join the Racial section of
 * the guild (if they want to). They can also leave the
 * racial guild here as well. 
 * 
 * Jaacar (Mike Phipps), July 2017
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Calia/guilds/elementalists/shadows/racial_options.h"
#include "defs.h"

#define CONNECTOR_ROOM    "/d/Calia/argos/nwterr/rooms/wfcave"
#define CONDUIT_ROOM      "/d/Calia/guilds/elementalists/temple/conduit"
#define DONE_SYMVIOSI     "_live_i_done_symviosi"
#define SYMVIOSI_DISSOLVE "_live_i_symviosi_dissolve"

// Global variables
string set_spirit, set_prefix, set_suffix;
int occupied = 0;

void
create_room()
{
    set_short("A chamber inside of the Conduit");
    set_long("@@long_description@@");
    
    add_exit(CONNECTOR_ROOM,"adeia","@@clean_props",1,1);
    add_exit(CONNECTOR_ROOM,"Adeia","@@clean_props",1,1);    

    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

}

public string
long_description()
{
    string long_desc = "You are standing in ";
    long_desc += CONDUIT_ROOM->query_external_conduit_desc();
    long_desc += ". It takes you a moment but you suddenly realize you "+
        "are standing IN the Conduit! ";
    
    if (!TP->is_elemental_racial_cleric() && !TP->query_prop(DONE_SYMVIOSI))
    {
    	long_desc += "A single word keeps echoing in your mind; Symviosi.\n";
    }
    else
    {
    	long_desc += "Two words keeps echoing in your mind; Symviosi and Adeia.\n";
    }
    
    return long_desc;
}

public void
set_occupied(int i)
{
	occupied = i;
}

public int
query_occupied()
{
	return occupied;
}

int
clean_props()
{
	TP->remove_prop(DONE_SYMVIOSI);
	TP->remove_prop(SYMVIOSI_DISSOLVE);
	set_occupied(0);
	set_spirit = 0;
	set_prefix = 0;
	set_suffix = 0;
	return 0;
}

public string *
query_title_spirits()
{
	return TITLE_SPIRITS;
}

public string *
query_title_prefix()
{
	return TITLE_SECONDS_PREFIX;
}

public string *
query_title_suffix()
{
	return TITLE_SECONDS_SUFFIX;
}

public int
do_symviosi(string str)
{
    string command, option1, option2, option3;
    
    string * spirits = query_title_spirits();
    string * prefixes = query_title_prefix();
    string * suffixes = query_title_suffix();
    
    if (!str)
    {
    	// If they aren't a racial member, show them options for joining
    	if (!TP->is_elemental_racial_cleric())
    	{
    		// If they haven't seen the introduction, show them it and the 
    		// instructions to join
	        if (!TP->query_prop(DONE_SYMVIOSI))
	        {
	            string *first_time = ({"\n\nYou close your eyes, clearing your mind "+
	            	"of everything and utter the word 'Symviosi'.\n\n",
					"\n\nJust as you open your eyes, the voice of Nysa echoes "+
					"in your mind saying, 'Greetings, "+capitalize(TP->query_real_name())+
					".'\n\n",
					"'You have entered a very sacred place. Here inside of this "+
					"area of the Conduit there is a connection with the Ancient "+
					"Kyrullians.'\n\n",
					"'The command you just invoked is actually the beginning of an "+
					"ancient ritual, the ritual of soul binding.'\n\n",
					"'This ritual will allow you to bind yourself with an Ancient "+
					"Kyrullian spirit of your choice.'\n\n",
					"'In order to do this you must have parted ways with all racial "+
					"relationships first, thus fully dedicating yourself to the "+
					"Five.'\n\n",
					"'If you are ready to proceed, you must first decide which "+
					"Ancient Kyrullian spirit you wish to bond with. To do so, "+
					"you can use <Symviosi spirits>.'\n\n",
					"'Once you have decided upon a spirit, you may use <Symviosi "+
					"choose spirit (Spiritname)>.'\n\n",
					"'You must then decide on your own portion of your Surname, "+
					"which is comprised of two parts, the prefix and the suffix. "+
					"To see what is available to you, you may use <Symviosi prefixes> "+
					"and <Symviosi suffixes>.'\n\n",
					"'Once you have decided upon a prefix and suffix, you may use "+
					"<Symviosi choose prefix (Prefix)> and <Symviosi choose suffix "+
					"(suffix)>.'\n\n",
					"'If you would like to review the options you have selected, "+
					"and to see what the final result will become, you may use "+
					"<Symviosi current>.'\n\n",
					"'Finally, once you are happy with your decisions, you may use "+
					"<Symviosi bind> to perform the ritual, binding the Ancient "+
					"Kyrullian spirit you have chosen to you.'\n\n",
					"'Choose wisely. Once you have bonded with the Ancient Kyrullian "+
					"spirit, you must dissolve the bond if you wish to change spirits.'\n\n",
					"'You may proceed if ready, otherwise you may use the ritual of "+
					"Adeia to leave this place.'\n\n"});    				
	    		for (int i=0; i < sizeof(first_time); i++)
	    			set_alarm((10.0*itof(i)), 0.0, &tell_object(TP, first_time[i]));
	    		TP->add_prop(DONE_SYMVIOSI,1);
	            return 1;
	        }
	        
	        // If they have seen the introduction, just give them the 
	        // instructions to join
	        string *second_time = ({"\n\nThe voice of Nysa echoes "+
				"in your mind saying, 'Greetings, "+capitalize(TP->query_real_name())+
				".'\n\n",
				"'If you are ready to proceed, you must first decide which "+
				"Ancient Kyrullian spirit you wish to bond with. To do so, "+
				"you can use <Symviosi spirits>.'\n\n",
				"'Once you have decided upon a spirit, you may use <Symviosi "+
				"choose spirit (Spiritname)>.'\n\n",
				"'You must then decide on your own portion of your Surname, "+
				"which is comprised of two parts, the prefix and the suffix. "+
				"To see what is available to you, you may use <Symviosi prefixes> "+
				"and <Symviosi suffixes>.'\n\n",
				"'Once you have decided upon a prefix and suffix, you may use "+
				"<Symviosi choose prefix (Prefix)> and <Symviosi choose suffix "+
				"(suffix)>.'\n\n",
				"'If you would like to review the options you have selected, "+
				"and to see what the final result will become, you may use "+
				"<Symviosi current>.'\n\n",
				"'Finally, once you are happy with your decisions, you may use "+
				"<Symviosi bind> to perform the ritual, binding the Ancient "+
				"Kyrullian spirit you have chosen to you.'\n\n",
				"'Choose wisely. Once you have bonded with the Ancient Kyrullian "+
				"spirit, you must dissolve the bond if you wish to change spirits.'\n\n",
				"'You may proceed if ready, otherwise you may use the ritual of "+
				"Adeia to leave this place.'\n\n"});    				
    		for (int i=0; i < sizeof(second_time); i++)
    			set_alarm((10.0*itof(i)), 0.0, &tell_object(TP, second_time[i]));
    		return 1;
        }
        
        // They are elemental racial members so show them instructions
        // on how to leave the guild
        string *not_first_time = ({"\n\nYou close your eyes, clearing your mind "+
        	"of everything and utter the word 'Symviosi'.\n\n",
			"Just as you open your eyes, the voice of Nysa echoes "+
			"in your mind saying, 'Greetings, "+capitalize(TP->query_real_name())+
			".'\n\n",
			"'If you wish to dissolve the binding, you may use <Symviosi "+
			"dissolve>, otherwise you may use the ritual of Adeia to leave "+
			"this place.'\n\n"});  				
		for (int i=0; i < sizeof(not_first_time); i++)
			set_alarm((10.0*itof(i)), 0.0, &tell_object(TP, not_first_time[i]));
        return 1;
    }
    
    // They want to see their current settings (and completed Surname if
    // they have selected everything
    if (str == "current")
    {
    	if (TP->is_elemental_racial_cleric())
    		return 0;
    		
    	write("\nYour currently chosen options are:\n");
    	if (set_spirit)
    		write("Chosen Spirit: "+set_spirit+"\n");
    	else
    		write("Chosen Spirit: None\n");
    	if (set_prefix)
    		write("Chosen Prefix: "+set_prefix+"\n");
    	else
    		write("Chosen Prefix: None\n");
    	if (set_suffix)
    		write("Chosen Suffix: "+set_suffix+"\n");
    	else
    		write("Chosen Suffix: None\n");
    	
    	if ((set_spirit) && (set_prefix) && (set_suffix))
    		write("With the current chosen options, your Surname would be: "+
    		    set_spirit + "-" + set_prefix + set_suffix + "\n");
    	write("\n");
    	return 1;
    }
    
    // They want to see their options for Spirit names to bond with
    if (str == "spirits")
    {    		
        int index;
		
		if (TP->is_elemental_racial_cleric())
    		return 0;
    				
		write("You can choose one of the following Spirits to bond with:\n");
		for (index = 0; index < sizeof (spirits); index++)
		{
		    write(spirits[index]);
		    if (index == sizeof (spirits)- 1)
		    	write(".");
		    else
		    	write(", ");
		}
		write("\n\n");
		return 1;
	}
    
    // They want to see their options for prefixes for their chosen Surname
    if (str == "prefixes")
    {
        int index;
				
		if (TP->is_elemental_racial_cleric())
    		return 0;
    		
		write("You can choose one of the following prefixes:\n");
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
    
    // They want to see their options for suffixes for their chosen Surname
    if (str == "suffixes")
    {
        int index;
				
		if (TP->is_elemental_racial_cleric())
    		return 0;
    		
		write("You can choose one of the following suffixes:\n");
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
    
    // They want to leave the racial guild
    if (str == "dissolve")
    {
    	string spirit_name = GUILD_MANAGER->query_racial_spirit_surname(TP);
    	
    	// Not an elemental cleric so the can no longer dissolve the binding
    	if (!TP->is_elemental_racial_cleric())
    		return 0;
    	
    	// If they don't have the prop, make them confirm they want to end
    	// the binding	
    	if (!TP->query_prop(SYMVIOSI_DISSOLVE))
    	{
    		write("You hear the voice of "+spirit_name+" echo in your mind: "+
	    	    "'If you are certain you want to dissolve the bonding, use the "+
	    	    "command <Symviosi dissolve> again.\n");
	    	TP->add_prop(SYMVIOSI_DISSOLVE, 1);
	    	return 1;
	    }
	    
	    // They have confirmed they want to end the binding, so do so
	    write("You hear the voice of "+spirit_name+" echo in your mind: 'I'm sorry "+
	        "that you have decided to end our bonding. May the Elementals forever "+
	        "guide you upon your path.'\n");
	    write("The aura surrounding you fades away and you no longer feel the spirit "+
	        "of "+spirit_name+" bound with you.\n");
	    GUILD_MANAGER->leave_race_guild(TP);
	    return 1;
	}
    
    // They want to finalize the bonding and join the racial guild
    if (str == "bind")
    {
    	if (TP->is_elemental_racial_cleric())
    		return 0;
    	
    	if (!set_spirit)
    	{
    		write("You must choose an Ancient Kyrullian spirit to bond with first. "+
    		    "(<Symviosi spirits> to view the list of available spirits, <Symviosi "+
    		    "choose (Spiritname)> to choose one)\n");
    		return 1;
    	}
    	
    	if (!set_prefix)
    	{
    		write("You must choose a prefix for your chosen Surname. "+
    		    "(<Symviosi prefixes> to view the list of available prefixes, <Symviosi "+
    		    "choose (Prefix)> to choose one)\n");
    		return 1;
    	}
    	
    	if (!set_suffix)
    	{
    		write("You must choose a suffix for your chosen Surname. "+
    		    "(<Symviosi suffixes> to view the list of available suffixes, <Symviosi "+
    		    "choose (suffix)> to choose one)\n");
    		return 1;
    	}
    	
    	string *binding_messages = ({"\n\nYou close your eyes, clearing your mind "+
        	"of everything and utter the words 'Symviosi bind'.\n\n",
			"An ancient timeless voice echoes in your mind, 'Greetings "+
			capitalize(TP->query_real_name())+".'\n\n", 
            "'You have invoked the ritual of Symviosi and called into the "+
            "Between. Through the teachings of Nysa and the grace of the "+
            "Fifth, I have responded.'\n\n",
			"'My name is " + set_spirit + " and I lived before the Dim "+
			"Time. I was a Kyrullian Cleric and my time was vested in "+
			"the teachings of our Ways.'\n\n",
			"'I look forward to the bonding and travelling with you.'\n\n",
			"You hand seems guided from beyond as you draw strange arcane "+
			"glyphs on your chest. They suddenly begin to glow with an "+
			"eerie silvery and shadowy glow, and your mandala begins to "+
            "thrum in response.\n\n",
			"You touch your sacred mandala to the glyphs on your chest and "+
			"feel the energies of the Conduit coursing through your very "+
			"soul.\n\n",
			"Every vein in your body begins to pulse with energy. Colorful "+
			"rays of light flow outward from your mandala, covering your "+
            "entire body.\n\n",
            "Everything suddenly stops and goes absolutely quiet. You no longer "+
            "feel the energy flowing through your body however you see a faint "+
            "aura surrounding you.\n\n",
            set_spirit + " speaks in your mind: 'My essence flows through you "+
            "now. Your gift of Synadyasmos is strengthened and I have imparted "+
            "upon you the Spirit Sight in your elemental form. You should also "+
            "visit your halls of training as I have shared with you my experiences "+
            "of a life of a cleric long past.\n\n",
            "You somehow feel you have done all you can here and should use the "+
            "ritual of Adeia.\n\n"});
        string full_surname = set_prefix + set_suffix;  
    	if (GUILD_MANAGER->join_racial_guild(TP, set_spirit, full_surname))
    	{ 				
			for (int i=0; i < sizeof(binding_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(TP, binding_messages[i]));
			return 1;
		}	  
    	return 1;
    }
    	
    // They gave three parameters (this should be the choose command)
    if (sscanf(str, "%s %s %s", command, option1, option2) == 3)
    {
    	if (TP->is_elemental_racial_cleric())
    		return 0;
    		
        if (command != "choose")
        {
            NF("Valid options are: bind, current, spirits, prefixes, "+
   		    "suffixes, choose spirit <Spiritname>, choose prefix <Prefix>, "+
   		    "choose suffix <suffix>\n");
            return 0;
        }
        if (option1 == "prefix")
        {
            // choose the prefix
            option2 = capitalize(option2);
			if (!IN_ARRAY(option2,prefixes))
			{
				notify_fail("The option "+option2+" is not a "+
					"valid prefix.\n");
				return 0;
			}			

            write("You have chosen "+option2+" as your prefix.\n");
            set_prefix = option2;
            return 1;
        }
        
        if (option1 == "suffix")
        {
            // choose the suffix
            option2 = lower_case(option2);
			if (!IN_ARRAY(option2,suffixes))
			{
				notify_fail("The option "+option2+" is not a "+
					"valid suffix.\n");
				return 0;
			}			

            write("You have chosen "+option2+" as your suffix.\n");
            set_suffix = option2;
            return 1;
        }
        
        if (option1 == "spirit")
        {
            // choose the spirit
            option2 = capitalize(option2);
			if (!IN_ARRAY(option2,spirits))
			{
				notify_fail(option2+" is not a valid Ancient Kyrullian "+
					"spirit.\n");
				return 0;
			}			

            write("You have chosen "+option2+" as your Ancient Kyrullian spirit.\n");
            set_spirit = option2;
            return 1;
        }
        
        NF("Valid options are: bind, current, spirits, prefixes, "+
   		    "suffixes, choose spirit <Spiritname>, choose prefix <Prefix>, "+
   		    "choose suffix <suffix>\n");
        return 0;
    }
    
    // They didn't choose a valid option, show them the valid options based
    // on them being a member or not
    if (!TP->is_elemental_racial_cleric())
   	{
   		write("Valid options are: bind, current, spirits, prefixes, "+
   		    "suffixes, choose spirit <Spiritname>, choose prefix <Prefix>, "+
   		    "choose suffix <suffix>\n");
    }
    else
    {
    	write("Valid options are: dissolve\n");
    }
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_symviosi,"symviosi");
    add_action(do_symviosi,"Symviosi");
}
