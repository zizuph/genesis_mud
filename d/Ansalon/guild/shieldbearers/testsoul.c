/* File name  : dwarf_lay_sould.c
 * Description: Sould for the Shieldbearers layman guild.
 *
 * Blizzard, 15.08.2003
 *
 * Modified from old Neidar shield slam special. (by Arman)
 */
  
#pragma strict_types

#include "/d/Krynn/common/defs.h"

/* Inherit this for guild souls */
inherit "/cmd/std/command_driver";

#include "test.h"

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <options.h>

#include "emotes.c"

#define  AXEWIELDR    query_weapon(W_RIGHT)->query_wt() == W_AXE
#define  AXEWIELDL    query_weapon(W_LEFT)->query_wt() == W_AXE
#define  AXEWIELDB    query_weapon(W_BOTH)->query_wt() == W_AXE

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

mapping
query_cmdlist()
{
    return ([
       /* Command name  : Function name */

        "shieldslam"    : "shieldslam_special",
        "slam"          : "shieldslam_special",
        "shlist"        : "members_list",
        "shieldbearers" : "members_list",

        ]) + emote_cmdlist();
}

public int
shieldslam_special(string str)
{
    object  ob, *obj, *objlist;
    string  how, shield_short;

    if(strlen(str))
    {
	if( !sizeof(obj = parse_this(str, "[the] %l")) )
	{
	    notify_fail("Choose a more appropriate target.\n");
	    return 0;
	}

	ob = obj[0];
    }
    else if (!(ob = this_player()->query_attack()))
    {
	notify_fail("But you are not in battle with anyone!\n");
	return 0;
    }

    if(member_array(A_SHIELD, TP->query_armour(-1)->query_at()) < 0)
    {
	notify_fail("You cannot slam if you are not wearing a shield!\n");
	return 0;
    }

    if ( !(this_player()->query_skill(SHIELDSLAM_SPECIAL)) )
    {
	write("First you should learn how to slam your enemies.\n");
	return 1;
    }

    if ( TP->query_prepare_slam() )
    {
	write("You are preparing a shield slam already!\n");
	return 1;
    }

    if ( TP->query_prepare_chop() )
    {
        if ( TP->AXEWIELDR || TP->AXEWIELDL || TP->AXEWIELDB )
            write("You are too focused on preparing chop, and " +
                "can't do that right now.\n");
        else
            write("You are too focused on preparing crush, and " +
                "can't do that right now.\n");
            
        return 1;
    }
    
    if( TP->query_slam() )
    {
	write("Patience! You are not ready to slam your opponent yet!\n");
	return 1;
    }

    if( stringp(how = TP->can_attack_with_slam(ob, "slam")) )
    {
	write(how);
	return 1;
    }

    if(TP->query_armour(W_RIGHT)->query_at() == A_SHIELD)
	shield_short = TP->query_armour(W_RIGHT)->short();
    else if(TP->query_armour(W_LEFT)->query_at() == A_SHIELD)
	shield_short = TP->query_armour(W_LEFT)->short();

    TP->catch_msg("You prepare to slam " + QTNAME(ob) + " with your " +
         shield_short + ".\n");
    
    if ( TP->query_prop(LIVE_O_LAST_KILL) != ob )
        TP->add_prop(LIVE_O_LAST_KILL, ob);
        
    this_player()->prepare_slam(ob);

    return 1;
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

    TP->more("The following Shidlebearers are currently awaken:\n\n" +
        list + "\n");
    
    return 1;
}

