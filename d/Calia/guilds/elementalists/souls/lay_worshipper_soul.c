/*
 * Command Soul for the Elemental Worshippers of Calia
 *
 * This is the command soul that every Elemental Worshipper will
 * have. It includes emotes as well as the abilities/spells that they
 * possess.
 *
 * Created by Petros, December 2010
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

// Defines
#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))
#define CARVING_CHAMBER (ELEMENTALIST_GARDEN + "carving_chamber")
#define MEMBER_LIST_UTILITY ("/d/Calia/guilds/scop/specials/member_list_utility")

/*
 * Function name: get_soul_id
 * Description:   Give a name for this soul
 * Returns:       string - the soul's id
 */
public string
get_soul_id()
{
    return GUILD_EW_NAME + " Soul";
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
        "ealeipso"      : "do_ability", // Heal Self Spell
        "eanemos"       : "do_ability", // Tell Spell
        "eapodosi"      : "do_ability", // Teleport Home Spell
        "echoma"        : "do_ability", // Summon Elemental Spell
        "edetramfip"    : "do_ability", // Detect Magic Spell
        "edynami"       : "do_ability", // Stat Boost Spell
        "eelefrinisi"   : "do_ability", // Lighten Burden/Relieve Encumbrance Spell
        "eevimero"      : "do_ability", // Haste Spell
        "efloga"        : "do_ability", // Fire attack spell
        "epyrofosti"    : "do_ability", // Light Spell
        "eschirmo"      : "do_ability", // Elemental Shield Spell
//        "espazopetra"   : "do_ability", // Shatter Spell
        "eunteristi"    : "do_ability", // Resistance Spell

        // Guild Abilities
        "esummon"       : "do_ability", // Retrieve/Recall Elemental Ability
        "edate"         : "edate",      // Shows the Elemental date
        "edismiss"      : "do_ability", // Dismiss Elemental Ability
        "ehistory"      : "ehistory",   // Lists the recent anemos history
        "etitle"        : "etitle",     // Custom title routine

        // Emotes
        "ebless"        : "ebless",
        "echant"        : "echant",
        "ech"           : "echant",
        "echarge"       : "echarge",
        "econvert"      : "econvert",
        "ecurse"        : "ecurse",
        "eeyes"         : "eeyes",
        "efare"         : "efarewell",
        "efarewell"     : "efarewell",
        "egaze"         : "egaze",
        "ehail"         : "ehail",
        "ejoy"          : "ejoy",
        "ekneel"        : "ekneel",
        "elaugh"        : "elaugh",
        "elisten"       : "elisten",
        "emeditate"     : "emeditate",
        "eprepare"      : "eprepare",
        "escoff"        : "escoff",
        "esilence"      : "esilence",
        "esmile"        : "esmile",
        "estare"        : "estare",
        "evictory"      : "evictory",

        // Help and Options
        "help"          : "help",
        "elist"         : "elist",
        "enotify"       : "enotify",

        // Casting and Spell Commands
        "pray"          : "pray",
        "prayers"       : "prayers",

    ]);
}

public mapping
query_ability_map()
{
    return ([
        "ealeipso"      : ELEMENTALIST_SPELLS + "aleipso",
        "eanemos"       : ELEMENTALIST_SPELLS + "anemos",
        "eapodosi"      : ELEMENTALIST_SPELLS + "apodosi",
        "echoma"        : ELEMENTALIST_SPELLS + "choma",
        "edetramfip"    : ELEMENTALIST_SPELLS + "detramfip",
        "edismiss"      : ELEMENTALIST_SPECIALS + "edismiss",
        "edynami"       : ELEMENTALIST_SPELLS + "dynami",
        "eelefrinisi"   : ELEMENTALIST_SPELLS + "elefrinisi",
        "eevimero"      : ELEMENTALIST_SPELLS + "evimero",
        "efloga"        : ELEMENTALIST_SPELLS + "floga",
        "epyrofosti"    : ELEMENTALIST_SPELLS + "pyrofosti",
        "eschirmo"      : ELEMENTALIST_SPELLS + "schirmo",
        "esummon"       : ELEMENTALIST_SPECIALS + "esummon",
        "eunteristi"    : ELEMENTALIST_SPELLS + "unteristi",
    ]);
}

/*
 * Function:    elist
 * Description: Function to list all the elemental worshippers
 *              that are awake.
 */
public int
elist(string str)
{
    setuid();seteuid(getuid());
    // We use the SCoP version of the member lister
    MEMBER_LIST_UTILITY->list_members();

    return 1;
}

public int
enotify(string str)
{
	string option1, option2;

	if (!str)
	{
		// Display current options here plus valid syntax
		if (GUILD_MANAGER->query_stop_all_notifications(this_player()))
			write("All Notifications: Off\n");
		else
		{
			if (GUILD_MANAGER->query_stop_cleric_notifications(this_player()))
				write("Cleric Notifications: Off\n");
			else
				write("Cleric Notifications: On\n");

			if (GUILD_MANAGER->query_stop_worshipper_notifications(this_player()))
				write("Worshipper Notifications: Off\n");
			else
				write("Worshipper Notifications: On\n");

			if (GUILD_MANAGER->query_stop_seeker_notifications(this_player()))
				write("Seeker Notifications: Off\n");
			else
				write("Seeker Notifications: On\n");
		}
		write("\nValid syntax: enotify <cleric/worshipper/seeker/all> <on/off>\n");
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
						write("You will see Cleric, Worshipper and Seeker notifications.\n");
						GUILD_MANAGER->set_stop_all_notifications(this_player(),0);
						GUILD_MANAGER->set_stop_cleric_notifications(this_player(),0);
						GUILD_MANAGER->set_stop_worshipper_notifications(this_player(),0);
						GUILD_MANAGER->set_stop_seeker_notifications(this_player(),0);
						break;
					case "off":
						write("You will no longer see Cleric, Worshipper and Seeker notifications.\n");
						GUILD_MANAGER->set_stop_all_notifications(this_player(),1);
						GUILD_MANAGER->set_stop_cleric_notifications(this_player(),1);
						GUILD_MANAGER->set_stop_worshipper_notifications(this_player(),1);
						GUILD_MANAGER->set_stop_seeker_notifications(this_player(),1);
						break;
					default:
						write("Valid syntax: enotify <cleric/worshipper/seeker/all> <on/off>\n");
						return 1;
						break;
				}
				break;
			case "cleric":
				switch(option2)
				{
					case "on":
						write("You will see Cleric notifications.\n");
						GUILD_MANAGER->set_stop_cleric_notifications(this_player(),0);
						break;
					case "off":
						write("You will no longer see Cleric notifications.\n");
						GUILD_MANAGER->set_stop_cleric_notifications(this_player(),1);
						break;
					default:
						write("Valid syntax: enotify <cleric/worshipper/seeker/all> <on/off>\n");
						return 1;
						break;
				}
				break;
			case "worshipper":
				switch(option2)
				{
					case "on":
						write("You will see Worshipper notifications.\n");
						GUILD_MANAGER->set_stop_worshipper_notifications(this_player(),0);
						break;
					case "off":
						write("You will no longer see Worshipper notifications.\n");
						GUILD_MANAGER->set_stop_worshipper_notifications(this_player(),1);
						break;
					default:
						write("Valid syntax: enotify <cleric/worshipper/seeker/all> <on/off>\n");
						return 1;
						break;
				}
				break;
			case "seeker":
				switch(option2)
				{
					case "on":
						write("You will see Seeker notifications.\n");
						GUILD_MANAGER->set_stop_seeker_notifications(this_player(),0);
						break;
					case "off":
						write("You will no longer see Seeker notifications.\n");
						GUILD_MANAGER->set_stop_seeker_notifications(this_player(),1);
						break;
					default:
						write("Valid syntax: enotify <cleric/worshipper/seeker/all> <on/off>\n");
						return 1;
						break;
				}
				break;
			default:
				write("Valid syntax: enotify <cleric/worshipper/seeker/all> <on/off>\n");
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
etitle(string str)
{
	string command, option1, option2, option3;
	string * adjectives;
	string * nouns;
	string * suffixes;
	string title;
	int index;
	string primary_element = GUILD_MANAGER->query_primary_element(this_player());

    if (GUILD_MANAGER->query_carved_value(TP) != ALL_FLAGS)
    {
    	notify_fail("You cannot use this command until you have carved "+
    	    "all of your tools.\n");
    	return 0;
    }

	if (!str)
	{
		notify_fail("Etitle valid commands: current, options adjectives, "+
		    "options nouns, options suffixes, set <adjective> <noun> <suffix>, "+
		    "hide, unhide, default\n");
		return 0;
	}

	// They gave four parameters (this should be the set command)
	if (sscanf(str, "%s %s %s %s", command, option1, option2, option3) == 4)
	{
		if (command == "set")
		{
			switch(primary_element)
			{
				case "fire":
					adjectives=TP->query_pyros_adjs();
					nouns=TP->query_pyros_nouns();
					suffixes=TP->query_pyros_suffixes();
					break;
				case "water":
					adjectives=TP->query_diabrecho_adjs();
					nouns=TP->query_diabrecho_nouns();
					suffixes=TP->query_diabrecho_suffixes();
					break;
				case "air":
					adjectives=TP->query_aeria_adjs();
					nouns=TP->query_aeria_nouns();
					suffixes=TP->query_aeria_suffixes();
					break;
				case "earth":
					adjectives=TP->query_gu_adjs();
					nouns=TP->query_gu_nouns();
					suffixes=TP->query_gu_suffixes();
					break;
				case "life":
					adjectives=TP->query_psuchae_adjs();
					nouns=TP->query_psuchae_nouns();
					suffixes=TP->query_psuchae_suffixes();
					break;
				default:
					write("You cannot set a custom title until a branch "+
						"is chosen\n");
					return 0;
					break;
			}

			// check if option1 is a valid adjective - if not
			// then tell them
			option1 = capitalize(option1);
			option2 = capitalize(option2);
			option3 = capitalize(option3);
			if (!IN_ARRAY(option1,adjectives))
			{
				notify_fail("The option "+option1+" is not a "+
					"valid adjective.\n");
				return 0;
			}

			// check if option2 is a valid noun - if not
			// then tell them
			if (!IN_ARRAY(option2,nouns))
			{
				notify_fail("The option "+option2+" is not a "+
					"valid noun.\n");
				return 0;
			}

			// check if option3 is a valid suffix - if not
			// then tell them
			if (!IN_ARRAY(option3,suffixes))
			{
				notify_fail("The option "+option3+" is not a "+
					"valid suffix.\n");
				return 0;
			}

			// All three options are valid, put the title
			// together and record it

			// Check to see if option1 is None, if so then
			// leave that blank
			if (option1 == "None")
				option1 = "";
			else
				option1 = option1 + " ";
			title = option1 + option2;
			if (option3 == "Elementals")
				title += " of the " + option3;
			else
				title += " of " + option3;

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
			if (option1 == "adjectives")
			{
				switch(primary_element)
				{
					case "fire":
						adjectives=TP->query_pyros_adjs();
						break;
					case "water":
						adjectives=TP->query_diabrecho_adjs();
						break;
					case "air":
						adjectives=TP->query_aeria_adjs();
						break;
					case "earth":
						adjectives=TP->query_gu_adjs();
						break;
					case "life":
						adjectives=TP->query_psuchae_adjs();
						break;
					default:
						write("No adjectives are available until a branch "+
						    "is chosen\n");
						return 0;
						break;
				}
				write("You can select one of the following adjectives:\n");
				for (index = 0; index < sizeof (adjectives); index++)
				{
				    write(adjectives[index]);
				    if (index == sizeof (adjectives)- 1)
				    	write(".");
				    else
				    	write(", ");
				}
				write("\n\n");
				return 1;
			}
			if (option1 == "nouns")
			{
				switch(primary_element)
				{
					case "fire":
						nouns=TP->query_pyros_nouns();
						break;
					case "water":
						nouns=TP->query_diabrecho_nouns();
						break;
					case "air":
						nouns=TP->query_aeria_nouns();
						break;
					case "earth":
						nouns=TP->query_gu_nouns();
						break;
					case "life":
						nouns=TP->query_psuchae_nouns();
						break;
					default:
						write("No nouns are available until a branch "+
						    "is chosen\n");
						return 0;
						break;
				}
				write("You can select one of the following nouns:\n");
				for (index = 0; index < sizeof (nouns); index++)
				{
				    write(nouns[index]);
				    if (index == sizeof (nouns)- 1)
				    	write(".");
				    else
				    	write(", ");
				}
				write("\n\n");
				return 1;
			}
			if (option1 == "suffixes")
			{
				switch(primary_element)
				{
					case "fire":
						suffixes=TP->query_pyros_suffixes();
						break;
					case "water":
						suffixes=TP->query_diabrecho_suffixes();
						break;
					case "air":
						suffixes=TP->query_aeria_suffixes();
						break;
					case "earth":
						suffixes=TP->query_gu_suffixes();
						break;
					case "life":
						suffixes=TP->query_psuchae_suffixes();
						break;
					default:
						write("No suffixes are available until a branch "+
						    "is chosen\n");
						return 0;
						break;
				}
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
		    "command. Valid options are: adjectives, nouns, suffixes.\n");
		return 0;
	}

	// They gave one command (this should be current, hide or unhide)
	if (sscanf(str, "%s", command) == 1)
	{
		if (command == "current")
		{
			write("Your current title is: "+TP->query_guild_title_lay()+"\n");
			write("Your current default title would be: "+
			    TP->query_guild_default_title_lay()+"\n");
			return 1;
		}

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

		if (command == "default")
		{
			write("You have reset your title back to the default title.\n");
			GUILD_MANAGER->set_created_own_title(TP, 0);
        	GUILD_MANAGER->set_title_created(TP,"");
			return 1;
		}

		if (command == "options")
		{
			write("Valid options are: adjectives, nouns, suffixes.\n");
			return 1;
		}

		notify_fail("The option "+command+" is not valid.\n");
		return 0;
	}
	notify_fail("The option "+str+" is not valid.\nEtitle valid commands: current, "+
	    "options adjectives, options nouns, options suffixes, set <adjective> "+
	    "<noun> <suffix>, hide, unhide\n");
	return 0;
}

/*
 * Function name: pray
 * Description:   The "pray" command.
 * Arguments:     string str - arguments to "pray" command
 * Returns:       1/0 - pray command executed/not executed
 */
public int
pray(string str)
{
    object ob;
    string spell, arg;

    if (!strlen(str))
    {
        notify_fail("Pray what?\n", 0);
        return 0;
    }

    if (!sscanf(str, "%s %s", spell, arg))
    {
        spell = str;
    }

    if (ob = this_player()->find_spell(spell))
    {
        this_player()->start_spell(spell, arg, ob);
        return 1;
    }

    notify_fail("Pray what?\n", 0);
    return 0;
}

/*
 * Function:    print_spell_list
 * Description: Used in the prayers command, this will print out
 *              each classification of spells with a header.
 */
public string
print_spell_list(string header, object * spellobjs)
{
    string message_text = "";
    int spells_known = 0;
    if (sizeof(spellobjs))
    {
        message_text += sprintf("%'='" + sprintf("%d", strlen(header) + 4) + "s\n", "");
        message_text += sprintf("= %s =\n", header);
        message_text += sprintf("%'='" + sprintf("%d", strlen(header) + 4) + "s\n", "");
        foreach (object spellobj : spellobjs)
        {
            if (!spellobj->query_spell_can_be_learned(this_player()))
            {
                // Only show spells that we actually know
                continue;
            }
            spells_known++;
            message_text += sprintf("%-=12.12s %-=57.57s\n", spellobj->query_spell_name(),
                spellobj->query_spell_desc() + " ("
                + spellobj->query_spell_ingredients_description() + ")");
        }
        message_text += "\n";
    }
    if (spells_known == 0)
    {
        return "";
    }
    return message_text;
}
/*
 * prayers - Show what prayers we know
 */
/*
 * Function name: prayers
 * Description:   List the active prayers.
 */
public int
prayers(string str)
{
    object *spellobjs = this_player()->query_spellobjs();
    spellobjs = filter(spellobjs, &wildmatch(ELEMENTALIST_SPELLS + "*") @ file_name);

    if (!sizeof(spellobjs))
    {
        write("You have no prayers.\n");
        return 1;
    }

    object * power_spells = filter(spellobjs, &->is_worshipper_power_spell());
    object * defensive_spells = filter(spellobjs, &->is_worshipper_defensive_spell());
    object * base_spells = spellobjs - power_spells - defensive_spells;

    string message_text = "Prayers for the Elemental Worshippers of Calia\n\n";
    message_text += print_spell_list("Lesser Elemental Worshipper Gifts", base_spells);
    message_text += print_spell_list("Defensive Elemental Worshipper Gifts", defensive_spells);
    message_text += print_spell_list("Greater Elemental Worshipper Gifts", power_spells);
    message_text += "To invoke your gift, simply <pray> with the name of the gift.\n";
    this_player()->more(generate_scroll_text(message_text, "Property of the Elemental Guilds of Calia"));
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

    if (str == "worshipper" || str == "worshippers")
    {
        if (!pointerp(files = get_dir(ELEMENTALIST_HELP)) || !sizeof(files))
        {
            return 0;
        }

        if (!stringp(content = read_file(ELEMENTALIST_HELP + "general")))
        {
            notify_fail("Something is terribly wrong! Please contact "
                + "the guildmaster and let them know that the help files "
                + "for the Worshippers are not working property.\n");
            return 0;
        }

        write("You fuss around with your notes and read the scroll "
            + "introducing the Elemental Worshippers of Calia.\n");
        this_player()->more(generate_scroll_text(content, "Property of the Elemental Worshippers"));
        return 1;
    }

    if (sscanf(str, "worshipper %s", str) != 1)
    {
        return 0;
    }

    str = lower_case(str); // set everything to lowercase
    // Players can get information about spells that they know
    if ((objectp(this_player()->find_spell(str))
         && stringp(content = read_file(ELEMENTALIST_HELP_SPELLS + str)))
        || stringp(content = read_file(ELEMENTALIST_HELP + str)))
    {
        write("You flip through your guild scrolls and read the scroll "
            + "pertaining to " + capitalize(str) + ".\n");
        this_player()->more(generate_scroll_text(content, "Property of the Elemental Worshippers"));
        return 1;
    }

    notify_fail("You can't seem to find any scrolls on that topic "
        + "among the notes that you received upon joining the "
        + "guild.\n");
    return 0;
}

public int
ehistory(string str)
{
    object player = this_player();
    // This will retrieve the last 10 messages in the tell history
    mixed history = GUILD_MANAGER->query_tell_history(player);
    if (!sizeof(history))
    {
        write("You have no message history.\n");
        return 1;
    }

    string history_text = "";
    history_text += sprintf("%15-s %-s\n", "Sender", "Message");
    history_text += sprintf("%'-'15-s %'-'60s\n", "", "");
    for (int index = sizeof(history) - 1; index >= 0; --index)
    {
        mixed message_item = history[index];
        if (sizeof(message_item) < 2)
        {
            continue;
        }
        string sender = message_item[0];
        string message = message_item[1];
        history_text += sprintf("%15-s %-s\n", capitalize(sender), message);
    }

    write(history_text + "\n");
    return 1;
}

public int
edate()
{
	string elemental_date;

	elemental_date = GUILD_MANAGER->query_calendar();
	write(elemental_date);
	return 1;
}

// EMOTES

public int
ebless(string str)
{
    setuid();seteuid(getuid());
    notify_fail("Bless who?\n");
    if (!strlen(str))
    {
        return 0;
    }

    object * who = parse_this(str, " %l");
    if (!sizeof(who))
    {
        return 0;
    }

    string primary_element = GUILD_MANAGER->query_primary_element(this_player());
    switch(primary_element)
    {
    case "fire":
        actor("You bless",who," saying `May you kindle Fire "+
              "and never be burned by it.'");
        target(" blesses you saying, `May you kindle "+
               "Fire and never be burned by it.'",who);
        all2actbb(" blesses",who," and says `May you kindle "+
                  "Fire and never be burned by it.'");
        break;
    case "water":
        actor("You bless",who," saying `May the Water of "+
              "your tears always taste sweet with joy.'");
        target(" blesses you saying, `May the Water of your "+
               "tears always taste sweet with joy.'",who);
        all2actbb(" blesses",who," and says `May the Water of "+
                  "your tears always taste sweet with joy.'");
        break;
    case "earth":
        actor("You bless",who," saying `May your path across "+
              "the Earth be a soft one.'");
        target(" blesses you saying, `May your path across "+
               "the Earth be a soft one.'",who);
        all2actbb(" blesses",who," and says `May your path "+
                  "across the Earth be a soft one.'");
        break;
    case "air":
        actor("You bless",who," saying `May the Air never "+
              "send storms across your path.'");
        target(" blesses you saying, `May the Air never "+
               "send storms across your path.'",who);
        all2actbb(" blesses",who," and says `May the Air "+
                  "never send storms across your path.'");
        break;
    case "life":
        actor("You bless",who," saying `May the Spirits never "+
              "hinder your path.'");
        target(" blesses you saying, `May the Spirits never "+
               "hinder your path.'",who);
        all2actbb(" blesses",who," and says `May the Spirits "+
                  "never hinder your path.'");
        break;
    default:
        actor("You bless",who," saying `May the Elements never "+
              "hinder your path.'");
        target(" blesses you saying, `May the Elements never "+
               "hinder your path.'",who);
        all2actbb(" blesses",who," and says `May the Elements "+
                  "never hinder your path.'");
        break;
    }
    return 1;
}

public int
echant(string str)
{
    setuid();seteuid(getuid());
    string patron_elemental = GUILD_MANAGER->query_primary_element(this_player());

    // Without any arguments, we just display the emote.
    if (!strlen(str))
    {
        switch (patron_elemental)
        {
        case "fire":
            write("You sit briefly and chant in the sounds of a "+
                  "crackling flame.\n");
            all(" sits down and begins to chant.\nYou hear the " +
                "sound of crackling flames in "+ this_player()->query_possessive() +
                " voice.  After a brief " + "moment, " +
                this_player()->query_pronoun() +" rises again.");
            break;
        case "earth":
            write("You sit briefly and chant in the sounds of the "+
                  "pounding earth.\n");
            all(" sits down and begins to chant.\nYou hear sounds "+
                "like that of the pounding earth in "+this_player()->query_possessive()+" voice.  "+
                "After a brief moment, "+this_player()->query_pronoun()+" rises again.");
            break;
        case "water":
            write("You sit briefly and chant in the sounds of the "+
                  "ocean waves.\n");
            all(" sits down and begins to chant.\nYou hear the "+
                "sound of the ocean in "+this_player()->query_possessive()+" voice.  After a brief "+
                "moment, "+this_player()->query_pronoun()+" rises again.");
            break;
        case "air":
            write("You sit briefly and chant in the sounds of the "+
                  "howling winds.\n");
            all(" sits down and begins to chant.\nYou hear the "+
                "sounds of the howling winds in "+this_player()->query_possessive()+" voice.  "+
                "After a brief moment, "+this_player()->query_pronoun()+" rises again.");
            break;
        case "life":
            write("You sit briefly and chant in the sounds of the "+
                  "inner spirit.\n");
            all(" sits down and begins to chant.\nYou hear the "+
                "sounds of the inner spirit in "+this_player()->query_possessive()+" voice.  "+
                "After a brief moment, "+this_player()->query_pronoun()+" rises again.");
            break;
        default:
            // No element chosen yet
            write("You sit briefly and chant in the ancient mantras.\n");
            all(" sits down and begins to chant.\nAfter a brief moment, "
                + this_player()->query_pronoun() + " rises again.");
            break;
        }
        return 1;
    }

    // If the user specified a message, we use a guild specific speech.
    write("You chant in the ancient mantras: " + str + "\n");
    this_player()->gmcp_comms("echant", 0, "You chant in the ancient mantras: " + str + "\n");

    object * listeners = FILTER_LIVING_OBJECTS(all_inventory(environment(this_player())));
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
    tell_room(environment(this_player()), QCTNAME(this_player()) + " chants: "
              + str + "\n", not_understand_speech + ({ this_player() }), this_player());
    object * understand_speech = listeners - not_understand_speech - ({ this_player() });
    filter(understand_speech, &->query_met(this_player()))->gmcp_comms("chant",
        this_player()->query_met_name(),
        this_player()->query_met_name() + " chants: " + str + "\n");
    filter(understand_speech, not @ &->query_met(this_player()))->gmcp_comms("chant",
        "The " + this_player()->query_nonmet_name(),
        "The " + this_player()->query_nonmet_name() + " chants: " + str + "\n");

    // For the people who don't understand, we send a generic message
    not_understand_speech->catch_msg(QCTNAME(this_player()) + " chants in ancient mantras.\n");
    return 1;
}

public int
echarge(string str)
{
    setuid();seteuid(getuid());
    string primary_element = GUILD_MANAGER->query_primary_element(this_player());
    if (!strlen(str))
    {
        switch (primary_element)
        {
        case "fire":
            write("Your eyes glow a fiery red as you call out a "+
                  "battle cry in honour of Lord Pyros!\n");
            all("'s eyes glow a fiery red as "+this_player()->query_pronoun()+" cries out, "+
                "'For Lord Pyros!' and charges into battle.");
            break;
        case "earth":
            write("You feel the ground tremble beneath your "+
                  "feet as you call out a battle cry in honour of Lady Gu!\n");
            all("'s fists almost appear to be stone as "+this_player()->query_pronoun()+" cries out,"+
                " 'For Lady Gu!' and charges into battle.");
            break;
        case "water":
            write("You hear the sound of waves crashing against a "+
                  "rocky shore as you call out a battle cry in honour "+
                  "of Lord Diabrecho!\n");
            all("'s eyes flash a deep sea blue as "+this_player()->query_pronoun()+" cries out, "+
                "'For Lord Diabrecho!' and charges into battle.");
            break;
        case "air":
            write("You hear the sound of the howling winds of Aeria "+
                  "as you call out a battle cry in honour of the Elemental "+
                  "Lady!\n");
            all("'s voice sounds like that of a hurricane force wind "+
                "as "+this_player()->query_pronoun()+" cries out, 'For Lady Aeria!' and charges "+
                "into battle.");
            break;
        case "life":
            write("Your eyes pulse with energy as you call out a "+
                  "battle cry in honour of Psuchae!\n");
            all("'s eyes pulse with energy as "+this_player()->query_pronoun()+" cries out, "+
                "'For Psuchae!' and charges into battle.");
            break;
        default:
            notify_fail("You must first select a primary element before you can perform an elemental charge.\n");
            return 0;
        }
        return 1;
    }

    object target = PARSE_COMMAND_ONE(str, environment(this_player()), "[the] %i");
    if (!target)
    {
        notify_fail("You have no idea how to attack that.\n");
        return 0;
    }

    if (!objectp(target) || !IS_LIVING_OBJECT(target))
    {
        notify_fail("You have no idea how to attack " + target->query_the_name(this_player()) + ".\n");
        return 0;
    }

    switch (primary_element)
    {
    case "fire":
        this_player()->catch_msg("You call out a battle cry in honour of Lord Pyros and "+
              "feel the strength of an unextinguishable fire flow through "+
              "you as you attack " + QTNAME(target) + ".\n");
        all("'s eyes glow a fiery read as "+this_player()->query_pronoun()+" cries out, "+
            "'For Lord Pyros!' and charges into battle.");
        this_player()->command("kill "+str);
        break;
    case "earth":
        this_player()->catch_msg("The ground shakes beneath your feet as you call out "+
              "a battle cry in honour of Lady Gu and attack " + QTNAME(target) + ".\n");
        all("'s fists almost appear to be stone as "+this_player()->query_pronoun()+" cries out,"+
            " 'For Lady Gu!' and charges into battle.");
        this_player()->command("kill "+str);
        break;
    case "water":
        this_player()->catch_msg("Your veins flow with the power of a mighty sea storm "+
              "as you call out a battle cry in honour of Lord "+
              "Diabrecho and attack " + QTNAME(target) + ".\n");
        all("'s eyes flash a deep sea blue as "+this_player()->query_pronoun()+" cries out, "+
            "'For Lord Diabrecho!' and charges into battle.");
        this_player()->command("kill "+str);
        break;
    case "air":
        this_player()->catch_msg("You feel the power of a great tornado flow throughout "+
              "your body as you call out a battle cry in honour of "+
              "Lady Aeria and attack " + QTNAME(target) + ".\n");
        all("'s voice sounds like that of a hurricane force wind "+
            "as "+this_player()->query_pronoun()+" cries out, 'For Lady Aeria!' and charges "+
            "into battle.");
        this_player()->command("kill "+str);
        break;
    case "life":
        this_player()->catch_msg("Your eyes pulse with energy as you call out a "+
                  "battle cry in honour of Psuchae and attack " + QTNAME(target) + ".\n");
        all("'s eyes pulse with energy as "+this_player()->query_pronoun()+" cries out, "+
                "'For Psuchae!' and charges into battle.");
        this_player()->command("kill "+str);
        break;
    default:
            notify_fail("You must first select a primary element before you can perform an elemental charge.\n");
            return 0;
    }
    return 1;
}

public int
econvert(string str)
{
    setuid();seteuid(getuid());
    notify_fail("Convert who?\n");
    if (!strlen(str))
    {
        return 0;
    }

    object * targets = parse_this(str, " %l");
    if (!sizeof(targets) || !objectp(targets[0]))
    {
        return 0;
    }

    string primary_element = GUILD_MANAGER->query_primary_element(this_player());
    object emotee = targets[0];

    if (!IS_MEMBER(emotee))
    {
        switch (primary_element)
        {
        case "fire":
            actor("You attempt to convert", targets, " to follow Lord Pyros.");
            target(" tries to convince you to convert, and follow the ways of Lord Pyros.", targets);
            break;

        case "earth":
            actor("You attempt to convert", targets," to follow Lady Gu.");
            target(" tries to convince you to convert, and follow the ways of Lady Gu.", targets);
            break;

        case "water":
            actor("You attempt to convert", targets," to follow Lord Diabrecho.");
            target(" tries to convince you to convert, and follow the ways of Lord Diabrecho.", targets);
            break;

        case "air":
            actor("You attempt to convert", targets," to follow Lady Aeria.");
            target(" tries to convince you to convert, and follow the ways of Lady Aeria.", targets);
            break;

        case "life":
            actor("You attempt to convert", targets," to follow Psuchae.");
            target(" tries to convince you to convert, and follow the ways of Psuchae.", targets);
            break;

        default:
            notify_fail("Before trying to convert others, you should first choose a primary element!\n");
            return 0;
        }
        all2actbb(" attempts to convert", targets, " to " + this_player()->query_possessive()
                + " Elemental ways.");
        return 1;
    }

    notify_fail("You can't convert someone who is already a follower of the Elementals of Calia!\n");
    return 0;
}

public int
ecurse(string str)
{
    setuid();seteuid(getuid());
    string primary_element = GUILD_MANAGER->query_primary_element(this_player());

    notify_fail("Curse who?\n");
    if (!strlen(str))
    {
        return 0;
    }

    object * who = parse_this(str, " %l");
    if (!sizeof(who))
    {
        return 0;
    }

    if (!IS_MEMBER(who[0]))
    {
        switch (primary_element)
        {
        case "fire":
            actor("You curse",who," in the name of Lord Pyros.");
            target(" curses you with the wrath of Lord Pyros.",who);
            break;
        case "earth":
            actor("You curse",who," in the name of Lady Gu.");
            target(" curses you with the wrath of Lady Gu.",who);
            break;
        case "water":
            actor("You curse",who," in the name of Lord Diabrecho.");
            target(" curses you with the wrath of Lord Diabrecho.",who);
            break;
        case "air":
            actor("You curse",who," in the name of Lady Aeria.");
            target(" curses you with the wrath of Lady Aeria.",who);
            break;
        case "life":
            actor("You curse",who," in the name of Psuchae.");
            target(" curses you with the wrath of Psuchae.",who);
            break;
        default:
            notify_fail("You must first choose a primary element before you can curse.\n");
            return 0;
        }
        all2actbb(" curses",who,".");
        return 1;
    }
    else
    {
        actor("You curse",who," in the name of the Elementals.");
        target(" curses you with the wrath of the five Elementals.",who);
        all2actbb(" curses",who,".");
        return 1;
    }
}

public int
eeyes()
{
    setuid();seteuid(getuid());
    string primary_element = GUILD_MANAGER->query_primary_element(this_player());
    switch (primary_element)
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
            all("'s eyes pulse with power.");
            break;
    }
    return 1;
}

public int
efarewell(string str)
{
    setuid();seteuid(getuid());
    notify_fail("Bid farewell to who?\n");
    if (!strlen(str))
    {
        return 0;
    }

    object * oblist = parse_this(str," %l");
    if (!sizeof(oblist))
    {
        return 0;
    }

    target(" bids you farewell and good luck in your journeys.",oblist);
    if (sizeof(oblist) == 1)
    {
        actor("You bid",oblist," farewell and good luck in "+
            oblist[0]->query_possessive()+" journeys.");
        all2actbb(" bids",oblist," farewell and good luck in "+
            oblist[0]->query_possessive()+" journeys.");
    }
    else
    {
        actor("You bid",oblist," farewell and good luck in their journeys.");
        all2actbb(" bids",oblist," farewell and good luck in their journeys.");
    }
    return 1;
}

public int
egaze()
{
    setuid();seteuid(getuid());
    if ((environment(this_player())->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER) ||
        (environment(this_player())->query_prop(ROOM_I_INSIDE)))
    {
        write("You gaze upwards in thoughtful silence.\n");
        all(" gazes upwards in thoughtful silence.");
        SOULDESC("gazing upwards in thoughtful silence");
    }
    else
    {
        write("You gaze off towards the sky in thoughtful silence.\n");
        all(" gazes off towards the sky in thoughtful silence.");
        SOULDESC("gazing upwards in thoughtful silence");
    }
    if (CARVING_CHAMBER->player_carve_count(this_player()) < CARVING_CHAMBER->max_carve_count(this_player()))
    {
        write("A voice echoes in your mind: "+
            "You are ready to carve a Word of Power into one of your "+
            "Elemental Tools.\n");
        all(" seems to radiate with power momentarily.");
    }
    return 1;
}

public int
filter_is_member(object player)
{
    return IS_MEMBER(player);
}

public int
ehail(string str)
{
    setuid();seteuid(getuid());
    notify_fail("Hail who?\n");
    if (!strlen(str))
    {
        return 0;
    }

    object * onl = FILTER_LIVE(all_inventory(environment(this_player())));
    if (!sizeof(onl))
    {
        return 0;
    }

    object * oblist = parse_this(str," %l");
    oblist -= ({this_player()});
    if (!sizeof(oblist))
    {
        return 0;
    }

    onl -= oblist;
    onl -= ({this_player()});

    object * members = filter(oblist, filter_is_member);
    object * nonmem = oblist - members;


    /* Non-members */
    if (sizeof(nonmem))
    {
        nonmem->catch_msg(QCTNAME(this_player()) + " reaches toward "
                          + "you with "+ this_player()->query_possessive()
                          +" left hand open, palm facing you, in an "
                          + "ancient sign of greetings.\n");
        this_player()->catch_msg("You hail " + FO_COMPOSITE_LIVE(nonmem, this_player())
                                 + " in an ancient sign of greetings.\n");
    }

    /* Members */
    if (sizeof(members))
    {
        members->catch_msg(QCTNAME(this_player()) + " reaches "
                           + "toward you with "
                           + this_player()->query_possessive()
                           +" left hand open, palm facing you, "
                           + "in an ancient sign of greetings.\n"
                           + "You place your right fist in "
                           + this_player()->query_possessive()
                           + " hand to complete the greeting.\n");
        this_player()->catch_msg("You hail " + FO_COMPOSITE_LIVE(members, this_player())
                                 + " in an ancient sign of greetings.  "
                                 + (sizeof(members) > 1 ? "They complete" :
                                    capitalize(members[0]->query_pronoun())+" completes")
                                 + " the greeting by placing "
                                 + (sizeof(members) > 1 ? "their right fists" :
                                    members[0]->query_possessive()+" right fist")
                                 + " in your left hand.\n");
    }

    foreach (object onlooker : onl)
    {
        onlooker->catch_msg(QCTNAME(this_player()) + " reaches toward "
                            + FO_COMPOSITE_LIVE(oblist, onlooker) + " with "
                            + this_player()->query_possessive() + " left hand, in an "
                            + "ancient sign of greetings.\n");
        if (sizeof(members))
        {
            onlooker->catch_msg(FO_COMPOSITE_LIVE(members, onlooker) + " "
                                + (sizeof(members) > 1 ? "complete" : "completes")
                                + " the greeting by placing "
                                + (sizeof(members) > 1 ? "their right fists" : members[0]->query_possessive()+" right fist")
                                + " in " + QTPNAME(this_player()) + " left hand.\n");
        }
    }

    return 1;
}

public int
ejoy()
{
    setuid();seteuid(getuid());
    write("You show an expression of your joy.\n");
    all("'s face brightens with joy.");
    return 1;
}

public int
ekneel(string str)
{
    setuid();seteuid(getuid());
    notify_fail("Kneel before who?\n");
    if (!strlen(str))
    {
        write("You kneel in prayer briefly.\n");
        all(" kneels briefly in prayer.");
        return 1;
    }

    object * who = parse_this(str, " %l");
    if (!sizeof(who))
    {
        return 0;
    }

    actor("You kneel briefly before", who);
    target(" kneels briefly before you.", who);
    all2actbb(" kneels briefly before", who, ".");
    return 1;
}

public int
elaugh()
{
    setuid();seteuid(getuid());
    string primary_element = GUILD_MANAGER->query_primary_element(this_player());
    switch (primary_element)
    {
    case "fire":
        write("You laugh chaotically with the sound of a crackling bonfire.\n");
        all(" tilts "+this_player()->query_possessive()+" head back in a chaotic laughter and you "+
            "are reminded inexplicably of a crackling bonfire.");
        break;
    case "earth":
        write("You laugh heartily like the earth rumbling.\n");
        all(" tilts "+this_player()->query_possessive()+" head back in a hearty laughter and you "+
            "are reminded of the sound of the ground rumbling.");
        break;
    case "water":
        write("You laugh merrily with the sound of a babbling brook.\n");
        all(" tilts "+this_player()->query_possessive()+" head back in a merry laughter and you "+
            "are reminded inexplicably of a babbling brook.");
        break;
    case "air":
        write("You laugh confidently with the sound of the howling winds.\n");
        all(" tilts "+this_player()->query_possessive()+" head back in a confident laughter and you "+
            "are reminded of the sound of a howling wind.");
        break;
    case "life":
        write("You laugh quietly, the sound soothing your soul.\n");
        all(" tilts "+this_player()->query_possessive()+" head back in a quiet laughter. The sound "+
            "seems to soothe your soul.");
        break;
    default:
        notify_fail("You need to select a primary element before you can "
                    + "laugh with the power of the elementals.\n");
        return 0;
    }

    return 1;
}

public int
emeditate()
{
	int practice_level, guild_conduit;

	string practice_desc, guild_desc;

	practice_level = GUILD_MANAGER->query_practice_level(this_player());
	guild_conduit = GUILD_MANAGER->query_guild_conduit();

    switch(practice_level)
    {
    	case 0:
    		practice_desc = "you have no practice at prayers.\n";
    		break;
    	case 1..4999:
    		practice_desc = "you have insignificant practice at prayers.\n";
    		break;
    	case 5000..9999:
    		practice_desc = "you have a tiny amount of practice at prayers.\n";
    		break;
    	case 10000..14999:
    		practice_desc = "you have a minimal amount of practice at prayers.\n";
    		break;
    	case 15000..19999:
    		practice_desc = "you have slight practice at prayers.\n";
    		break;
    	case 20000..24999:
    		practice_desc = "you have a low amount of practice at prayers.\n";
    		break;
    	case 25000..29999:
    		practice_desc = "you have some amount of practice at prayers.\n";
    		break;
    	case 30000..34999:
    		practice_desc = "you have a modest amount of practice at prayers.\n";
    		break;
    	case 35000..39999:
    		practice_desc = "you have a decent amount of practice at prayers.\n";
    		break;
    	case 40000..44999:
    		practice_desc = "you have a nice amount of practice at prayers.\n";
    		break;
    	case 45000..54999:
    		practice_desc = "you have a good amount of practice at prayers.\n";
    		break;
    	case 55000..59999:
    		practice_desc = "you have a very good amount of practice at prayers.\n";
    		break;
    	case 60000..67499:
    		practice_desc = "you have a major amount of practice at prayers.\n";
    		break;
    	case 67500..72499:
    		practice_desc = "you have a great amount of practice at prayers.\n";
    		break;
    	case 72500..77499:
    		practice_desc = "you have an extremely good amount of practice at prayers.\n";
    		break;
    	case 77500..82499:
    		practice_desc = "you have an awesome amount of practice at prayers.\n";
    		break;
    	case 82500..87499:
    		practice_desc = "you have an immense amount of practice at prayers.\n";
    		break;
    	case 87500..92499:
    		practice_desc = "you have a tremendous amount of practice at prayers.\n";
    		break;
    	default:
    		practice_desc = "you have a fantastic amount of practice at prayers.\n";
    		break;
    }

    switch(guild_conduit)
    {
    	case 0:
    		guild_desc = "the Temple Conduit is empty!\n";
    		break;
    	case 1..33750:
    		guild_desc = "the Temple Conduit has a low level of energy.\n";
    		break;
    	case 33751..67500:
    		guild_desc = "the Temple Conduit has a medium level of energy.\n";
    		break;
    	default:
    		guild_desc = "the Temple Conduit has a high level of energy.\n";
    		break;
    }

    write("You focus your energies inwards and meditate on yourself. "+
        "You determine " + practice_desc);
    write("\nYou focus your energies and meditate on the Temple Conduit. "+
        "You determine " + guild_desc);

	return 1;
}

public int
eprepare()
{
    setuid();seteuid(getuid());
    string primary_element = GUILD_MANAGER->query_primary_element(this_player());
    switch (primary_element)
    {
    case "fire":
        write("You murmur a prayer to Lord Pyros in preparation "+
              "of your next battle.\n");
        all(" murmurs a prayer under "+this_player()->query_possessive()+" breath in preparation "+
            "of "+this_player()->query_possessive()+" next battle.");
        break;
    case "earth":
        write("You murmur a prayer to Lady Gu in preparation "+
              "of your next battle.\n");
        all(" murmurs a prayer under "+this_player()->query_possessive()+" breath in preparation "+
            "of "+this_player()->query_possessive()+" next battle.");
        break;
    case "water":
        write("You murmur a prayer to Lord Diabrecho in preparation "+
              "of your next battle.\n");
        all(" murmurs a prayer under "+this_player()->query_possessive()+" breath in preparation "+
            "of "+this_player()->query_possessive()+" next battle.");
        break;
    case "air":
        write("You murmur a prayer to Lady Aeria in preparation "+
              "of your next battle.\n");
        all(" murmurs a prayer under "+this_player()->query_possessive()+" breath in preparation "+
            "of "+this_player()->query_possessive()+" next battle.");
        break;
    case "life":
        write("You murmur a prayer to Psuchae in preparation "+
              "of your next battle.\n");
        all(" murmurs a prayer under "+this_player()->query_possessive()+" breath in preparation "+
            "of "+this_player()->query_possessive()+" next battle.");
        break;
    default:
        notify_fail("You need to select a primary element before you can prepare "
                    + "for battle with the power of the elementals.\n");
        return 0;
    }
    return 1;
}

public int
elisten(string str)
{
    setuid();seteuid(getuid());
    if (!strlen(str))
    {
        notify_fail("Listen to what? Air/Fire/Water/Earth/Spirit perhaps?\n");
        return 0;
    }

    string element = lower_case(str);
    switch (element)
    {
        case "earth":
            write("You listen attentively to the rumble of a distant earthquake.\n");
            all(" listens attentively to the rumble of a distant earthquake.");
            break;
        case "water":
            write("You listen attentively to the hum of waves.\n");
            all(" listens attentively to the hum of waves.");
            break;
        case "air":
            write("You listen attentively to the whispers of the wind.\n");
            all(" listens attentively to the whispers of the wind.");
            break;
        case "fire":
            write("You listen attentively to the crackling flame.\n");
            all(" listens attentively to the crackling flame.");
            break;
        case "spirit":
            write("You listen attentively to the energies of all things.\n");
            all(" listens attentively to the energies of all things.");
            break;
        default:
            notify_fail("Listen to what? Earth/Air/Fire/Water/Spirit perhaps?\n");
            return 0;
    }

    return 1;
}

public int
escoff(string str)
{
    setuid();seteuid(getuid());
    notify_fail("Scoff at who?\n");
    if(!strlen(str))
    {
        return 0;
    }
    object * who = parse_this(str, " %l");
    if (!sizeof(who))
    {
        return 0;
    }

    if (IS_MEMBER(who[0]))
    {
        notify_fail("You can't scoff at an Elemental Worshipper!\n");
        return 0;
    }

    actor("You scoff at",who," for believing in the power of such a minor diety.");
    target(" scoffs at you for believing in the power of such a "+
        "minor diety.",who);
    all2actbb(" scoffs at",who,".");
    return 1;
}

public int
esilence()
{
    setuid();seteuid(getuid());
    write("You motion for a moment of silence.\n");
    all(" raises "+this_player()->query_possessive()+" hand and calls for a moment of silence.");
    return 1;
}

public int
esmile(string str)
{
    setuid();seteuid(getuid());
    notify_fail("Smile at who?\n");
    if (!strlen(str))
    {
        write("You smile confidently about your allies.\n");
        all(" smiles confidently, knowing " + this_player()->query_pronoun() + " has " +
            "such powerful allies to aid " + this_player()->query_objective() + ".");
        return 1;
    }
    object * who = parse_this(str, " %l");
    if (!sizeof(who))
    {
        return 0;
    }
    actor("You smile confidently at",who);
    target(" smiles confidently at you, knowing " + this_player()->query_pronoun() +
           " has such powerful allies to aid " + this_player()->query_objective() + ".", who);
    all2actbb(" smiles confidently at", who, ", knowing that " +
              this_player()->query_pronoun() + " has such powerful allies to aid "
              + this_player()->query_objective() + ".");
    return 1;
}

public int
estare(string str)
{
    setuid();seteuid(getuid());
    string primary_element = GUILD_MANAGER->query_primary_element(this_player());
    notify_fail("Stare at who?\n");
    if (!strlen(str))
    {
        return 0;
    }

    if (environment(this_player())->query_prop(ROOM_I_INSIDE))
    {
        notify_fail("You cannot use your Elemental stare indoors.\n");
        return 0;
    }

    object * who = parse_this(str, "[at] %l");
    if (!sizeof(who))
    {
        return 0;
    }

    switch (primary_element)
    {
    case "fire":
        actor("The temperature starts rising as you stare angrily "+
              "at",who,".");
        target(" stares angrily at you.\nYour skin temperature "+
               "suddenly begins to rise, almost burning you, then "+
               "returns to normal.",who);
        all2actbb(" stares angrily at",who,".  Their skin temperature "+
                  "suddenly beings to rise, almost burning them, then "+
                  "returns to normal.");
        break;
    case "earth":
        actor("The earth starts rumbling as you stare angrily at",who,".");
        target(" stares angrily at you.\nThe ground beneath your feet "+
               "begins to rumble for a moment but quickly calms.",who);
        all2actbb(" stares angrily at",who,".  The ground beneath "+
                  "their feet begins to rumble for a moment, then "+
                  "quickly calms.");
        break;
    case "air":
        actor("The wind starts picking up speed as you stare angrily "+
              "at",who,".");
        target(" stares angrily at you.\nSuddenly a gust of wind almost "+
               "knocks you over.",who);
        all2actbb(" stares angrily at",who,".  Suddenly a gust of "+
                  "wind knocks them over.");
        break;
    case "life":
        actor("The temperature starts falling as you stare angrily "+
              "at",who,".");
        target(" stares angrily at you.\nYour skin temperature "+
               "suddenly begins to drop, almost freezing you, then "+
               "returns to normal.",who);
        all2actbb(" stares angrily at",who,".  Their skin temperature "+
                  "suddenly beings to drop, almost freezing them, then "+
                  "returns to normal.");
        break;
    default:
        actor("The sky darkens and it begins raining on",who," as you "+
              "stare angrily at them.");
        target(" stares angrily at you.\nSuddenly the sky darkens and "+
               "it begins raining on you for a brief moment.  The rain "+
               "stops and the sky returns to normal.",who);
        all2actbb(" stares angrily at",who,".  Suddenly the sky "+
                  "darkens and it begins raining on them for a brief moment.  "+
                  "The rain stops and the sky returns to normal.");
        break;
    }
    return 1;
}

public int
evictory()
{
    setuid();seteuid(getuid());
    string primary_element = GUILD_MANAGER->query_primary_element(this_player());
    switch (primary_element)
    {
    case "fire":
        write("You close your eyes and bow your head in thanks "+
              "to Lord Pyros for your victory.\n");
        all(" closes "+this_player()->query_possessive()+" eyes and bows "+this_player()->query_possessive()+" head in thanks "+
                "to Lord Pyros for "+this_player()->query_possessive()+" victory.");
        break;
    case "earth":
        write("You close your eyes and bow your head in thanks "+
              "to Lady Gu for your victory.\n");
        all(" closes "+this_player()->query_possessive()+" eyes and bows "+this_player()->query_possessive()+" head in thanks "+
            "to Lady Gu for "+this_player()->query_possessive()+" victory.");
        break;
    case "water":
        write("You close your eyes and bow your head in thanks "+
              "to Lord Diabrecho for your victory.\n");
        all(" closes "+this_player()->query_possessive()+" eyes and bows "+this_player()->query_possessive()+" head in thanks "+
            "to Lord Diabrecho for "+this_player()->query_possessive()+" victory.");
        break;
    case "air":
        write("You close your eyes and bow your head in thanks "+
              "to Lady Aeria for your victory.\n");
        all(" closes "+this_player()->query_possessive()+" eyes and bows "+this_player()->query_possessive()+" head in thanks "+
            "to Lady Aeria for "+this_player()->query_possessive()+" victory.");
        break;
    case "life":
        write("You close your eyes and bow your head in thanks "+
              "to Psuchae for your victory.\n");
        all(" closes "+this_player()->query_possessive()+" eyes and bows "+this_player()->query_possessive()+" head in thanks "+
            "to Psuchae for "+this_player()->query_possessive()+" victory.");
        break;
    default:
        notify_fail("You can't give thanks to an Elemental until you select "
                    + "a primary element!\n");
        return 0;
    }
    return 1;
}
