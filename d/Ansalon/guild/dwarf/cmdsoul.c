/*
 * NOTE:  See /cmd/std/soul_cmd.c for more examples of coding emotes.
 */

#pragma strict_types
#include "/d/Ansalon/common/defs.h"

/* Inherit this for guild souls */
inherit "/cmd/std/command_driver";

#include "guild.h"

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


mapping
query_cmdlist()
{
    return ([
      /* Command name : Function name */

      "battlerage"    : "stand_special",
      "chop"          : "guildchop",
      "crush"         : "guildchop",
      "clantitle"     : "set_clantitle",

    ]) +emote_cmdlist();
}

int
guildchop(string str)
{
    object ob, *obj, *oblist;
    string how;

    if(!sizeof(TP->query_weapon(-1)))
    {
	notify_fail("You have no weapon wielded! You can't do that!\n");
	return 0;
    }

    if(AXEWIELDER && CLUBWIELDER)
    {
	notify_fail("You don't have the appropriate weapon to do that.\n");
	return 0;
    }

    /* What are we attacking anyway? */
    if (strlen(str))
    {
	if (!sizeof(obj = parse_this(str, "[the] %l")))
	{
	    notify_fail("Choose a more appropriate target.\n");
	    return 0;
	}

	ob = obj[0];
    }
    /* if the player doesn't specify a target, we assume the player's
     * current enemy.
     */
    else if (!(ob = this_player()->query_attack()))
    {
	notify_fail("But you aren't in battle with anyone!\n");
	return 0;
    }

    /* Does attacker have the skill? */
    if (!(this_player()->query_skill(SS_GUILD_SPECIAL_SKILL)))
    {
	write("First you should learn how.\n");
	return 1;
    }

    if(TP->query_alignment() < -100)
    {
	write("You have drifted from the noble path of the dwarven warrior. " +
	  "You no longer have the fire to use chop or crush.\n");
	return 1;
    }

    /* Is the attacker already busy? */
    if(TP->query_chop())
    {
	write("Patience! You have not yet recovered from your " +
	  "last attack!\n");
	return 1;
    }

    /*
    if(TP->query_prepare_slam())
    {
	write("You are too focused on preparing a shield slam, " +
	    "and can't do that!\n");
	return 1;
    }
    */

    /* Are we even allowed to attack it?  Use can_attack_with_occ_special(),
     * which is defined in the guild shadow, to find out.
     */
    if (stringp(how = this_player()->can_attack_with_occ_special(ob, "chop")))
    {
	write(how);
	return 1;
    }

    if(!TP->query_attack())
    {
        write("You roar an ancient dwarven warcry, and " +
          "charge into battle!\n");
        say(QCTNAME(TP)+ " roars an ancient dwarven warcry, " +
          "and charges into battle!\n");
    }

    if ( TP->query_prop(LIVE_O_LAST_KILL) != ob )
        TP->add_prop(LIVE_O_LAST_KILL, ob);
        
    /* The shadow takes care of the rest */
    this_player()->chop(ob);

    return 1;
}

int
stand_special(string str)
{
    if(!str)
    {
	notify_fail("Battlerage how?\n");
	return 0;
    }


    if(!TP->query_attack())
    {
	notify_fail("You are not in battle with anyone, " +
	  "so there is no point in going into a " +
	  "battlerage.\n");
	return 0;
    }


    if(!(TP->query_skill(SLAM_SPECIAL_SKILL)))
    {
	notify_fail("Perhaps you should learn how to " +
	  "battlerage like a dwarven warrior first?\n");
	return 0;
    }

    if(TP->query_stand())
    {
	notify_fail("Patience! You are not ready yet.\n");
	return 0;
    }

    if(TP->query_prop(LIVE_I_ATTACK_DELAY) ||
      TP->query_prop(LIVE_I_STUNNED))
    {
	notify_fail("You are too stunned to do that.\n");
	return 0;
    }

    if(TP->query_fatigue() < TP->query_stat(SS_CON) /6)
    {
	notify_fail("You are too weary to work yourself " +
	  "into a battlerage.\n");
	return 0;
    }

    if(str == "fiercely")
    {
	TP->stand(str);
	return 1;
    }

    if(str == "stubbornly")
    {
     /* This feature has been removed.       
	TP->stand(str);
	return 1;
      */
    	return 0;
    }

    if(str == "aggressively")
    {
	if(TP->query_stat(SS_OCCUP) < 90)
	{
	    notify_fail("Only experienced battleragers " +
	      "can rage aggressively!\n");
	    return 0;
	}
	TP->stand(str);
	return 1;
    }

    write("How did you want to stand?\n");
    return 1;
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
