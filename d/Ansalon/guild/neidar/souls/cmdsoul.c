/*
 * NOTE:  See /cmd/std/soul_cmd.c for more examples of coding emotes.
 */

#pragma strict_types
#include "/d/Ansalon/common/defs.h"

/* Inherit this for guild souls */
inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";

#include "../guild.h"

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>

#include "emotes.c"

#define AXEWIELDER member_array(W_AXE, TP->query_weapon(-1)->query_wt()) < 0
#define CLUBWIELDER member_array(W_CLUB, TP->query_weapon(-1)->query_wt()) < 0

#define WARRIOR_STAT         56
#define BATTLERAGER_STAT    105
#define OGRESLAYER_STAT     133
#define TROLLSLAYER_STAT    140
#define GIANTSLAYER_STAT    147
#define HERO_STAT           154
#define WARLEADER_STAT      161

string
get_soul_id() 
{ 
    return GUILD_NAME + " soul"; 
}


int 
query_cmd_soul() 
{ 
    return 1; 
}


public mapping
query_ability_map() 
{
    return ([
        "chop"          : CHOP_ABILITY,
        "crush"         : CHOP_ABILITY,
        "dmaster"       : DMASTER_ABILITY,
        "battlerage"    : BATTLERAGE_ABILITY,
        "defend"        : DEFEND_ABILITY,
    ]);
}

mapping
query_cmdlist()
{
    return ([
      /* Command name : Function name */

      "battlerage"    : "do_ability",
      "chop"          : "do_ability",
      "crush"         : "do_ability",
      "clantitle"     : "set_clantitle",
      "defend"        : "do_ability",
      "dmaster"       : "do_ability",
      "doptions"      : "show_options",
      
    ]) +emote_cmdlist();
}

/* Function name: set_clantitle
 * Description  : Sets the special title for the guild member. It checks
 *                if he is allowed to set it first. The player must have
 *                the true title higher than the new one.
 * Arguments    : int 0       - True title,
 *                    1       - Warrior,
 *                    2       - Battlerager,
 *                    3       - Ogreslayer,
 *                    4       - Trollslayer,
 *                    5       - Giantslayer,
 *                    6       - Hero,
 *                    7       - Warleader.
 */
public int
set_clantitle(string str)
{
    string *titles    = ({ });
    string TitleList  = "";
    string temp       = "";
    
    int    GuildStat  = TP->query_stat(SS_OCCUP);
    int    level      = TP->query_skill(SS_CLANTITLE);   

    if ( !strlen(str) )
    {
        notify_fail("Your current clan title is set to:\n\n\t" +
            TP->query_guild_title_occ() + "\n\n" +
            "If you want to change it you should check what titles " +
            "are available for you. Use: 'clantitle list'. " +
            "To set your true title use: 'clantitle true'.\n");
        return 0;
    }
    
    if ( str == "list" )
    {
        if ( GuildStat >= WARRIOR_STAT )
            titles += ({ "Shieldbearer" });
        if ( GuildStat >= BATTLERAGER_STAT )
            titles += ({ "Warrior" });
        if ( GuildStat >= OGRESLAYER_STAT )
            titles += ({ "Battlerager" });
        if ( GuildStat >= TROLLSLAYER_STAT )
            titles += ({ "Ogreslayer" });
        if ( GuildStat >= GIANTSLAYER_STAT )
            titles += ({ "Trollslayer" });
        if ( GuildStat >= HERO_STAT )
            titles += ({ "Giantslayer" });
        if ( GuildStat >= WARLEADER_STAT )
            titles += ({ "Hero" });
        if ( GuildStat >= CHIEFTAIN_STAT )
            titles += ({ "Warleader" });

        if ( !sizeof(titles) )
        {
            write("You can present yourself only with your true title.\n");
            return 1;
        }
        
        TitleList = implode(titles, ",\n\t");
        
        write("You are allowed to choose one of the following titles:\n\t" +
            TitleList + ".\n" +
            "You may also use 'clantitle true' to set your true title.\n");    
        
        return 1;    
    }

    temp = "You will now present yourself as a ";
    
    switch (lower_case(str))
    {
    case "true":
        TP->set_clantitle(0);
        write("You will now present yourself with your true title.\n");
        return 1;
    break;
    case "shieldbearer":
        if ( GuildStat < WARRIOR_STAT )
        {
            write("You can't use this option yet.\n");
            return 1;
        }
        
        TP->set_clantitle(8);
        write(temp + "Shieldbearer of the Neidar Clan.\n");
        return 1;
    case "warrior":
        if ( GuildStat < BATTLERAGER_STAT )
        {
            if ( GuildStat >= WARRIOR_STAT )
            {   
                if (level == 1)
                {
                    write("But you are the dwarven Warrior now and only " +
                        "your death can change that!\n");
                    return 1;
                }

                write("You will now present yourself with your true title.\n");
                TP->set_clantitle(0);
                return 1;
            }            

            write("No, you are not a true dwarven Warrior yet.\n");
            return 1;
        }
        
        TP->set_clantitle(1);        
        write(temp + "Warrior of the Neidar Clan.\n");
        return 1;
    break;
    case "battlerager":
        if ( GuildStat < OGRESLAYER_STAT )
        {
            if ( GuildStat >= BATTLERAGER_STAT )
            {   
                if (level == 2)
                {
                    write("But you are the true Battlerager already!\n");
                    return 1;
                }

                write("You will now present yourself with your true title.\n");
                TP->set_clantitle(0);
                return 1;
            }            
            
            write("You can't title yourself this way yet. You must prove " +
                "it on the battlefield first!\n");
            return 1;
        }
        
        TP->set_clantitle(2);
        write(temp + "Battlerager of the Neidar Clan.\n");
        return 1;
    break;
    case "ogreslayer":
        if ( GuildStat < TROLLSLAYER_STAT )
        {
            if ( GuildStat >= OGRESLAYER_STAT ) 
            {
                if ( level == 3 )
                {
                    write("But everyone knows you as a Mighty Ogreslayer " +
                        "already!\n");
                    return 1;
                }
                
                write("You will now present yourself with your true title.\n");
                TP->set_clantitle(0);
                return 1;

            }

            write("Ogreslayer? You should make them tremble first! " +
                "Be patient!\n");
            return 1;
        }
        
        TP->set_clantitle(3);
        write(temp + "Ogreslayer of the Neidar Clan.\n");
        return 1;
    break;
    case "trollslayer":
        if ( GuildStat < GIANTSLAYER_STAT )
        {
            if ( GuildStat >= TROLLSLAYER_STAT ) 
            {
                if ( level == 4 )
                {
                    write("But you are the Renowned Trollslayer already!\n");
                    return 1;
                }

                write("You will now present yourself with your true title.\n");
                TP->set_clantitle(0);
                return 1;

            }

            write("It is not so easy... Prove yourself to be worthy of " +
                "that title first!\n");
            return 1;
        }

        TP->set_clantitle(4);
        write(temp + "Trollslayer of the Neidar Clan.\n");
        return 1;
    break;
    case "giantslayer":
        if ( GuildStat < HERO_STAT )
        {
            if ( GuildStat >= GIANTSLAYER_STAT ) 
            {
                if ( level == 5 )
                {
                    write("Giants or not, they have heard of you already!\n");
                    return 1;
                }
                
                write("You will now present yourself with your true title.\n");
                TP->set_clantitle(0);
                return 1;
            }

            write("You do not deserve that title yet. So far, giants " +
                "laugh when they hear of you! Change that first!\n");
            return 1;
        }

        TP->set_clantitle(5);
        write(temp + "Giantslayer of the Neidar Clan.\n");
        return 1;
    break;
    case "hero":
        if ( GuildStat < WARLEADER_STAT )
        {
            if ( GuildStat >= HERO_STAT ) 
            {
                if ( level == 6 )
                {
                    write("You are true Dwarven Hero already! There is no " +
                        "need to change that.\n");
                    return 1;
                }
                
                write("You will now present yourself with your true title.\n");
                TP->set_clantitle(0);
                return 1;
            }

            write("Let others decide if you deserve that title!\n");
            return 1;
        }

        TP->set_clantitle(6);
        write(temp + "Hero of the Neidar Clan.\n");
        return 1;
    break;
    case "warleader":
        if ( GuildStat < CHIEFTAIN_STAT )
        {
            if ( GuildStat >= WARLEADER_STAT ) 
            {
                if ( level == 7 )
                {
                    write("But you hold the position of the Clan Warleader " +
                        "already!\n");
                    return 1;
                }
                
                write("You will now present yourself with your true title.\n");
                TP->set_clantitle(0);
                return 1;
            }

            write("You think the Clan would choose you as their " +
                "Warleader? I do not think so... yet.\n");
            return 1;
        }

        TP->set_clantitle(7);
        write(temp + "Warleader of the Hill Dwarves.\n");
        return 1;
    break;
    case "chieftain":
        if ( GuildStat > CHIEFTAIN_STAT )
        {
            TP->set_clantitle(0);
            write("You will now present yourself with your true title.\n");
            return 1;
        }
        
        write("You are not allowed to set this title.\n");
        return 1;
    break;
    }
    
    notify_fail("The syntax is: 'clantitle list', or for example: 'clantitle " +
        "battlerager'\n");
    return 0;
}

public int
show_options(string str)
{   
    object player;
    string * arguments;
    string player_name;
     
    setuid();
    seteuid(getuid());
    
    player = this_player();
    player_name = player->query_real_name();
    if (!str)
    {
        write("Neidar Clan Options\n");
        write("===================\n");
        write("Battlerage [battlerage]: ");
        switch (OPTIONS_MANAGER->query_option("battlerage", player_name))
        {
        case 1:
            write("Aggressively\n");
            break;
        case 2:
            write("Stubbornly\n");
            break;            
        case 0:
        default:
            write("Fiercely\n");
            break;
        }
        write("\n");
        write("To set your options, use \"doptions <option> <value>\"\n");
        write("\n");
        return 1;
    }
    else if (str == "battlerage")
    {
        switch (OPTIONS_MANAGER->query_option("battlerage", player_name))
        {
        case 1:
            write("When you rage in battle, you do so aggressively.\n");
            break;
        case 2:
            write("When you rage in battle, you do so stubbornly.\n");
            break;
        case 0:
        default:
            write("When you rage in battle, you do so fiercely.\n");
            break;
        }
        write("\n");
        return 1;
    }
            
    arguments = explode(str, " ");
    if (sizeof(arguments) == 2
        && lower_case(arguments[0]) == "battlerage")
    {
        switch (lower_case(arguments[1]))
        {
        case "fiercely":
            OPTIONS_MANAGER->set_option("battlerage", player_name, 0);
            write("You will now battlerage fiercely.\n");
            break;
        
        case "aggressively":
            OPTIONS_MANAGER->set_option("battlerage", player_name, 1);
            write("You will now battlerage aggressively.\n");
            break;

        case "stubbornly":
            OPTIONS_MANAGER->set_option("battlerage", player_name, 2);
            write("You will now battlerage stubbornly.\n");
            break;
        }
        return 1;
    }           

    notify_fail(str + " is not a recognized option for the Neidar Clan.\n");
    return 0;
}
