/*
 * Command Soul for the Academy of Elemental Arts
 *
 * This is the command soul that every member of the Academy will
 * have. It includes emotes as well as the abilities/spells that they
 * possess.
 *
 * Created by Petros, September 2009
 */

#pragma strict_types

#include <macros.h>
#include "defs.h"

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";

/* 
 * Function name: get_soul_id
 * Description:   Give a name for this soul
 * Returns:       string - the soul's id
 */
public string
get_soul_id() 
{ 
    return GUILD_NAME + " Soul"; 
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
        "acheiropoto"       : "do_ability",
        "apyrofosti"        : "do_ability",
        "anumastomo"        : "do_ability",
        "ahydrokine"        : "do_ability",
        "alithodermu"       : "do_ability",
        "apetifrago"        : "do_ability",
        // Emotes
        "ameditate"         : "ameditate",
        "apractice"         : "apractice",
        "alisten"           : "alisten",
        "afocus"            : "afocus",
        "ayawn"             : "ayawn",
        "astudy"            : "astudy",
        "aobserve"          : "aobserve",
        "afarewell"         : "afarewell",
        "akneel"            : "akneel",
        "aspark"            : "aspark",
        "awater"            : "awater",
        "atwirl"            : "atwirl",
        "acalm"             : "acalm",
        "apraise"           : "apraise",
        "adraw"             : "adraw",
        "ateach"            : "ateach",
        "atell"             : "atell",
        "ahistory"          : "ahistory",
        // Help and Options
        "alist"             : "alist",
        "aprimary"          : "aprimary",        
        "help"              : "help",        
        "aleave"            : "aleave",
    ]);
}

public mapping
query_ability_map()
{
    return ([
        "acheiropoto"  : ACADEMIC_SPELLS + "cheiropoto",
        "apyrofosti"   : ACADEMIC_SPELLS + "pyrofosti",
        "anumastomo"   : ACADEMIC_SPELLS + "numastomo",
        "ahydrokine"   : ACADEMIC_SPELLS + "hydrokine",
        "alithodermu"  : ACADEMIC_SPELLS + "lithodermu",
        "apetifrago"   : ACADEMIC_SPELLS + "petifrago",
    ]);
}

public int
ameditate(string str)
{
    if (strlen(str))
    {
        notify_fail("You can only meditate on your own!\n");
        return 0;
    }
    
    // Focusing meditation
    write("You close your eyes and focus your attention inward, meditating "
        + "upon the mysteries of the Elemental Arts.\n");
    allbb(" closes " + this_player()->query_possessive() + " eyes and focuses "
        + this_player()->query_possessive() + " attention inward, "
        + "meditating silently.");
    return 1;
}

public int
apractice(string str)
{
    if (strlen(str))
    {
        notify_fail("Practicing should be done on your own!\n");
        return 0;
    }
    
    // Mental excercises
    write("You concentrate upon your studies, practicing drills that "
        + "you have been taught.\n");
    allbb(" concentrates upon " + this_player()->query_possessive()
        + " studies, practicing drills " + this_player()->query_pronoun()
        + " has been taught.");
    return 1;
}

public int
alisten(string str)
{
    // Listen to gain knowledge from others
    object * oblist;
    
    notify_fail("Whom do you wish to listen to?\n");
    if (!str)
    {
        return 0;
    }

    oblist = parse_this(str, "[the] %l");
    if (!sizeof(oblist))
    {
        return 0;
    }

    target(" inclines " + this_player()->query_possessive() + " ear towards "
        + "you and listens closely to gain knowledge.", 
        oblist);
    actor("You incline your ear towards", oblist, " and listen closely to "
        + "gain knowledge.");
    all2act(" inclines " + this_player()->query_possessive() + " ear towards", 
        oblist, " and listens closely to gain knowledge.");    
        
    return 1;
}

public int
ayawn(string str)
{
    if (strlen(str))
    {
        notify_fail("Yawning is a personal thing, even if it is contagious!\n");
        return 0;
    }
    
    // Yawn from being tired from studies
    write("You stretch out your arms above you, tense your muscles and "
        + "let out a huge YAAAAAAWN.\n");
    allbb(" stretches out " + this_player()->query_possessive() + " arms above "
        + this_player()->query_objective() + ", tenses up " 
        + this_player()->query_possessive() + " muscles and lets out a huge "
        + "YAAAAAAAWN.");
    return 1;
}

public int
astudy(string str)
{
    if (strlen(str))
    {
        notify_fail("You should study on your own!\n");
        return 0;
    }
    
    // Go over study notes
    write("You pull out some notes from class and pore over them, "
        + "ignoring your surroundings.\n");
    allbb(" pulls out some notes from class and pores over them, ignoring "
        + this_player()->query_possessive() + " surroundings.");
    return 1;
        
}

public int
aobserve(string str)
{
    if (strlen(str))
    {
        notify_fail("You don't know how to force someone else to observe!\n");
        return 0;
    }
    
    // Observe the forces of nature around you
    write("You observe the subtle forces of the elements which surround "
        + "you.\n");
    allbb(" observes the subtle forces of the elements which surround "
        + this_player()->query_objective() + ".");
    return 1;
}

public int
afarewell(string str)
{
    object * oblist;
    
    notify_fail("Whom do you wish to say farewell to?\n");
    if (!str)
    {
        return 0;
    }

    oblist = parse_this(str, "[the] %l");
    if (!sizeof(oblist))
    {
        return 0;
    }

    target(" informs you that " + this_player()->query_pronoun() + " must "
        + "return to " + this_player()->query_possessive() + " studies, and "
        + "bids you farewell.", 
        oblist);
    actor("You inform", oblist, " that you must return to your studies, and "
        + "bid farewell.");
    all2act(" informs", oblist, " that " + this_player()->query_pronoun()
        + " must return to " + this_player()->query_possessive()
        + " studies, and bids them farewell.");    
        
    return 1;
}

public int
akneel(string str)
{    
    if (strlen(str))
    {
        notify_fail("You can only cause yourself to kneel!\n");
        return 0;
    }
    
    // Kneel on the ground to inspect the earth
    write("You kneel upon the ground and study the ground for earthly "
        + "elemental properties.\n");
    allbb(" kneels upon the ground and studies the ground for earthly "
        + "elemental properties.");
    return 1;
}

public int
aspark(string str)
{
    if (strlen(str))
    {
        notify_fail("You cannot cause sparks to appear from anyone "
            + "besides yourself!\n");
        return 0;
    }
    
    // Create sparks with hands
    write("You snap your fingers and create bright sparks from your "
        + "hand that dance around before flickering out.\n");
    allbb(" snaps " + this_player()->query_possessive() + " fingers and "
        + "creates bright sparks from " + this_player()->query_possessive()
        + " hand that dance around before flickering out.");
    return 1;
}

public int
awater(string str)
{
    if (strlen(str))
    {
        notify_fail("Try this on your own, not with someone else!\n");
        return 0;
    }
    
    // Collect moisture from the air to create raindrops
    write("You cup your hands in front of you and blow gently into them, "
        + "directing the moisture in the air to form into droplets of "
        + "water which puddle in your hands.\n");
    all(" cups their hands in front of them and blows gently, directing "
        + "the moisture in the air to form into droplets of water which "
        + "puddle in their hands.");
    return 1;
}

public int
atwirl(string str)
{
    if (strlen(str))
    {
        notify_fail("Twirling is not something you can make someone else do!\n");
        return 0;
    }
    
    // Twirls hands generating small vortexes of air
    write("You twirl your hands in a circular fashion, creating tiny "
        + "dust devils that spin around in front of you.\n");
    all(" twirls " + this_player()->query_possessive() + " hands in a "
        + "circular fashion, creating tiny dust devils that spin around "
        + "in front of " + this_player()->query_objective() + ".");
    return 1;
}

public int
acalm(string str)
{
    if (strlen(str))
    {
        notify_fail("You can only calm yourself!\n");
        return 0;
    }
    
    // Concentrates on remaining calm in the face of distractions
    write("You focus your attention inward and the distractions around "
        + "you fade to nothingness, allowing you to remain perfectly "
        + "calm.\n");
    allbb(" focuses his attention inwards and appears to be extremely calm.");
    return 1;
}

public int
apraise(string str)
{
    object * oblist;
    
    // Praises others for their attention to the Elements
    notify_fail("Whom do you wish to praise?\n");
    if (!str)
    {
        return 0;
    }

    oblist = parse_this(str, "[the] %l");
    if (!sizeof(oblist))
    {
        return 0;
    }

    target(" praises you for your attention to the Elements around you.", oblist);
    actor("You praise", oblist, " for their attention to the Elements "
        + "around them.");
    all2act(" praises", oblist, " for their attention to the Elements "
        + "around them.");
    
    return 1;
}

public int
adraw(string str)
{
    // Draws runes in the air symbolizing the Elements
    write("You use your finger to draw rune symbols of the elements "
        + "in the air.\n");
    allbb(" uses " + this_player()->query_possessive() + " finger to draw "
        + "rune symbols of the elements in the air.");
    return 1;
}

public int
ateach(string str)
{
    object * oblist;
    
    // Teach others about the Elements
    notify_fail("Whom do you wish to teach?\n");
    if (!str)
    {
        return 0;
    }

    oblist = parse_this(str, "[the] %l");
    if (!sizeof(oblist))
    {
        return 0;
    }

    target(" teaches you about the wonders of the Elements that surround "
        + "you.", oblist);
    actor("You teach", oblist, " about the wonders of the Elements that "
        + "surround them.");
    all2act(" teaches", oblist, " about the wonders of the Elements that "
        + "surround them.");
    
    return 1;    
}

public int
aprimary(string str)
{
    // Displays the users primary elemental focus
    string primary_element = ACADEMIC_MANAGER->query_primary_element(this_player());
    if (!strlen(primary_element))
    {
        write("You have not yet chosen a primary element to focus upon "
            + "in your studies.\n");
        return 1;
    }
    
    write("The primary element your studies are focused upon is "
        + capitalize(primary_element) + ". Should you wish to refocus "
        + "your studies, you can do so in the joinroom of the Academy "
        + "if you <choose> again.\n");
    return 1;
}

public int
alist(string str)
{
    // List of other Academics
    mixed list = ACADEMIC_MANAGER->query_awake_members(this_player());

    list = sort_array(map(list, &->query_presentation()));  
    list = implode(map(list, &operator(+)("- ",)), "\n");  

    this_player()->more("The following Academics are currently playing:\n"+
                        list + "\n");
    
    return 1;
}

public string
generate_scroll_text(string content)
{
    if (!strlen(content))
    {
        return "";
    }
    
    string output = "";
    string * lines = explode(content, "\n");
    
    // Create the scroll header
    output += sprintf("  %'_'68s\n", "");
    output += sprintf(" / \\%' '66s\\\n", "");
    output += sprintf("/___|%' '66s|\n", "");
    output += sprintf("|\\_/%'_'66s/\n", "");
    output += sprintf(" \\%' '65s\\\n", "");
    
    // Print the text header
    output += sprintf("  \\ %|64s\\\n", lines[0]);
    output += sprintf("   |%|64s |\n", sprintf("%'='" + strlen(lines[0]) + "s", ""));
    // Now print the text itself
    foreach (string line : lines[1..])
    {
        output += sprintf("   | %-64s|\n", line);
    }

    // Create the scroll footer
    output += sprintf("  /%' '65s/\n", "");
    output += sprintf(" /%'_'64s /_\n", "");
    output += sprintf("|/\\%' '66s\\\n", "");
    output += sprintf("\\\\_|%|66s|\n", 
        "     === Property of the Academy of Elemental Arts ===");
    output += sprintf(" \\/%'_'66s/\n", "");
    
    return output;
}

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
    
    if (str == "academic") 
    {         
        if (!pointerp(files = get_dir(ACADEMIC_HELP)) || !sizeof(files))
        {
            return 0; 
        }
        
        if (!stringp(content = read_file(ACADEMIC_HELP + "general")))
        {
            notify_fail("Something is terribly wrong! Please contact "
                + "the guildmaster and let them know that the help files "
                + "for the Academics are not working property.\n");
            return 0;
        }
        
        write("You fuss around with your notes and read the scroll "
            + "introducing the Academy of Elemental Arts.\n");
        this_player()->more(generate_scroll_text(content));
        return 1;
    } 

    if (sscanf(str, "academic %s", str) != 1)
    {
        return 0;
    }
    
    str = lower_case(str); // set everything to lowercase
    // Players can get information about spells that they know
    if ((objectp(this_player()->find_spell(str))
         && stringp(content = read_file(ACADEMIC_SPELLS_HELP + str)))
        || stringp(content = read_file(ACADEMIC_HELP + str)))
    {
        write("You flip through your class notes and read the scroll "
            + "pertaining to " + capitalize(str) + ".\n");
        this_player()->more(generate_scroll_text(content)); 
        return 1;         
    }

    notify_fail("You can't seem to find any scrolls on that topic "
        + "among the notes that you received upon joining the "
        + "guild.\n"); 
    return 0;     
}

public void
remove_confirmation_prop(object player)
{    
    player->remove_prop(ACADEMIC_I_CONFIRM_LEAVE);
}

public int
aleave(string str)
{
    object player = this_player();

    if (!objectp(player))
    {
        return 0;
    }
    
    if (!strlen(str) || str != "academy")
    {
        notify_fail("Did you want to <aleave academy>?\n");
        return 0;
    }
    
    if (!IS_MEMBER(player))
    {
        notify_fail("You are not a member of the Academy!\n");
        return 0;
    }
    
    if (!player->query_prop(ACADEMIC_I_CONFIRM_LEAVE))
    {
        write("Type the <aleave academy> command again in the next minute "
            + "to confirm that you really want to leave.\n");
        player->add_prop(ACADEMIC_I_CONFIRM_LEAVE, 1);
        // Give them 1 minute to respond. If they don't then just remove
        // the property
        set_alarm(60.0, 0.0, &remove_confirmation_prop(player));
        return 1;
    }
    
    player->remove_prop(ACADEMIC_I_CONFIRM_LEAVE);
    setuid();
    seteuid(getuid());
    if (ACADEMIC_STARTROOM->leave_guild(player))
    {
        write("You have left the Academy of Elemental Arts.\n");
        say(QCTNAME(player) + " has left the Academy of Elemental Arts.\n");
        return 1;
    }
    
    notify_fail("For some reason you can't leave the Academy.\n");
    return 0;
}

public int
afocus(string str)
{
    object player = this_player();
    if (present("_academic_focus_paralyze_object", player))
    {
        notify_fail("You are already trying to focus!\n");
        return 0;
    }
    
    if (player->query_attack())
    {
        notify_fail("You are in the middle of combat! It would be unwise to "
            + "try to focus while in combat.\n");
        return 0;
    }
    
    if (present("_academic_focus_object_", player))
    {
        notify_fail("You are already elementally focused!\n");
        return 0;
    }

    // Draws runes in the air symbolizing the Elements
    write("You calm yourself and prepare to focus yourself elementally.\n");
    allbb(" closes " + this_player()->query_possessive() + " eyes and "
        + "concentrates.");
    
    setuid();
    seteuid(getuid());
    object focus_paralyze = clone_object(ACADEMIC_FOCUS_PARALYZE);
    focus_paralyze->move(player, 1);
   
    return 1;
}

public int
atell(string str)
{
    return (ACADEMIC_SPELLS + "numastomo")->do_ability(str);
}

public int
ahistory(string str)
{
    object player = this_player();
    // This will retrieve the last 10 messages in the tell history
    mixed history = ACADEMIC_MANAGER->query_tell_history(player);
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
