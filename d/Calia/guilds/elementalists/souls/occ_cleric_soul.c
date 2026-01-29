/*
 * Occupational Command Soul for the Elemental Clerics of Calia
 *
 * This is the command soul that every Elemental Cleric will
 * have. It includes emotes as well as the abilities/spells that they
 * possess.
 *
 * Created by Petros, April 2010
 */

#pragma strict_types

#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <time.h>
#include "../defs.h"

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";
inherit "/d/Genesis/specials/guilds/lib/utility_functions";

#define MEMBER_LIST_UTILITY ("/d/Calia/guilds/elementalists/lib/member_list_utility")
#define SOULDESC(x) (TP->add_prop(LIVE_S_SOULEXTRA, x))

/* 
 * Function name: get_soul_id
 * Description:   Give a name for this soul
 * Returns:       string - the soul's id
 */
public string
get_soul_id() 
{ 
    return GUILD_EC_NAME + " Occupational Soul"; 
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
        "etitle"        : "etitle",     // Custom title routine
        	
        // Emotes
        "eassess"       : "eassess",
        "ebless"        : "ebless",
        "ebrush"        : "ebrush",
        "eboredom"      : "eboredom",
        "echant"        : "echant",
        "ech"           : "echant",
        "echoose"       : "echoose",
        "eclose"        : "eclose",
        "econgratulate" : "econgratulate",
        "econsume"      : "econsume",
        "edisgust"      : "edisgust",
        "ecdismiss"     : "ecdismiss",
        "eembrace"      : "eembrace",
        "eeyes"         : "eeyes",
        "efare"         : "efarewell",
        "efarewell"     : "efarewell",
        "egaze"         : "egaze",
        "egesture"      : "egesture",
        "eglare"        : "eglare",
        "egrin"         : "egrin",
        "ehail"         : "ehail",
        "ehug"          : "ehug",
        "eincline"      : "eincline",
        "ejoy"          : "ejoy",
        "eknee"         : "eknee",
        "ekneel"        : "ekneel",
        "elaugh"        : "elaugh",
        "epause"        : "epause",
        "eplay"         : "eplay",
        "epray"         : "epray",
        "eprepare"      : "eprepare",
        "erage"         : "erage",
        "eraise"        : "eraise",
        "erise"         : "erise",
        "eshrug"        : "eshrug",
        "eshake"        : "eshake",
        "esilence"      : "esilence",
        "esmile"        : "esmile",
        "esnap"         : "esnap",
        "estand"        : "estand",
        "estretch"      : "estretch",
        "etense"        : "etense",
        "ethank"        : "ethank",
        "eunimpressed"  : "eunimpressed",
        "evictory"      : "evictory",
        	
            
        // Help and Options
        "elist"         : "elist",
        "enotify"       : "enotify",
    ]);
}

public mapping
query_ability_map()
{
    return ([

    ]);
}

public string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}

int
is_spirit(object living)
{
    return living->query_guild_name_occ() == "Spirit Circle of Psuchae";
}

int
is_seeker(object living)
{
	return living->query_guild_name_lay() == GUILD_ES_NAME;
}

int
is_worship(object living)
{
    return living->query_guild_name_lay() == GUILD_EW_NAME;
}

int
is_cleric(object living)
{
	return living->query_guild_name_occ() == GUILD_EC_NAME;
}

string
group_desc(object looking, object *group, int cap)
{
    string *qdesc, qd;

    if (member_array(looking, group) > -1) {
        group -= ({looking});
        if (cap)
            qdesc = ({"You"});
        else
            qdesc = ({"you"});
        if (sizeof(group))
            qdesc += map(group, &->query_the_name(looking));
    }
    else {
        if (cap)
            qdesc = ({group[0]->query_The_name(looking) });
        else
            qdesc = ({group[0]->query_the_name(looking) });
        group -= ({group[0]});
        if (sizeof(group))
            qdesc += map(group, &->query_the_name(looking));
    }

    return COMPOSITE_WORDS(qdesc); 
}

public int
enotify(string str)
{
	string option1, option2;
	
	if (!str)
	{
		// Display current options here plus valid syntax
		if (GUILD_MANAGER->query_stop_all_notifications(TP))
			write("All Notifications: Off\n");
		else
		{
			if (GUILD_MANAGER->query_stop_cleric_notifications(TP))
				write("Cleric Notifications: Off\n");
			else
				write("Cleric Notifications: On\n");
				
			if (GUILD_MANAGER->query_stop_worshipper_notifications(TP))
				write("Worshipper Notifications: Off\n");
			else
				write("Worshipper Notifications: On\n");
				
			if (GUILD_MANAGER->query_stop_seeker_notifications(TP))
				write("Seeker Notifications: Off\n");
			else
				write("Seeker Notifications: On\n");
		}
		write("\nValid syntax: enotify <cleric/worshipper/seeker/all> "+
		    "<on/off>\n");
		return 1;
	}
	if (sscanf(str, "%s %s", option1, option2) == 2)
	{
		switch(option1)
		{
			case "all":
				switch(option2)
				{
					case "on":
						write("You will see Cleric, Worshipper and Seeker "+
						    "notifications.\n");
						GUILD_MANAGER->set_stop_all_notifications(TP,0);
						GUILD_MANAGER->set_stop_cleric_notifications(TP,0);
						GUILD_MANAGER->set_stop_worshipper_notifications(TP,0);
						GUILD_MANAGER->set_stop_seeker_notifications(TP,0);
						break;
					case "off":
						write("You will no longer see Cleric, Worshipper and "+
						    "Seeker notifications.\n");
						GUILD_MANAGER->set_stop_all_notifications(TP,1);
						GUILD_MANAGER->set_stop_cleric_notifications(TP,1);
						GUILD_MANAGER->set_stop_worshipper_notifications(TP,1);
						GUILD_MANAGER->set_stop_seeker_notifications(TP,1);
						break;
					default:
						write("Valid syntax: enotify <cleric/worshipper/seeker"+
						    "/all> <on/off>\n");
						return 1;
						break;
				}
				break;
			case "cleric":
				switch(option2)
				{
					case "on":
						write("You will see Cleric notifications.\n");
						GUILD_MANAGER->set_stop_cleric_notifications(TP,0);
						break;
					case "off":
						write("You will no longer see Cleric notifications.\n");
						GUILD_MANAGER->set_stop_cleric_notifications(TP,1);
						break;
					default:
						write("Valid syntax: enotify <cleric/worshipper/seeker"+
						    "/all> <on/off>\n");
						return 1;
						break;
				}
				break;
			case "worshipper":
				switch(option2)
				{
					case "on":
						write("You will see Worshipper notifications.\n");
						GUILD_MANAGER->set_stop_worshipper_notifications(TP,0);
						break;
					case "off":
						write("You will no longer see Worshipper notifications"+
						    ".\n");
						GUILD_MANAGER->set_stop_worshipper_notifications(TP,1);
						break;
					default:
						write("Valid syntax: enotify <cleric/worshipper/seeker"+
						    "/all> <on/off>\n");
						return 1;
						break;
				}
				break;
			case "seeker":
				switch(option2)
				{
					case "on":
						write("You will see Seeker notifications.\n");
						GUILD_MANAGER->set_stop_seeker_notifications(TP,0);
						break;
					case "off":
						write("You will no longer see Seeker notifications.\n");
						GUILD_MANAGER->set_stop_seeker_notifications(TP,1);
						break;
					default:
						write("Valid syntax: enotify <cleric/worshipper/seeker"+
						    "/all> <on/off>\n");
						return 1;
						break;
				}
				break;
			default:
				write("Valid syntax: enotify <cleric/worshipper/seeker/all> "+
				    "<on/off>\n");
				return 1;
				break;
		}
		return 1;
	}
	else
	{
		write("Valid syntax: enotify <cleric/worshipper/seeker/all> <on/off>\n");	
		return 1;
	}
}

public int
elist(string str)
{
    setuid();seteuid(getuid());

    MEMBER_LIST_UTILITY->list_members();   
    return 1;

}

public int
etitle(string str)
{
	string command, option1, option2, temp_title;
	string * noun1s;
	string * noun2s;
	string * temp_option2;
	string title;
	int index;
	string primary_element = GUILD_MANAGER->query_primary_element(TP);

    if (!GUILD_MANAGER->query_is_full_master(TP))
    {
    	notify_fail("You cannot use this command until you have reached "+
    	    "the rank of Full Master.\n");
    	return 0;
    }
   
	if (!str)
	{
		notify_fail("Etitle valid commands: current, default, options noun1s, "+
		    "options noun2s, set <noun1> <noun2>.\n");
		return 0;
	}
	
	// They gave three parameters (this should be the set command)
	if (sscanf(str, "%s %s %s", command, option1, option2) == 3)
	{
		if (command == "set")
		{
			noun1s = noun1s=TP->query_master_noun_1s();
			if (GUILD_MANAGER->query_is_elder_cleric(TP))
				noun1s += TP->query_elder_noun_1s();
			
			switch(primary_element)
			{
				case "fire":
					noun2s=TP->query_master_fire_noun_2s();					
					break;
				case "water":
					noun2s=TP->query_master_water_noun_2s();	
					break;
				case "air":
					noun2s=TP->query_master_air_noun_2s();	
					break;
				case "earth":
					noun2s=TP->query_master_earth_noun_2s();	
					break;
				case "life":
					noun2s=TP->query_master_spirit_noun_2s();
					break;
				default:
					write("You cannot set a custom title until a branch "+
						"is chosen\n");
					return 0;
					break;										
			}
			if (GUILD_MANAGER->query_is_elder_cleric(TP))
				noun2s += TP->query_elder_noun_2s();
			
			// check if option1 is a valid noun1 - if not
			// then tell them

			if (!IN_ARRAY(option1,noun1s))
			{
				notify_fail("The option "+option1+" is not a "+
					"valid noun1.\n");
				return 0;
			}
			
			// check if option2 is a valid noun2 - if not
			// then tell them
			if (!IN_ARRAY(option2,noun2s))
			{
				notify_fail("The option "+option2+" is not a "+
					"valid noun2.\n");
				return 0;
			}				
			
			// Fix up option2 if it's a t- or L- word
			
			temp_option2 = explode(option2,"-");			
			if (temp_option2)
			{
				if (temp_option2[0] == "t")
				{
					temp_title = "the " + temp_option2[1];
					option2 = temp_title;
				}
					
				if (temp_option2[0] == "L")
				{
					if (temp_option2[1] == "Pyros" || temp_option2[1] == 
						"Diabrecho")
						    temp_title = "Lord " + temp_option2[1];
					if (temp_option2[1] == "Aeria" || temp_option2[1] == "Gu")
						temp_title = "Lady " + temp_option2[1];
					option2 = temp_title;
				}
			}
				
			
			// Both options are valid, put the title
			// together and record it
				
			title = option1 + " of " + option2;

				
			GUILD_MANAGER->set_title_created(TP,title);
			GUILD_MANAGER->set_created_own_title(TP,1);
			write("Your new title has been set as:\n"+title+"\n\n");
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
			if (option1 == "noun1s")
			{
				noun1s = TP->query_master_noun_1s();
				if (GUILD_MANAGER->query_is_elder_cleric(TP))
					noun1s += TP->query_elder_noun_1s();

				write("You can select one of the following noun1s:\n");
				for (index = 0; index < sizeof (noun1s); index++)
				{
				    write(noun1s[index]);
				    if (index == sizeof (noun1s)- 1)
				    	write(".");
				    else
				    	write(", ");
				}
				write("\n\n");
				return 1;
			}
			if (option1 == "noun2s")
			{				
				switch(primary_element)
				{
					case "fire":
						noun2s=TP->query_master_fire_noun_2s();
						break;
					case "water":
						noun2s=TP->query_master_water_noun_2s();
						break;
					case "air":
						noun2s=TP->query_master_air_noun_2s();
						break;
					case "earth":
						noun2s=TP->query_master_earth_noun_2s();
						break;
					case "life":
						noun2s=TP->query_master_spirit_noun_2s();
						break;
					default:
						write("No nouns are available until a branch "+
						    "is chosen\n");
						return 0;
						break;
				}				
				if (GUILD_MANAGER->query_is_elder_cleric(TP))
					noun2s += TP->query_elder_noun_2s();
					
				write("You can select one of the following noun2s:\n");
				for (index = 0; index < sizeof (noun2s); index++)
				{
				    write(noun2s[index]);
				    if (index == sizeof (noun2s)- 1)
				    	write(".");
				    else
				    	write(", ");
				}				
				write("\n\nNOTE: For those nouns that begin with 't-<noun>', "+
				    "they will show up as 'the <noun>'. For example "+
				    "'t-Flames' would become 'the flames'.\n"+
				    "For those nouns that begin with 'L-<noun>', they will "+
				    "show up as 'Lord/Lady <noun>' (depending on the gender "+
				    "of the Elemental). For "+
				    "example 'L-Pyros' would become 'Lord Pyros'.\n\n");
				return 1;
			}			
		}
		notify_fail("The option "+str+" is not valid with the options "+
		    "command. Valid options are: noun1s, noun2s.\n");
		return 0;
	}
	
	// They gave one command (this should be current, hide or unhide)
	if (sscanf(str, "%s", command) == 1)
	{
		if (command == "current")
		{
			write("Your current title is: "+TP->query_guild_title_occ()+"\n");
			write("Your current default title would be: "+
			    TP->query_elemental_cleric_title()+"\n");
			return 1;
		}
/*		
		if (command == "hide")
		{
			write("You are now hiding your extra title.\n");
			GUILD_MANAGER->set_hide_extra_title(TP,1);
			return 1;
		}
		
		if (command == "unhide")
		{
			write("You are now not hiding your extra title.\n");
			GUILD_MANAGER->set_hide_extra_title(TP,0);
			return 1;
		}
*/		
		if (command == "default")
		{
			write("You have reset your title back to the default title.\n");
			GUILD_MANAGER->set_created_own_title(TP, 0);
        	GUILD_MANAGER->set_title_created(TP,"");
			return 1;
		}
		
		if (command == "options")
		{
			write("Valid options are: noun1s, noun2s.\n");
			return 1;
		}
		
		notify_fail("The option "+command+" is not valid.\n");
		return 0;
	}
	notify_fail("The option "+str+" is not valid.\nEtitle valid commands: "+
	    "current, "+
	    "default, options noun1s, options noun2s, set <noun1> "+
	    "<noun2>.\n");
	return 0;
}

int
eassess(string str)
{
    object *oblist;

    if (!str || str == "")
    {
        NF("Assess whom with a discriminating glance?\n");
        return 0;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        NF("Assess whom with a discriminating glance?\n");
        return 0;
    }

    actor("You assess",oblist," with a discriminating glance, but "+
        "discard them as harmless.");
    all2act(" assesses",oblist," with a discriminating glance, but "+
        "discards them as harmless.");
    target(" assesses you with a discriminating glance, but discards "+
        "you as harmless.",oblist);
    return 1;
}

int
ebless(string str)
{
    object *oblist;

    if (!str || str == "")
    {
        NF("Bless whom quietly in the name of the Elementals?\n");
        return 0;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        NF("Bless whom quietly in the name of the Elementals?\n");
        return 0;
    }

    actor("You bless",oblist," quietly in the name of the Elementals.");
    all2act(" blesses",oblist," quietly in the name of the Elementals.");
    target(" blesses you quietly in the name of the Elementals.",oblist);
    return 1;
}

int
eboredom()
{
    write("Your attention wavers and you gaze off into the distance, "+
        "having grown bored with the current conversation.\n");
    all("'s attention wavers and "+HE+" gazes off into the distance, "+
        "having grown bored with the current conversation.");
    return 1;
}

int
ebrush(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "gently", 0);

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
        NF("Brush [how] on whom?\n");
        return 0;
    }

    actor("You brush your fingertips briefly across",oblist,"'s forearm, "+
        "touching it"+how[1]+".");
    all2act(" brushes "+HIS+" fingertips briefly across",oblist,"'s forearm, "+
        "touching it"+how[1]+".",how[1]);
    target(" brushes "+HIS+" fingertips briefly across your forearm, "+
        "touching it"+how[1]+".",oblist,how[1]);
    return 1;
}

public int
echant(string str)
{
    setuid();seteuid(getuid());
    string patron_elemental = GUILD_MANAGER->query_primary_element(TP);
    
    // Without any arguments, we just display the emote.
    if (!strlen(str))
    {
        switch (patron_elemental)
        {
        case "fire":
            write("You sit briefly and chant in the sounds of a "+
                  "crackling flame.\n");
            all(" sits down and begins to chant.\nYou hear the " +
                "sound of crackling flames in "+ TP->query_possessive() + 
                " voice. After a brief " + "moment, " + 
                TP->query_pronoun() +" rises again.");
            break;
        case "earth":
            write("You sit briefly and chant in the sounds of the "+
                  "pounding earth.\n");
            all(" sits down and begins to chant.\nYou hear sounds "+
                "like that of the pounding earth in "+TP->query_possessive()+
                " voice. "+
                "After a brief moment, "+TP->query_pronoun()+" rises again.");
            break;
        case "water":
            write("You sit briefly and chant in the sounds of the "+
                  "ocean waves.\n");
            all(" sits down and begins to chant.\nYou hear the "+
                "sound of the ocean in "+TP->query_possessive()+" voice. "+
                "After a brief "+
                "moment, "+TP->query_pronoun()+" rises again.");
            break;
        case "air":
            write("You sit briefly and chant in the sounds of the "+
                  "howling winds.\n");
            all(" sits down and begins to chant.\nYou hear the "+
                "sounds of the howling winds in "+TP->query_possessive()+
                " voice. "+
                "After a brief moment, "+TP->query_pronoun()+" rises again.");
            break;
        case "life":
            write("You sit briefly and chant in the sounds of the "+
                  "inner spirit.\n");
            all(" sits down and begins to chant.\nYou hear the "+
                "sounds of the inner spirit in "+TP->query_possessive()+
                " voice. "+
                "After a brief moment, "+TP->query_pronoun()+" rises again.");
            break;
        default:
            // No element chosen yet
            write("You sit briefly and chant in the ancient mantras of the "+
                "Kyrullians.\n");
            all(" sits down and begins to chant.\nAfter a brief moment, " 
                + TP->query_pronoun() + " rises again.");
            break;
        }
        return 1;
    }    
    
    // If the user specified a message, we use a guild specific speech.
    write("You chant in the ancient mantras of the Kyrullians: " + str + "\n");
    TP->gmcp_comms("echant", 0, "You chant in the ancient mantras of the "+
        "Kyrullians: " + str + "\n");

    object * listeners = FILTER_LIVING_OBJECTS(all_inventory(environment(TP)));
    object * not_understand_speech = ({ });
    foreach (object listener : listeners)
    {
        if (!IS_MEMBER(listener)
            && listener->query_skill(SS_LANGUAGE) < 70
            && !listener->query_wiz_level())
        {
            not_understand_speech += ({ listener });
        }
    }
    
    // Send message to everyone that understands the speech
    tell_room(environment(TP), QCTNAME(TP) + " chants: "
              + str + "\n", not_understand_speech + ({ TP }), TP);
    object * understand_speech = listeners - not_understand_speech - ({ TP });
    filter(understand_speech, &->query_met(TP))->gmcp_comms("chant", 
        TP->query_met_name(), 
        TP->query_met_name() + " chants: " + str + "\n");
    filter(understand_speech, not @ &->query_met(TP))->gmcp_comms("chant", 
        "The " + TP->query_nonmet_name(), 
        "The " + TP->query_nonmet_name() + " chants: " + str + "\n");

    // For the people who don't understand, we send a generic message
    not_understand_speech->catch_msg(QCTNAME(TP) + " chants in ancient "+
        "mantras.\n");
    return 1;
}

int
echoose(string str)
{
    object *who;
    object chosen;
    string my_name, apprentice;

    if (!(GUILD_MANAGER->query_is_elder_cleric(TP->query_real_name())))
    {
        NF("You are not permitted to accept Apprentices until you "+
            "have reached the Elder status.\n");
        return 0;
    }

    if (!str || str == "")
    {
        NF("Choose who?\n");
        return 0;
    }

    who = parse_this(str, " %l");

    if (!sizeof(who))
        return 0;

    if (!who)
        return 0;

    if (sizeof(who)>1)
    {
        NF("You can't choose more than one person at a time!\n");
        return 0;
    }

    if (GUILD_MANAGER->query_is_cleric(who[0]))
    {
        NF("That person is already a Elemental Cleric!\n");
        return 0;
    }

    if (present("_echosen_", who[0]))
    {
        NF("That person has already been chosen!\n");
        return 0;
    }

    my_name = TP->query_real_name();

    
    target(" places "+HIS+" hands on your shoulders. You feel "+
        "power flowing through your body.",who);
    actor("You place your hands on",who,"'s shoulder, allowing "+
        who[0]->query_objective()+" to become a Child of the Elementals.");
    all2actbb(" places "+HIS+" hands on",who,"'s shoulders.");
    apprentice = who[0]->query_real_name();
    
    COUNCIL_LOG_BOOK->update_log_book(my_time() + capitalize(my_name) +
        " has allowed "+capitalize(apprentice) +
        " to become a Child Cleric.\n");

    setuid();
    seteuid(getuid());
    chosen=clone_object(ELEMENTALIST_OBJS+"chosen");
    chosen->move(who[0],1);
    return 1;
}

int
eclose()
{
    write("You close your eyes, turning your focus inwards.\n");
    all(" closes "+HIS+" eyes, turning "+HIS+" focus inwards.");
    return 1;
}

public int
econgratulate(string str)
{
    setuid();seteuid(getuid());
    notify_fail("Congratulate whom?\n");
    if (!strlen(str))
    {
        return 0;
    }

    object * oblist = parse_this(str," %l");
    if (!sizeof(oblist))
    {
        return 0;
    }

    target(" congratulates you, recognizing your achievements.",oblist);
    if (sizeof(oblist) == 1)
    {
        actor("You congratulate",oblist,", recognizing "+
            oblist[0]->query_possessive()+" achievements.");
        all2actbb(" congratulates",oblist,", recognizing "+
            oblist[0]->query_possessive()+" achievements.");
    }
    else
    {
        actor("You congratulate",oblist,", recognizing their achievements.");
        all2actbb(" congratulates",oblist,", recognizing their achievements.");
    }
    return 1;
}

int
econsume()
{
    write("You are consumed with a derisive laughter.\n");
    all(" is consumed with derisive laughter. The disturbing sound "+
        "strikes fear in your very soul.");
    return 1;
}

int
edisgust()
{
    write("You observe the area with obvious disgust.\n");
    all(" observes the area with obvious disgust.");
    return 1;
}

int
ecdismiss(string str)
{
    object *oblist;

    NF("Dismiss whom?\n");
    if (!strlen(str))
        return 0;
    
    oblist = parse_this(str,"[the] %l");
    if (!sizeof(oblist))
        return 0;
    
    target(" dismisses you, wanting you out of "+HIS+" sight.",oblist);
    if (sizeof(oblist) == 1)
    {
        actor("You dismiss",oblist,", wanting them out of your sight.");
        all2actbb(" dismisses",oblist,", wanting them out of "+HIS+" sight.");
    }
    else
    {
        actor("You dismiss",oblist,", wanting them out of your sight.");
        all2actbb(" dismisses",oblist,", wanting them out of "+HIS+" sight.");
    }
    return 1;
}

int
eembrace(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "warmly", 1);

    oblist = parse_this(how[0], "[the] %l");

    if (!sizeof(oblist))
    {
        NF("Embrace whom [how]?\n");
        return 0;
    }

    actor("You open your arms and embrace",oblist,how[1]+", infusing "+
          "their body and soul with a profound sense of peace.");
    all2act(" opens "+HIS+" arms and embraces",oblist, how[1]+", infusing "+
        "their body and soul with a profound sense of peace.",how[1]);
    target(" opens "+HIS+" arms and embraces you"+how[1]+", infusing "+
        "your body and soul with a profound sense of peace.",oblist,how[1]);
    return 1;
}

int
eeyes()
{
    int who;
    who = GUILD_MANAGER->query_primary_element(TP);
    
    switch (who)
    {
        case "fire":
            write("Your eyes flare with the power of Lord Pyros!\n");
            all("'s eyes flare like a bright red flame.");
            break;
        case "earth":
            write("Your eyes sparkle with the power of Lady Gu!\n");
            all("'s eyes sparkle like two perfectly cut diamonds.");
            break;
        case "water":
            write("Your eyes glow with the power of Lord Diabrecho!\n");
            all("'s eyes glow a bright watery blue.");
            break;
        case "air":
            write("Your eyes flash with the power of Lady Aeria!\n");
            all("'s eyes flash suddenly like a lightning strike.");
            break;
        case "life":
            write("Your eyes flash with the power of Psuchae!\n");
            all("'s eyes darken suddenly like a they are filled with shadows.");
            break;
        default:
            write("Your eyes flash with the power!\n");
            all("'s eyes flash with power.");
            break;
    }
    return 1;
}

int
efarewell(string str)
{
    object *oblist;

    NF("Bow and wave farewell to who?\n");
    if (!strlen(str))
        return 0;
    
    oblist = parse_this(str,"[to] [the] %l");
    if (!sizeof(oblist))
        return 0;
    
    target(" bows slightly and waves farewell to you. You "+
        "somehow know that "+HE+" wishes you all the best "+
        "in your travels.",oblist);
    if (sizeof(oblist) == 1)
    {
        actor("You bow slightly and wave farewell to",oblist,".");
        all2actbb(" bows slightly and waves farewell to",oblist,".");
    }
    else
    {
        actor("You bow slightly and wave farewell to",oblist,".");
        all2actbb(" bows slightly and waves farewell to",oblist,".");
    }
    return 1;
}

int
egaze(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "intensely", 0);

    if (!stringp(how[0]))
    {
        write("You fix your eyes on an invisible point in front of "+
            "you and gaze at it"+how[1]+".\n");
        all(" fixes "+HIS+" eyes on an invisible point and gazes"+
            how[1]+" at it, causing "+HIS+" pupils to dialate and "+
            "turning "+HIS+" eyes into black voids.",how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
        NF("Gaze [how] at whom?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        actor("You gaze"+how[1]+" at",oblist);
        all2act(" gazes"+how[1]+" at",oblist,0,how[1]);
        target(" gazes"+how[1]+" at you.",oblist, how[1]);
        return 1;
    }

    actor("You gaze"+how[1]+" at",oblist,", not bothering to conceal "+
        "your contempt. "+capitalize(oblist[0]->query_pronoun())+
        " looks back, but quickly trembles and looks away.");
    all2act(" gazes"+how[1]+" at",oblist," with unconcealed contempt. "+
        "After a brief struggle, "+oblist[0]->query_pronoun()+" trembles "+
        "and averts "+oblist[0]->query_possessive()+ " gaze.", how[1]);
    target(" gazes"+how[1]+" at you, not bothering to conceal "+HIS+
        " contempt. Bravely you look "+TP->query_objective()+" in the "+
        "eye and suddenly feel you are looking into a dark void. "+
        "A sharp pain spreads from behind your eyes and just as you feel "+
        "you are about to faint, you tremble and lower your gaze.",
        oblist,how[1]);
    return 1;
}

int
egesture()
{
    write("You make a quick gesture in front of yourself, kissing your "+
        "fingers "+
        "and touching your forehead softly to protect yourself against all "+
        "evil.\n");
    all(" makes a quick gesture in front of "+HIM+", kissing "+HIS+" fingers "+
        "and touching "+HIS+" forehead softly to protect "+HIM+"self against "+
        "all evil.");
    return 1;
}

int
eglare(string str)
{
    object *who;

    if (!str || str == "")
    {
       write("You glare around, obviously in a foul mood.\n");
       all(" glares around, obviously in a foul mood.");
       return 1;
    }

    who = parse_this(str, "[at] [the] %l");

    if (!sizeof(who))
    {
        NF("Glare at whom?\n");
        return 0;
    }

    actor("You glare at",who);
    all2act(" glares at",who,", obviously in a foul mood.");
    target(" glares at you, obviously in a foul mood. You silently "+
        "pray "+HE+" does not take it out on you.",who);
    return 1;
}

int
egrin(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "delightedly", 0);

    if (!stringp(how[0]))
    {
        write("You grin"+how[1]+", your face brightening as you do so.\n");
        all(" grins"+how[1]+", "+HIS+" face brightening as "+HE+" does so.");
        SOULDESC("grinning"+how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] %l");

    if(!sizeof(oblist))
    {
       NF("Grin [how] at whom?\n");
       return 0;
    }

    actor("You grin"+how[1]+" at",oblist,".");
    all2act(" grins"+how[1]+" at",oblist,", "+HIS+" eyes "+
        "seem to look knowingly into their soul!",how[1]);
    target(" grins at you"+how[1]+", "+HIS+" eyes seem to look "+
        "knowingly into your soul.",oblist,how[1]);
    SOULDESC("grinning"+how[1]);
    return 1;
}

int
ehail(string str)
{
    object *onl, *oblist, *members, *nonmem;
    
    int i;
    
    NF("Hail who?\n");
    if (!strlen(str))
        return 0;

    onl = FILTER_LIVE(all_inventory(environment(TP))); 
    if (!sizeof(onl)) 
        return 0;

    oblist = parse_this(str," %l");
    oblist -= ({TP});
    if (!sizeof(oblist)) return 0;

    onl -= oblist; 
    onl -= ({TP}); 

    members = filter(oblist, is_cleric);
    members += filter(oblist, is_seeker);
    members += filter(oblist, is_worship);
    members += filter(oblist, is_spirit);
    nonmem = oblist - members;


    /* Non-members */ 
    for (i = 0; i < sizeof(nonmem); i++)  
    { 
        nonmem[i]->catch_msg(TP->query_The_name(nonmem[i])+" reaches toward " +
            "you with "+ HIS+" left hand open, palm facing you, in an " +
            "ancient sign of greetings.\n");
    } 

   if (sizeof(nonmem)) 
       TP->catch_msg("You hail " + group_desc(TP, nonmem, 0) +
            " in an ancient sign of greetings.\n");

    /* Members */ 
    for (i = 0; i < sizeof(members); i++)  
    { 
        members[i]->catch_msg(TP->query_The_name(members[i]) + " reaches " +
            "toward you with "+ HIS+" left hand open, palm facing you, " +
            "in an ancient sign of greetings.\n"+
            "You place your right fist in "+HIS+" hand to complete the "+
            "greeting.\n");
    } 
    if (sizeof(members)) 
        TP->catch_msg("You hail "+group_desc(TP, members, 0) + 
            " in an ancient sign of greetings. "+
            (sizeof(members) > 1 ? "They complete" : 
            capitalize(members[0]->query_pronoun())+" completes") +
            " the greeting by placing "+
            (sizeof(members) > 1 ? "their right fists" :
            members[0]->query_possessive()+" right fist")+
            " in your left hand.\n");


    /* Onlookers */ 

    for (i = 0; i < sizeof(onl); i++) 
    { 
        onl[i]->catch_msg(TP->query_The_name(onl[i]) + " reaches toward " +
            group_desc(onl[i], oblist, 0) + " with "+HIS+" left hand, in an "+
            "ancient sign of greetings.\n"); 
        if (sizeof(members)) {  
            onl[i]->catch_msg(group_desc(onl[i], members, 1) + " " +  
               (sizeof(members) > 1 ? "complete" : "completes") +
               " the greeting by placing "+
               (sizeof(members) > 1 ? "their right fists" :
               members[0]->query_possessive()+" right fist")+
               " in " +TP->query_the_name(onl[i]) +"'s left hand.\n");
        } 
    } 

    return 1;
}

int
ehug(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "closely", 1);

    oblist = parse_this(how[0], "[the] %l");

    if (!sizeof(oblist))
    {
        NF("Hug whom [how]?\n");
        return 0;
    }

    actor("You hug",oblist,how[1]+", enveloping them in "+
        "shadow, concealing them from sight for a brief moment.");
    all2act(" hugs",oblist, how[1]+", enveloping them in "+
        "shadow, concealing them from sight for a brief moment.",how[1]);
    target(" hugs you"+how[1]+", enveloping you in shadow, "+
        "concealing you from sight for a brief moment.",oblist,how[1]);
    return 1;
}

int
eincline(string str)
{
    object *oblist;

    if(!strlen(str))
    {
       NF("Incline your head to whom?\n");
       return 0;
    }

    oblist = parse_this(str, "[to] [the] %l");

    if(!sizeof(oblist))
    {
       NF("Incline your head to whom?\n");
       return 0;
    }
       
    actor("You incline your head respectfully to",oblist,", recognizing "+
        "them as a kindred spirit.");
    all2actbb(" inclines "+HIS+" head respectfully to",oblist,", recognizing "+
        "them as a kindred spirit.");
    target(" inclines "+HIS+" head respectfully to you, recognizing you "+
        "are a kindred spirit.",oblist);
    return 1;
}

int
ejoy()
{
    write("You show an expression of your joy.\n");
    all("'s face brightens with joy.");
    return 1;
}

int
eknee()
{
    write("You get down on one knee and mentally call upon the power of "+ 
        "the Elementals.\n");
    all(" gets down on one knee and gets a look of extreme concentration "+
        "on "+HIS+" face.");
    return 1;
}

int
ekneel()
{
    if (!present("corpse",environment(TP)))
    {
        write("There is no corpse here to kneel beside.\n");
        return 1;
    }

    write("You kneel serenely beside the corpse and lay your hands over "+
        "its eyes and chest. A silvery form seems to appear from the body, "+
        "only to dissipate immediately into the surroundings.\n");
    all(" kneels serenely beside the corpse and lays "+HIS+" hands over "+
        "its eyes and chest. A silvery form seems to appear from the body, "+
        "only to dissipate immediately into the surroundings. Were it not "+
        "for the tingling in your skin, you would think you had imagined it.");
    return 1;
}

int
elaugh(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "wickedly", 0);

    if (!stringp(how[0]))
    {
        write("Concentrating all of your energies, you laugh"+how[1]+
            ", emmitting a thunderous echo.\n");
        all(" laughs"+how[1]+", emmitting a thunderous echo!",how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
        NF("Laugh [how] at whom?\n");
        return 0;
    }

    actor("Concentrating all of your energies, you laugh"+how[1]+
        " at",oblist,", emmiting a thunderous echo.");
    all2act(" laughs"+how[1]+" at",oblist,", emmitting a thunderous "+
        "echo.",how[1]);
    target(" laughs"+how[1]+" at you, emmitting a thunderous echo "+
       "that eats away at your very soul!",oblist,how[1]);
    return 1;
}

int
epause()
{
    write("A shadow passes over your eyes as you pause for a moment of "+
        "reflection and contemplation.\n");
    all("'s eyes are clouded over with shadows briefly as "+HE+" pauses "+
        "for a moment of reflection and contemplation.");
    return 1;
}

int
eplay()
{
    write("You weave your hands in an intricate design causing "+
        "your shadow to dance around on the ground.\n");
    all(" weaves "+HIS+" hands in an intricate design causing "+
        HIS+" shadow to dance around on the ground.");
    return 1;
}

int
epray()
{
    write("You look up into the sky and call out for the power of "+
        "the Elementals to guide you forth.\n");
    all(" looks up into the sky and prays silently.");
    return 1;
}

int
eprepare()
{
    write("You make a graceful gesture with your hands indicating "+
        "that you need a moment's preparation.\n");
    all(" makes a graceful gesture with "+HIS+" hands indicating "+
        "that "+HE+" needs a moment's preparation.");
    return 1;
}

int
erage()
{
    write("You contort your face in violent anger for a few moments.\n");
    all("'s face contorts in violent anger, but the fit passes in a "+
        "few moments and "+HE+" appears as serene as ever.");
    return 1;
}

int
eraise(string str)
{
    object *oblist;

    if(!strlen(str))
    {
        write("You raise your hand in warning.\n");
        all(" raises "+HIS+" hand in warning.");
        return 1;  
    }

    oblist = parse_this(str, "[at] [the] %l");

    if(!sizeof(oblist))
    {
       NF("Raise your hand in warning to whom?\n");
       return 0;
    }

    actor("You raise your hand in warning to",oblist,".");
    all2actbb(" raises "+HIS+" hand in warning to",oblist,".");
    target(" raises "+HIS+" hand in warning to you.",oblist);
    return 1;
}

int
erise()
{
    string p_sex;
    if (TP->query_gender() == G_FEMALE)
        p_sex = "goddess";
    else
        p_sex = "god";

    write("You rise to your full height and show everyone your "+p_sex+
        "like beauty and majesty.\n");
    all(" rises up to "+HIS+" full height and as your eyes are drawn to "+
        TP->query_objective()+", you are humbled by "+HIS+" "+p_sex+
        "like beauty and majesty.");
    return 1;
}

int
eshake(string str)
{
    object *oblist;

    if(!strlen(str))
    {
       NF("Shake hands with whom?\n");
       return 0;
    }

    oblist = parse_this(str, "[with] [the] %l");

    if(!sizeof(oblist))
    {
       NF("Shake hands with whom?\n");
       return 0;
    }

    actor("You shake",oblist," with a cold hand.");
    all2actbb(" grasps",oblist," by the hand in a strong "+
        "shake.");
    target(" grasps your hand in a strong shake. You recoil and "+
       "jerk back as you feel your soul being sucked into "
       +HIS+" hand!",oblist);
    return 1;
}

int
eshrug()
{
    write("You shrug, not caring one way or the other.\n");
    all(" shrugs, not caring one way or the other.");
    return 1;
}

int
esilence()
{
    write("You motion for a moment of silence.\n");
    all(" raises "+HIS+" hand and motions for a moment of silence.");
    return 1;
}

int
esmile(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "disdainfully", 0);

    if (!stringp(how[0]))
    {
        write("You smile"+how[1]+".\n");
        all(" smiles"+how[1]+". Your muscles tighten in an "+
            "unconscious response.",how[1]);
        SOULDESC("smiling"+how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");
      
    if (!sizeof(oblist))
    {
        NF("Smile [how] at whom?\n");
        return 0;
    }

    actor("You smile"+how[1]+" at",oblist);
    all2act(" smiles"+how[1]+" at",oblist,0,how[1]);
    target(" smiles"+how[1]+" at you. Your muscles tighten in an "+
        "unconscious response.",oblist,how[1]);
    SOULDESC("smiling"+how[1]);
    return 1;
}

int
esnap(string str)
{
    str = check_adverb_with_space(str, "loudly");

    if (str == NO_ADVERB_WITH_SPACE)
    {
        NF("Snap how?\n");
        return 0;
    }
    write("You snap your fingers"+str+".\n");
    all(" snaps "+HIS+" fingers"+str+".",str);
    return 1;
}

int
estand()
{
    write("You stand in the shadows, unassuming, yet your presence "+
        "seems to pervade the area.\n");
    all(" stands in the shadows, unassuming, yet "+HIS+" presence seems "+
        "to pervade the area.");
    return 1;
}


int
estretch()
{
    write("You stretch your body out and assume a resting position, "+
        "briefly letting your body absorb down into your shadow.\n");
    all(" stretches out " + HIS+ " body and assumes a resting position. "+
        capitalize(HIS)+" body briefly sinks into "+HIS+" own shadow "+
        "on the ground.");
    return 1;
}

int
etense(string str)
{
    object *who;

    if (!str || str == "")
    {
       NF("Tense up over whom?\n");
       return 0;
    }

    who = parse_this(str, "[at] [the] %l");

    if (!sizeof(who))
    {
        NF("Tense up over whom?\n");
        return 0;
    }

    if (sizeof(who)>1)
    {
        NF("You can only tense over one person at a time.\n");
        return 0;
    }

    if (!who[0]->query_prop(LIVE_I_UNDEAD))
    {
        NF("That person is not a Soulless one.\n");
        return 0;
    }

    actor("You body tenses with the holy power of the Elementals as you "+
        "focus your attention on the soulless body of",who);
    all2act("'s body tenses with the holy power of the Elementals as "+
        HE+" focuses "+HIS+" attention on the soulless body of",who);
    target("'s body tenses with the holy power of the Elementals as "+
        HE+" focuses "+HIS+" attention on you.",who);
    return 1;
}

int
ethank(string str)
{
    object *who;

    if (!str || str == "")
    {
       NF("Smile in thanks to whom?\n");
       return 0;
    }

    who = parse_this(str, "[at] [the] %l");

    if (!sizeof(who))
    {
        NF("Smile in thanks to whom?\n");
        return 0;
    }

    actor("You smile graciously in thanks to",who);
    all2act(" smiles graciously in thanks to",who);
    target(" smiles graciously in thanks to you. Your soul "+
        "feels uplifted.",who);
    return 1;
}

public int
eunimpressed(string str)
{
    setuid();seteuid(getuid());
    notify_fail("Be unimpressed with whom?\n");
    if (!strlen(str))
    {
        return 0;
    }

    object * oblist = parse_this(str," %l");
    if (!sizeof(oblist))
    {
        return 0;
    }

    target(" appears unimpressed by your arguments.",oblist);
    if (sizeof(oblist) == 1)
    {
        actor("You appear unimpressed by",oblist,"'s arguments.");
        all2actbb(" appears unimpress by",oblist,"'s arguments.");
    }
    else
    {
        actor("You appear unimpressed by the arguments of",oblist,".");
        all2actbb(" appears unimpressed by the arguments of",oblist,".");
    }
    return 1;
}

public int
evictory()
{
    setuid();
    seteuid(getuid());
    string primary_element = GUILD_MANAGER->query_primary_element(TP);
    switch (primary_element)
    {
    case "fire":
        write("You close your eyes and bow your head in thanks "+
              "to Lord Pyros for your victory.\n");
        all(" closes "+TP->query_possessive()+" eyes and bows "+
            TP->query_possessive()+" head in thanks "+
            "to Lord Pyros for "+TP->query_possessive()+" victory.");
        break;
    case "earth":
        write("You close your eyes and bow your head in thanks "+
              "to Lady Gu for your victory.\n");
        all(" closes "+TP->query_possessive()+" eyes and bows "+
            TP->query_possessive()+" head in thanks "+
            "to Lady Gu for "+TP->query_possessive()+" victory.");
        break;
    case "water":
        write("You close your eyes and bow your head in thanks "+
              "to Lord Diabrecho for your victory.\n");
        all(" closes "+TP->query_possessive()+" eyes and bows "+
            TP->query_possessive()+" head in thanks "+
            "to Lord Diabrecho for "+TP->query_possessive()+" victory.");
        break;
    case "air":
        write("You close your eyes and bow your head in thanks "+
              "to Lady Aeria for your victory.\n");
        all(" closes "+TP->query_possessive()+" eyes and bows "+
            TP->query_possessive()+" head in thanks "+
            "to Lady Aeria for "+TP->query_possessive()+" victory.");
        break;
    case "life":
        write("You close your eyes and bow your head in thanks "+
              "to Psuchae for your victory.\n");
        all(" closes "+TP->query_possessive()+" eyes and bows "+
            TP->query_possessive()+" head in thanks "+
            "to Psuchae for "+TP->query_possessive()+" victory.");
        break;
    default:
        notify_fail("You can't give thanks to an Elemental until you select "
                    + "a primary element!\n");
        return 0;
    }
    return 1;
}
