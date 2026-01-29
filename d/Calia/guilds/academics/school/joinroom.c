/*
 * Joining Room for the Gelan Academy of Elemental Arts
 * 
 * This is the room where one can join the Academics, a free join
 * layman guild that serves the same purpose as the Cadet Guild, except
 * that it focuses on magical arts instead of combat.
 *
 * Created by Petros, August 2009
 */

#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include "defs.h"

inherit SCHOOL_ROOM_BASE;
inherit "/lib/skill_raise"; 

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define SCHOOL_ENTRANCE "/d/Calia/gelan/rooms/school"

// Global Variables
public string * beta_testers = ({ "petrosjr", "iluryn", "annika", "anja", 
       "uznel", "alfirin", "opheliajr" });
public object   guildmaster;

// Prototypes
public void     set_up_skills();

public void
create_school_room()
{
    set_short("Gelan Academy of Elemental Arts");
    set_long("This is the entrance to the Gelan Academy of Elemental "
        + "Arts. Youngsters who want to prepare for life beyond that "
        + "of a simple warrior often spend time here as an academic under "
        + "the wise guidance of Xania, the headmistress of this Academy. "
        + "The school looks like it is in remarkable condition. If you "
        + "are interested in enrolling, you can <asign on>. For more "
        + "information about joining, you should read <help academic "
        + "rules> and <help academic joining>. "
        + "Members of the Academy can <learn> and <improve> their "
        + "skills and can also <choose> a primary Element to focus "
        + "their studies upon.\n\n");
    
    try_item( ({ "entrance", "entryway" }),
                 "You stand in the entrance way between the main "
               + "entrance of the School of Gelan and the rest of "
               + "the Gelan Academy of Elemental Arts."
               + "\n");
    
    try_item( ({ "main entrance", "south" }),
                "The main entrance to the School of Gelan is to your "
              + "south.\n");
    
    try_item( ({ "north", "construction", "rest of the school",
                 "rest of school" }),
                 "To the north you hear loud sounds of construction. You "
               + "get glimpses occasionally of the construction workers, "
               + "but mostly you just see the beginnings of classrooms "
               + "and study areas being built.\n");
            
    add_exit(SCHOOL_ENTRANCE, "south");
    add_exit(ACADEMIC_SCHOOL + "boardroom", "north", "@@can_enter_school@@");
    
    // Set up the room as a training room
    create_skill_raise();
    set_up_skills();
    
    set_alarm(0.0, 0.0, reset_room);

    // Clone the board and bring it here
    clone_object(ACADEMIC_OBJS + "drop_box")->move(this_object());     
}

public void
reset_room()
{
    // Ensure that the guildmaster is always present
    if (!objectp(guildmaster))
    {
        setuid();
        seteuid(getuid());
        guildmaster = clone_object(ACADEMIC_GUILDMASTER);
        guildmaster->move(this_object());
        guildmaster->arm_me();        
    }
}

/*
 * Function:    can_enter_school
 * Desrciption: Used in the exit func check to see if the person can 
 *              go into the school.
 */
public mixed
can_enter_school()
{
    // Wizards are always allowed to enter.
    if (this_player()->query_wiz_level())
    {
        write("Being a wizard, you are allowed to enter the school.\n");
        return 0;
    }    
    
    if (!IS_MEMBER(this_player()))
    {
        write("Only members of the Academy of Elemental Arts can enter "
            + "the grounds of the Academy.\n");
        return 1;
    }    
}

public void
init()
{
    ::init(); 
    init_skill_raise(); 
    add_action("asign", "asign");
    add_action("choose", "choose"); 
    add_action("help", "help");   
}

public void
set_up_skills()
{
    sk_add_train(SS_ELEMENT_AIR, "cast air spells", 0, 0, 50);
    sk_add_train(SS_ELEMENT_FIRE, "cast fire spells", 0, 0, 50);
    sk_add_train(SS_ELEMENT_WATER, "cast water spells", 0, 0, 50);
    sk_add_train(SS_ELEMENT_EARTH, "cast earth spells", 0, 0, 50);
   
    sk_add_train(SS_FORM_ABJURATION, "cast abjuration spells", 0, 0, 40);
    sk_add_train(SS_FORM_TRANSMUTATION, "cast transmutation spells", 0, 0, 40);
    sk_add_train(SS_FORM_DIVINATION, "cast divination spells", 0, 0, 30);
    sk_add_train(SS_FORM_ENCHANTMENT, "cast enchantment spells", 0, 0, 30);

    sk_add_train(SS_LANGUAGE, "comprehend languages", 0, 0, 40);
    sk_add_train(SS_SPELLCRAFT, "understand spells", 0, 0, 50);
    sk_add_train(SS_HERBALISM, "identify herbs", 0, 0, 40);
    sk_add_train(SS_DEFENCE, "defend yourself", 0, 0, 45);
    sk_add_train(SS_APPR_MON, "appraise monsters", 0, 0, 40);
}

/*
 * Function name: sk_hook_allow_train
 * Description:   Function called when player tries to do the improve command
 *                Will determine if a player can train skills here.
 *                ( Default is:  yes )
 * Arguments:     object - The player trying to improve/learn
 *                string - The string from sk_improve
 *                verb   - improve or learn typically
 * Returns:       1 - yes (default) / 0 - no
 */
public varargs int
sk_hook_allow_train(object who, string str, string verb)
{
    setuid();
    seteuid(getuid());
    // Only allow those who are members to train here.
    if (!ACADEMIC_MANAGER->query_is_member(who))
    {
        who->catch_msg("Only those who are currently enrolled in the Academy "
            + "of Elemental Arts may train here.\n");
        return 0;
    }
        
    return 1;
}

/* 
 * Function:     sk_query_max
 * Description:  give the max we can teach of a skill
 * Arguments:    int snum   - the skill number to check
 *               int silent - don't tell anything to the player if true
 * Returns:      int - the maximum you can train the skill to 
 */ 
public varargs int
sk_query_max(int snum, int silent)
{
    object player = this_player(); 
 
    int max_skill = ::sk_query_max(snum, silent);

    setuid();
    seteuid(getuid());
    string prev_obj_file = MASTER_OB(previous_object());
    if (!objectp(player))
    {
        return 0;
    }
    
    if (prev_obj_file != "/d/Genesis/specials/guilds/guild_tester_soul"
        && !ACADEMIC_MANAGER->query_is_member(player))
    {
        return 0;
    }
        
    int player_max = max_skill;
    // Primary Skill can be trained to maximum. Non Primary Element
    // Skills can only be trained to 40.
    switch (snum)
    {
    case SS_ELEMENT_FIRE:
    case SS_ELEMENT_WATER:
    case SS_ELEMENT_AIR:
    case SS_ELEMENT_EARTH:
        if (ACADEMIC_MANAGER->query_primary_element_skillnum(player) != snum)
        {            
            return 40;
        }
        break;
    }
    
    return min(player_max, max_skill);
}

/*
 * Function:    leave_guild
 * Description: Function to remove someone from the guild.
 */
public int 
leave_guild(object player) 
{ 
    if (!IS_MEMBER(player))
    {        
        return 0;
    }
    
    // Remove the person's layman guild
    if (!player->remove_guild_lay()) 
    { 
        return 0; 
    } 

    // Clear guild stat, remove guild learn, and begin skill decay
    player->clear_guild_stat(SS_LAYMAN); 
    player->setup_skill_decay(); 
    player->set_guild_pref(SS_LAYMAN, 0); 

    // Reset the start location of the person leaving the guild
    if (player->query_default_start_location() == (ACADEMIC_SCHOOL + "startroom"))
    {
        player->set_default_start_location(player->query_def_start());
    }

    // Remove the command soul
    player->remove_cmdsoul(ACADEMIC_SOUL);
    player->update_hooks();
    
    // Remove the guild object
    object guild_object = present("academic_guild_object", player);
    if (objectp(guild_object))
    {
        guild_object->remove_object();
    }
    
    // Update the Guild Manager
    ACADEMIC_MANAGER->remove_member(player);
    
    return 1; 
}

/*
 * Function:    join_guild
 * Description: Function to add someone to the guild
 */
public int
join_guild(object player)
{
    // Add Guild Shadow
    object guild_shadow = clone_object(ACADEMIC_SHADOW);
    int shadow_result = guild_shadow->shadow_me(player, GUILD_TYPE, GUILD_STYLE, GUILD_NAME);
    switch (shadow_result)
    {
    case -4:
        player->catch_tell("You can't join the Academy while you are still "
            + "enrolled in other guilds. Leave your other guilds first, and "
            + "then return and try again.\n");
        return 0;
    
    case 1:
        // Everything is fine. Autoshadow should have been added as well.
        break;
    
    default:
        player->catch_tell("An error occurred in the fabric of space "
            + "and you are not able to join the Academy of Elemental "
            + "Arts. Please contact the guildmaster for help.\n");
        return 0;
    }

    // Clear the guild stat, in case it wasn't cleared, and add necessary
    // skill decay and guild tax.
    player->setup_skill_decay(); 
    player->clear_guild_stat(SS_LAYMAN); 
    player->set_guild_pref(SS_LAYMAN, GUILD_TAX); 

    // Add the member to the Guild Manager
    ACADEMIC_MANAGER->add_member(player);
    
    return 1;    
}

public void
remove_join_confirm_prop(object player)
{
    player->remove_prop(ACADEMIC_I_CONFIRM_JOIN);
}

public void
display_join_sequence()
{
    object player = this_player();
    write("You enroll yourself the Academy of Elemental Arts.\n");
    player->catch_msg(QCTNAME(guildmaster) + " scrutinizes you as you enroll.\n");
    tell_room(environment(player), QCTNAME(guildmaster) + " scrutinizes "
        + QTNAME(player) + " as " + player->query_pronoun() + " enrolls "
        + "in the Academy of Elemental Arts.\n", ({ player }));
    guildmaster->command("say Joining the Academy is no walk in the park.");
    guildmaster->command("say You will need to study hard and work diligently "
        + "to learn the Arts and perfect them.");
    player->catch_msg(QCTNAME(guildmaster) + " gives you a scrollcase.\n");
    tell_room(environment(player), QCTNAME(guildmaster) + " gives "
        + QTNAME(player) + " a scrollcase.\n", ({ player }));
    guildmaster->command("say Read over those scrolls carefully!");
    guildmaster->command("say Now that you have joined, let me teach "
        + "you your first spell, numastomo.");
    player->catch_msg(QCTNAME(guildmaster) + " mumbles a few words and you "
        + "sense her presence in your mind.\n");
    tell_room(environment(player), QCTNAME(guildmaster) + " mumbles a few "
        + "words.\n", ({ player }));
    write("You have learned the numastomo spell! You can read <help "
        + "academic numastomo> for more information.\n");
    write("You are now a member of the Academy of Elemental Arts!\n\n");
    write("For general help on the guild, read <help academic>.\n");
    tell_room(environment(player), QCTNAME(player) + " is now a member of "
        + "the Academy of Elemental Arts!\n", ({ player }));
}

public int
asign(string str)
{
    object player = this_player();

    if (IS_MEMBER(player))
    {
        notify_fail("You are already a member of the Academy "
            + "of Elemental Arts!\n");
        return 0;
    }
    
    if (!objectp(guildmaster) || environment(guildmaster) != this_object())
    {
        notify_fail("The guildmaster must be present for you to join!\n");
        return 0;
    }
    
    // Academics cannot be higher than veteran level
    if (player->query_average_stat() > ACADEMIC_MAX_AVG_STAT)
    {
        notify_fail("You are much too set in your ways to be "
            + "capable of being properly molded here at the Academy.\n");
        return 0;
    }

    if (strlen(player->query_guild_name_occ()))
    {
        notify_fail("You can't join the Academy while you are still "
            + "enrolled in other guilds. Leave your other guilds first, and "
            + "then return and try again.\n");
        return 0;
    }

/*        
    // ACADEMICS ARE NOW OPEN - February 1, 2010
    
    // For now, only beta testers (and wizards) can use this command.
    if (!player->query_wiz_level() 
        && !IN_ARRAY(player->query_real_name(), beta_testers))
    {
        notify_fail("Sorry, the Academy is currently only open to select "
            + "applicants. Please try again later.\n");
        return 0;
    }
*/

    // Academics who are banned from casting, or were kicked out cannot
    // join for the duration of their restrictions
    if (ACADEMIC_MANAGER->is_join_restricted(player)
        || ACADEMIC_MANAGER->is_casting_banned(player))
    {
        notify_fail("Your past behaviors prevent you from being able "
            + "to rejoin the Academy. You will need to wait for some "
            + "time before you will be allowed back into the guild.\n");
        return 0;
    }
    
    if (player->query_prop(ACADEMIC_I_CONFIRM_JOIN))
    {
        notify_fail("To confirm that you wish to join the Academy of "
            + "Elemental Arts, you need to <asign confirm>.\n");
    }
    else
    {
        notify_fail("Do you wish to <asign on> and join the Academy of "
            + "Elemental Arts?\n");
    }
    
    if (!strlen(str))
    {
        return 0;
    }
    
    
    switch (str)
    {
    case "on":
        if (player->query_prop(ACADEMIC_I_CONFIRM_JOIN))
        {
            return 0;
        }
        write("To confirm that you wish to join the Academy of Elemental "
            + "Arts, you have to <asign confirm> in the next minute.\n");
        player->add_prop(ACADEMIC_I_CONFIRM_JOIN, 1);
        set_alarm(60.0, 0.0, &remove_join_confirm_prop(player));
        return 1;
        
    case "confirm":
        if (!player->query_prop(ACADEMIC_I_CONFIRM_JOIN))
        {
            return 0;
        }
        player->remove_prop(ACADEMIC_I_CONFIRM_JOIN);
        if (join_guild(player))
        {
            display_join_sequence();
        }
        return 1;    
    }
    
    return 0;    
}

public int
choose(string str)
{
    object player = this_player();
    if (!IS_MEMBER(player))
    {
        return 0;
    }
    
    notify_fail("Which element do you wish to choose as your primary? "
        + "Fire, water, air, or earth?\n");

    if (!strlen(str))
    {
        return 0;
    }
    
    str = lower_case(str);
    string old_primary;
    switch (str)
    {
    case "fire":        
    case "water":
    case "air":
    case "earth":
        old_primary = ACADEMIC_MANAGER->query_primary_element(player);
        if (!strlen(old_primary))
        {
            write("You choose to focus your studies upon the element of "
                + capitalize(str) + ".\n");
            ACADEMIC_MANAGER->set_primary_element(player, str);        
        }
        else if (old_primary != str)
        {
            int old_skillnum = ACADEMIC_MANAGER->query_primary_element_skillnum(player);
            if (player->query_skill(old_skillnum) > 40)
            {
                player->set_skill(old_skillnum, 40);            
                write("You choose to refocus your studies upon the element of "
                    + capitalize(str) + " and lose the training that you "
                    + "previously had in " + old_primary + " spells.\n");
            }
            else
            {
                write("You choose to refocus your studies upon the element of "
                    + capitalize(str) + ".\n");
            }
            ACADEMIC_MANAGER->set_primary_element(player, str);
        }
        else
        {
            write("You have already chosen the element of " + capitalize(str)
                + " as your primary element.\n");
        }
        return 1;
        
    default:
        notify_fail("You can only choose between fire, water, air, or earth.\n");
    }

    return 0;    
}

public int
help(string str)
{
    // Access help files
    string content; 
    setuid(); 
    seteuid(getuid()); 

    if (!stringp(str) || !strlen(str))
    { 
        return 0; 
    }
    
    switch (str)
    {
    case "academic joining":
        if (!stringp(content = read_file(ACADEMIC_HELP + "joining")))
        {
            return 0;
        }
        break;
        
    case "academic leaving":
        if (!stringp(content = read_file(ACADEMIC_HELP + "leaving")))
        {
            return 0;
        }
        break;

    case "academic rules":
        if (!stringp(content = read_file(ACADEMIC_HELP + "rules")))
        {
            return 0;
        }
        break;
    
    default:
        return 0;
    }
    
    write("You look through the scrolls here and find one related "
        + "to the topic you're looking for.\n");
    this_player()->more(ACADEMIC_SOUL->generate_scroll_text(content));
    
    return 1;
}
