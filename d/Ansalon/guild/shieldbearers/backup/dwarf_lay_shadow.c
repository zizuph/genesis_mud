
/* File name  : dwarf_lay_shadow.c
 * Description: Shieldbearers layman guild shadow.
 *
 * Blizzard, 10.08.2003.
 *
 * Update: 6.12.2003 - added updating the guild start location while leaving.
 *           Blizzard.
 */
  
#pragma  strict_types

inherit  "/std/guild/guild_lay_sh";

#include "guild.h"

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "slam_special.c"

#define  MAX_GUILD_LEVEL  15
#define  SW               shadow_who

static string  *Titles = TITLES;
public void    remove_lay_member();

public int
query_guild_tax_lay()
{
    return GUILD_TAX;
}

public string
query_guild_name_lay()
{
    return GUILD_NAME;
}

public string
query_guild_style_lay()
{
    return GUILD_STYLE;
}

public int
query_guild_not_allow_join_lay(object player, string type, string style,
                               string name)
{
    if ( ::query_guild_not_allow_join_lay(player, type, style, name) )
        return 1;

    return 0;
}

/* Function name: acceptable_member
 * Description:   test to see if the player is an acceptable member of this
 *                guild.
 * Arguments:     object who - the player to test
 * Returns:       0 or a string message saying why the player isn't acceptable
 */
public nomask mixed
acceptable_member(object who)
{
    if ( !objectp(who) )
        return 0;
        
 /* Only dwarves, gnomes and kenders are acceptable */
    if ((who->query_race_name() != "dwarf") && 
        (who->query_race() != "hobbit") &&
        (who->query_race_name() != "gnome") && !who->query_ghost() )
        return "Only dwarves, gnomes, kenders and hobbits may become " +
            "Shieldbearers!\n";

 /* Those who are not Neidars, must be considered their friends before 
    they are allowed to join */
    if ( !who->query_guild_member(NEIDAR_CLAN) &&
        !who->test_bit("Ansalon", 3, 13) )
        return "You are not considered a friend of the Neidar Clan. " +
            "You can not be a Shieldbearer!\n";
    
 /* Mountain dwarves are not allowed to join. */
    if ( (who->query_region_title() == "kayolin mountain dwarf" ) ||
        ( who->query_region_title() == "thorbardin mountain dwarf" ) ||
        ( who->query_region_title() == "zhakar mountain dwarf" ) )
        return "Our abilities will not be taught to Mountain dwarves!\n"; 
 
    return 0;
}

/* Function name: check_valid_members
 * Description  : We check if player is allowed to be a member of the guild.
 *                We are doing it with delay to make sure all shadows are
 *                loaded.
 */
public nomask void
check_valid_members(object who)
{
    string why;
    
    if ( !objectp(who) )
        return;
    
    if ( stringp(why = acceptable_member(who)) )
    {
        who->catch_msg(why);
        set_alarm(1.0, 0.0, &remove_lay_member() );
    
        setuid();
        seteuid(getuid());
        
        write_file(LEFT, extract(ctime(time()), 4, 15) + " " +
            TP->query_real_name() + " has lost his " +
            "Shieldbearer's insignia!\n");
            
        write_file(MEMBERS, TP->query_name() + " left " +
            extract(ctime(time()), 4, 15) +
            ", StatAvg: " + TP->query_average_stat() +
            ", Race: " + TP->query_race() +
            ", Align: " + TP->query_alignment() + "\n");
                                                                        
        return;
    }
    
    return;
}

/* Function name: query_guild_keep_player
 * Description  : Test if we want to keep the player in the guild
 * Arguments    : ob - the player
 * Returns      : 1 if keeping,
 *                0 if not
 */
public int
query_guild_keep_player(object ob)
{
    if (ob->query_wiz_level())
        return 1;
    
    /* Let's check if player is allowed to be a member of the guild. We do
       it with a delay to make sure all shadows have loaded (like kender,
       Mountain dwarves..*/    
    set_alarm(10.0, 0.0, &check_valid_members(ob));
    
    return 1;
}

/* Function name: query_guild_level_lay
 * Description  : The member's level within the guild.
 * Returns      : int - level
 */
public int
query_guild_level_lay()
{
   return MIN(MAX_GUILD_LEVEL, query_shadow_who()->query_stat(SS_LAYMAN) / 10);
}

/* Function name: query_guild_title_lay
 * Description  : Member's guild title
 * Resturns     : string - title
 */
public string
query_guild_title_lay()
{
    if ( query_shadow_who()->query_guild_member(NEIDAR_CLAN) )
    {
        if ( query_guild_level_lay() == MAX_GUILD_LEVEL ) 
            return Titles[MAX_GUILD_LEVEL];
        else 
            return "";
    }
    else
        return Titles[query_guild_level_lay()];

}

/* Function name: query_guild_skill_name
 * Description  : Gives a name for the guild's special skill
 * Arguments    : type - the number of the skill
 * Returns      : 0        if no skill, or
 *                string - the name
 */
public mixed
query_guild_skill_name(int type)
{
    if ( type == SHIELDSLAM_SPECIAL ) 
        return "shield slam";
}

/* Function name: query_guild_trainer_lay
 * Description  : Returns the skill trainer for the guild
 * Returns      : string *  an array of paths to the guild's trainers.
 */
public mixed
query_guild_trainer_lay()
{
    return ({ GUILD_DIR + "joinroom" });
}

/* Function name: init_guild_member
 * Description  : Add necessary guild items to the player and 
 *                do any other kind of initialization necessary
 */
public void
init_guild_member()
{
    object guild_emblem, who = query_shadow_who();
    
    setuid();
    seteuid(getuid());
    
    if ( guild_emblem = clone_object(GUILD_EMBLEM) )
    {
        guild_emblem->move(who, 1);
    }
    
    /* Add the guild soul to the player */
    who->add_cmdsoul(GUILD_CMDSOUL);
    who->update_hooks();
    
}

/* Function name: start_player
 * Description  : This is called when the player logs in
 */
public void
start_player()
{
    SW->start_player();
    init_guild_member();
}

/*
 * Function name: add_lay_shadow
 * Description:   Shadow an object with this shadow
 * Arguments:     object who - the object to shadow
 * Returns:       as shadow_me in /std/guild/guild_base.c
 *                or -5 if who argument isn't an object
 */
public int 
add_lay_shadow(object who)
{
    int ret = shadow_me(who, "layman", GUILD_STYLE, GUILD_NAME);
    
    if ( ret == 1 )
    {
        init_guild_member();
    }
    
    return ret;
}

/*
 * Function name: remove_lay_member
 * Description:   remove this member from the guild
 */
public void
remove_lay_member()
{
    object emblem, who = query_shadow_who();

    /* Remove the special skill */ 
    who->remove_skill(SHIELDSLAM_SPECIAL);
     
    /* Clear the player's guild stat */
    who->clear_guild_stat(SS_LAYMAN);
        
    /* Remove any instances of the guild emblem on the player */
    while (emblem = present(GUILD_EMBLEM_ID, who))
    {
        emblem->remove_object();
    }
                                
    /* If the player is using our start location, remove it */
    if ( who->query_default_start_location() == GUILD_STARTLOC )
    {
        who->set_default_start_location(who->query_def_start());
    }
                        
    /* Remove the guild soul */
    who->remove_cmdsoul(GUILD_CMDSOUL);
    who->update_hooks();
                                            
    /* Remove the guild shadow.  This also resets tax to 0. */
    remove_guild_lay();
}

                                                                      