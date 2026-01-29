
 /* 
  * Elemental Worshippers of Calia council code
  * 
  * This code is adapted from Maniac's code for the Calian Council. 
  *
  * by Jaacar and Khail August 7th, 1996
  * modifications by Maniac 31/10/96, 16/11/96
  */

#pragma save_binary

#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <std.h>
#include "defs.h"
#include WORSHIP_HEADER
#include COUNCIL_HEADER
inherit WORSHIPPER_CODE;

#define EDIT "/obj/edit"
#define MESSAGE_MAX_CHARS 720
#define MIN_TIME_BETWEEN_EDITS 900
#define COUNCIL_S_EDITING "_council_s_editing"
#define SPIRIT_COUNCIL_CODE "/d/Calia/guilds/scop/specials/council_code"

#pragma save_binary

string *council = ({ });
mapping punishments = ([ ]);
string leader = "";
static mixed earlier_commands = ({ });
static mapping recently_edited = ([ ]);

string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}

/*
    Function: check_earlier_command
    Someone has tried to issue a secured command (eg. expel).
    return 1 if it has been issued before by someone else (eg. it may
    now be carried out); return 0 if it has been issued before by the
    same person (eg. it may not yet carried out); record it and return 0
    if it has not been issued at all (so someone can confirm it in the
    future).

    This feature has been removed for the time being.  If need be, it can
    be reinstalled by deleting the first line of the function and the
    remark braces.  - Jaacar
*/
int
check_earlier_command(string verb, string doer, string to)
{
    return 1;
    /*
    mixed e;
    int marker = -1;
    int i;
    mixed to_add;

    to_add = ({verb, doer, to});
    for (i = 0; i < sizeof(earlier_commands); i++)
    {
        e = earlier_commands[i];
        if ((e[0] == verb) && (e[1] != doer) && (e[2] == to))
            marker = i;
        else if ((e[0] == verb) && (e[1] == doer) && (e[2] == to))
            to_add = ({ });
    }
    if (marker > -1)
    {
        earlier_commands = exclude_array(earlier_commands, marker, marker);
        return 1;
    }
    if (sizeof(to_add) == 3)
        earlier_commands += ({to_add});
    return 0;
    */
}

/* Action: show council members what commands need to be confirmed. */
int
see_pending_commands()
{
    int i;
    if (!sizeof(earlier_commands))
    {
        notify_fail("No commands requiring confirmation have been issued.\n");
        return 0;
    }
    write("The following commands require confirmation (i.e. Someone else "+
        "must enter the given command again in order for it to be "+
        "carried out):\n");
    for (i = 0; i < sizeof(earlier_commands); i++)
        write(earlier_commands[i][0] + " by " + earlier_commands[i][1] +
            " on " + earlier_commands[i][2] + ".\n");
    return 1;
}


/* Action: Council member may cancel any of his/her commands
           that await confirmation. */ 
int
cancel_pending_commands()
{
    int i;
    object tp = this_player();
    mixed ec = ({ });

    write("Ok, cancelling any of your commands that were awaiting " +
          "confirmation.\n");
    
    if (!sizeof(earlier_commands)) 
        return 1;

    for (i = 0; i < sizeof(earlier_commands); i++) 
        if (earlier_commands[i][1] != tp->query_real_name())
             ec += ({ earlier_commands[i] });

    earlier_commands = ec;

    return 1;
}

void
remove_non_existant()
{
    int i;
    string *ind;

    restore_object(COUNCIL);
    for (i = 0; i < sizeof(council); i++) 
        if (!SECURITY->exist_player(lower_case(council[i])))
            council[i] = "to_remove";

    council -= ({"to_remove"});
    ind = m_indexes(punishments);
    for (i = 0; i < sizeof(ind); i++)
        if (!SECURITY->exist_player(lower_case(ind[i])))
            punishments = m_delete(punishments, ind[i]);

    save_object(COUNCIL);
}


void
create()
{
    seteuid(getuid());
    restore_object(COUNCIL);
//  set_alarm(1.0, 0.0, remove_non_existant);
}

string 
query_council()
{
    string cstr;
    int x; 

    seteuid(getuid());
    restore_object(COUNCIL);
    if (sizeof(council) == 0)
    cstr = "The Worshippers Council does not currently have any members.\n";
    else if (sizeof(council) == 1) 
        cstr = "The Worshippers Council currently has the following member: " +
            capitalize(council[0]) + ".\n";
    else
    {
        cstr = "The Worshippers Council currently has the following members: ";
        cstr += (COMPOSITE_WORDS(map(council, capitalize)) + ".\n"); 
    }

    return cstr;
}

string
query_leader()
{
    string lstr;
    int x;

    seteuid(getuid());
    restore_object(COUNCIL);
    if (!strlen(leader))
        lstr = "There is currently no leader of the Worshippers.\n";
    else 
        lstr = "The leader of the Worshippers is "+capitalize(leader)+".\n";
    return lstr;
}

public int
is_leader(string str)
{
    if (!str)
        return 0;
    seteuid(getuid());
    restore_object(COUNCIL);
    return (lower_case(leader) == lower_case(str));
}


int 
is_council_member(string str)
{
    if (!str)
	return 0;
    str = lower_case(str);

    // As of January 22, 2014, we allow all Spirit Circle elders
    // to be considered EW council members. The reason for this is
    // to have better oversight of the layman as we bring the occ
    // and layman together.
    if (IN_ARRAY(str, council)
        || SPIRIT_COUNCIL_CODE->is_spirit_elder(str))
    {
        return 1;
    }

    return 0;
}


string *query_council_members()
{
    return council;
}

int
see_council(string str)
{
    object tp = TP;
     
    tp->catch_msg(query_council());
    return 1;
}

int
add_council_member(string str)
{
    object tp = TP; 
    object target;
    string adder;
 
    if (!str) return 0;
    adder = tp->query_real_name();
    str = lower_case(str);
    seteuid(getuid());
    restore_object(COUNCIL);
    if (sizeof(council) >= COUNCIL_MAX_SIZE)
    {
        NF("The council is already full.\n");
        return 0;
    }

    if (! (SECURITY->exist_player(lower_case(str))) )
    {
        NF("No such player!\n");
        return 0;
    }

    if (is_council_member(adder) || is_calian_wiz(tp))
    {
        if (member_array(str, council) >= 0)
        {
            NF(capitalize(str) + " is already a member of the " +
                "council.\n");
            return 0;
        }
        council += ({ str });
        (WOR_OBJECTS + "council_log_book")->update_log_book(my_time() + 
           capitalize(str) + " has been added to the Worshipper " +
           "Council by " + capitalize(adder) + ".\n");
        save_object(COUNCIL);
        write("Ok.\n");
        if (target=find_player(lower_case(str)))
        {
            target->set_skill(SS_CARVED,ALL_FLAGS);
            
            target->init_worshipper_titles();
            target->set_guild_pref(SS_LAYMAN, TP->query_guild_tax_lay());
            tell_object(target, "You have been added "+
                "to the Worshippers Council.\n");
        }
        return 1;
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

int
add_leader(string str)
{
    object tp = TP; 
    object target;
    string adder;

    if (!str) return 0;
    adder = tp->query_real_name();
    str = lower_case(str);
    target = find_player(str);
    seteuid(getuid());
    restore_object(COUNCIL);
    if (strlen(leader))
    {
        NF("There is already a leader!\n");
        return 0;
    }

    if (! (SECURITY->exist_player(str)) )
    {
        NF("No such player!\n");
        return 0;
    }

    if (!find_player(str))
    {
        write("But "+capitalize(str)+" isn't logged in!\n");
        return 1;
    }
    if (is_council_member(adder) || is_calian_wiz(tp))
    {
        if (str == leader)
        {
            NF(capitalize(str) + " is already the leader!\n");
            return 0;
        }
        leader = str;
        (WOR_OBJECTS + "council_log_book")->update_log_book(my_time() + 
         capitalize(str) + " has been promoted to the leader by " + 
         capitalize(adder) + ".\n");
        save_object(COUNCIL);
        target->set_guild_pref(SS_LAYMAN,TP->query_guild_tax_lay());
        tell_object(target,"You have been promoted to the leader "+
            "of the Worshippers.\n");
        target->init_worshipper_titles();
        target->set_skill(SS_CARVED,ALL_FLAGS);
        
        write("Ok.\n");
        return 1;
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

int
remove_council_member(string str)
{
    object tp = TP;
    object target;
    string remover;

    if (!str)
	return 0;
    remover = tp->query_real_name();
    str = lower_case(str);
    seteuid(getuid());
    restore_object(COUNCIL);

    if (sizeof(council) == 0)
    {
         NF("No-one in the council yet!\n");
         return 0;
    } 

    if (!SECURITY->exist_player(str) )
    {
        NF("No such player!\n");
        return 0;
    }

    if (is_council_member(remover) || is_calian_wiz(tp) ) 
    { 
        if (member_array(str, council) > -1)
	{
            council -= ({ str }); 
            save_object(COUNCIL);
            (WOR_OBJECTS + "council_log_book")->update_log_book(my_time() + 
             capitalize(str) + " has been removed from the Worshipper " +
             "Council by " + capitalize(remover) + ".\n");
            write("Ok.\n");
        if (target=find_player(lower_case(str)))
        {
            target->init_worshipper_titles();
            tell_object(target,"You have been removed "+
                "from the Worshippers Council.\n");
        }
            return 1;
        }
        else
        {
            NF("No such player on the council!\n");
            return 0; 
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

int
remove_leader(string str)
{
    object tp = TP;
    string remover;

    if (!str)
        return 0;
    remover = tp->query_real_name();
    str = lower_case(str);
    seteuid(getuid());
    restore_object(COUNCIL);
    
    if (!strlen(leader))
    {
         NF("There is no leader yet!\n");
         return 0;
    } 

    if (!SECURITY->exist_player(str) )
    {
        NF("No such player!\n");
        return 0;
    }

    if (is_council_member(remover) || is_calian_wiz(tp) ) 
    { 
        if (str == leader)
        {
            leader = "";
            save_object(COUNCIL);
            (WOR_OBJECTS+"council_log_book")->update_log_book(my_time() + 
               capitalize(str) + " has been removed as leader by " + 
               capitalize(remover) + ".\n");
            tp->catch_msg("Ok.\n");
            return 1;
        }
        else
        {
            NF("That is not the leader!\n");
            return 0; 
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

int
is_train_banned(object player)
{
    if (player->query_skill(SS_PUNISHMENT) == NO_TRAINING) return 1;
    else return 0;
}

int
is_spell_banned(object player)
{
    if (player->query_skill(SS_PUNISHMENT) == SPELL_BANNED) return 1;
    else return 0;
}

int
is_discharged(object player)
{
    if (player->query_skill(SS_PUNISHMENT) == DISCHARGED) return 1;
    else return 0;
}

int
is_expelled(object player)
{
    if (player->query_skill(SS_PUNISHMENT) == EXPULSION) return 1;
    else return 0;
}

/* Give player a message */
void
a_message(object player, string message)
{
     player->catch_msg(message);
}

void
exec_stop_train(object player)
{
    string player_name;

    seteuid(getuid());
    restore_object(COUNCIL);
    player_name = player->query_real_name();
    if(is_worshipper(player))
    {
        player->set_skill(SS_PUNISHMENT, NO_TRAINING);
        set_alarmv(1.5, 0.0, "a_message", ({ player,
            "You have been banned by the Worshippers Council from " +
            "using the guild's training facilities" +
            ".\n" }) );
    }
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
}

void
exec_spell_banned(object player)
{
    string player_name;

    seteuid(getuid());
    restore_object(COUNCIL);
    player_name = player->query_real_name();
    if(is_worshipper(player))
    {
        player->set_skill(SS_PUNISHMENT, SPELL_BANNED);
        set_alarmv(1.5, 0.0, "a_message", ({ player,
            "You have been banned by the Worshippers Council from " +
            "using the guild's spells" +
            ".\n" }) );
    }
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
}

void
exec_expel_player(object player)
{
    string player_name;
    object tp = this_player();

    seteuid(getuid());
    restore_object(COUNCIL);
    player_name = player->query_real_name();
    player->set_skill(SS_PUNISHMENT, EXPULSION);
    if (is_worshipper(player))
    {
        set_alarmv(1.5, 0.0, "a_message", ({ player,
            "You have been expelled from the Worshippers guild " +
            "by the Worshippers Council.\n" }) );
        player->move_living("X",WOR_TEMPLE+"s_chamber",0,1);
        player->command("betray the Elementals");
    }
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
}

void
exec_discharge_player(object player)
{
    string player_name;
    object tp = this_player();

    seteuid(getuid());
    restore_object(COUNCIL);
    player_name = player->query_real_name();
    if (is_worshipper(player))
    {
        player->set_skill(SS_PUNISHMENT, DISCHARGED);
        set_alarmv(1.5, 0.0, "a_message", ({ player,
            "You have been discharged from the Worshippers guild " +
            "by the Worshippers Council.\n" }) );
        present("worshipper_chalice",player)->remove_object();
        present("worshipper_dagger",player)->remove_object();
        present("worshipper_sceptre",player)->remove_object();
        present("worshipper_wand",player)->remove_object();
        present("worshipper_pentacle",player)->remove_object();
        player->remove_skill(SS_CARVED);
       
        player->remove_skill(SS_PATRON_ELEMENTAL); 
        player->remove_guild_lay();
        player->clear_guild_stat(SS_LAYMAN);
        player->remove_cmdsoul(WORSHIPPER_CMDSOUL);
        player->update_hooks();
        player->catch_msg("Your Elemental Tools shatter " +
                          "into thousands of tiny pieces!\n");
        if (player->query_default_start_location() == WORSTART)
        {
            player->set_default_start_location(player->query_def_start());
            if (file_name(environment(player)) == WORSTART) 
               player->move_living("out of the temple", WOR_TEMPLE+"path");   
        }
    }
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
}

void
exec_remove_punish(object player)
{
    string player_name;

    seteuid(getuid());
    restore_object(COUNCIL);
    player_name = player->query_real_name();
    player->set_skill(SS_PUNISHMENT, NO_PUNISHMENT);
    set_alarmv(1.5, 0.0, "a_message", ({ player,
        "The Worshipper Council has removed any punishments " +
        "that has been previously placed on you" +
        ".\n" }) );
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);

}

void
carry_out_punishments(object player)
{
    string player_name;
    
    player_name = player->query_real_name();
    seteuid(getuid());
    restore_object(COUNCIL);

    if (punishments[player_name]) {
        if (punishments[player_name] == REMOVE_PUNISHMENTS)
        {
            if (player->query_skill(SS_PUNISHMENT) != NO_PUNISHMENT)
            exec_remove_punish(player);
        }
        else if (punishments[player_name] == NO_TRAINING)
            exec_stop_train(player);
        else if (punishments[player_name] == EXPULSION)
            exec_expel_player(player);
        else if (punishments[player_name] == DISCHARGED)
            exec_discharge_player(player);
        else if (punishments[player_name] == SPELL_BANNED)
            exec_spell_banned(player);
        
    }
}

void
add_punishment(string punished, int punishment)
{

    seteuid(getuid());
    restore_object(COUNCIL);
    /* only one punishment allowed at a time */
    if (punishments[punished])
        punishments = m_delete(punishments, punished);
    punishments += ([ punished : punishment ]);
    save_object(COUNCIL);
}

int
record_stop_train(string str)
{
    object tp, player;
    string banner;

    tp = TP;

    if (!stringp(str)) {
        notify_fail("Stop who from training?\n"); 
        return 0;
    }

    banner = tp->query_real_name();
    str = lower_case(str); 

    if (is_council_member(banner) || is_calian_wiz(tp) ) 
    {
        player = find_living(str);
        if ( (!player) && SECURITY->exist_player(str) )
        {
            add_punishment(str, NO_TRAINING); 
            (WOR_OBJECTS+"council_log_book")->update_log_book(my_time() + 
               capitalize(banner) + " has banned " + capitalize(str) + 
              " from using the guild's training facilities.\n");
            tp->catch_msg("Ok.\n");
            return 1;
        }
        else if (is_worshipper(player))
        {
            exec_stop_train(player);
            (WOR_OBJECTS+"council_log_book")->update_log_book(my_time() + 
                capitalize(banner) + " has banned " + capitalize(str) + 
               " from using the guild's training facilities.\n");
            tp->catch_msg("Ok.\n");
            return 1;
        } 
        else
        {
            NF("Either player doesn't exist or is not a Worshipper.\n");
            return 0;
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

int
record_spell_banned(string str)
{
    object tp, player;
    string banner;

    tp = TP;

    if (!stringp(str)) {
        notify_fail("Stop who from using spells?\n"); 
        return 0;
    }

    banner = tp->query_real_name();
    str = lower_case(str); 

    if (is_council_member(banner) || is_calian_wiz(tp) ) 
    {
        player = find_living(str);
        if ( (!player) && SECURITY->exist_player(str) )
        {
            add_punishment(str, SPELL_BANNED); 
            (WOR_OBJECTS+"council_log_book")->update_log_book(my_time() + 
               capitalize(banner) + " has banned " + capitalize(str) + 
              " from using the guild's spells.\n");
            tp->catch_msg("Ok.\n");
            return 1;
        }
        else if (is_worshipper(player))
        {
            exec_spell_banned(player);
            (WOR_OBJECTS+"council_log_book")->update_log_book(my_time() + 
                capitalize(banner) + " has banned " + capitalize(str) + 
               " from using the guild's spells.\n");
            tp->catch_msg("Ok.\n");
            return 1;
        } 
        else
        {
            NF("Either player doesn't exist or is not a Worshipper.\n");
            return 0;
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

int 
record_expel_player(string str)
{
    object tp, player;
    string banner;

    tp = TP;

    if (!stringp(str)) {
        notify_fail("Expel whom?\n"); 
        return 0;
    }

    banner = tp->query_real_name();
    str = lower_case(str); 

    if (is_council_member(banner) || is_calian_wiz(tp) ) 
    {
        if (!check_earlier_command(query_verb(), banner, str)) {
             write("Someone else will now have to " + 
                   "issue this same command, in this reboot, " +
                   "for it to be carried through.\n");
             return 1;
        }
        player = find_living(str);
        if ( (!player) && SECURITY->exist_player(str) )
        {
            add_punishment(str, EXPULSION); 
            (WOR_OBJECTS+"council_log_book")->update_log_book(my_time() + 
               capitalize(banner) + " has expelled " + capitalize(str) + 
               " from the guild.\n");
            tp->catch_msg("Ok.\n");
            return 1;
        }
        else if (is_worshipper(player))
        {
            exec_expel_player(player);
            (WOR_OBJECTS+"council_log_book")->update_log_book(my_time() + 
            capitalize(banner) + " has expelled " + capitalize(str) + 
            " from the guild.\n");
            tp->catch_msg("Ok.\n");
            return 1;
        } 
        else
        {
            NF("Either player doesn't exist or is not a Worshipper.\n");
            return 0;
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

int 
record_discharge_player(string str)
{
    object tp, player;
    string banner;

    tp = TP;

    if (!stringp(str)) {
        notify_fail("Discharge whom?\n"); 
        return 0;
    }

    banner = tp->query_real_name();
    str = lower_case(str); 

    if (is_council_member(banner) || is_calian_wiz(tp) ) 
    {
        if (!check_earlier_command(query_verb(), banner, str)) {
             write("Someone else will now have to issue this same " + 
                   "command, in this reboot, for it to be " +
                   "carried through.\n");
             return 1;
        }
        player = find_living(str);
        if ( (!player) && SECURITY->exist_player(str) )
        {
            add_punishment(str, DISCHARGED);
            (WOR_OBJECTS+"council_log_book")->update_log_book(my_time() + 
              capitalize(banner) + " has discharged " + capitalize(str) + 
              " from the guild.\n");
            tp->catch_msg("Ok.\n");
            return 1;
        }
        else if (is_worshipper(player))
        {
            exec_discharge_player(player);
            (WOR_OBJECTS+"council_log_book")->update_log_book(my_time() + 
            capitalize(banner) + " has discharged " + capitalize(str) + 
            " from the guild.\n");
            tp->catch_msg("Ok.\n");
            return 1;
        } 
        else
        {
            NF("Either player doesn't exist or is not a Worshipper.\n");
            return 0;
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

int
record_remove_punish(string str)
{
    object tp, player;
    string banner;

    tp = TP;

    if (!stringp(str)) {
        notify_fail("Remove punishment from whom?\n"); 
        return 0;
    }

    banner = tp->query_real_name();
    if (is_council_member(banner) || is_calian_wiz(tp) ) 
    {
        str = lower_case(str);
        player = find_living(str);
        if ( (!player) && SECURITY->exist_player(str) )
        {
            add_punishment(str, REMOVE_PUNISHMENTS); 
            (WOR_OBJECTS+"council_log_book")->update_log_book(my_time() + 
             capitalize(banner) + " has removed all punishment from " + 
             capitalize(str) + ".\n");
            tp->catch_msg("Ok.\n");
            return 1;
        }
        else if (player)
        {
            exec_remove_punish(player);
            (WOR_OBJECTS+"council_log_book")->update_log_book(my_time() + 
            banner + " has removed all punishment from " + str + ".\n");
            tp->catch_msg("Ok.\n");
            return 1;
        } 
        else
        {
            NF("No such player exists!\n");
            return 0;
        }
    }
    else
    {
        NF("You do not have the authority to do that.");
        return 0;
    }    

}

int
filter_string(mixed s)
{
    return stringp(s);
}

