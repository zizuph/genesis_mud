
/*
 * ~Calia/fireball/special/schedule_handler.c
 *
 * This module manages the setting up of teams and booking of fireball
 * matches. It is used whenever a player registers or unregisters 
 * a team, or declares the players in that team. 
 * It informs the game handler of the details of the next match at the 
 * appropriate time. It is informed by the game handler when a match 
 * finishes, then determines the next match and sends the details through. 
 * 
 * Coded by Maniac@Genesis, 1997/1998/1999
 *
 * Copyright (C) Miguel Leith 1997/1998/1999
 *
 * Removed the maximum size limit on the quests, so all players can
 * finish all Fireball quests, Cherek September 2020
 */ 

#pragma save_binary
#pragma strict_types
#pragma no_inherit

#include "defs.h"
#include FIREBALL_HEADER

inherit "/std/object"; 
inherit FIREBALL_UTILS; 

#include <stdproperties.h>
#include <language.h>
#include <macros.h>
#include <files.h>
#include <money.h>
#include <composite.h>
#include <ss_types.h>

/* Retain a team record for this number of seconds 
   since the last time it was active.  */ 
#define DURATION_RETAIN_TEAM  3600 

#define MAX_TEAM_NAME_STRLEN 45 
#define TEAM_STAT_DIFF_MAX 10000 

/* Team record indices */ 
#define FIREBALL_TR_TEAM_NAME 0
#define FIREBALL_TR_LAST_TIME_ACTIVE 1
#define FIREBALL_TR_PLAYERS 2 

/* Schedule record indices */ 
#define FIREBALL_SR_HOME_CAPTAIN 0
#define FIREBALL_SR_HOME_TEAM_NAME 1 
#define FIREBALL_SR_HOME_TEAM 2 
#define FIREBALL_SR_AWAY_CAPTAIN 3 
#define FIREBALL_SR_AWAY_TEAM_NAME 4
#define FIREBALL_SR_AWAY_TEAM 5
#define FIREBALL_SR_TRAINING_MATCH 6

private void start_next_match(); 
private void garbage_collect_teams(); 

static int wait_alarm; 

mixed schedule; 
mapping team_record; 

void
create_object()
{
    set_name("scheduler"); 
    seteuid(getuid()); 
    restore_object(FIREBALL_SCHEDULE_SAVE);  

    if (!team_record) 
        team_record = ([ ]); 

    if (!schedule)
        schedule = ({ }); 

    garbage_collect_teams(); 
    set_alarm(1.0, 0.0, start_next_match); 
}


/*
 * Function:      query_match_booked_for()
 * Description:   returns -1 if a there is no booked match involving  
 *                the named player as captain, otherwise returns the 
 *                index of the schedule array containing the match 
 *                record. 
 */ 
int
query_match_booked_for(string player_name)
{
    int i;

    if (!stringp(player_name)) 
        return -1;

    for (i = 0; i < sizeof(schedule); i++) 
        if ((schedule[i][FIREBALL_SR_HOME_CAPTAIN] == player_name) || 
            (schedule[i][FIREBALL_SR_AWAY_CAPTAIN] == player_name)) 
            return i;

    return -1;
}


/*
 * Function:     wait_seq
 * Description:  This function is called from alarm when awaiting 
 *               confirmation of match readiness from team captains. 
 *               If the captains have missed their chance, the match 
 *               becomes void and the next match is started (if any). 
 */ 
private void
wait_seq(int stage, string *captains) 
{
    if (!sizeof(schedule) || !sizeof(captains)) 
        return;

    seteuid(getuid()); 
    if (stage < 6) { 
        (FIREBALL_SURROUND+"foyer")->ask_captains_ready(60 - stage*10, 
                                                        captains); 
        wait_alarm = 
            set_alarm(10.0, 0.0, &wait_seq(stage+1, captains)); 
        return;
    } 

    (FIREBALL_SURROUND+"foyer")->tell_captains_too_late(captains); 
    wait_alarm = 0; 
    schedule = exclude_array(schedule, 0, 0); 
    save_object(FIREBALL_SCHEDULE_SAVE); 
    start_next_match(); 
}


/* 
 * Function:      unbook_match
 * Description:   This action function is called when a captain unbooks a 
 *                match. The booked match will be removed from the schedule. 
 *                If there is a current countdown and the captain is involved 
 *                in that match, abandon it. 
 */ 
int 
unbook_match(string str)
{
    int i; 
    string rn; 
    string *rem_cap;

    if (!stringp(rn = this_player()->query_real_name())) 
        return 0; 

    if ((i = query_match_booked_for(rn)) == -1) { 
        notify_fail("You do not have a match booked.\n"); 
        return 0;
    } 

    schedule = exclude_array(schedule, i, i);  
    seteuid(getuid()); 
    save_object(FIREBALL_SCHEDULE_SAVE); 
    write("Ok, you unbooked your match.\n"); 
    say(QCTNAME(this_player()) + " unbooks " + 
        this_player()->query_possessive() + " team's match.\n"); 

    if (i)
        return 1;

    /* If we reach here we're dealing with the next match in 
       the schedule */  

    if (wait_alarm) { 
        remove_alarm(wait_alarm); 
        wait_alarm = 0; 
        set_alarm(1.0, 0.0, start_next_match); 
    } 

    return 1;
}



/* 
 * Function:       init_match 
 * Description:    Sets up a match in game_handler.c using the 
 *                 first element in the schedule array. 
 * 
 */ 
private void
init_match()
{
    mixed el, al; 
    int training; 
    string home, *home_players, away, *away_players, *fail;

    el = secure_var(schedule[0]); 
    schedule = exclude_array(schedule, 0, 0); 
    seteuid(getuid()); 
    save_object(FIREBALL_SCHEDULE_SAVE); 

    home = el[FIREBALL_SR_HOME_TEAM_NAME]; 
    home_players = el[FIREBALL_SR_HOME_TEAM];   
    away = el[FIREBALL_SR_AWAY_TEAM_NAME]; 
    away_players = el[FIREBALL_SR_AWAY_TEAM]; 
    training = el[FIREBALL_SR_TRAINING_MATCH]; 

    /** Try to initialise the match, if it doesn't work announce 
        failure and start the next match countdown. **/ 
    if (stringp(fail = 
               FIREBALL_GAME_HANDLER->init_match(home, 
                                                 secure_var(home_players), 
                                                 away, 
                                                 secure_var(away_players), 
                                                 training))) { 
        (FIREBALL_SURROUND+"foyer")->announce(fail); 
        start_next_match(); 
        return;
    } 

    (FIREBALL_SURROUND + "foyer")->usher_teams(home, away); 
}



/* 
 * Function:       captain_ready 
 * Description:    This function is called from the foyer when  
 *                 a captain proclaims readiness for the next 
 *                 match. If all captains are ready the next match 
 *                 may proceed, in which case game_handler.c is 
 *                 informed. 
 */ 
void
captain_ready(string captain) 
{
    mixed al; 
    string *rem_cap; 

    if (!stringp(captain) || !wait_alarm || !(al = get_alarm(wait_alarm))) 
        return; 

    rem_cap = al[4][1]; 

    if (member_array(captain, rem_cap) == -1) 
        return; 

    rem_cap -= ({ captain }); 

    remove_alarm(wait_alarm); 

    if (!sizeof(rem_cap)) { 
        wait_alarm = 0; 
        init_match(); 
        return; 
    } 

    wait_alarm = set_alarm(al[2], 0.0, &wait_seq(al[4][0], rem_cap)); 
} 



/* 
 * Function:      query_has_registered_team 
 * Description:   This function returns 1 if the named captain 
 *                has registered a team, otherwise it returns 0. 
 */ 
int
query_has_registered_team(string captain)
{
    mixed tmp; 

    return ((tmp = team_record[captain]) && 
            sizeof(tmp[FIREBALL_TR_PLAYERS])); 
} 


/* 
 * Function:      start_next_match 
 * Description:   This function tries to start the next match on the 
 *                schedule (if there is one), this involves a countdown 
 *                if there is one or more interactive teams, in which 
 *                case captains must confirm readiness (see wait_seq()) 
 */ 
void
start_next_match()
{
    string cap1, cap2, *captains; 

    if (!sizeof(schedule))
        return;

    seteuid(getuid()); 
    if (FIREBALL_GAME_HANDLER->query_current_match()) 
        return;

    cap1 = schedule[0][FIREBALL_SR_HOME_CAPTAIN]; 
    cap2 = schedule[0][FIREBALL_SR_AWAY_CAPTAIN];

    /* Make sure the two teams are registered */ 
    while (((cap1 != FIREBALL_NPC_CAPTAIN) && 
             !query_has_registered_team(cap1)) ||
           ((cap2 != FIREBALL_NPC_CAPTAIN) && 
             !query_has_registered_team(cap2))) 
    { 
        schedule = exclude_array(schedule, 0, 0);    
        if (!sizeof(schedule)) { 
            save_object(FIREBALL_SCHEDULE_SAVE); 
            return;
        } 
        cap1 = schedule[0][FIREBALL_SR_HOME_CAPTAIN]; 
        cap2 = schedule[0][FIREBALL_SR_AWAY_CAPTAIN];
    } 

    save_object(FIREBALL_SCHEDULE_SAVE); 

    captains = ({ }); 

    if (cap1 != FIREBALL_NPC_CAPTAIN) 
        captains += ({ cap1 }); 

    if (cap2 != FIREBALL_NPC_CAPTAIN) 
        captains += ({ cap2 }); 

    /* There can be npc vs npc matches for testing purposes */ 
    if (!sizeof(captains)) { 
        init_match(); 
        return; 
    } 

    wait_alarm = set_alarm(1.0, 0.0, &wait_seq(0, captains)); 
}



/* 
 * Function:    garbage_collect_teams
 * Description: remove team records for teams that registered 
 *              too long ago. 
 */ 
private void
garbage_collect_teams() 
{
    string *ix;
    int i, t;

    t = time(); 
    ix = m_indexes(team_record); 
    for (i = 0; i < sizeof(ix); i++) {  
        if ((t - team_record[ix[i]][FIREBALL_TR_LAST_TIME_ACTIVE]) > 
                                   DURATION_RETAIN_TEAM) 
            team_record = m_delete(team_record, ix[i]);  
    } 
    seteuid(getuid()); 
    save_object(FIREBALL_SCHEDULE_SAVE); 

    set_alarm(itof(2 * DURATION_RETAIN_TEAM), 0.0, garbage_collect_teams); 
}


void
log_check(string str)
{
    if (objectp(this_interactive())) 
       log_file("fireball", ctime(time()) + ": " + 
                         this_interactive()->query_real_name() + 
                         " " + str + "\n"); 
}


void
remove_object()
{
    log_check("caused removal of scheduler"); 
    ::remove_object(); 
}


/*
 * Function:     unregister_team
 * Description:  This is the action function for unregistering a team,
 *               called as a proxy from the foyer. 
 */ 
int
unregister_team(string str)
{
    string rn; 
    mixed rec; 

    rn = this_player()->query_real_name(); 

    if (!stringp(rn)) 
        return 0;

    if (!(rec = team_record[rn])) { 
        notify_fail("There is no team registered in your name.\n"); 
        return 0;
    } 

    if (query_match_booked_for(rn) > -1) { 
        notify_fail("You will have to unbook your match first.\n"); 
        return 0;
    } 

    team_record = m_delete(team_record, rn);  
    seteuid(getuid()); 
    save_object(FIREBALL_SCHEDULE_SAVE); 
    write("Ok, you unregistered the team: " + rec[FIREBALL_TR_TEAM_NAME] + ".\n"); 
    say(QCTNAME(this_player()) + " unregisters the team: " + 
        rec[FIREBALL_TR_TEAM_NAME] + ".\n"); 
    return 1;
}


/*
 * Function:     contains_non_alpha
 * Description:  returns 1 if the given string contains a non-alphabetical 
 *               character, otherwise returns 0.  
 * 
 */ 
int
contains_non_alpha(string str)
{
    int i;

    if (!stringp(str) || !strlen(str)) 
        return 1; 

    for (i = 0; i < strlen(str); i++)  
        if ((str[i] < 'a') || (str[i] > 'z')) 
            return 1; 

    return 0;
}


/*
 * Function:     register_team
 * Description:  This is the action function for registering a team,
 *               called as a proxy from the foyer. 
 */ 
int
register_team(string team_name)
{
    int i;
    string rn, *ix, *tmp; 
    mixed rec;

    rn = this_player()->query_real_name(); 

    if (!stringp(rn)) 
        return 0;

    if (!stringp(team_name)) { 
        notify_fail("What team name do you want to register?\n"); 
        return 0;
    } 

    if (team_record[rn]) { 
        notify_fail("There is already a team registered in your name.\n"); 
        return 0;
    } 

    if (strlen(team_name) > MAX_TEAM_NAME_STRLEN) { 
        notify_fail("That team name is too long, think if another one.\n"); 
        return 0;
    } 

    team_name = lower_case(team_name); 
    if (LOGIN_OBJECT->offensive_name(team_name) ||
        LOGIN_OBJECT->offensive_name(implode(explode(team_name, " "), ""))) {  
        notify_fail("Please do not use offensive team names.\n"); 
        return 0;
    } 

    if (sizeof(filter(tmp = explode(team_name, " "), contains_non_alpha))) { 
        notify_fail("Please use only alphabetical characters " +
                    "and single spaces in your team name.\n");  
        return 0;
    } 

    team_name = query_proper_team_name(team_name); 

    seteuid(getuid()); 
    if (FIREBALL_TEAM_HANDLER->query_npc_team(team_name)) { 
        notify_fail("There is a fireball league team with that name.\n"); 
        return 0;
    } 

    ix = m_indexes(team_record); 
    for (i = 0; i < sizeof(ix); i++) { 
        if (team_name == team_record[ix[i]][FIREBALL_TR_TEAM_NAME]) {  
            notify_fail("There is another registered team with that name.\n"); 
            return 0;
        } 
    } 

    if (!MONEY_ADD(this_player(), -FIREBALL_REGISTRATION_FEE)) {  
        notify_fail("You cannot afford the registration fee of " + 
                    FIREBALL_REGISTRATION_FEE + " cc!\n");  
        return 0;
    } 

    write("You pay the registration fee of " + 
          FIREBALL_REGISTRATION_FEE + " cc.\n"); 

    rec = ({ team_name, time(), ({ }) });  
    team_record[rn] = rec; 
    seteuid(getuid()); 
    save_object(FIREBALL_SCHEDULE_SAVE); 
    write("You have registered the team name: " + team_name + ".\n");  
    say(QCTNAME(this_player()) + " registers the team name: " + 
        team_name + ".\n"); 
    return 1;
}


int
not_player(string str)
{
    return (!SECURITY->exist_player(str) && 
            !FIREBALL_TEAM_HANDLER->is_fireball_npc(str)); 
}


/*
 * Function:     register_players
 * Description:  This is the action function for registering a team of
 *               players for the team of which the registering player
 *               is captain, called as a proxy from the foyer. 
 */ 
int
register_players(string str)
{
    string *pn, *fpn, cpl, rn;
    int i, j; 
    mixed rec; 

    rn = this_player()->query_real_name(); 

    if (!stringp(rn)) 
        return 0;

    if (!(rec = team_record[rn])) { 
        notify_fail("There is no team name registered in your name.\n"); 
        return 0;
    } 

    if (sizeof(rec[FIREBALL_TR_PLAYERS])) { 
        notify_fail("You will have to unregister your team and " +
                    "register again if you want to change the " +
                    "team members.\n"); 
        return 0;
    } 

    if (!stringp(str) || !sizeof(pn = explode(str, " "))) {
        notify_fail("Syntax: pregister <defender> <left midfielder> " +
                    "<right midfielder> <attacker>.\n"); 
        return 0;
    }

    if (member_array(rn, pn = map(pn, lower_case)) == -1)   { 
        notify_fail("You must be part of the team!\n"); 
        return 0;
    }  

    if (sizeof(fpn = filter(pn, not_player))) { 
        notify_fail("The following players do not exist: " + 
                    COMPOSITE_WORDS(map(fpn, capitalize)) +  ".\n"); 
        return 0;
    } 

    cpl = COMPOSITE_WORDS(map(pn, capitalize)); 
    if (sizeof(pn) < 4) {  
        notify_fail("The player list: " + cpl + " " + 
                    "does not make up a whole team. A team " +
                    "must have four players, one of which " +
                    "must be you, in the order <defender> " +
                    "<left midfielder> <right midfielder> <attacker>.\n");
        return 0;
    } 

    if (sizeof(pn) > 4) {  
        notify_fail("The player list: " + cpl + " " +  
                    "has too many people for one team. A team " +
                    "must have four players, in the order " +
                    "<defender> <left midfielder> <right midfielder> " +
                    "<attacker>.\n"); 
        return 0;
    } 

    for (i = 0; i < 4; i++) {
        for (j = i + 1; j < 4; j++) { 
            if (pn[i] == pn[j]) {
                notify_fail("No player may appear more than once in " +
                            "a team.\n"); 
                return 0; 
            } 
        } 
    } 

    rec[FIREBALL_TR_PLAYERS] = pn;   
    seteuid(getuid()); 
    save_object(FIREBALL_SCHEDULE_SAVE); 
    write("You have registered the following player list for your team: " + 
          cpl + ".\n"); 
    say(QCTNAME(this_player()) + " registers the following player list " + 
        "for " + this_player()->query_possessive() + " team: " + cpl + 
        ".\n"); 
    return 1;
}


string
query_captain_of_team(string team_name)
{
    int i; 
    string *ix; 

    team_name = query_proper_team_name(team_name); 
    ix = m_indexes(team_record); 

    for (i = 0; i < sizeof(ix); i++) 
        if (team_record[ix[i]][FIREBALL_TR_TEAM_NAME] == team_name)
            return ix[i]; 

    return 0;
} 


/* 
 * Function:     book_match 
 * Description:  This is the action function for booking a match 
 *               against another team, called as a proxy from 
 *               the foyer. 
 */ 
int
book_match(string str)
{
    mixed rec, rec2; 
    string rn, *match, our_players, opp_players, opposing_captain; 
    int i, j, pl_avg, npc_avg, fee, old_winners, our_npc_count; 
    object tmp, foyer, team_handler; 

    if (!stringp(str)) { 
        notify_fail("Book a match with which team?\n"); 
        return 0; 
    } 

    if (!stringp(rn = this_player()->query_real_name())) 
        return 0;

    if (!(rec = team_record[rn])) { 
        notify_fail("There is no team registered in your name.\n"); 
        return 0;
    } 

    if (query_match_booked_for(rn) > -1) { 
        notify_fail("There is already a match booked for your registered " + 
                    "team.\n"); 
        return 0;
    } 

    if (!sizeof(our_players = rec[FIREBALL_TR_PLAYERS])) { 
        notify_fail("You do not have any players registered for your team!\n"); 
        return 0;
    } 

    str = query_proper_team_name(str); 

    seteuid(getuid()); 
    team_handler = FIREBALL_TEAM_HANDLER->get_this_object(); 

    if (stringp(opposing_captain = query_captain_of_team(str))) { 
        rec2 = team_record[opposing_captain]; 
        if (!sizeof(opp_players = rec2[FIREBALL_TR_PLAYERS])) { 
            notify_fail("That team has no players!\n"); 
            return 0; 
        } 
    } 
    else { 
        if (pointerp(opp_players = 
            team_handler->query_team(str, 1))) { 
            opposing_captain = FIREBALL_NPC_CAPTAIN; 
        } 
        else { 
            notify_fail("That team is unknown!\n"); 
            return 0; 
        } 
    } 


    /* The next loop calculates the fee, counts npcs on our 
       team and makes sure no player is on both teams. */ 
    fee = 0; 
    our_npc_count = 0; 
    for (i = 0; i < 4; i++) { 
        for (j = 0; j < 4; j++) { 
            if (our_players[i] == opp_players[j])  { 
                notify_fail(capitalize(our_players[i]) + 
                            " is in both teams!\n"); 
                return 0; 
            } 
        } 
        if (team_handler->is_fireball_npc(our_players[i])) { 
            our_npc_count++; 
            fee += team_handler->query_wages(our_players[i]); 
        } 
        if (team_handler->is_fireball_npc(opp_players[i])) 
            fee += team_handler->query_wages(opp_players[i]); 
    } 

    if (opposing_captain == FIREBALL_NPC_CAPTAIN) { 
        pl_avg = 0; 
        foyer = (FIREBALL_SURROUND + "foyer")->get_this_object(); 
        npc_avg = team_handler->query_team_average_stat(str); 
        old_winners = 0; 

        for (i = 0; i < 4; i++) { 
            if (team_handler->is_fireball_npc(our_players[i]))
                continue;

            tmp = find_player(rec[FIREBALL_TR_PLAYERS][i]); 

            if (!objectp(tmp) || !objectp(present(tmp, foyer))) {
                notify_fail("All team players must be in the foyer to book " + 
                            "a match. At least one is missing.\n"); 
                return 0; 
            } 

            pl_avg = ((tmp->query_stat(SS_CON) + tmp->query_stat(SS_DEX) + 
                       tmp->query_stat(SS_STR)) / 3); 

            /*
            if (npc_avg > 30 && ((npc_avg / pl_avg) >= 2)) { 
                notify_fail("Not a chance, that team is too much for " + 
                            capitalize(tmp->query_real_name()) + 
                            " to handle!\n"); 
                return 0; 
            } 

            if (npc_avg < 80 && ((pl_avg / npc_avg) >= 2)) { 
                notify_fail("Not a chance, " + 
                            capitalize(tmp->query_real_name()) + 
                            " is over-qualified to play that team!\n"); 
                return 0;
            } 
            */

            if (team_handler->query_beaten_team(tmp, str)) 
                old_winners++; 
        } 

        if (old_winners > 1) { 
            write("Your team has more than one player who has defeated " + 
                  str + " before, so there will be no quest rewards if " + 
                  "you win.\n"); 
        } 
        else if (our_npc_count > 1) { 
            write("As you have hired league players for your team " + 
                  "there will be no quest rewards if you win.\n"); 
        } 
    } 

    if (fee && !MONEY_ADD(this_player(), -fee)) { 
        notify_fail("You cannot afford the booking fee of " + fee + " cc!\n");  
        return 0; 
    } 

    if (opposing_captain == FIREBALL_NPC_CAPTAIN) 
        schedule += ({ ({ FIREBALL_NPC_CAPTAIN, str, 
                          opp_players, 
                          /* npcs play at home against pcs */ 
                          rn, rec[FIREBALL_TR_TEAM_NAME], 
                          our_players, 
                          old_winners > 1 || our_npc_count }) }); 
    else 
        schedule += ({ ({ rn, rec[FIREBALL_TR_TEAM_NAME], our_players, 
                          opposing_captain, str, opp_players, 1 }) }); 

    rec[FIREBALL_TR_LAST_TIME_ACTIVE] = time(); 
    team_record[rn] = rec; 
    seteuid(getuid()); 
    save_object(FIREBALL_SCHEDULE_SAVE); 

    write("You pay the booking fee of " + fee + " cc.\n"); 
    write("You are now booked for a match against the team: " + str + 
          ".\nThe match is queued in position: " + 
          LANG_WNUM(sizeof(schedule)) + ".\n"); 

    say(QCTNAME(this_player()) + " books a match against the team: " + 
        str + ".\n"); 

    set_alarm(1.0, 0.0, start_next_match); 
    return 1; 
} 


/* 
 * Function:        book_match_npc_vs_npc 
 * Description:     Action function to book a match between two 
 *                  npc teams, can only be invoked by wizards 
 *                  with the necessary privileges. 
 * 
 */ 
int 
book_match_npc_vs_npc(string str) 
{
    mixed rec; 
    string home_team_name, away_team_name; 
    object tmp; 

    if (!SECURITY->valid_write(file_name(this_object()), 
                               this_player(), "write_file")) {
        notify_fail("You do not have the authority to do that.\n"); 
        return 0;
    }

    notify_fail("Book <team> vs <team>?\n"); 

    if (!stringp(str) || !strlen(str)) 
        return 0;

    if (sscanf(str, "%s vs %s", home_team_name, away_team_name) != 2) 
        return 0;

    home_team_name = query_proper_team_name(home_team_name); 
    away_team_name = query_proper_team_name(away_team_name); 
 
    if (home_team_name == away_team_name) {
        notify_fail("A team cannot play itself!\n");
        return 0; 
    } 

    seteuid(getuid());
    if (!FIREBALL_TEAM_HANDLER->query_npc_team(home_team_name) ||
        !FIREBALL_TEAM_HANDLER->query_npc_team(away_team_name))  { 
        notify_fail("One or more of those teams does not exist.\n"); 
        return 0; 
    } 

    schedule += 
       ({ ({ FIREBALL_NPC_CAPTAIN, home_team_name, 
             FIREBALL_TEAM_HANDLER->query_team(home_team_name, 0), 
             FIREBALL_NPC_CAPTAIN, away_team_name, 
             FIREBALL_TEAM_HANDLER->query_team(away_team_name, 0), 
             1 }) }); 

    save_object(FIREBALL_SCHEDULE_SAVE); 

    write("You have booked a match: " + home_team_name + " vs " + 
                                        away_team_name + ".\n" + 
          "The match is queued in position: " + 
          LANG_WNUM(sizeof(schedule)) + ".\n"); 

    say(QCTNAME(this_player()) + " books a match: " + 
        home_team_name + " vs " + away_team_name + ".\n"); 

    set_alarm(1.0, 0.0, start_next_match); 
    return 1; 
}
