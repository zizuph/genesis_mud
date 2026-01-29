/*
 * Command Soul for the Elemental Seekers of Calia
 *
 * This is the command soul that every Elemental Seeker will
 * have. It includes emotes as well as the abilities/spells that they
 * possess.
 *
 * Created by Petros, December 2010
 * Modified for Seekers by Jaacar, May 2016
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
    return GUILD_ES_NAME + " Soul"; 
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
        "eanemos"       : "do_ability", // Tell Spell
        "eapodosi"      : "do_ability", // Teleport Home Spell
        "eelefrinisi"   : "do_ability", // Lighten Burden/Relieve Encumbrance Spell
        "epyrofosti"    : "do_ability", // Light Spell

        // Guild Abilities            
        "ehistory"      : "ehistory",   // Lists the recent anemos history
        "edate"         : "edate",      // Shows the Elemental date 
        
        // Emotes
        "echant"        : "echant",
        "ech"           : "echant",
        "efare"         : "efarewell",
        "efarewell"     : "efarewell",
        "egaze"         : "egaze",
        "ehail"         : "ehail",
        "ejoy"          : "ejoy",
        "ekneel"        : "ekneel",
        "elisten"       : "elisten",
        "esilence"      : "esilence",
        "estare"        : "estare",

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
        "eanemos"       : ELEMENTALIST_SPELLS + "anemos",
        "eapodosi"      : ELEMENTALIST_SPELLS + "apodosi",
        "eelefrinisi"   : ELEMENTALIST_SPELLS + "elefrinisi",
        "epyrofosti"    : ELEMENTALIST_SPELLS + "pyrofosti",
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
	write("You cannot use this command as a Seeker.\n");
	return 1;
}

/*
 * Function name: pray
 * Description:   The "pray" command.
 * Arguments:     string str - arguments to "pray" command
 * Returns:       1/0 - pray command executed/not executed
 */
int
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
    
    string message_text = "Prayers for the Elemental Seekers of Calia\n\n";
    message_text += print_spell_list("Elemental Seeker Gifts", base_spells);
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
    
    if (str == "seeker") 
    {         
        if (!pointerp(files = get_dir(ELEMENTALIST_HELP)) || !sizeof(files))
        {
            return 0; 
        }
        
        if (!stringp(content = read_file(ELEMENTALIST_HELP + "seeker_general")))
        {
            notify_fail("Something is terribly wrong! Please contact "
                + "the guildmaster and let them know that the help files "
                + "for the Seekers are not working property.\n");
            return 0;
        }
        
        write("You fuss around with your notes and read the scroll "
            + "introducing the Elemental Seekers of Calia.\n");
        this_player()->more(generate_scroll_text(content, "Property of the Elemental Seekers"));
        return 1;
    } 

    if (sscanf(str, "seeker %s", str) != 1)
    {
        return 0;
    }
    
    str = lower_case(str); // set everything to lowercase
    // Players can get information about spells that they know
    if ((objectp(this_player()->find_spell(str))
         && stringp(content = read_file(ELEMENTALIST_HELP_SPELLS + str)))
        || stringp(content = read_file(ELEMENTALIST_HELP + "seeker_"+str)))
    {
        write("You flip through your guild scrolls and read the scroll "
            + "pertaining to " + capitalize(str) + ".\n");
        this_player()->more(generate_scroll_text(content, "Property of the Elemental Seekers")); 
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
echant(string str)
{
    setuid();seteuid(getuid());
    
    // Without any arguments, we just display the emote.
    if (!strlen(str))
    {
        write("You sit briefly and chant in the ancient mantras.\n");
        all(" sits down and begins to chant.\nAfter a brief moment, " 
            + this_player()->query_pronoun() + " rises again.");
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
elisten(string str)
{
    setuid();seteuid(getuid());
    if (!strlen(str))
    {
        notify_fail("Listen to what? Air/Fire/Water/Earth perhaps?\n");
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
        default:
            notify_fail("Listen to what? Earth/Air/Fire/Water perhaps?\n");
            return 0;
    }

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
estare(string str)
{
    setuid();seteuid(getuid());
    notify_fail("Stare at who?\n");
    if (!strlen(str))
    {
        return 0;
    }

    object * who = parse_this(str, "[at] %l");
    if (!sizeof(who))
    {
        return 0;
    }

    actor("You stare angrily at",who);
    target(" stares angrily at you.\n",who);
    all2actbb(" stares angrily at",who,".");
    return 1;
}

