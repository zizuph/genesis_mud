/*
 *
 *  Copyright (C) Chad Richardson a.k.a.  Igneous@Genesis
 *
 *  Modification log:
 * 
 *  add_exp(exp, 0); updated with add_exp_quest(exp);
 *  -- Finwe, August 1998
 *  Reformatted text
 *  -- Finwe, April 2020
 *
 */
#pragma strict_types
#pragma no_clone
#pragma no_inherit

#include <std.h>

#define ERROR(s) log_file("quest_errors", ctime(time()) +" "+ s +"\n")

#define TRUSTED ({"finwe", "tomas", "raymundo", "varian"})

#define INFO_MAP_SAVE "/d/Shire/sys/global/quest_info"
// Indexes for the mapping
#define GROUP   0
#define BIT     1
#define EXP     2
#define CLOSED  3
#define Q_NAME  4

// Prototypes
nomask void load_info();
nomask void save_info();
nomask public int valid_wizard(object wizard, int flag);

private mapping gQuest_info = ([ ]);

nomask public void
create()
{
    load_info();
}

/*
 * Function    : check_quest
 * Description : Determines if the player has done this quest or not.
 * 
 * Arguments   : player:  The player we are checking.
 *               name  :  The short name of the quest.
 * Returns     : 0 if the player hasn't done the quest
 *               1 if the player has done the quest or
 *                 and error has occured.
 */
nomask public int
check_quest(object player, string name)
{
    if (!objectp(player))
    {
        ERROR("No player supplied.");
        return 1;
    }

    if (!interactive(player))
    {
        ERROR("NPC tested.");
        return 1;
    }

    if (!stringp(name))
    {
        ERROR("No quest name was supplied.");
        return 1;
    }

    if (!pointerp(gQuest_info[name]))
    {
        ERROR("Quest "+ name +" does not exists in the mapping!");
        return 1;
    }

    // If the status of this quest is closed
    if (gQuest_info[name][CLOSED])
    {
        if (!valid_wizard(player, 1) && 
          (extract(player->query_real_name(), -2) != "jr"))
        {
            ERROR(player->query_real_name() +" tried to access a closed "+
              "quest.\n");
            return 1;
        }
    }

    return player->test_bit(creator(this_object()), 
      gQuest_info[name][GROUP], gQuest_info[name][BIT]);
}

/*
 * Function    : reward_quest
 * Description : Determines if the player is worthy of a quest reward.
 *               If the player hasn't done the quest the appropriate 
 *               bit is set and experience is given.
 * Arguments   : player:  The player we are trying to reward
 *               name  :  The short name of the quest.
 *               exp   :  (optional)  Some quests give variable
 *                        amounts of quest exp.  Use this third
 *                        arguement if the exp the player is to get
 *                        differs from the exp amount in the gQuest_exp
 *                        mapping.
 * Returns     : 0 if we don't reward the player
 *               1 if we do reward the player
 */
nomask varargs int
reward_quest(object player, string name, int exp)
{
    string log_str;

    // test to see if we've done this quest before
    if (check_quest(player, name))
    	return 0;

    if (!player->set_bit(gQuest_info[name][GROUP], gQuest_info[name][BIT]))
    {
        ERROR("Set_bit failed for "+player->query_name()+" at "+
          ctime(time()) +" for "+ gQuest_info[name][Q_NAME] +"!");
        player->catch_msg("Something has gone wrong, please leave a bug "+
          "report and try this quest again at a later date.\n");
        return 0;
    }

    //  No variable exp was set so we use the one set in the mapping.
    if (!exp)
        exp = gQuest_info[name][EXP];
        player->add_exp_quest(exp);

        log_str = ctime(time()) + " "+ capitalize(player->query_real_name()) +
        " (" + player->query_average_stat() + ") completed the "+
        gQuest_info[name][Q_NAME]+" and received "+exp+" experience.\n";

        setuid(); seteuid(getuid());
        log_file("quest/" + name, log_str);
        log_file("quest/QUEST_MASTER", log_str, -1);
        return 1;
} 

nomask public int
add_quest(string short, int group, int bit, int exp, string long)
{
    object player;
    string *index;
    int i;

    if (!objectp(player = this_interactive()))
    {
        ERROR("Add quest must be added by an interactive.");
        return 0;
    }

    if (!valid_wizard(player, 0))
    {
        ERROR("Invalid wizard ("+player->query_real_name()+") tried "+
          "to add a quest!");
        return 0;
    }
    if (group < 0 && group > 4)
    {
        player->catch_msg("Invalid group was used!  You must use a "+
          "group between the numbers of 0 and 4!\n");
        return 1;
    }

    if (bit < 0 && bit > 19)
    {
        player->catch_msg("Invalid bit number was used!  You must use a "+
          "bit number between the numbers of 0 and 19!\n");
        return 1;
    }

    index = m_indexes(gQuest_info);

    for (i = 0;i < sizeof(index);i++)
    {
        if (gQuest_info[index[i]][GROUP] == group)
        {
            if (gQuest_info[index[i]][BIT] == bit)
            {
                player->catch_msg("Group "+ group +" Bit "+ bit +" is already "+
                  "used for the "+ gQuest_info[index[i]][Q_NAME] +".\n");
                return 1;
            }
        }
    }

    if (!stringp(long))
    {
        player->catch_msg("You must set a long description for "+
          "this quest.");
        return 1;
    }

    if ((!stringp(short)) || (sizeof(explode(short, " ")) > 1))
    {
        player->catch_msg("Invalid short quest name "+short+" was used.");
        return 1;
    }

    if (pointerp(gQuest_info[short]))
    {
        player->catch_msg("Quest name: "+short+" is already in use.\n");
        return 1;
    }

    //  OKie we passed everything so we add the quest!
    //  The status of the quest is always set to open
    gQuest_info[short] = ({group,bit,exp,0,long});
    player->catch_msg(capitalize(long) +" was added to the quest "+
      "logger.\n");     
    save_info();
    return 1;
}

nomask public int
close_quest(string name)
{
    object player;

    if (!objectp(player = this_interactive()))
    {
        ERROR("Closing a quest can only be done by an interactive.");
        return 0;
    }

    if (!valid_wizard(player, 0))
    {
        ERROR("Invalid wizard ("+player->query_real_name()+") tried "+
           "to reserve a bit!");
        return 0;
    }

    if (!pointerp(gQuest_info[name]))
    {
        player->catch_msg("Quest name "+ name +" does not exist.\n");
        return 1;
    }

    gQuest_info[name][CLOSED] = 1;
    save_info();
    player->catch_msg(gQuest_info[name][Q_NAME] + " has been closed!\n");
    return 1;
}

nomask public int
open_quest(string name)
{
    object player;

    if (!objectp(player = this_interactive()))
    {
        ERROR("Opening quests must be done by an interactive.");
        return 0;
    }

    if (!valid_wizard(player, 0))
    {
        ERROR("Invalid wizard ("+player->query_real_name()+") tried "+
            "to reserve a bit!");
        return 0;
    }

    if (!pointerp(gQuest_info[name]))
    {
        player->catch_msg("Quest name "+ name +" does not exist.\n");
        return 1;
    }

    gQuest_info[name][CLOSED] = 0;
    save_info();
    player->catch_msg(gQuest_info[name][Q_NAME] + " has been opened!\n");
    return 1;
}

nomask public int
remove_quest(string short)
{
    object player;

    if (!objectp(player = this_interactive()))
    {
        ERROR("Removing a quest must be done by an interactive.");
        return 0;
    }

    if (!valid_wizard(player, 0))
    {
        ERROR("Invalid wizard ("+player->query_real_name()+") tried "+
            "to add a quest!");
        return 0;
    }

    if (!pointerp(gQuest_info[short]))
    {
        player->catch_msg("Quest name: "+short+" does not exist.\n");
        return 1;
    }

    //  OKie we passed everything so we remove the quest
    gQuest_info = m_delete(gQuest_info, short);
    player->catch_msg("Quest "+short+" was removed from the quest "+
      "logger.\n");     
    save_info();
    return 1;
}

nomask public int
sort_bits(string str1, string str2)
{
    int b1, b2;

    if (gQuest_info[str1][GROUP] == gQuest_info[str2][GROUP])
    {
        b1 = gQuest_info[str1][BIT];
        b2 = gQuest_info[str2][BIT];
        return ((b1 < b2) ? -1 : (b1 == b2 ? 0 : 1));
    }

    return (gQuest_info[str1][GROUP] > gQuest_info[str2][GROUP] ? 1 : -1);

}

nomask public int
list(string flag)
{
    string *index, to_write;
    int i;

    if (!valid_wizard(this_interactive(), 1))
	return 0;

    if (!stringp(flag))
    	flag = "quests";

    index = m_indexes(gQuest_info);
    index = sort_array(index, "sort_bits");
    to_write = "The following " + (flag == "quests" ? "quests are" :
        "bits are used") + " within "+creator(this_object())+" Domain:\n";
    sprintf("%'*'75s","\n");
    to_write += "GROUP   BIT   "+ (flag == "bits" ? "" : "EXP   ") +
        "QUEST_NAME\n";
    for (i = 0;i < sizeof(index); i++)
    {
        if (gQuest_info[index[i]][EXP] || flag == "bits")
        {
            to_write += sprintf("  %-6s", 
              val2str(gQuest_info[index[i]][GROUP]));
            to_write += sprintf("%-6s", 
              val2str(gQuest_info[index[i]][BIT]));
            if (flag == "quests")
            {
            to_write += sprintf("%-9s", 
              val2str(gQuest_info[index[i]][EXP]));
            }
            to_write += capitalize(gQuest_info[index[i]][Q_NAME]);
            to_write += (gQuest_info[index[i]][CLOSED] ? 
              " (CLOSED)\n" : "\n");
        }
    }
    to_write += sprintf("%'*'75s", "\n");

    this_interactive()->more(to_write);
    return 1;
}

nomask public int
valid_wizard(object wizard, int flag)
{
    string domain = creator(this_object());
    int rank = SECURITY->query_wiz_rank(wizard->query_real_name());

    // TRUSTED players can access this quest master
    if (member_array(wizard->query_real_name(), TRUSTED) != -1)
    	return 1;

    // Damn Arches can do just about anything ;-)
    if (rank >= WIZ_ARCH)
	    return 1;

    // Lord of this Domain can do whatever he wishes
    if (SECURITY->query_domain_lord(domain) == wizard->query_real_name())
	return 1;

    // And so can this Domains steward and at times a normal wizard.
    if ((rank >= (flag ? WIZ_NORMAL : WIZ_STEWARD)) && 
        (SECURITY->query_wiz_dom(wizard->query_real_name()) == domain))
	return 1;

    return 0;
}

nomask void
load_info()
{
    setuid(); seteuid(getuid());
    gQuest_info = restore_map(INFO_MAP_SAVE);
}

nomask void
save_info()
{
    save_map(gQuest_info, INFO_MAP_SAVE);
}

