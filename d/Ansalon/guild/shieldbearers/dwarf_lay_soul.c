/* File name  : dwarf_lay_sould.c
 * Description: Sould for the Shieldbearers layman guild.
 *
 * Blizzard, 15.08.2003
 *
 * Modified from old Neidar shield slam special. (by Arman)
 *
 * Special check for chop/crush disable by Navarre
 * April 15th 2007
*/
  
#pragma strict_types

#include "/d/Krynn/common/defs.h"

/* Inherit this for guild souls */
inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";

#include "guild.h"

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <options.h>

#include "emotes.c"

// Defines
#define OPT_SHORT_SLAM  "short_slam"
#define OPT_POWER_STUN  "power_stun"
#define OPTIONS_MGR     (GUILD_DIR+"options_manager")

static   string   *Titles = TITLES;
 
public string
get_soul_id()
{
    return GUILD_NAME + " soul";
}

public int
query_cmd_soul()
{
    return 1;
}

public mapping
query_ability_map()
{
    return ([
    "slam" : "/d/Ansalon/guild/shieldbearers/slam_attack",
    "shieldslam" : "/d/Ansalon/guild/shieldbearers/slam_attack",
    ]);
}

mapping
query_cmdlist()
{
    return ([
       /* Command name  : Function name */

        "shieldslam"    : "do_ability",
        "slam"          : "do_ability",
        "shlist"        : "members_list",
        "shieldbearers" : "members_list",
        "sboptions"     : "show_options",

        ]) + emote_cmdlist();
}

public string
print_title(object ob)
{
    string str;
    string guild_level = Titles[MIN(15, ob->query_stat(SS_LAYMAN) / 10)];
    
    str = ob->query_name() + " the " + (ob->query_guild_member(NEIDAR_CLAN) ?
        guild_level : ob->query_guild_title_lay());
    str  = break_string(str, 75, 10)[10..];

    return str;
}

public string
print_full_title(object ob)
{
    string str;
    int    opt_width = ob->query_option(1);
    
    if ( opt_width < 6 )
        opt_width = 80;
        
    str = ob->query_presentation();
    str = break_string(str, opt_width - 5, 10)[10..];
    
    return str;
}

public int
members_list(string str)
{
    mixed list;
    
    if ( strlen(str) && (str != "list") && (str != "full") )
    {
        notify_fail("You want to know the Shieldbearers list?\n");
        return 0;
    }
    
    list = filter(users(), &operator(==)(GUILD_NAME) @ 
        &->query_guild_name_lay());
    list = filter(list, not @ &->query_wiz_level());

    if ( strlen(str) && str == "full" )
        list = map(list, print_full_title);
    else
        list = map(list, print_title);
     
    list = sort_array(list);
    list = implode(map(list, &operator(+)(" * ",)), "\n");

    TP->more("The following Shieldbearers are currently awaken:\n\n" +
        list + "\n");
    
    return 1;
}

public int
show_options(string str)
{   
    object player;
    string * arguments;
     
    setuid();
    seteuid(getuid());
    
    player = this_player();
    if (!str)
    {
        write("Shieldbearer Options\n");
        write("====================\n");
        write("Slam Distance [slam]: ");
        switch (OPTIONS_MGR->query_option(OPT_SHORT_SLAM, player->query_real_name()))
        {
        case 1:
            write("Short\n");
            break;
        case 0:
        default:
            write("Long\n");
            break;
        }
        write("Power Stun   [power]: ");
        switch (OPTIONS_MGR->query_option(OPT_POWER_STUN, player->query_real_name()))
        {
        case 1:
            write("On\n");
            break;
        case 0:
        default:
            write("Off\n");
            break;
        }
        write("\n");
        write("To set your options, use \"sboptions <option> <value>\"\n");
        write("\n");
        return 1;
    }
    else if (str == "slam")
    {
        switch (OPTIONS_MGR->query_option(OPT_SHORT_SLAM, player->query_real_name()))
        {
        case 1:
            write("You are currently focused on taking shorter strides "
                + "to slam your opponents.\n");
            break;
        case 0:
        default:
            write("You are currently focused on taking longer strides "
                + "to slam your opponents.\n");
            break;
        }
        write("\n");
        return 1;
    }
    else if (str == "power")
    {
        switch (OPTIONS_MGR->query_option(OPT_POWER_STUN, player->query_real_name()))
        {
        case 1:
            write("You are using your shield to stun your foes "
                + "powerfully.\n");
            break;
        case 0:
        default:
            write("You are using your shield to stun your foes in a "
                + "normal fashion.\n");
            break;
        }
        write("\n");
        return 1;
    }
            
    arguments = explode(str, " ");
    if (sizeof(arguments) == 2
        && lower_case(arguments[0]) == "slam")
    {
        switch (lower_case(arguments[1]))
        {
        case "short":
            OPTIONS_MGR->set_option(OPT_SHORT_SLAM, player->query_real_name(), 1);
            write("You will now take short strides in slamming your opponents.\n");
            break;
        
        case "long":
            OPTIONS_MGR->set_option(OPT_SHORT_SLAM, player->query_real_name(), 0);
            write("You will now take long strides in slamming your opponents.\n");
            break;
        }
        return 1;
    }           
    else if (sizeof(arguments) == 2
        && lower_case(arguments[0]) == "power")
    {
        switch (lower_case(arguments[1]))
        {
        case "on":
            OPTIONS_MGR->set_option(OPT_POWER_STUN, player->query_real_name(), 1);
            write("You will now use your shield to stun your foes "
                + "powerfully.\n");
            break;
        
        case "off":
            OPTIONS_MGR->set_option(OPT_POWER_STUN, player->query_real_name(), 0);
            write("You will now use your shield normally when stunning "
                + "your opponents.\n");
            break;
        }
        return 1;
    }       

    notify_fail(str + " is not a recognized option for Shieldbearers.\n");
    return 0;
}
