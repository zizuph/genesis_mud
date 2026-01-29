
/*
   Code for all of the functions used in the Calian Council, 
   for doing various possible punishments or rewards on players,
   and also adding / removing members from the council etc.
   Assistance from Elessar of Gondor in allowing
   inspection of some of their council code.

   Coded by Maniac 

   April/May 1994

  History: 
          23-26/7/01      added "glass medallion" list     Maniac 
           3/6/00      enemy info list = enemy list        Maniac
          12/2/00      optimisations                       Maniac
          29/7/96      updates and bug fix                 Maniac
          20/6/96      'more'ing improved                  Maniac
           4/6/96       necessary to enter enemy info      Maniac 
           31/5/96      query_prevent_shadow added         Maniac 
           4/4/96       times for council actions          Maniac
           16/3/96      enemy info functions added         Maniac
           13/3/96      create function used to set stuff up,
                        separated from councilroom1        Maniac
           22.12.95     double commands added              Maniac
           15.11.94     Bug in leave() dealt with          Maniac
            9.01.95     query_wiz_dom for query_domain     Maniac
           16.02.95     trunc_skill modified               Maniac
           11.03.95     calian_code.c spliced              Glykron
           28.3.95      enemies of Calia code added        Maniac     
           16.6.95      query_enemy_list added             Maniac
           26.6.95      remove not existing players 
                        from lists on creation             Maniac
           17/7/95      minor modification                 Maniac
          27/10/95      honourable discharge added         Maniac
*/

#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <std.h>
#include "defs.h"
#include CALIAN_HEADER
#include COUNCIL_HEADER

#define MAX_ENEMIES 100
#define ENEMY_INFO_DIR (CRPALACE_TEXTS+"enemy_info/")
#define EDIT "/obj/edit"
#define MESSAGE_MAX_CHARS 7200
#define MIN_TIME_BETWEEN_EDITS 900
#define CALIAN_COUNCIL_S_EDITING "_calian_council_s_editing"

#pragma save_binary
#pragma no_inherit

inherit CRPALACE_SPECIALS + "calian_code";


// Prototypes 

string *    query_enemy_list(); 
int         remove_council_member(string str);
string *    query_have_glass_medallion();
void        remove_has_glass_medallion(string player_name);

// Global variables 
string *enemies = ({ }); 
mapping punishments = ([ ]); /* This actually holds rewards and honourable
                                discharges from the guild too */
string *have_glass_medallion = ({ }); 
mapping council_slots = ([ ]);

static mixed earlier_commands = ({ });
static mapping recently_edited = ([ ]);



// Functions 

int 
query_prevent_shadow() 
{
    return 1;
}


string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}

public void
log_council_event(string description)
{
    OBJECT("council_log_book")->update_log_book(my_time() + description + "\n");
}

/* 
 * Function:     check_earlier_command.
 * Description:  Someone has tried to issue an secured command (e.g. "expel"). 
 * returns 1 if it has been issued before by someone else (i.e. it may   
 * now be carried out); returns 0 if it has been issued before by the same 
 * person; (i.e. it may not yet carried out).  record command and return 0 
 * if it has not been previously issued (so someone can confirm it in the 
 * future). 
 */
int
check_earlier_command(string verb, string doer, string to)
{
    mixed e;
    int marker = -1;
    int i;
    mixed to_add;

    // Wizards don't need to be checked
    if (find_player(lower_case(doer))->query_wiz_level())
    {
        return 1;
    }
    
    to_add = ({verb, doer, to});
    for (i = 0; i < sizeof(earlier_commands); i++) {
        e = earlier_commands[i];
        if ((e[0] == verb) && (e[1] != doer) && (e[2] == to)) 
            marker = i; 
        else if ((e[0] == verb) && (e[1] == doer) && (e[2] == to))
            to_add = ({ });
    }

    if (marker > -1) {
        earlier_commands = exclude_array(earlier_commands, marker, marker);
        return 1; 
    }

    if (sizeof(to_add) == 3) 
        earlier_commands += ({ to_add });
 
    return 0;
}


/* 
 * Function:    see_pending_commands.
 * Description: show council member what commands need to be confirmed. 
 */
int
see_pending_commands()
{
     int i;

     if (!sizeof(earlier_commands)) {
         notify_fail("No commands requiring confirmation have been issued.\n");
         return 0;
     }

     write("The following commands require confirmation (i.e. someone " +
           "else must enter the given command again in order for it " +
           "to be carried out):\n");

     for (i = 0; i < sizeof(earlier_commands); i++) 
         write(earlier_commands[i][0] + " by " + earlier_commands[i][1] +
               " on " + earlier_commands[i][2] + ".\n");

     return 1;
}


/* 
 * Function:    cancel_pending_commands
 * Description: Council member may cancel any of his/her commands
 *              that await confirmation. 
 */ 
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
        if (earlier_commands[i][1] != capitalize(tp->query_real_name()))
             ec += ({ earlier_commands[i] });

    earlier_commands = ec;

    return 1;
}

/*
 * Function:    query_council_members
 * Description: Returns a list of the current council members.
 */
public string *
query_council_members()
{
    string * results = map(map(m_values(council_slots), lower_case), capitalize);
    results -= ({ 0 });
    
    return results;
}

public string
get_council_member_at_slot(int slot)
{
    if (slot < 0 || slot >= COUNCIL_MAX_SIZE)
    {
        return 0;
    }
    
    return council_slots[slot];
}

void
remove_non_existant()
{
    int i;
    string *ind, *elist;

    string * council_members = query_council_members();
    foreach (string name : council_members)
    {
        if (!SECURITY->exist_player(lower_case(name)))
        {
            remove_council_member(lower_case(name));
        }
    }     

    elist = query_enemy_list(); 
    for (i = 0; i < sizeof(elist); i++)
        if (!SECURITY->exist_player(lower_case(elist[i]))) {
            if (file_size(ENEMY_INFO_DIR + elist[i]) > -1)
                rm(ENEMY_INFO_DIR + elist[i]);
        }

    ind = m_indexes(punishments);
    for (i = 0; i < sizeof(ind); i++)
        if (!SECURITY->exist_player(lower_case(ind[i])))
            punishments = m_delete(punishments, ind[i]);

    foreach (string name : query_have_glass_medallion())
    {
        if (!SECURITY->exist_player(lower_case(name)))
        {
            remove_has_glass_medallion(name);
        }
    }
    
    save_object(COUNCIL);
}

public void
initialize_council_voting()
{
    COUNCIL_VOTING_MANAGER->start_votes();
}

void
create()
{
    seteuid(getuid());
    restore_object(COUNCIL);
    set_alarm(1.0, 0.0, remove_non_existant);
    set_alarm(1.0, 0.0, initialize_council_voting);
}


string 
query_council()
{
    string cstr;
    int x; 

    string * council_members = query_council_members();
    if (sizeof(council_members) == 0)
        cstr = "The Calian Council does not currently have any members.\n";
    else if (sizeof(council_members) == 1) 
        cstr = "The Calian Council currently has the following member: " +
            council_members[0] + ".\n";
    else
    {
        cstr = "The Calian Council currently has the following members: "; 
        cstr += (COMPOSITE_WORDS(council_members) + ".\n"); 
    }

    return cstr;
}


int 
is_council_member(string str)
{
    if (!str)
        return 0;

    return IN_ARRAY(capitalize(lower_case(str)), query_council_members());
}


/* return array giving the enemies of Calia */
string
*query_enemy_list()
{
    return get_dir(ENEMY_INFO_DIR);
}


/* return the enemies of Calia as a string */
string
query_enemies()
{
    string *elist;

    if (!sizeof(elist = query_enemy_list())) 
        return "There are currently no listed enemies of Calia.\n";

    return ("The following people are listed as enemies of Calia: " 
           + COMPOSITE_WORDS(elist) + ".\n"); 
}


int
is_enemy(string nm)
{
    return
        (file_size(ENEMY_INFO_DIR + capitalize(lower_case(nm)))
         != -1);
}


int
see_enemies()
{
    write(query_enemies());
    return 1;
}


void
now_do_ceinfo(object tp, string ename)
{
    if (!objectp(tp)) 
        return;

    set_this_player(tp); 
    this_object()->add_enemy_info(ename); 
}


int 
add_enemy(string str)
{
    object tp = TP; 
    string adder, *elist;
 
    if (!str) 
        return 0;

    adder = capitalize(tp->query_real_name());
    seteuid(getuid());

    if (sizeof(elist = query_enemy_list()) >= MAX_ENEMIES) {
        NF("Too many enemies, about time you updated the list.\n");
        return 0;
    }

    if (!(SECURITY->exist_player(str = lower_case(str))))
    {
        NF("No such player!\n");
        return 0;
    }

    if (is_council_member(adder) || is_calian_wiz(tp) )
    {
        if (member_array(str = capitalize(str), elist) > -1) {
             NF("That player is already on the enemy list.\n");
             return 0;
        }

        write_file(ENEMY_INFO_DIR + str, 
            "Information about this enemy is yet to be added.\n"); 
        log_council_event(str + " has been added to the list of enemies by " 
            + adder + ".");
        tell_object(tp, "Ok.\n");
        set_alarm(0.0, 0.0, &now_do_ceinfo(tp, str)); 
        return 1;
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}


int 
remove_enemy(string str)
{
    object tp = TP;
    string remover, *elist;

    if (!str)
        return 0;

    remover = capitalize(tp->query_real_name());
    seteuid(getuid());

    if (!sizeof(elist = query_enemy_list()))
    {
         NF("No-one on the enemy list yet!\n");
         return 0;
    } 

    if (!SECURITY->exist_player(str = lower_case(str)) )
    {
        NF("No such player!\n");
        return 0;
    }

    if (is_council_member(remover) || is_calian_wiz(tp) ) 
    { 
        if (member_array(str = capitalize(str), elist) > -1) 
        {
            if (file_size(ENEMY_INFO_DIR + str) > -1)
                rm(ENEMY_INFO_DIR + str);
            log_council_event(str + " has been removed from the list of enemies "
                + "by " + remover + ".");
            tell_object(tp, "Ok.\n");
            return 1;
        }
        else
        {
            NF("No such listed enemy!\n");
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
see_council(string str)
{ 
    tell_object(this_player(), query_council());
    return 1;
}

public int
add_council_member_internal(string person)
{
    if (!strlen(person))
    {
        return 0;
    }
    
    int bSuccess = 0;
    person = capitalize(lower_case(person));
    if (IN_ARRAY(person, query_council_members()))
    {
        // Person is already in the council.
        return 0;
    }
    for (int index = 0; index < COUNCIL_MAX_SIZE; ++index)
    {
        // Find the first available slot and set the council member
        // there
        if (!council_slots[index])
        {
            council_slots[index] = person;
            bSuccess = 1;
            break;
        }
    }
    if (bSuccess)
    {
        save_object(COUNCIL);
    }
    return bSuccess;
}

int 
add_council_member(string str)
{
    object tp = TP; 
    string adder;
 
    if (!str) return 0;
    adder = capitalize(tp->query_real_name());
    str = capitalize(lower_case(str));
    seteuid(getuid());

    if (sizeof(query_council_members()) >= COUNCIL_MAX_SIZE)
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
        if (!check_earlier_command(query_verb(), adder, str)) {
             write("Someone else will now have to issue this same " + 
                   "command, in this reboot, for it to be " +
                   "carried through.\n");
             return 1;
        }
        if (!add_council_member_internal(str))
        {
            NF("Could not add " + str + " to the Calian Council. Please notify "
                + "the Guildmaster.\n");
            return 0;
        }
        log_council_event(str + " has been added to the Calian Council by "
            + adder + ".");
        save_object(COUNCIL);
        tell_object(tp, "Ok.\n");
        return 1;
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

public int
remove_council_member_internal(string person)
{
    if (!strlen(person))
    {
        return 0;
    }
    
    int bSuccess = 0;
    person = capitalize(lower_case(person));
    for (int index = 0; index < COUNCIL_MAX_SIZE; ++index)
    {
        if (council_slots[index] == person)
        {
            council_slots[index] = 0;
            bSuccess = 1;
            break;
        }
    }
    
    if (bSuccess)
    {
        save_object(COUNCIL);    
    }
    return bSuccess;
}

int 
remove_council_member(string str)
{
    object tp = TP;
    string remover;

    if (!str)
	return 0;
    remover = capitalize(tp->query_real_name());
    str = capitalize(lower_case(str));
    seteuid(getuid());
    
    if (sizeof(query_council_members()) == 0)
    {
         NF("No-one in the council yet!\n");
         return 0;
    } 

    if (is_council_member(remover) || is_calian_wiz(tp) ) 
    { 
        if (!IN_ARRAY(str, query_council_members()))
        {
            NF("No such player on the council!\n");
            return 0; 
        }          
        if (!check_earlier_command(query_verb(), remover, str)) {
             write("Someone else will now have to issue this same " + 
                   "command, in this reboot, for it to be " +
                   "carried through.\n");
             return 1;
        }
        remove_council_member_internal(str);   
        log_council_event(str + " has been removed from the Calian Council "
            + "by " + remover + ".");              
        tell_object(tp, "Ok.\n");
        return 1;
    }

    NF("You do not have the authority to do that.\n");
    return 0;
}

int
is_tunnel_access_banned(object player)
{
    if ((player->query_skill(PUNISHMENT) & NO_TUNNEL_ACCESS) > 0)
    {
        return 1;
    }
    return 0;
}

int
is_vote_banned(object player)
{
    if ((player->query_skill(PUNISHMENT) & NO_VOTE) > 0)
    {
        return 1;
    }
    return 0;
}

int
is_rack_banned(object player)
{
    if ((player->query_skill(PUNISHMENT) & NO_RACK) > 0)
    {
        return 1;
    }
    return 0;
}

int 
is_swarm_banned(object player)
{
    int base_punishment = player->query_skill(PUNISHMENT) & 0x07;
    if (base_punishment == NO_SWARM) return 1;
    else return 0;
}


int 
is_upstairs_banned(object player)
{
    int base_punishment = player->query_skill(PUNISHMENT) & 0x07;
    if (base_punishment == NO_SANCTUARY) return 1;
    else return 0;
}


int 
is_train_banned(object player)
{
    int base_punishment = player->query_skill(PUNISHMENT) & 0x07;
    if (base_punishment == NO_TRAINING) return 1;
    else return 0;
}

int 
is_discharged(object player)
{
    int base_punishment = player->query_skill(PUNISHMENT) & 0x07;
    if (base_punishment == DISCHARGED) return 1;
    else return 0;
}

int 
is_expelled(object player)
{
    int base_punishment = player->query_skill(PUNISHMENT) & 0x07;
    if (base_punishment == EXPULSION) return 1;
    else return 0;
}



/* 
 * These next six functions execute punishments/rewards on players who
 * are currently logged on, also informing the player of the punishment.
 */


/*
 * Function:     exec_ban_vote
 * Description:  Ban a currently logged on player from being able to vote
 */ 
void 
exec_ban_vote(object player)
{
    string player_name;

    seteuid(getuid());
    player_name = capitalize(player->query_real_name());
    int skill_value = player->query_skill(PUNISHMENT);
    skill_value = skill_value | NO_VOTE;
    player->set_skill(PUNISHMENT, skill_value);
    set_alarm(1.5, 0.0, &tell_object(player,
        "You have been banned by the Calian Council from " +
        "voting.\n"));
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
}

/*
 * Function:     exec_ban_rack
 * Description:  Ban a currently logged on player from being able to use
 *               the racks.
 */ 
void 
exec_ban_rack(object player)
{
    string player_name;

    seteuid(getuid());
    player_name = capitalize(player->query_real_name());
    int skill_value = player->query_skill(PUNISHMENT);
    skill_value = skill_value | NO_RACK;
    player->set_skill(PUNISHMENT, skill_value);
    set_alarm(1.5, 0.0, &tell_object(player,
        "You have been banned by the Calian Council from " +
        "using the racks.\n"));
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
}

/*
 * Function:     exec_ban_tunnel_access
 * Description:  Ban a currently logged on player from accessing the
 *               Calian tunnels.
 */ 
void 
exec_ban_tunnel_access(object player)
{
    string player_name;

    seteuid(getuid());
    player_name = capitalize(player->query_real_name());
    int skill_value = player->query_skill(PUNISHMENT);
    skill_value = skill_value | NO_TUNNEL_ACCESS;
    player->set_skill(PUNISHMENT, skill_value);
    set_alarm(1.5, 0.0, &tell_object(player,
        "You have been banned by the Calian Council from " +
        "using the Calian tunnels.\n"));
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
}

/*
 * Function:     exec_ban_upstairs
 * Description:  Ban a currently logged in player from entering private 
 *               Calian rooms.
 */ 
void 
exec_ban_upstairs(object player)
{
    string player_name;

    seteuid(getuid());
    player_name = capitalize(player->query_real_name());
    int skill_value = player->query_skill(PUNISHMENT);
    skill_value = (skill_value & 0xF8) | NO_SANCTUARY;
    player->set_skill(PUNISHMENT, skill_value);
    set_alarm(1.5, 0.0, &tell_object(player,
        "You have been banned by the Calian Council from " +
        "using private Calian rooms.\n"));
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
}


/*
 * Function:     exec_stop_train
 * Description:  Stop a currently logged in player from being able 
 *               to train at the Calian guild.  
 */ 
void 
exec_stop_train(object player)
{
    string player_name;

    seteuid(getuid());
    player_name = capitalize(player->query_real_name());
    int skill_value = player->query_skill(PUNISHMENT);
    skill_value = (skill_value & 0xF8) | NO_TRAINING;
    player->set_skill(PUNISHMENT, skill_value);
    set_alarm(1.5, 0.0, &tell_object(player,
        "You have been banned by the Calian Council from " +
        "using the guild's training facilities.\n"));

    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
}


/*
 * Function:     exec_stop_swarm
 * Description:  Stop a currently logged in player from being able to 
 *               swarm or maul.  
 */ 
void 
exec_stop_swarm(object player)
{
    string player_name;

    seteuid(getuid());
    player_name = capitalize(player->query_real_name());
    int skill_value = player->query_skill(PUNISHMENT);
    skill_value = (skill_value & 0xF8) | NO_SWARM;
    player->set_skill(PUNISHMENT, skill_value);
    set_alarm(1.5, 0.0, &tell_object(player,
        "You have been banned by the Calian Council from " +
        "using the swarm skill.\n"));

    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
}


/*
 * Function:     exec_stop_train
 * Description:  Stop a currently logged in player from being able to 
 *               swarm or maul.  
 */ 
void 
exec_expel_player(object player)
{
    string player_name;
    object tp = this_player();

    seteuid(getuid());
    player_name = capitalize(player->query_real_name());
    int skill_value = player->query_skill(PUNISHMENT);
    skill_value = (skill_value & 0xF8) | EXPULSION;
    player->set_skill(PUNISHMENT, skill_value);
    set_alarm(1.5, 0.0, &tell_object(player,
        "You have been expelled from the Calian guild " +
        "by the Calian Council.\n"));
    leave("trust", player, "expulsion");
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
}


/*
 * Function:     exec_discharge_player
 * Description:  Discharge a currently logged in player from the guild.
 */ 
void 
exec_discharge_player(object player)
{
    string player_name;
    object tp = this_player();

    seteuid(getuid());
    player_name = capitalize(player->query_real_name());
    int skill_value = player->query_skill(PUNISHMENT);
    skill_value = (skill_value & 0xF8) | DISCHARGED;
    player->set_skill(PUNISHMENT, skill_value);
    set_alarm(1.5, 0.0, &tell_object(player,
        "You have been honourably discharged from the Calian guild " +
        "by the Calian Council.\n"));
    leave("trust", player, "discharge");
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
}


/*
 * Function:     exec_remove_punish
 * Description:  Remove punishment from a currently logged in player. 
 */ 
void 
exec_remove_punish(object player)
{
    string player_name;

    seteuid(getuid());
    player_name = capitalize(player->query_real_name());
    player->set_skill(PUNISHMENT, NO_PUNISHMENT);
    set_alarm(1.5, 0.0, &tell_object(player,
        "The Calian Council has removed any punishments " +
        "that it has previously placed on you.\n"));
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
}


/*
 * Function:     exec_add_reward
 * Description:  Reward a currently logged in player. 
 */ 
void 
exec_add_reward(object player)
{
    string player_name;
    int reward_value;

    seteuid(getuid());
    player_name = capitalize(player->query_real_name());
    reward_value = player->query_skill(REWARD);
    reward_value++;
    player->set_skill(REWARD, reward_value);
    set_alarm(1.5, 0.0, &tell_object(player,
        "The Calian Council has rewarded you for " +
        "being a true Calian. You have been " +
        "decorated.\n"));
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
}


/*
 * Function:    carry_out_punishments
 * Description: Carry out any recorded punishments on a player 
 *              who has just logged in (called from the Calian
 *              shadow).  
 */ 
void 
carry_out_punishments(object player)
{
    string player_name;
    
    player_name = capitalize(player->query_real_name());
    seteuid(getuid());
 
    if (punishments[player_name]) {
        if (punishments[player_name] == REMOVE_PUNISHMENTS)
        {
            if (player->query_skill(PUNISHMENT) != NO_PUNISHMENT)
            exec_remove_punish(player);
        }
        else if (punishments[player_name] == NO_TUNNEL_ACCESS)
            exec_ban_tunnel_access(player);
        else if (punishments[player_name] == NO_SANCTUARY)
            exec_ban_upstairs(player);
        else if (punishments[player_name] == NO_TRAINING)
            exec_stop_train(player);
        else if (punishments[player_name] == NO_SWARM) 
            exec_stop_swarm(player);
        else if (punishments[player_name] == EXPULSION)
            exec_expel_player(player);
        else if (punishments[player_name] == DISCHARGED)
            exec_discharge_player(player);
        else if (punishments[player_name] == ADD_REWARD)
            exec_add_reward(player);
        else if (punishments[player_name] == NO_VOTE)
            exec_ban_vote(player);
        else if (punishments[player_name] == NO_RACK)
            exec_ban_rack(player);
    }
}


/*
 * Function:     add_punishment
 * Description:  Record a punishment for a player who 
 *               isn't currently logged in. The punishment
 *               is carried out when s/he logs in next. 
 */ 
void 
add_punishment(string punished, int punishment)
{
    seteuid(getuid());
    /* only one punishment allowed at a time */
    if (punishments[punished])
        punishments = m_delete(punishments, punished);
    punishments += ([ punished : punishment ]);
    save_object(COUNCIL);
}



/* 
 * These next six functions do the following: 
 * Record in council log book that player has been punished, and what 
 * the punishment is. If player is on at the time, effect the 
 * punishment, but if player is not on, add the punishment in council 
 * save file so player is punished when logging on
 */

/*
 * Function:     record_ban_vote
 * Description:  Action function for council members to ban
 *               a Calian from being able to vote
 */ 
int 
record_ban_vote(string str)
{
    object tp, player;
    string banner;

    tp = TP;

    if (!stringp(str)) {
        notify_fail("Ban whom?\n"); 
        return 0;
    }

    banner = capitalize(tp->query_real_name());
    if (is_council_member(banner) || is_calian_wiz(tp) ) 
    {
        str = lower_case(str);
        player = find_living(str);
        str = capitalize(str);
        if ( (!player) && SECURITY->exist_player(lower_case(str)) )
        {
            add_punishment(str, NO_VOTE); 
            log_council_event(banner + " has banned " + str + " from "
                + "being able to vote.");
            tell_object(tp, "Ok.\n");
            return 1;
        }
        else if (is_calian(player))
        {
            exec_ban_vote(player);
            log_council_event(banner + " has banned " + str + " from "
                + "being able to vote.");
            tell_object(tp, "Ok.\n");
            return 1;
        } 
        else
        {
            NF("Either player doesn't exist or is not Calian.\n");
            return 0;
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    } 
}

/*
 * Function:     record_ban_rack
 * Description:  Action function for council members to ban
 *               a Calian from being able to use the racks
 */ 
int 
record_ban_rack(string str)
{
    object tp, player;
    string banner;

    tp = TP;

    if (!stringp(str)) {
        notify_fail("Ban whom?\n"); 
        return 0;
    }

    banner = capitalize(tp->query_real_name());
    if (is_council_member(banner) || is_calian_wiz(tp) ) 
    {
        str = lower_case(str);
        player = find_living(str);
        str = capitalize(str);
        if ( (!player) && SECURITY->exist_player(lower_case(str)) )
        {
            add_punishment(str, NO_RACK); 
            log_council_event(banner + " has banned " + str + " from "
                + "using the racks.");
            tell_object(tp, "Ok.\n");
            return 1;
        }
        else if (is_calian(player))
        {
            exec_ban_rack(player);
            log_council_event(banner + " has banned " + str + " from "
                + "using the racks.");
            tell_object(tp, "Ok.\n");
            return 1;
        } 
        else
        {
            NF("Either player doesn't exist or is not Calian.\n");
            return 0;
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    } 
}

/*
 * Function:     record_ban_tunnel_access
 * Description:  Action function for council members to ban
 *               a Calian from using the tunnels
 */ 
int 
record_ban_tunnel_access(string str)
{
    object tp, player;
    string banner;

    tp = TP;

    if (!stringp(str)) {
        notify_fail("Ban whom?\n"); 
        return 0;
    }

    banner = capitalize(tp->query_real_name());
    if (is_council_member(banner) || is_calian_wiz(tp) ) 
    {
        str = lower_case(str);
        player = find_living(str);
        str = capitalize(str);
        if ( (!player) && SECURITY->exist_player(lower_case(str)) )
        {
            add_punishment(str, NO_TUNNEL_ACCESS); 
            log_council_event(banner + " has banned " + str + " from using "
                + "the Calian tunnels.");
            tell_object(tp, "Ok.\n");
            return 1;
        }
        else if (is_calian(player))
        {
            exec_ban_tunnel_access(player);
            log_council_event(banner + " has banned " + str + " from using "
                + "the Calian tunnels.");
            tell_object(tp, "Ok.\n");
            return 1;
        } 
        else
        {
            NF("Either player doesn't exist or is not Calian.\n");
            return 0;
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    } 
}

/*
 * Function:     record_ban_upstairs.
 * Description:  Action function for council members to ban
 *               a Calian from using private guild rooms. 
 */ 
int 
record_ban_upstairs(string str)
{
    object tp, player;
    string banner;

    tp = TP;

    if (!stringp(str)) {
        notify_fail("Ban whom?\n"); 
        return 0;
    }

    banner = capitalize(tp->query_real_name());
    if (is_council_member(banner) || is_calian_wiz(tp) ) 
    {
        str = lower_case(str);
        player = find_living(str);
        str = capitalize(str);
        if ( (!player) && SECURITY->exist_player(lower_case(str)) )
        {
            add_punishment(str, NO_SANCTUARY); 
            log_council_event(banner + " has banned " + str + " from entering "
                + "Calian private rooms.");
            tell_object(tp, "Ok.\n");
            return 1;
        }
        else if (is_calian(player))
        {
            exec_ban_upstairs(player);
            log_council_event(banner + " has banned " + str + " from entering "
                + "Calian private rooms.");
            tell_object(tp, "Ok.\n");
            return 1;
        } 
        else
        {
            NF("Either player doesn't exist or is not Calian.\n");
            return 0;
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    } 
}


/*
 * Function:     record_ban_upstairs.
 * Description:  Action function for council members to ban
 *               a Calian from using the guild training 
 *               facilities. 
 */ 
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

    banner = capitalize(tp->query_real_name());
    if (is_council_member(banner) || is_calian_wiz(tp) ) 
    {
        str = lower_case(str);
        player = find_living(str);
        str = capitalize(str);
        if ( (!player) && SECURITY->exist_player(lower_case(str)) )
        {
            add_punishment(str, NO_TRAINING); 
            log_council_event(banner + " has banned " + str + " from training "
                + "in this guild.");
            tell_object(tp, "Ok.\n");
            return 1;
        }
        else if (is_calian(player))
        {
            exec_stop_train(player);
            log_council_event(banner + " has banned " + str + " from training "
                + "in this guild.");
            tell_object(tp, "Ok.\n");
            return 1;
        } 
        else
        {
            NF("Either player doesn't exist or is not Calian.\n");
            return 0;
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}


/*
 * Function:     record_stop_swarm
 * Description:  Action function for council members to stop
 *               a Calian from using the swarm or maul 
 *               abilities. 
 */ 
int 
record_stop_swarm(string str)
{
    object tp, player;
    string banner;

    tp = TP;

    if (!stringp(str)) {
        notify_fail("Stop who from swarming?\n"); 
        return 0;
    }

    banner = capitalize(tp->query_real_name());
    if (is_council_member(banner) || is_calian_wiz(tp) ) 
    {
        str = lower_case(str);
        player = find_living(str);
        str = capitalize(str);
        if ( (!player) && SECURITY->exist_player(lower_case(str)) )
        {
            add_punishment(str, NO_SWARM); 
            log_council_event(banner + " has banned " + str + " from using "
                + "the swarm skill.");
            tell_object(tp, "Ok.\n");
            return 1;
        }
        else if (is_calian(player))
        {
            exec_stop_swarm(player);
            log_council_event(banner + " has banned " + str + " from using "
                + "the swarm skill.");
            tell_object(tp, "Ok.\n");
            return 1;
        } 
        else
        {
            NF("Either player doesn't exist or is not Calian.\n");
            return 0;
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}


/*
 * Function:     record_stop_swarm
 * Description:  Action function for council members to expel
 *               a Calian from the guild.
 */ 
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

    banner = capitalize(tp->query_real_name());
    if (is_council_member(banner) || is_calian_wiz(tp) ) 
    {
        if (!check_earlier_command(query_verb(), banner, str)) {
             write("Someone else will now have to " + 
                   "issue this same command, in this reboot, " +
                   "for it to be carried through.\n");
             return 1;
        }
        str = lower_case(str);
        player = find_living(str);
        str = capitalize(str);
        if ( (!player) && SECURITY->exist_player(lower_case(str)) )
        {
            add_punishment(str, EXPULSION); 
            log_council_event(banner + " has expelled " + str + " from the "
                + "guild.");
            tell_object(tp, "Ok.\n");
            return 1;
        }
        else if (is_calian(player))
        {
            exec_expel_player(player);
            log_council_event(banner + " has expelled " + str + " from the "
                + "guild.");
            tell_object(tp, "Ok.\n");
            return 1;
        } 
        else
        { 
            NF("Either player doesn't exist or is not Calian.\n");
            return 0;
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}


/*
 * Function:     record_discharge_player
 * Description:  Action function for council members to give
 *               a Calian an honourable discharge from the guild.
 */ 
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

    banner = capitalize(tp->query_real_name());
    if (is_council_member(banner) || is_calian_wiz(tp) ) 
    {
        if (!check_earlier_command(query_verb(), banner, str)) {
             write("Someone else will now have to issue this same " + 
                   "command, in this reboot, for it to be " +
                   "carried through.\n");
             return 1;
        }
        str = lower_case(str);
        player = find_living(str);
        str = capitalize(str);
        if ( (!player) && SECURITY->exist_player(lower_case(str)) )
        {
            add_punishment(str, DISCHARGED); 
            log_council_event(banner + " has discharged " + str + " from the "
                + "guild.");
            tell_object(tp, "Ok.\n");
            return 1;
        }
        else if (is_calian(player))
        {
            exec_discharge_player(player);
            log_council_event(banner + " has discharged " + str + " from the "
                + "guild.");
            tell_object(tp, "Ok.\n");
            return 1;
        } 
        else
        { 
            NF("Either player doesn't exist or is not Calian.\n");
            return 0;
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}


/*
 * Function:     record_remove_punish
 * Description:  Action function for council members to remove
 *               a punishment from a Calian. 
 */ 
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
   
    banner = capitalize(tp->query_real_name());
    if (is_council_member(banner) || is_calian_wiz(tp) ) 
    {
        str = lower_case(str);
        player = find_living(str);
        str = capitalize(str);
        if ((!player) && SECURITY->exist_player(lower_case(str)))
        {
            add_punishment(str, REMOVE_PUNISHMENTS); 
            log_council_event(banner + " has removed all punishment from "
                + str + ".");
            tell_object(tp, "Ok.\n");
            return 1;
        }
        else if (player)
        {
            exec_remove_punish(player);
            log_council_event(banner + " has removed all punishment from "
                + str + ".");
            tell_object(tp, "Ok.\n");
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


/*
 * Function:     record_remove_punish
 * Description:  Action function for council members to reward
 *               a Calian (improve their insignia). 
 */ 
int 
record_add_reward(string str)
{
    object tp, player;
    string banner;

    tp = TP;

    if (!stringp(str)) {
        notify_fail("Reward whom?\n"); 
        return 0;
    }

    banner = capitalize(tp->query_real_name());
    if (is_council_member(banner) || is_calian_wiz(tp) ) 
    {
        str = lower_case(str);
        player = find_living(str);
        str = capitalize(str);
        if ( (!player) && SECURITY->exist_player(lower_case(str)) )
        {
            add_punishment(str, ADD_REWARD); 
            log_council_event(banner + " has rewarded " + str + " for being "
                + "a true Calian.");
            tell_object(tp, "Ok.\n");
            return 1;
        }
        else if (is_calian(player))
        {
            exec_add_reward(player);
            log_council_event(banner + " has rewarded " + str + " for being "
                + "a true Calian.");
            tell_object(tp, "Ok.\n");
            return 1;
        } 
        else
        {
            NF("Either player doesn't exist or is not Calian.\n");
            return 0;
        }
    }
    else
    {
        NF("You do not have the authority to do that.");
        return 0;
    }
}


/* 
 * Function:     add_enemy_info
 * Description:  Action function for a Council member to add information 
 *               about an enemy.
 */
int
add_enemy_info(string str)
{
    string adder, *elist;
    object tp = this_player();
    int last_edit_time;

    if (!stringp(str)) {
        notify_fail("Add enemy info about what player?\n"); 
        return 0;
    }

    adder = tp->query_real_name();
    if (is_council_member(adder) || is_calian_wiz(tp)) 
    {
        if (SECURITY->exist_player(str = lower_case(str)))
        {
            if (!is_enemy(str = capitalize(str))) {
                NF("That player is not an enemy of Calia!\n");
                return 0;
            }
            if (last_edit_time = recently_edited[str]) {
                if ((time() - last_edit_time) < MIN_TIME_BETWEEN_EDITS) {
                    tell_object(tp, "Someone has edited that enemy's info " +
                      "within the last 15 minutes, a re-edit will not "+
                      "possible until that time has elapsed. This is " +
                      "to lower the risk of abuse of the system. "+
                      "Sorry for any inconvenience.\n");
                    return 1;
                }
                else 
                    recently_edited = m_delete(recently_edited, str); 
            }

            tp->add_prop(CALIAN_COUNCIL_S_EDITING, str);
            set_this_player(tp);
            tell_object(tp, "You may now enter enemy info about " + 
                          str + ". Please do not exceed " + 
                          MESSAGE_MAX_CHARS/80 + " lines " + 
                          "(" + MESSAGE_MAX_CHARS + " characters).\n");
            seteuid(getuid());
            clone_object(EDIT)->edit("done_editing");
            return 1;
        }
        else
        {
            NF("No such player!\n");
            return 0;
        }
    }
    else
    {
        NF("You do not have the authority to do that.");
        return 0;
    }
}


/* 
 * Function: done_editing
 * Description: Called when a Council member has done editing the 
 *              information about an enemy. This adds it to the
 *              directory of enemy information. 
 */
void
done_editing(string message)
{
    object tp = this_player();
    string nm;

    if (message == "")
        return;

    if (strlen(message) > MESSAGE_MAX_CHARS) {
        tell_object(tp, "That info was too long! It has not been added. " +
                      "Please try again and enter shorter info about " +
                      "yourself.\n");
        return;
    }

    if (!stringp(nm = tp->query_prop(CALIAN_COUNCIL_S_EDITING))) {
         tell_object(tp, "Hmm, technical problems, please re-enter that.\n"); 
         return;
    }

    recently_edited += ([ nm : time() ]);
    tp->remove_prop(CALIAN_COUNCIL_S_EDITING); 

    nm = ENEMY_INFO_DIR + nm;

    seteuid(getuid());
    if (file_size(nm) > -1)
        rm(nm);

    write_file(nm, message);
    tell_object(tp, "The enemy info you entered has now been added.\n"); 
}


/*
 * Function:     see_enemy_info
 * Description:  Action function to read information about an enemy
 *               of the guild or list all enemies if the parameter
 *               is 0 or an empty string. 
 */ 
int
see_enemy_info(string str)
{
    object tp = this_player();
    string fn, *einf;
    int i;

    seteuid(getuid());

    if (!stringp(str)) {
        einf = query_enemy_list(); 
        tp->more("Information exists about the following enemies:\n" + 
            sizeof(einf) ? sprintf("%-#80s\n", implode(einf, "\n")) : 
            "None.\n"); 
        return 1;
    }

    if (SECURITY->exist_player(str = lower_case(str))) {
        fn = (ENEMY_INFO_DIR + (str = capitalize(str))); 
        if (file_size(fn) == -1) {
             NF("No enemy info on that player!\n"); 
             return 0;
        }
        tp->more("The following is written about " + str + 
                 ":\n" + read_file(fn)); 
        return 1;
    }
    else {
        NF("No such player!\n");
        return 0;
    }
}


int filter_string(mixed s) { return stringp(s); }


/* 
 * Function:     add_has_glass_medallion 
 * Description:  Adds the player's name to the list of those 
 *               with a glass medallion. 
 */ 
void
add_has_glass_medallion(string player_name) 
{ 
    if (member_array(player_name = capitalize(lower_case(player_name)), 
                     have_glass_medallion) > -1) 
        return; 

    have_glass_medallion = have_glass_medallion + ({ player_name }); 
    save_object(COUNCIL); 
} 


/* 
 * Function:     remove_has_glass_medallion 
 * Description:  Removes the player's name from the list of those 
 *               with a glass medallion. 
 */ 
void 
remove_has_glass_medallion(string player_name) 
{ 
    if (member_array(player_name = capitalize(lower_case(player_name)), 
                     have_glass_medallion) == -1) 
        return; 
    
    have_glass_medallion = have_glass_medallion - ({ player_name }); 
    save_object(COUNCIL); 
} 


/* 
 * Function:     query_has_glass_medallion 
 * Description:  Should return whether 
 */ 
int 
query_has_glass_medallion(string player_name) 
{ 
    return (member_array(capitalize(lower_case(player_name)), 
                         have_glass_medallion) > -1); 
} 


/* 
 * Function:      query_have_glass_medallion 
 * Description:   Should return a list of names of players who 
 *                have a glass medallion. 
 * Returns:       string * - names of players who have a glass medallion. 
 */ 
string *
query_have_glass_medallion() 
{ 
    return have_glass_medallion; 
} 


/* 
 * Function:       list_glass_medallion_owners 
 * Description:    Lists the owners of glass medallions. 
 * Returns:        int - whether successful. 
 */ 
int 
list_glass_medallion_owners(string str) 
{ 
    if (!is_council_member(this_player()->query_real_name()) && 
        !is_calian_wiz(this_player())) 
    { 
        notify_fail("Heheh, none of your business!\n"); 
        return 0; 
    } 

    write("The following people had rack points low enough " + 
          "for a glass medallion when they last left the realms: " + 
          COMPOSITE_WORDS(sort_array(query_have_glass_medallion())) + 
          ".\n"); 
    return 1; 
} 
