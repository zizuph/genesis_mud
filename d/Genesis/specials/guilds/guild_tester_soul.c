/* 
 *  Object to help test guilds
 *  
 *  This object keeps track of all the guild shadows and souls, and
 *  allows the user of it to add guilds to themselves or others to
 *  do testing.
 *
 *  Changed in March 2009 to a modular system of adding guilds. It is
 *  now much more flexible and allows for multiple shadows/souls per
 *  guild.
 *
 *  Created by Petros, October 2008
 *   
 */

#pragma no_clone
#pragma save_binary
#pragma strict_types

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <cmdparse.h>

inherit "/cmd/std/command_driver";
inherit "/d/Sparkle/area/city/lib/utility_functions";

#define     MODULES_DIR     ("/d/Genesis/specials/guilds/modules/")

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Public Interfaces Prototypes
public int          start_guild(string name, object player);
public int          stop_guild(string name, object player);
public int          start_guild_player_version(string name, object player);
public int          stop_guild_player_version(string name, object player);

// Utility Functions Prototypes
static string *     query_guild_shadows(string name);
static void         set_guild_shadows(string name, object player, int bPlayerVersion = 0);
static void         stop_guild_shadows(string name, object player);
static string *     query_guild_souls(string name);
static void         set_guild_souls(string name, object player);
static void         stop_guild_souls(string name, object player);
static mapping      query_guild_skills(string name);
static void         set_guild_skills(string name, object player);
static void         clear_all_skills(object player);
static string *     get_shadow_guild_info(object shadow_obj);
static void         print_guild_info(string name);
static string *     query_registered_guilds();
static void         copy_stats(object source, object target);
static void         copy_skills(object source, object target);
static void         set_player_stat(object player, int statid, int input_stat);
static void         set_max_skills(object player);


/*
 * Function name: get_soul_id
 * Description  : Returns the proper name in order to get a nice printout.
 *                On the other hand the name is simple so people can type
 *                it if they only want to know which commands this soul
 *                supports.
 * Returns      : string - the name.
 */
string
get_soul_id()
{
    return "guild_tester";
}

/*
 * Function name: query_tool_soul
 * Description  : Identify this as a tool soul.
 * Returns      : int 1 - always.
 */
nomask public int
query_tool_soul()
{
    return 1;
}

/*
 * Function name: query_cmdlist
 * Description  : This function returns mapping with the commands this soul
 *                supports and the functions to call. Please put new in
 *                alphabetical order.
 * Returns      : mapping - the commands and functions.
 */
mapping
query_cmdlist()
{       
    return ([
             "gtester"      : "cmd_gtester",
             "list"         : "cmd_list",
             "teststart"    : "cmd_teststart",
             "teststop"     : "cmd_teststop",
             "clearskills"  : "cmd_clearskills",
             "setstats"     : "cmd_setstats",
             "maxskills"    : "cmd_maxskills",
             "copyall"      : "cmd_copyall",
             ]);
}

public int
cmd_gtester(string arg)
{
    if (!arg)
    {
        notify_fail("Usage: " + query_verb() + " help\n");
        return 0;
    }
    
    if (arg == "help")
    {
        write("This guild tester allows one to register and test any guild "
           + "on any living. Here are some basic commands:\n\n"
           + "General Test Commands\n"
           + "---------------------\n"
           + "  gtester      help            - This help text.\n"
           + "  list guilds                  - Lists all the available guilds\n"
           + "  list         <guildname>     - Lists the info for that guild.\n"
           + "  teststart    <name> <target> - Loads the shadow and soul into the object\n"
           + "  teststop     <name> <target> - Removes the loaded shadow and souls\n"           
           + "  maxskills    <target>        - Maxes all skills for guilds target is in\n"
           + "  clearskills  <target>        - Removes all skills from the target\n"
           + "  setstats     <target> <num>  - Sets all stats to a certain value\n"
           + "  copyall      <player> <tgt>  - Sets the target to all the same stats and skills\n"
           + "\n");
        return 1;
    }
    
    return 0;
}

public int
cmd_list(string arg)
{   
    string * guilds;
    
    if (!arg)
    {
        return 0;
    }
    
    arg = lower_case(arg);
    guilds = sort_array(query_registered_guilds());
    if (arg == "guilds")
    {
        if (!sizeof(guilds))
        {
            write("There are no guilds available for testing.\n");
            return 1;
        }        
        write("These are the guilds that are available for testing:\n\n");
        for (int i = 1; i <= sizeof(guilds); ++i)
        {
            write(sprintf("%:3d. %s\n", i, guilds[i-1]));
        }
        write("\n");
        return 1;
    }
    
    if (!IN_ARRAY(arg, guilds))
    {
        notify_fail("The guild '" + arg + "' does not exist.\n");
        return 0;
    }
    
    print_guild_info(arg);
        
    return 1;
}

public int
cmd_teststart(string arg)
{   
    string guild, person;
    object target;
    string * guilds;
    
    if (!arg)
    {
        notify_fail("Usage: " + query_verb() + " <guildname> <person>\n");
        return 0;
    }
    
    arg = lower_case(arg);
    guilds = query_registered_guilds();
    
    if (IN_ARRAY(arg, guilds))
    {
        // No target specified, just the guild
        person = this_player()->query_real_name();
        guild = arg;
    }
    else if (sscanf(arg, "%s %s", guild, person) != 2)
    {
        notify_fail("Usage: " + query_verb() + " <guildname> <person>\n");
        return 0;
    }
    
    if (!IN_ARRAY(guild, guilds))
    {
        notify_fail("There is no guild available called '" + guild
                  + " for you to test.\n");
        return 0;
    }
    
    if (person == this_player()->query_real_name())
    {
        target = this_player();
    }
    else
    {
        target = PARSE_COMMAND_ONE(person, 0, "[the] %i");
        if (!objectp(target) || !IS_LIVING_OBJECT(target))
        {
            notify_fail(person + " is not a valid living to test guilds on.\n");
            return 0;
        }
    }

    write("Use the tag 'guild_tester_soul' to see the debug messages.\n");
    start_guild(guild, target);
    
    return 1;
}

public int
cmd_teststop(string arg)
{   
    string guild, person;
    object target;
    string * guilds;
    
    if (!arg)
    {
        notify_fail("Usage: " + query_verb() + " <guildname> <person>\n");
        return 0;
    }
    
    guilds = query_registered_guilds();
    arg = lower_case(arg);
    if (IN_ARRAY(arg, guilds))
    {
        // No target specified, just the guild
        person = this_player()->query_real_name();
        guild = arg;
    }
    else if (sscanf(arg, "%s %s", guild, person) != 2)
    {
        notify_fail("Usage: " + query_verb() + " <guildname> <person>\n");
        return 0;
    }
    
    if (!IN_ARRAY(guild, guilds))
    {
        notify_fail("There is no guild available called '" + guild
                  + " for you to stop.\n");
        return 0;
    }
    
    if (person == this_player()->query_real_name())
    {
        target = this_player();
    }
    else
    {
        target = PARSE_COMMAND_ONE(person, 0, "[the] %i");
        if (!objectp(target) || !IS_LIVING_OBJECT(target))
        {
            notify_fail(person + " is not a valid living to stop testing guilds on.\n");
            return 0;
        }
    }
    
    write("Use the tag 'guild_tester_soul' to see the debug messages.\n");
    stop_guild(guild, target);
    
    return 1;
}

public int
cmd_clearskills(string arg)
{
    string person;
    object target;
    
    if (!arg)
    {
        notify_fail("Usage: " + query_verb() + " <person>\n");
        return 0;
    }
    
    arg = lower_case(arg);
    if (sscanf(arg, "%s", person) != 1)
    {
        notify_fail("Usage: " + query_verb() + " <person>\n");
        return 0;
    }
    
    if (person == this_player()->query_real_name())
    {
        target = this_player();
    }
    else
    {
        target = PARSE_COMMAND_ONE(person, 0, "[the] %i");
        if (!objectp(target) || !IS_LIVING_OBJECT(target))
        {
            notify_fail(person + " is not a valid living to clear skills.\n");
            return 0;
        }
    }
    
    clear_all_skills(target);
    write("All skills have been cleared.\n");
    return 1;
}

public int
cmd_maxskills(string arg)
{
    string person;
    object target;
    
    if (!arg)
    {
        notify_fail("Usage: " + query_verb() + " <person>\n");
        return 0;
    }
    
    arg = lower_case(arg);
    if (sscanf(arg, "%s", person) != 1)
    {
        notify_fail("Usage: " + query_verb() + " <person>\n");
        return 0;
    }
    
    if (person == this_player()->query_real_name())
    {
        target = this_player();
    }
    else
    {
        target = PARSE_COMMAND_ONE(person, 0, "[the] %i");
        if (!objectp(target) || !IS_LIVING_OBJECT(target))
        {
            notify_fail(person + " is not a valid living to max skills.\n");
            return 0;
        }
    }
    
    set_max_skills(target);
    write("All skills have been maxed.\n");
    return 1;
}

public int
cmd_setstats(string arg)
{
    int level;
    string person;
    object target;
    
    if (!arg)
    {
        notify_fail("Usage: " + query_verb() + " <person> <level>\n");
        return 0;
    }
    
    arg = lower_case(arg);
    if (sscanf(arg, "%s %d", person, level) != 2)
    {
        notify_fail("Usage: " + query_verb() + " <person> <level>\n");
        return 0;
    }
    
    if (person == this_player()->query_real_name())
    {
        target = this_player();
    }
    else
    {
        target = PARSE_COMMAND_ONE(person, 0, "[the] %i");
        if (!objectp(target) || !IS_LIVING_OBJECT(target))
        {
            notify_fail(person + " is not a valid living to clear skills.\n");
            return 0;
        }
    }
    
    int * stats = ({ SS_STR, SS_DEX, SS_CON, SS_INT, SS_WIS, SS_DIS,
                     SS_OCCUP, SS_LAYMAN, SS_RACE, SS_CRAFT });
    
    foreach (int statid : stats)
    {
        set_player_stat(target, statid, level);
    }
    
    return 1;
}

public int
cmd_copyall(string arg)
{
    object source, target;
    string person, target_name;
    if (!arg)
    {
        notify_fail("Usage: " + query_verb() + " <player> <target>\n");
        return 0;
    }
    
    arg = lower_case(arg);
    if (sscanf(arg, "%s %s", person, target_name) != 2)
    {
        notify_fail("Usage: " + query_verb() + " <player> <target>\n");
        return 0;
    }
    
    if (target_name == this_player()->query_real_name())
    {
        target = this_player();
    }
    else
    {
        target = PARSE_COMMAND_ONE(target_name, 0, "[the] %i");
        if (!objectp(target) || !IS_LIVING_OBJECT(target)
            || (IS_PLAYER_OBJECT(target) && !wildmatch("*jr", target->query_real_name())))
        {
            notify_fail(target_name + " is not a valid living to copy to.\n");
            return 0;
        }
    }
    
    object loaded_source;
    if (!objectp(source = find_player(person))
        && !objectp(loaded_source = SECURITY->finger_player(person)))
    {
        notify_fail("Could not find the player " + capitalize(person) 
            + " to copy.\n");
        return 0;
    }
    
    if (objectp(loaded_source))
    {
        source = loaded_source;        
    }
    clear_all_skills(target);
    copy_stats(source, target);
    copy_skills(source, target);
    write("All skills and stats have been copied.\n");
    if (objectp(loaded_source))
    {
        loaded_source->remove_object();
    }
    return 1;
}

public int
start_guild(string name, object player)
{
    string * guilds;
    
    guilds = query_registered_guilds();
    if (!IN_ARRAY(name, guilds))
    {
        player->catch_tell("There is no such guild.\n");
        return 0;
    }
    
    set_guild_shadows(name, player);
    set_guild_souls(name, player);
    set_guild_skills(name, player);
    
    call_other(MODULES_DIR + name, "start_guild_" + name, player);
    
    return 1;
}

/*
 * Function:    start_guild_player_version
 * Description: This is a version of the start_guild function
 *              that does not change the autoshadow and does not
 *              set the skills. It merely adds the appropriate
 *              shadows and souls temporarily.
 */
public int
start_guild_player_version(string name, object player)
{
    string * guilds;
    
    guilds = query_registered_guilds();
    if (!IN_ARRAY(name, guilds))
    {
        return 0;
    }
    
    set_guild_shadows(name, player, 1);
    set_guild_souls(name, player);
    
    return 1;
}

public int
stop_guild(string name, object player)
{
    string * guilds;
    
    guilds = query_registered_guilds();
    if (!IN_ARRAY(name, guilds))
    {
        player->catch_tell("There is no such guild.\n");
        return 0;
    }
    
    stop_guild_shadows(name, player);
    stop_guild_souls(name, player);
    
    call_other(MODULES_DIR + name, "stop_guild_" + name, player);
    
    return 1;
}

/*
 * Function:    stop_guild_player_version
 * Description: This is a player version of the stop_guild function
 *              that removes the shadow and soul from the player.
 *              It does not write to the player, and does not call
 *              the stop functions.
 */
public int
stop_guild_player_version(string name, object player)
{
    string * guilds;
    
    guilds = query_registered_guilds();
    if (!IN_ARRAY(name, guilds))
    {
        return 0;
    }
    
    stop_guild_shadows(name, player);
    stop_guild_souls(name, player);

    call_other(MODULES_DIR + name, "stop_guild_" + name, player);
    
    return 1;
}

// Utility Helper Functions Below

static string *
query_guild_shadows(string name)
{
    return call_other(MODULES_DIR + name, "query_guild_shadows_" + name);
}

static void
set_guild_shadows(string name, object player, int bPlayerVersion = 0)
{
    string * shadows, * parents;
    object shadow_obj;
    string type;
    
    shadows = query_guild_shadows(name);
    if (!pointerp(shadows))
    {
        return;
    }
    
    foreach (string shadowfile : shadows)
    {
        shadow_obj = clone_object(shadowfile);
        if (!objectp(shadow_obj))
        {
            continue;
        }
        string * info = get_shadow_guild_info(shadow_obj);
        if (!pointerp(info))
        {
            continue;
        }
        if (!player->add_autoshadow(shadowfile + ":"))
        {
            if (bPlayerVersion)
            {
                player->catch_tell("Shadow '" + shadowfile + "' could not be "
                    + "added to autoshadow.\n");

                // Don't continue to try to shadow the player if the autoshadow doesn't
                // work in the first place.
                continue;
            }
        }
        send_debug_message("guild_tester_soul", "Adding shadow " + shadowfile + " to " + player->query_real_name() + ".");
        send_debug_message("guild_tester_soul", "shadow_obj->shadow_me(player, \"" + info[0] + "\", \"" + info[1] + "\", \"" + info[2] + "\", \"\");");
        int result = shadow_obj->shadow_me(player, info[0], info[1], info[2], ""); // player, type, style, name, init_arg
        if (result == 1)
        {
            send_debug_message("guild_tester_soul", "Shadow '" + shadowfile + "' added successfully.");
        }
        else
        {
            send_debug_message("guild_tester_soul", "Shadow '" + shadowfile + "' failed to be added with an error code of " + result);
        }
    }
}

static void
stop_guild_shadows(string name, object player)
{
    string * shadows, * parents;
    object shadow_obj;
    string type;
    
    shadows = query_guild_shadows(name);
    if (!pointerp(shadows))
    {
        return;
    }
    
    foreach (string shadowfile : shadows)
    {
        shadow_obj = find_object(shadowfile);
        if (!objectp(shadow_obj))
        {
            continue;
        }
        string * info = get_shadow_guild_info(shadow_obj);
        if (!pointerp(info))
        {
            continue;
        }
        switch (info[0])
        {
        case "race":
            send_debug_message("guild_tester_soul", "Removing racial guild shadow '"
                               + shadowfile + "' for '" + name + "' from "
                               + player->query_real_name());
            player->remove_guild_race();
            break;

        case "occupational":
            send_debug_message("guild_tester_soul", "Removing occupational guild shadow '"
                               + shadowfile + "' for '" + name + "' from "
                               + player->query_real_name());            
            player->remove_guild_occ();
            break;

        case "layman":
            send_debug_message("guild_tester_soul", "Removing layman guild shadow '"
                               + shadowfile + "' for '" + name + "' from "
                               + player->query_real_name());            
            player->remove_guild_lay();
            break;

        case "craft":
            send_debug_message("guild_tester_soul", "Removing craft guild shadow '"
                               + shadowfile + "' for '" + name + "' from "
                               + player->query_real_name());            
            player->remove_guild_craft();
            break;
        }
    }
}

static string *
query_guild_souls(string name)
{
    return call_other(MODULES_DIR + name, "query_guild_souls_" + name);    
}

static void
set_guild_souls(string name, object player)
{
    string * souls;
    
    souls = query_guild_souls(name);
    if (!pointerp(souls))
    {
        return;
    }
    
    foreach (string soulfile : souls)
    {
        player->add_cmdsoul(soulfile);
    }
    player->update_hooks();
}

static void
stop_guild_souls(string name, object player)
{
    string * souls;
    
    souls = query_guild_souls(name);
    if (!pointerp(souls))
    {
        return;
    }
    
    foreach (string soulfile : souls)
    {
        player->remove_cmdsoul(soulfile);
    }
    player->update_hooks();
}

public mapping
query_guild_skills(string name)
{
    mapping skills;
    string * shadows;
    
    skills = call_other(MODULES_DIR + name, "query_guild_skills_" + name) + ([]);
    
    shadows = query_guild_shadows(name);
    foreach (string shadowfile : shadows)
    {
        object shadowobj;
        if (!objectp(shadowobj = find_object(shadowfile)))
        {
            continue;
        }
        
        mixed * obs;
        mixed otmp;
        
        obs = ({});
        otmp = shadowobj->query_guild_trainer_occ();
        obs += pointerp(otmp) ? otmp : ({ otmp });
        otmp = shadowobj->query_guild_trainer_race();
        obs += pointerp(otmp) ? otmp : ({ otmp });
        otmp = shadowobj->query_guild_trainer_lay();
        obs += pointerp(otmp) ? otmp : ({ otmp });
        otmp = shadowobj->query_guild_trainer_craft();
        obs += pointerp(otmp) ? otmp : ({ otmp });
        obs -= ({ 0 });
        
        foreach (mixed trainer : obs)
        {
            object trainer_obj = trainer;
            if (stringp(trainer) && strlen(trainer))
            {
                trainer_obj = safely_load_master_file(trainer);
            }
            if (!objectp(trainer_obj))
            {
                continue;
            }
            foreach (int snum : trainer->sk_query_train())
            {
                if (!IN_ARRAY(snum, m_indices(skills)))
                {
                    skills[snum] = trainer->sk_query_max(snum);
                }
                else
                {
                    skills[snum] = min(100, 
                        max(skills[snum], trainer->sk_query_max(snum)));
                }
            }
        }
    }
        
    return skills;
}

public void
set_guild_skills(string name, object player)
{
    mapping skills;
    
    skills = query_guild_skills(name);
    if (!mappingp(skills))
    {
        return;
    }
    
    foreach (int snum : m_indices(skills))
    {
        player->set_skill(snum, min(max(skills[snum], 
                          player->query_base_skill(snum)), 100));
    }
}

static string *
get_shadow_guild_info(object shadow_obj)
{
    string * parents;
    
    parents = inherit_list(shadow_obj);
    if (IN_ARRAY("/std/guild/guild_occ_sh.c", parents))
    {
        return ({ "occupational", shadow_obj->query_guild_style_occ(), shadow_obj->query_guild_name_occ() });
    }
    else if (IN_ARRAY("/std/guild/guild_lay_sh.c", parents))
    {
        return ({ "layman", shadow_obj->query_guild_style_lay(), shadow_obj->query_guild_name_lay() });
    }
    else if (IN_ARRAY("/std/guild/guild_race_sh.c", parents))
    {
        return ({ "race", shadow_obj->query_guild_style_race(), shadow_obj->query_guild_name_race() });
    }
    else if (IN_ARRAY("/std/guild/guild_craft_sh.c", parents))
    {
        return ({ "craft", shadow_obj->query_guild_style_craft(), shadow_obj->query_guild_name_craft() });
    }
    
    return 0;
}

static void
clear_all_skills(object player)
{
    foreach (int snum : player->query_all_skill_types())
    {
        player->remove_skill(snum);
    }
}

static void
set_max_skills(object player)
{
    mixed * obs;
    mixed otmp;
    
    /* Get the list of trainer objects */
    obs = ({});
    otmp = player->query_guild_trainer_occ();
    obs += pointerp(otmp) ? otmp : ({ otmp });
    otmp = player->query_guild_trainer_race();
    obs += pointerp(otmp) ? otmp : ({ otmp });
    otmp = player->query_guild_trainer_lay();
    obs += pointerp(otmp) ? otmp : ({ otmp });
    otmp = player->query_guild_trainer_craft();
    obs += pointerp(otmp) ? otmp : ({ otmp });
    obs -= ({ 0 });
    
    foreach (mixed trainer : obs)
    {
        foreach (int snum : trainer->sk_query_train())
        {
            player->set_skill(snum, min(100, 
                max(player->query_base_skill(snum), trainer->sk_query_max(snum))));
        }
    }
}

static void
copy_skills(object source, object target)
{
    clear_all_skills(target);
    foreach (int snum : source->query_all_skill_types())
    {
        target->set_skill(snum, source->query_base_skill(snum));
    }    
}

static void
set_player_stat(object player, int statid, int input_stat)
{
    int experience;
    
    switch (statid)
    {
    case SS_RACE:
    case SS_OCCUP:
    case SS_LAYMAN:
    case SS_CRAFT:        
        if (input_stat > 125)
        {
            // Strange bug in stat_to_exp where it is off by one after
            // 125.
            ++input_stat;
        }    
        experience = player->stat_to_exp(input_stat);
        player->set_guild_stat(statid, experience);
        break;
        
    default:
        player->set_base_stat(statid, input_stat);
    }
}

static void
copy_stats(object source, object target)
{
    int * stats = ({ SS_STR, SS_DEX, SS_CON, SS_INT, SS_WIS, SS_DIS,
                     SS_OCCUP, SS_LAYMAN, SS_RACE, SS_CRAFT });
    
    foreach (int statid : stats)
    {
        set_player_stat(target, statid, source->query_base_stat(statid));
    }
}

static string *
query_registered_guilds()
{
    string * modules = ({ });    
    if (!getuid())
    {
        setuid();
        seteuid(getuid());
    }
    send_debug_message("guild_tester", "Effective UID is " + getuid());    
    foreach (string file : get_dir(MODULES_DIR))
    {
        if (!wildmatch("*.c", file))
        {
            continue;
        }
        modules += ({ file[..-3] });           
    }
    
    return modules;
}

static void
print_guild_info(string name)
{
    string * shadows, * souls;
    mapping skills;
    object shadowobj, soul;
    object * shadowobjs;
    
    // Now list the specific information for the guild
    write("Information about the '" + capitalize(name) + "' Guild\n\n");
    shadows = query_guild_shadows(name);
    souls = query_guild_souls(name);
    skills = query_guild_skills(name);
    shadowobjs = ({ });
    
    if (pointerp(shadows))
    {
        foreach (string shadowfile : shadows)
        {
            if (!objectp(shadowobj = find_object(shadowfile)))
            {
                if (LOAD_ERR(shadowfile))
                {
                    continue;
                }
                shadowobj = find_object(shadowfile);
            }
            string * info = get_shadow_guild_info(shadowobj);
            if (!pointerp(info))
            {
                continue;
            }
            shadowobjs += ({ shadowobj });
            write(capitalize(info[0]) + " Guild Shadow: " + shadowfile + "\n");
        }
    }
    else
    {
         write("Guild Shadows: none\n");
    }   

    if (pointerp(souls))
    {
        foreach (string soulfile : souls)
        {
            write("Guild Command Soul: " + soulfile + "\n");
            if (!objectp(soul = find_object(soulfile)))
            {
                if (LOAD_ERR(soulfile))
                {
                    continue;
                }
                soul = find_object(soulfile);
            }
            string cmdlist = "";
            write("\nAvailable Guild Commands:\n");
            write("-------------------------\n");
            foreach (string cmd : sort_array(m_indices(soul->query_cmdlist())))
            {
                cmdlist += cmd + "\n";
            }
            write(sprintf("%80.4#-s", cmdlist));
            write("\n\n");
        }
    }
    else
    {
        write("Guild Command Soul: none\n");
    }   
    
    write("Skills Set by this Guild:\n");    
    mapping skill_desc = SS_SKILL_DESC;
    foreach (int snum : sort_array(m_indices(skills)))
    {
        if (IN_ARRAY(snum, m_indices(skill_desc)))
        {
            write(sprintf("    %-:35'.'s%d\n", skill_desc[snum][0], skills[snum]));
        }
        else
        {
            // Look for the skill name in the shadow objects
            shadowobjs = filter(shadowobjs, &not() @ &operator(==)("") 
                                 @ &->query_guild_skill_name(snum));
            if (sizeof(shadowobjs))
            {
                write(sprintf("    %-:35'.'s%d\n",
                    strlen(shadowobjs[0]->query_guild_skill_name(snum)) ? shadowobjs[0]->query_guild_skill_name(snum) : "special", skills[snum]));
            }
            else
            {
                write(sprintf("    %-:35'.'s%d\n",
                    "special", skills[snum]));
            }
        }
    }
}
