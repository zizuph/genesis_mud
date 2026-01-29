
/* 
    ~Calia/fireball/special/game_handler.c 

    This is the game handler for the game of Fireball. 
    It timekeeps the game, keeps track of the score and 
    the position of players and the ball, and defines 
    all the game actions. Control of each npc team's 
    movements is delegated to its team manager. 

    Functional structure:
        Display functions
        Match control functions
        Location functions
        Player action functions

    Coded by Maniac@Genesis, 1998/1999

    Copyright (C) Miguel Leith 1998/1999

    History: 
    1998/1999        Created                                 Maniac
    2000             blah blah undocumented modifications    Maniac 
    15/12/01         Changed reward call to team handler 
                     so general xp can be given.             Maniac 
*/ 

#pragma strict_types
#pragma no_inherit
#pragma save_binary

#include "defs.h"
#include FIREBALL_HEADER
#include EVH_HEADER

#define NO_TELLS_FOR_NPCS

inherit "/std/object"; 
inherit FIREBALL_UTILS; 
inherit FIREBALL_POSITIONING; 

#include <ss_types.h>
#include <files.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <formulas.h>
#include <tasks.h>

/* Start of prototypes */ 
void report(string message, object *where_not); 
void freport(string message, object *where_not); 
private int query_rebound(int from_x, int from_y, int hit_x, int hit_y); 
private void made_kickoff(); 
private void check_npc_kickoff(); 
private void npc_home_kickoff(object kicker);
private void npc_away_kickoff(object kicker);
private int missing_players_reset(); 
private void reset_game(int clear_arena); 
private void save_game(); 
private void next_match_state(); 
private void start_npc_teams(); 
private void stop_npc_teams(); 
int do_control(string str); 
int do_release(string str); 
int do_shoot(string str, int far);
int do_tackle(string str); 
int do_kick(string str, int far); 
int do_pass(string str, int far); 
int move_ball(int x1, int y1, int x2, int y2, int test, 
              object target, int shot, int far); 
/* End of prototypes */ 

/* Start of global variables */
/* Start of static globals */  
static int match_alarm; 
static int max_power = F_PENMOD(75, 100) / 2;  
static string *home_team_symbol = ({"d", "l", "r", "a" }); 
static string *away_team_symbol = ({"D", "L", "R", "A" }); 

/* 
 * Start speedup globals (used in arena display functions) 
 * Ok I know using all these miscellaneous globals is 
 * anti-modular, but the code should work faster by using 
 * these in the very frequently called functions.
 */ 
static int xl, yl, d, i, j; 
static object *oblist; 
static string hs, as, bs, display, tmp; 
/* End of speedup globals */ 
/* End of static globals */ 

/* Start of saved global variables */ 
int time_until_next_state; 
int time_until_next_substate; 
int npcs_home, npcs_away; 
string match_state; 
string match_substate; 
int home_score; 
int away_score; 
mapping home_scorers; 
mapping away_scorers; 
mapping last_arena_start; 
string home_team_name, away_team_name, 
       home_team_manager_file, away_team_manager_file; 
string *home_player_names; 
string *away_player_names; 
object *home_players, *away_players, ball, home_team_manager, 
       away_team_manager; 
int home_kicking; 
int away_kicking; 
int home_has_first_centre; 
int home_centre; 
int in_play; 
int training_match; 

mixed arena; 

object *viewers = ({ });   //  People in the stands
object *listeners = ({ });  //  Can't see game but hear the crowd
object *participants = ({ });  // People in the arena 
/* End of saved global variables */ 
/* End of global variables */ 


void
create_object()
{
    int c, c2; 

    seteuid(getuid()); 
    restore_object(FIREBALL_GAME_SAVE); 

    if (match_state == FIREBALL_MS_NO_MATCH) { 
        reset_game(1); 
        return; 
    } 

    if (missing_players_reset()) 
        return; 

    for (c = 0; c < sizeof(arena); c++) 
        for (c2 = 0; c2 < sizeof(arena[c]); c2++) 
            if (pointerp(arena[c][c2])) 
                arena[c][c2] = filter(arena[c][c2], objectp); 

    participants = filter(participants, objectp); 
    listeners = filter(listeners, objectp); 
    viewers = filter(viewers, objectp); 

    if (stringp(match_substate)) 
        match_alarm = set_alarm(itof(time_until_next_substate), 0.0, 
                                next_match_state); 
    else if (match_state != FIREBALL_MS_NO_MATCH)
        match_alarm = set_alarm(itof(time_until_next_state), 0.0, 
                                next_match_state); 

    if (!stringp(match_substate) && 
        ((match_state == FIREBALL_MS_FIRST_HALF) || 
         (match_state == FIREBALL_MS_SECOND_HALF)))
        start_npc_teams(); 
}


int
is_or_was_in_arena(object pl)
{
    return (objectp(pl) && 
            (IS_FIREBALL_ARENA_ROOM(environment(pl)) ||
             pl->query_prop(FIREBALL_LIVE_I_LINKDEAD_FROM_ARENA))); 
}


int
missing_players_reset()
{
    if (match_state == FIREBALL_MS_PRE_MATCH || 
        match_state == FIREBALL_MS_POST_MATCH)  
        return 0; 

    if (match_state == FIREBALL_MS_PRACTICE) {
        if (sizeof(filter(home_players, is_or_was_in_arena)) == 0) {
            reset_game(1); 
            return 1; 
        } 
        return 0; 
    }  

    if (sizeof(filter(home_players, is_or_was_in_arena)) != 4 ||
        sizeof(filter(away_players, is_or_was_in_arena)) != 4) {
        freport("\nA gong sounds four times indicating an " +
                "abandoned match due to missing players.\n", ({ }));
        (home_players + away_players)->catch_tell("A guard tells you " +
              "that your match has been abandoned due to missing players.\n"); 
        reset_game(1); 
        return 1; 
    } 
    return 0;  
}


int
query_current_player(object pl)
{
    return ((member_array(pl, home_players) != -1) ||
            (member_array(pl, away_players) != -1)); 
}


/* S T A R T   O F   D I S P L A Y   F U N C T I O N S */ 

/*
 * Function:      query_arena_room_display
 * Description:   returns a string describing the arena room of
 *                the supplied indices, called from check_arena_display()
 *                for each arena room 
 */ 
private string
query_arena_room_display(int x, int y, object tp)
{
    if (!sizeof(oblist = arena[y][x]) || 
        !sizeof(oblist = oblist - ({ 0 })))
        return "|   "; 

    hs = as = bs = " "; 

    if (member_array(tp, oblist) > -1) {
        if (member_array(tp, home_players) > -1)
            hs = "*"; 
        else if (member_array(tp, away_players) > -1)
            as = "*"; 
    } 

    j = 0; 
    while (j < sizeof(oblist) && (as == " " || hs == " ")) {
        if (((d = member_array(oblist[j], home_players)) != -1) &&
              hs == " ")
            hs = home_team_symbol[d]; 
        else if (((d = member_array(oblist[j], away_players)) != -1) &&
                 as == " ") 
            as = away_team_symbol[d]; 
        j++; 
    } 

    if (member_array(ball, oblist) > -1)
        bs = "o"; 
    return ("|" + hs + as + bs); 
}


/*
 * Function:     check_arena_display
 * Description:  Prints a display of the arena for a living. Aiming 
 *               for some kind of speed here so trying to minimize
 *               array index access. 
 */ 
int
check_arena_display()
{
    object tp = this_player(); 

    display =  ("      1   2   3   4   5   6   7   8   9  10  11\n\n");  

    /* row 0 */ 
    tmp = ""; 
    for (i = 4; i < 7; i++) 
        tmp += query_arena_room_display(i, 0, tp); 
    display += ("11                  " + tmp + "|                " + 
                "  11\n");

    /* row 1 */ 
    tmp = "";  
    for (i = 3; i < 8; i++) 
        tmp += query_arena_room_display(i, 1, tp); 
    display += ("10              " + tmp + "|              10\n"); 

    /* row 2 */ 
    tmp = ""; 
    for (i = 2; i < 9; i++) 
        tmp += query_arena_room_display(i, 2, tp); 
    display += (" 9          " + tmp + "|           9\n");  

    /* row 3 */ 
    tmp = ""; 
    for (i = 1; i < 10; i++) 
        tmp += query_arena_room_display(i, 3, tp); 
    display += (" 8      " + tmp + "|       8\n"); 

    /* row 4 */
    tmp = "";  
    for (i = 0; i < 5; i++) 
        tmp += query_arena_room_display(i, 4, tp); 
    tmp += "|###"; 
    for (i = 6; i < 11; i++) 
        tmp += query_arena_room_display(i, 4, tp); 

    display += (" 7  " + tmp + "|   7\n"); 

    /* row 5 */
    tmp = "";  
    for (i = 0; i < 4; i++) 
        tmp += query_arena_room_display(i, 5, tp); 
    tmp += "|###|###|###"; 
    for (i = 7; i < 11; i++) 
        tmp += query_arena_room_display(i, 5, tp); 

    display += (" 6  " + tmp + "|   6\n"); 

    /* row 6 */
    tmp = "";  
    for (i = 0; i < 5; i++) 
        tmp += query_arena_room_display(i, 6, tp); 
    tmp += "|###"; 
    for (i = 6; i < 11; i++) 
        tmp += query_arena_room_display(i, 6, tp); 

    display += (" 5  " + tmp + "|   5\n"); 

    /* row 7 */
    tmp = "";  
    for (i = 1; i < 10; i++) 
        tmp += query_arena_room_display(i, 7, tp); 
    display += (" 4      " + tmp + "|       4\n"); 

    /* row 8 */
    tmp = "";  
    for (i = 2; i < 9; i++) 
        tmp += query_arena_room_display(i, 8, tp); 
    display += (" 3          " + tmp + "|           3\n"); 

    /* row 9 */ 
    tmp = "";  
    for (i = 3; i < 8; i++) 
        tmp += query_arena_room_display(i, 9, tp); 
    display += (" 2              " + tmp + "|               2\n"); 

    /* row 10 */ 
    tmp = ""; 
    for (i = 4; i < 7; i++) 
        tmp += query_arena_room_display(i, 10, tp); 
    display += (" 1                  " + tmp + "|                " +
                "   1\n");

    display += ("\n      1   2   3   4   5   6   7   8   9  10  11\n");  

    tell_object(tp, display); 
    return 1; 
}


int
query_current_match()
{
    return (match_state != FIREBALL_MS_NO_MATCH); 
}


/* 
 * Function:     query_match_description
 * Description:  Returns a description of the state of the current 
 *               match, the names of the teams involved, the score 
 *               and scorers, as a string over a few lines.
 *               A list of the players in the two teams is included 
 *               if the argument list_teams is not zero. 
 */ 
string
query_match_description(int list_teams)
{
    int c; 
    string str, *idh, *ida; 

    if (!query_current_match()) 
        return "No current match.\n"; 

    str = sprintf("%|71s\n\n", capitalize(match_state)); 

    str += sprintf("%30s", home_team_name); 
    str += sprintf("%4s - %-4s", home_score + "", away_score + ""); 
    str += sprintf("%-30s\n\n", away_team_name);  

    c = 0; 
    idh = m_indexes(home_scorers); 
    ida = m_indexes(away_scorers); 
    while (c < sizeof(idh) || c < sizeof(ida)) {
        if (c < sizeof(idh))
            str += sprintf("%30s%11s", idh[c] + " " +  
                           home_scorers[idh[c]],""); 
        else 
            str += sprintf("%41s", "");

        if (c < sizeof(ida))
            str += sprintf("%-30s\n", ida[c] + " " + 
                           away_scorers[ida[c]]); 
        else
            str += sprintf("%30s\n", ""); 
        c++; 
    } 

    if (list_teams) {
        str += ("\nTeams:\n" + 
                home_team_name + ": " + 
                COMPOSITE_WORDS(home_player_names) + ".\n" + 
                away_team_name + ": " + 
                COMPOSITE_WORDS(away_player_names) + ".\n"); 
    }

    return str;
}

/* E N D   O F   D I S P L A Y   F U N C T I O N S */ 



/* S T A R T   O F   M A T C H   C O N T R O L   F U N C T I O N S */ 

/*
 *  Function:     init_match
 *  Description:  initializes a match. This consists of categorising
 *                teams (whether player team or npc team) and then
 *                checking that the players and npcs are available. 
 *                Also registers whether this is a training match 
 *                (no rewards). 
 *                Returns 0 on success or a fail message (string) on
 *                failure. 
 */ 
string 
init_match(string h, string *hp, string a, string *ap, int training) 
{
    int c; 

    if (match_state != FIREBALL_MS_NO_MATCH)
        return "There is a match in progress."; 

    reset_game(1); 

    npcs_home = 0; 
    home_players = ({ 0, 0, 0, 0 }); 

    for (c = 0; c < 4; c++) {
        if (!objectp(home_players[c] = find_player(hp[c]))) { 
            if (objectp(home_players[c] = 
                    FIREBALL_TEAM_HANDLER->make_team_member(hp[c], h))) {
                npcs_home++; 
            } 
            else
                return ("There are players missing from the team " + 
                    h + "."); 
        } 
        hp[c] = capitalize(hp[c]); 
        (FIREBALL_SURROUND + "locker_room")->reset_locker_times(home_players);  
        if (npcs_home == 4) {
            home_team_manager_file = 
                FIREBALL_TEAM_HANDLER->query_formation_file(h); 
        }  
    } 

    away_players = ({ 0, 0, 0, 0 }); 
    npcs_away = 0; 

    for (c = 0; c < 4; c++) {
        if (!objectp(away_players[c] = find_player(ap[c]))) { 
            if (objectp(away_players[c] = 
                    FIREBALL_TEAM_HANDLER->make_team_member(ap[c], a))) {
                npcs_away++; 
            }
            else
                return ("There are players missing from the team " + 
                    h + "."); 
        } 
        ap[c] = capitalize(ap[c]); 
        (FIREBALL_SURROUND + "locker_room")->reset_locker_times(away_players);
        if (npcs_away == 4) {
            away_team_manager_file = 
                FIREBALL_TEAM_HANDLER->query_formation_file(a);
        }
    }

    home_player_names = hp; 
    away_player_names = ap; 
    home_team_name = h; 
    away_team_name = a;
    training_match = training;  
    match_alarm = set_alarm(itof(FIREBALL_IVL_INIT), 0.0, next_match_state); 

    return 0; 
}


/*
 *  Function:     query_home_team_manager
 *  Description:  Returns the object managing the movements of the
 *                npcs in the home team. 
 */ 
object
query_home_team_manager()
{
    if (objectp(home_team_manager))
        return home_team_manager; 

    return (home_team_manager = clone_object(home_team_manager_file)); 
    
}


/*
 *  Function:     query_away_team_manager
 *  Description:  Returns the object managing the movements of the
 *                npcs in the away team. 
 */ 
object
query_away_team_manager()
{
    if (objectp(away_team_manager))
        return away_team_manager; 

    return (away_team_manager = clone_object(away_team_manager_file)); 
}


private void
stop_npc_teams()
{
    if (npcs_home)
        query_home_team_manager()->stop_team(); 
    if (npcs_away)
        query_away_team_manager()->stop_team(); 
}


private void
start_npc_teams()
{
    if (npcs_home) 
        query_home_team_manager()->start_team(home_players, home_kicking, ball); 
    if (npcs_away)
        query_away_team_manager()->start_team(away_players, away_kicking, ball); 
}


/*
 * Function:       new_game
 * Description:    Start a the next game by calling the schedule handler,
 *                 which will call back if there are matches queued.  
 *
 */ 
private void
new_game()
{
    seteuid(getuid()); 
    reset_game(1); 
    FIREBALL_SCHEDULE_HANDLER->start_next_match();     
}


private void
do_goal_reaction()
{
    string crowd_reaction; 

    crowd_reaction = ({ "cheers fanatically", "goes wild", 
                        "applauds madly", 
                        "bounces around in celebration" })[random(4)];    
    freport("Stand: The crowd " + crowd_reaction + "!\n", ({ })); 

}


private void
do_end_match_reaction()
{
    string wt; 

    if (home_score == away_score) 
        freport("Stand: Informer shouts: The match is drawn!\n", ({ })); 
    else if (home_score > away_score) 
        freport(HANGING_INDENT("Stand: Informer shouts: " + home_team_name + 
                " are the winners!", 7, 0), ({ })); 
    else if (away_score > home_score) 
        freport(HANGING_INDENT("Stand: Informer shouts: " + away_team_name + 
                " are the winners!\n", 7, 0), ({ })); 

    freport(sprintf("%30s", home_team_name) +  
           sprintf("%4s - %-4s", home_score + "", away_score + "") + 
           sprintf("%-30s\n", away_team_name), ({ }));  

    freport("Stand: The crowd bounces around and applauds.\n", ({ })); 
}


/*
 * Function:       score_goal
 * Description:    Score a goal in the current game. 
 */
private void
score_goal(object player)
{  
    int c; 
    string nm; 
    mixed al; 

    if (member_array(player, home_players) > -1) {
        home_score++;
        nm = capitalize(player->query_real_name());  
        c = home_scorers[nm];
        home_scorers += ([ nm : ++c ]); 
        home_centre = 0; 
    }
    else if (member_array(player, away_players) > -1) {
        away_score++; 
        nm = capitalize(player->query_real_name()); 
        c = away_scorers[nm];
        away_scorers += ([ nm : ++c ]);
        home_centre = 1;  
    } 
    else
        return;

    match_substate = FIREBALL_MSS_GOAL_SCORED; 

    al = get_alarm(match_alarm); 
    time_until_next_state = ftoi(al[2]); 
    remove_alarm(match_alarm); 

    match_alarm = 
      set_alarm(itof(FIREBALL_IVL_GOAL_TO_KICKOFF), 0.0, next_match_state); 
    set_alarm(1.0, 0.0, do_goal_reaction);   // oops

    freport(sprintf("%30s", home_team_name) +  
           sprintf("%4s - %-4s", home_score + "", away_score + "") + 
           sprintf("%-30s\n", away_team_name), ({ }));  

    in_play = 0; 
    stop_npc_teams(); 
}


private void
introduce_half(int h)
{
    string ks, kn, ko; 

    if (home_centre) 
        ko = home_team_name; 
    else 
        ko = away_team_name; 

    if (home_kicking == FIREBALL_KICKING_NORTH)  { 
        kn = home_team_name; 
        ks = away_team_name;  
    } 
    else { 
        kn = away_team_name; 
        ks = home_team_name; 
    } 

    freport(HANGING_INDENT("Stand: Informer shouts: " + ko + 
            " will kick off. " + 
            kn + " will be kicking north in the " + 
            (h == 1 ? "first" : "second") + " half, " + 
            ks + " south.\n", 7, 0), ({ }));
}


private void
introduce_players()
{
    int i; 
    string rn; 

    freport(HANGING_INDENT("Stand: Informer shouts: Ladies and " +
            "Gentlemen, introducing the team " + home_team_name + ": " + 
           COMPOSITE_WORDS(home_player_names) + ", versus the team " + 
           away_team_name + ": " + COMPOSITE_WORDS(away_player_names) + 
           "!\n", 7, 0), ({ })); 

    for (i = 0; i < 4; i++) {
        rn = home_players[i]->query_real_name(); 
        participants->add_introduced(rn); 
        viewers->add_introduced(rn); 
        rn = away_players[i]->query_real_name(); 
        participants->add_introduced(rn); 
        viewers->add_introduced(rn); 
    } 
}


object
query_ball()
{
    return ball; 
}


private void
configure_kicking(int hk, int ak)
{
    int c; 
    home_kicking = hk; 
    away_kicking = ak; 
    for (c = 0; c < sizeof(home_players); c++)
        if (objectp(home_players[c])) 
            home_players[c]->add_prop(FIREBALL_LIVE_I_KICK_DIRECTION, hk);

    for (c = 0; c < sizeof(away_players); c++) 
        if (objectp(away_players[c])) 
            away_players[c]->add_prop(FIREBALL_LIVE_I_KICK_DIRECTION, ak);  
}





/* 
 * Function:     time_to_path_arr
 * Description:  For the given time in string form (from ctime()), return an 
 *               array describing the path leading to the results
 *               file, e.g. ({ "1999", "Jun", "19" })
 */ 
string *
time_to_path_arr(string ct)
{
    return  ({ 
               implode(explode(extract(ct, 20, 23), " "), ""), 
               implode(explode(extract(ct, 4, 6), " "), ""), 
               implode(explode(extract(ct, 8, 9), " "), "")
             }); 
}


/* 
 *  Function:     register_result
 *  Description:  Register the current result in the archive and
 *                give a quest reward if appropriate. 
 *
 */ 
private void
register_result()
{
    string desc = query_match_description(1); 
    string ct = ctime(time()); 
    string *path_arr = time_to_path_arr(ct);
    string dir = FIREBALL_RESULTS + path_arr[0];  

    if (npcs_home == 4 && !npcs_away) 
         FIREBALL_TEAM_HANDLER->reward_team(away_players, 
                                            home_team_name, 
                                            desc, 
                                            away_score, 
                                            home_score, 
                                            training_match); 
    else if (npcs_away == 4 && !npcs_home) 
         FIREBALL_TEAM_HANDLER->reward_team(home_players, 
                                            away_team_name, 
                                            desc, 
                                            home_score, 
                                            away_score, 
                                            training_match); 

    if ((file_size(dir) != -2 && !mkdir(dir)) ||
        (file_size(dir += ("/" + path_arr[1])) != -2 && !mkdir(dir)))
        return; 

    write_file(dir + "/" + path_arr[2], "\n" + desc + "\n\n"); 
}


/*
 * Function:    npc_home_kickoff
 * Description: make the npc forward of the home team kick off 
 */ 
private void
npc_home_kickoff(object kicker) 
{
    query_home_team_manager()->npc_kickoff(kicker, home_players, 
                               home_kicking);
}


/*
 * Function:    npc_away_kickoff
 * Description: make the npc forward of the away team kick off 
 */ 
private void
npc_away_kickoff(object kicker)
{
    query_away_team_manager()->npc_kickoff(kicker, away_players, 
                               away_kicking);
}


/*
 * Function:     check_npc_kickoff
 * Description:  Set up an npc kickoff if there should be one. 
 */ 
void
check_npc_kickoff()
{
    object player; 

    if ((player = home_players[3])->query_npc() && home_centre) 
        set_alarm(itof(random(5) + 3), 0.0, 
            &npc_home_kickoff(player)); 
    else if ((player = away_players[3])->query_npc() && !home_centre) 
        set_alarm(itof(random(5) + 3), 0.0, 
            &npc_away_kickoff(player)); 
}


/* 
 * Function:      next_match_state
 * Description:   Advance the match to its next state, e.g. from pre match 
 *                to first half.
 */ 
private void
next_match_state()
{
    if (stringp(match_substate)) {
        if (match_substate == FIREBALL_MSS_GOAL_SCORED) {
            if (missing_players_reset())
                return; 
            match_substate = FIREBALL_MSS_AWAITING_KICKOFF; 
            freport("\nA gong sounds once indicating kick-off.\n", 
                   ({ })); 
            if (home_kicking == FIREBALL_KICKING_NORTH) 
                position_home_kicking_north(home_centre, ball, home_players,
                                            away_players);  
            else 
                position_home_kicking_south(home_centre, ball, home_players,
                                            away_players);
            match_alarm = set_alarm(itof(FIREBALL_IVL_KICKOFF_MAX), 0.0, 
                                    next_match_state); 
            check_npc_kickoff(); 
        } 
        else if (match_substate == FIREBALL_MSS_AWAITING_KICKOFF) {
            made_kickoff(); 
        } 
    } 
    else switch (match_state) {

        case FIREBALL_MS_NO_MATCH : 
            move_players_to_locker_room(filter(home_players, &->query_npc())); 
            move_players_to_locker_room(filter(away_players, &->query_npc())); 
            match_state = FIREBALL_MS_PRE_MATCH; 
            match_alarm = set_alarm(itof(FIREBALL_IVL_PRE_MATCH), 0.0, 
                                    next_match_state); 
            break; 

        case FIREBALL_MS_PRE_MATCH :
            filter(home_players, &->query_npc())->command("east"); 
            filter(away_players, &->query_npc())->command("east"); 

            if (missing_players_reset())
                return; 

            home_centre = (home_has_first_centre = random(2)); 
            if (random(2))  
                configure_kicking(FIREBALL_KICKING_NORTH, 
                                  FIREBALL_KICKING_SOUTH); 
            else  
                configure_kicking(FIREBALL_KICKING_SOUTH,
                                  FIREBALL_KICKING_NORTH);

            set_alarm(4.0, 0.0, introduce_players); 
            set_alarm(8.0, 0.0, &introduce_half(1)); 

            match_state = FIREBALL_MS_INTRO_FIRST_HALF; 
            match_alarm = set_alarm(itof(FIREBALL_IVL_INTRO_FIRST_HALF), 
                                    0.0, next_match_state); 
            break; 

        case FIREBALL_MS_INTRO_FIRST_HALF : 
            if (missing_players_reset())
                return; 
            if (!objectp(ball))  {
                seteuid(getuid()); 
                ball = clone_object(FIREBALL_OBJ + "ball");
                ball->set_active(); 
            } 

            filter(home_players, &->query_npc())->command("$wear all"); 
            filter(away_players, &->query_npc())->command("$wear all"); 

            match_state = FIREBALL_MS_FIRST_HALF; 
            match_substate = FIREBALL_MSS_AWAITING_KICKOFF; 
            time_until_next_state = FIREBALL_IVL_FIRST_HALF; 

            if (home_kicking == FIREBALL_KICKING_NORTH) 
                position_home_kicking_north(home_centre, ball, home_players,
                                            away_players);  
            else
                position_home_kicking_south(home_centre, ball, home_players,
                                            away_players); 

            match_alarm = set_alarm(itof(FIREBALL_IVL_KICKOFF_MAX), 0.0, 
                                    next_match_state); 
            check_npc_kickoff(); 
            freport("\nA gong sounds once indicating kick-off for the " +
                    "first half.\n", ({ })); 
            break; 

        case FIREBALL_MS_FIRST_HALF :
            freport("\nA gong sounds three times indicating half time.\n", 
                   ({ }));
            in_play = 0;  
            stop_npc_teams(); 
            (ball->query_current_dribbler())->command("$frelease"); 
            match_state = FIREBALL_MS_HALF_TIME; 
            match_alarm = set_alarm(itof(FIREBALL_IVL_HALF_TIME), 0.0, 
                                    next_match_state); 

            home_centre = !home_has_first_centre;  

            if (home_kicking == FIREBALL_KICKING_SOUTH) 
                configure_kicking(FIREBALL_KICKING_NORTH, 
                                  FIREBALL_KICKING_SOUTH);
            else 
                configure_kicking(FIREBALL_KICKING_SOUTH,
                                  FIREBALL_KICKING_NORTH); 
            position_teams_for_conference(home_players, away_players, 
                                          home_kicking); 
            break; 

        case FIREBALL_MS_HALF_TIME :
            introduce_half(2); 

            match_state = FIREBALL_MS_INTRO_SECOND_HALF; 
            match_alarm = set_alarm(itof(FIREBALL_IVL_INTRO_SECOND_HALF), 
                                    0.0, next_match_state); 
            break; 

        case FIREBALL_MS_INTRO_SECOND_HALF : 
            match_state = FIREBALL_MS_SECOND_HALF; 
            match_substate = FIREBALL_MSS_AWAITING_KICKOFF; 
            time_until_next_state = FIREBALL_IVL_SECOND_HALF; 

            if (home_kicking == FIREBALL_KICKING_NORTH) 
                position_home_kicking_north(home_centre, ball, home_players,
                                            away_players);  
            else
                position_home_kicking_south(home_centre, ball, home_players,
                                            away_players);

            match_alarm = set_alarm(itof(FIREBALL_IVL_KICKOFF_MAX), 0.0, 
                                    next_match_state); 
            check_npc_kickoff(); 
            freport("\nA gong sounds once indicating kick-off for the " +
                    "second half.\n", ({ }));
            break; 

        case FIREBALL_MS_SECOND_HALF : 
            freport("\nA gong sounds three times indicating " +
                    "the end of the match.\n", ({ })); 
            in_play = 0; 
            stop_npc_teams(); 
            match_state = FIREBALL_MS_POST_MATCH; 
            match_alarm = set_alarm(itof(FIREBALL_IVL_POST_MATCH), 0.0, 
                                    next_match_state); 
            register_result(); 
            set_alarm(1.0, 0.0, do_end_match_reaction);
            break; 

        case FIREBALL_MS_POST_MATCH :
            new_game(); 
            break; 
    } 
}


int 
remove_if_npc(object ob) 
{ 
    if (ob->query_npc()) { 
        ob->move_living("M", FIREBALL_TEAM_HANDLER); 
        return 0; 
    } 
    return 1; 
}


/*
 * Function:        reset-game
 * Description:     Resets global game-related variables to empty/zero, 
 *                  clears the arena if parameter is non-zero. 
 */
private int 
reset_game(int clear_arena)
{
    int i; 

    if (match_alarm) { 
        remove_alarm(match_alarm); 
        match_alarm = 0; 
    } 

    if (clear_arena) { 
        move_players_to_locker_room(filter(home_players, remove_if_npc)); 
        move_players_to_locker_room(filter(away_players, remove_if_npc)); 
    } 

    participants = filter(participants, objectp); 
    viewers = filter(viewers, objectp); 
    listeners = filter(listeners, objectp); 

    arena = 
    ({ 
      ({   1,   1,   1,   1,({}),({}),({}),   1,   1,   1,   1 }), 
      ({   1,   1,   1,({}),({}),({}),({}),({}),   1,   1,   1 }), 
      ({   1,   1,({}),({}),({}),({}),({}),({}),({}),   1,   1 }), 
      ({   1,({}),({}),({}),({}),({}),({}),({}),({}),({}),   1 }), 
      ({({}),({}),({}),({}),({}),   1,({}),({}),({}),({}),({}) }), 
      ({({}),({}),({}),({}),   1,   1,   1,({}),({}),({}),({}) }), 
      ({({}),({}),({}),({}),({}),   1,({}),({}),({}),({}),({}) }), 
      ({   1,({}),({}),({}),({}),({}),({}),({}),({}),({}),   1 }), 
      ({   1,   1,({}),({}),({}),({}),({}),({}),({}),   1,   1 }), 
      ({   1,   1,   1,({}),({}),({}),({}),({}),   1,   1,   1 }), 
      ({   1,   1,   1,   1,({}),({}),({}),   1,   1,   1,   1 }) 
    });  

    stop_npc_teams(); 
    home_team_manager->remove_object();
    away_team_manager->remove_object(); 
    home_team_manager_file = away_team_manager_file = 
        FIREBALL_ARROW_FORMATION_FILE; 
    time_until_next_state = 0; 
    time_until_next_substate = 0; 
    npcs_home = 0; 
    npcs_away = 0; 
    home_kicking = 0;
    away_kicking = 0; 
    match_state = FIREBALL_MS_NO_MATCH; 
    match_substate = 0; 
    home_has_first_centre = 0; 
    home_centre = 0; 
    home_score = 0; 
    away_score = 0; 
    in_play = 0; 
    training_match = 0; 
    home_scorers = ([ ]); 
    away_scorers = ([ ]); 
    last_arena_start = ([ ]); 
    home_team_name = ""; 
    away_team_name = ""; 
    home_player_names = ({ }); 
    away_player_names = ({ }); 
    home_players = ({ }); 
    away_players = ({ }); 

    return 1;
}


int
query_match_alarm_going()
{
    return (match_alarm && get_alarm(match_alarm)); 
}


/* 
 * Function:        save_game
 * Description:     Save all details of the current game to the 
 *                  game save file.
 */
private void
save_game()
{
    mixed al;

    seteuid(getuid()); 
    if (match_alarm && (al = get_alarm(match_alarm))) {
        if (stringp(match_substate)) 
            time_until_next_substate = ftoi(al[2]); 
        else
            time_until_next_state = ftoi(al[2]); 
    } 
    save_object(FIREBALL_GAME_SAVE); 
}


/* 
 * If this is removed when something important is in 
 * progress there should be some security, so we save it. 
 */ 
void
remove_object()
{
    save_game(); 
    ::remove_object(); 
}

/* E N D   O F   M A T C H   C O N T R O L   F U N C T I O N S */ 



/* S T A R T   O F   L O C A T I O N   F U N C T I O N S */ 

/* 
 * Function:    enter_stand 
 * Description: called when someone enters the stand.  
 *              These people will be able to see events occurring in 
 *              the arena. 
 */ 
void
enter_stand(object tp, object from)
{
    viewers = filter(viewers, objectp);
    if (objectp(tp) && member_array(tp, viewers) == -1)
        viewers += ({ tp });
}

/* 
 * Function:    leave_stand 
 * Description: called when someone leaves the stand.  
 */ 
void
leave_stand(object tp, object dest)
{
    viewers = filter(viewers, objectp);
    viewers -= ({ tp });
}


/* 
 * Function:    enter_outside
 * Description: Called when someone enters a room outside the arena
 *              but in its vicinity.  
 *              These people will be able to hear some events occurring 
 *              in the arena. 
 */ 
void
enter_outside(object tp, object from, object to)
{
   listeners = filter(listeners, objectp);  
   if (objectp(tp) && member_array(tp, listeners) == -1)
       listeners += ({ tp }); 
}


/* 
 * Function:    leave_outside
 * Description: Called when someone leaves a room outside the arena
 *              but in its vicinity.  
 */ 
void
leave_outside(object tp, object from, object to)
{
   listeners = filter(listeners, objectp);  
   listeners -= ({ tp }); 
}


int
should_see(object onlooker, object *where_not)
{
    if (objectp(onlooker) &&
        member_array(environment(onlooker), where_not) == -1)
        return 1;
    else
        return 0;
}


/* Report a message to the viewers and participants, with vbfc support */ 
void 
report(string message, object *where_not) 
{
    (viewers + (sizeof(where_not) ?
                          filter(participants, &should_see(,where_not)) : 
                          participants))->catch_msg(message); 
}


/* Fast report of a message to viewers and participants, no vbfc checks */ 
void
freport(string message, object *where_not) 
{
    (viewers + (sizeof(where_not) ?
                          filter(participants, &should_see(,where_not)) : 
                          participants))->catch_tell(message); 
}


/* 
 * Function:    enter_arena 
 * Description: called from an arena room when someone enters the arena
 *              from a non-arena room. 
 */ 
void
enter_arena(object tp, object from, object to)
{
     int pkd, room_y, *coords;
     string s, relocate, msg;
     object pobj; 

     if (!objectp(tp)) 
         return;

     relocate = msg = 0;  

     if (objectp(from) && (file_name(from) == OWN_STATUE)) {
         s = " returns to the arena from the ethereal sidelines.\n"; 
         tp->remove_prop(FIREBALL_LIVE_I_LINKDEAD_FROM_ARENA);

         if ((member_array(tp, home_players) == -1) &&
             (member_array(tp, away_players) == -1)) {
             msg = "for the locker room chased by a couple of " + 
                   "guards"; 
             relocate = (FIREBALL_SURROUND + "locker_room");
         }  
         /* If someone returns from linkdeath when kickoff is 
            being awaited we have to make sure they haven't 
            returned to a room in the other team's half. If
            they have, move them back to default position. */ 
         else if (match_substate == FIREBALL_MSS_AWAITING_KICKOFF) {
             pkd = tp->query_prop(FIREBALL_LIVE_I_KICK_DIRECTION); 
             room_y = to->query_y();
             if ((pkd == FIREBALL_KICKING_NORTH && room_y > 5) ||
                 (pkd == FIREBALL_KICKING_SOUTH && room_y < 7)) {
                 relocate = last_arena_start[tp->query_real_name()];
                 msg = "hurriedly back into position"; 
             }   
         } 
     }
     else
         s = " enters the arena.\n";

     participants = filter(participants, objectp); 

     report(to->short() + ": " + QCTNAME(tp) + s, ({ to })); 

#ifdef NO_TELLS_FOR_NPCS 
     if (!tp->query_npc()) 
#endif 
     if (member_array(tp, participants) == -1) 
         participants += ({ tp }); 

     if (!objectp(pobj = present(FIREBALL_PLAYER_OBJ_ID, tp))) { 
         seteuid(getuid()); 
         clone_object(FIREBALL_PLAYER_OBJ)->move(tp); 
     } 
     else 
         pobj->cancel_remove_object_after_delay(); 

     if (stringp(relocate)) 
         set_alarm(0.0, 0.0, &position_player(tp, msg, relocate,
                                              last_arena_start)); 
} 


/* 
 * Function:    leave_arena 
 * Description: called from an arena room when someone leaves the arena 
 *              to a non-arena room. 
 */ 
void
leave_arena(object tp, object from, object to)
{
     string s;

     if (!objectp(tp) || living(to)) 
         return;

     if (objectp(to) && (file_name(to) == OWN_STATUE)) {
         s = " leaves the arena for the ethereal sidelines.\n";
         tp->add_prop(FIREBALL_LIVE_I_LINKDEAD_FROM_ARENA, 1); 
     }  
     else
         s = " leaves the arena.\n"; 

     participants = filter(participants, objectp);
     participants -= ({ tp });

     present(FIREBALL_PLAYER_OBJ_ID, tp)->remove_object_after_delay();

     report(from->short() + ": " + QCTNAME(tp) + s, ({ from })); 
}


/* 
 * Function:    enter_arena_location
 * Description: called from an arena room when someone enters it.
 */ 
void
enter_arena_location(object pl, object room)
{ 
    xl = room->query_real_x(); 
    yl = room->query_real_y();
    arena[yl][xl] += ({ pl }); 
}


/* 
 * Function:    leave_arena_location
 * Description: called from an arena room when someone leaves it.
 */ 
void
leave_arena_location(object pl, object room)
{
    xl = room->query_real_x(); 
    yl = room->query_real_y();
    arena[yl][xl] -= ({ pl });  
}


/* 
 * Function:     update_ball_location
 * Description:  Called from an active ball when it moves. 
 */ 
void
update_ball_location(object the_ball, object from, object to)
{ 
    int x, y; 

    if (the_ball != ball) 
        return;

    if (objectp(from)) { 
        x = from->query_real_x(); 
        y = from->query_real_y(); 
        if (x != 0 || y != 0) 
            arena[y][x] -= ({ the_ball }); 
    } 

    if (objectp(to)) { 
        x = to->query_real_x(); 
        y = to->query_real_y(); 
        if (x != 0 || y != 0)
            arena[y][x] += ({ the_ball }); 
    } 
}

/*  E N D   O F   L O C A T I O N    F U N C T I O N S  */



/* A C T I O N   F U N C T I O N S   S T A R T   H E R E */ 


/* 
 * Function:     made_kickoff
 * Description:  End the "awaiting kickoff" sequence and restart the game
 */ 
private void
made_kickoff()
{
    if (match_substate == FIREBALL_MSS_AWAITING_KICKOFF) {
        remove_alarm(match_alarm); 
        match_substate = 0; 
        time_until_next_substate = 0; 
        match_alarm = 
            set_alarm(itof(time_until_next_state), 0.0, next_match_state);
        start_npc_teams(); 
        freport(sprintf("%70|s", "!! Game on !!\n"), ({ }));
        in_play = 1; 
    } 
}


/* 
 * Function:      query_ball_vector
 * Description:   returns a vector for the path of a ball
 *                across the arena, for use in move_ball() 
 */ 
mixed
query_ball_vector(int x1, int y1, int x2, int y2)
{
    int x, y, absx, absy, mult, rem; 
    mixed v = ({ 0, 0, 0 }); 

    x = 100 * (x2 - x1); 
    y = 100 * (y2 - y1); 

    /* Aiming for the goal is treated as directed at the line */
    if (y2 == 12) {
        y -= 51; 
    } 
    else if (y2 == 0) {
        y += 51; 
    } 

    absx = ABS(x); 
    absy = ABS(y); 

    if (x == 0 || absy > absx) {
        mult = 100000 / y; 
    }
    else if (y == 0 || absx > absy) {
        mult = 100000 / x; 
    } 
    else {
        mult = min(100000 / x, 100000 / y); 
    } 

    mult = ABS(mult); 

    v[0] = (x = (x * mult) / 1000); 
    v[1] = (y = (y * mult) / 1000); 

    if (absx == 0 || (absy > absx * 2)) {
        if (y > 0) 
            v[2] = "north"; 
        else
            v[2] = "south";
    }
    else if (absy == 0 || (absx > absy * 2)) {
        if (x > 0) 
            v[2] = "east"; 
        else
            v[2] = "west"; 
    }
    else if (x > 0) {
        if (y > 0)
            v[2] = "northeast"; 
        else
            v[2] = "southeast"; 
    } 
    else {
        if (y > 0)
            v[2] = "northwest"; 
        else
            v[2] = "southwest"; 
    } 

    return v; 
}


/* 
 * Function:     query_rebound
 * Description:  if the point (hit_x, hit_y) is in the fire, return 
 *               the type of rebound given that the ball arrived 
 *               from point (from_x, from_y). 
 */ 
int
query_rebound(int from_x, int from_y, int hit_x, int hit_y)
{
/*  
 *        4   5   6   7   8 
 *  8       |   |   |   |
 *  7   |   |   |###|   |   |
 *  6   |   |###|###|###|   |
 *  5   |   |   |###|   |   |
 *  4       |   |   |   |
 */ 

    switch (hit_x) {
        case 5  : 
            if (hit_y == 6) {
                if (from_x == hit_x) 
                    return (FIREBALL_REBOUND_X | FIREBALL_REBOUND_Y); 
                return FIREBALL_REBOUND_X; 
            } 
            return 0; 
            break;
        case 6 : 
            switch (hit_y) {
                case 5 : 
                    if (from_y == hit_y)
                        return (FIREBALL_REBOUND_X | FIREBALL_REBOUND_Y); 
                    return FIREBALL_REBOUND_Y; 
                    break; 
                case 6 :  
                    return (FIREBALL_REBOUND_X | FIREBALL_REBOUND_Y); 
                    break; 
                case 7 : 
                    if (from_y == hit_y)
                        return (FIREBALL_REBOUND_X | FIREBALL_REBOUND_Y); 
                    return FIREBALL_REBOUND_Y; 
                    break; 
            } 
            return 0; 
            break;
        case 7 :
            if (hit_y == 6) {
                if (from_x == hit_x) 
                    return (FIREBALL_REBOUND_X | FIREBALL_REBOUND_Y); 
                return FIREBALL_REBOUND_X; 
            } 
            return 0;  
            break;
    } 
    return 0; 
}


/* 
 * Function:     move_ball
 * Description:  Tries to execute a move of the ball from 
 *               one room to another in the Firedrome arena
 *               given the start and end co-ordinates. If the
 *               value of the test variable is non-zero, the
 *               hypothetical move will be checked, otherwise 
 *               the move will be carried out for real. 
 *               Returns 1 for success, 0 for failure, 
 *               -1 for a bad pass if this is a test. 
 */ 
int
move_ball(int x1, int y1, int x2, int y2, int test, 
               object target, int shot, int far)
{
    int next_to_goal, change_x, change_y, last_x, last_y, 
        target_distance, kick_distance, start_x, start_y, next_x, 
        next_y, distance_moved, pkd, tmp, bad_pass;  
    object pl, next_room, old_room, opponent, controller;
    string str; 
    mixed v; 

    /* Begin initial checks for legality of ball move */ 
    if (x1 == x2 && y1 == y2) {
        if (!test)
            notify_fail("That's kicking the ball no distance!\n"); 
        return 0;
    } 

    if (file_size(query_arena_room_path(x2, y2)) == -1) { 
        if (!test) 
            notify_fail("That is not a valid coordinate " +
                        "in the arena!\n"); 
        return 0;
    } 

    target_distance = query_distance(x1, y1, x2, y2); 

    if (target_distance > 425) {
        if (!far) {
            if (!test)
                notify_fail("That is too far to kick the ball.\n"); 
            return 0; 
        } 
        kick_distance = 425; 
    } 
    else {
       if (shot)
           kick_distance = shot; 
       else
           kick_distance = target_distance; 
    } 

    next_room = old_room = environment(pl = this_player());  

    v = query_ball_vector(x1, y1, x2, y2); 

    /* Give the message for the initial kick for a pass or shot */ 
    if (!test) { 
        if (x2 == 6 && (y2 == 12 || y2 == 0)) {
            if (shot) {
                switch (shot / 100) {
                    case 1 : 
#ifdef NO_TELLS_FOR_NPCS
                        if (interactive(pl))
#endif
                        write("You steer the ball goalwards!\n"); 
                        say(str = (QCTNAME(pl) + " steers the ball " +
                            "goalwards!\n")); 
                        report(old_room->short() + ": " + str, 
                               ({ old_room })); 
                        break; 
                    case 2 : 
#ifdef NO_TELLS_FOR_NPCS
                        if (interactive(pl))
#endif
                        write("You shoot!\n"); 
                        say(str = (QCTNAME(pl) + " shoots!\n")); 
                        report(old_room->short() + ": " + str, 
                               ({ old_room })); 
                        break; 
                    case 3 : 
#ifdef NO_TELLS_FOR_NPCS
                        if (interactive(pl))
#endif
                        write("You hammer the ball goalwards!\n"); 
                        say(str = (QCTNAME(pl) + " hammers the ball " +
                            "goalwards!\n")); 
                        report(old_room->short() + ": " + str, 
                               ({ old_room })); 
                        break; 
                    case 4 : 
#ifdef NO_TELLS_FOR_NPCS
                        if (interactive(pl))
#endif
                        write("You blast the ball towards goal!\n"); 
                        say(str = (QCTNAME(pl) + " blasts the ball " +
                            "towards goal!\n")); 
                        report(old_room->short() + ": " + str, 
                               ({ old_room })); 
                        break; 
                 } 
            } 
            else { 
                notify_fail("You can't pass there.\n"); 
                return 0;
            } 
        } 
        else {  
            tmp = (kick_distance / 100) - 1; 
            pkd = random(sizeof(FIREBALL_KICK[tmp])); 
            if (objectp(target)) { 
#ifdef NO_TELLS_FOR_NPCS
                if (interactive(pl))
#endif
                write("You " + FIREBALL_KICK[tmp][pkd] + 
                      " the ball " + v[2] + " towards " + 
                      target->query_the_name(pl) + ".\n"); 
                say(str = (QCTNAME(pl) + " " + 
                    FIREBALL_KICKS[tmp][pkd] + 
                    " the ball " + v[2] + " towards " + 
                    QTNAME(target) + ".\n"));
#ifdef NO_TELLS_FOR_NPCS
                if (interactive(target))
#endif
                tell_object(target, pl->query_The_name(target) + 
                    FIREBALL_KICKS[tmp][pkd] + 
                    " the ball " + v[2] + " towards you.\n"); 
                tell_room(environment(target), str, target); 
                report(old_room->short() + ": " + str, 
                      ({ old_room, environment(target) })); 
            } 
            else {
#ifdef NO_TELLS_FOR_NPCS
                if (interactive(pl))
#endif
                write("You " + FIREBALL_KICK[tmp][pkd] + 
                      " the ball " + v[2] + ".\n"); 
                say(str = (QCTNAME(pl) + " " + 
                    FIREBALL_KICKS[tmp][pkd] + 
                    " the ball " + v[2] + ".\n"));
                report(old_room->short() + ": " + str, 
                      ({ old_room })); 
            } 
        } 
        ball->set_current_dribbler(0); 
        ball->set_last_kicker(pl); 
    } 


    /* Set up variables prior to the move loop */ 
    pkd = pl->query_prop(FIREBALL_LIVE_I_KICK_DIRECTION); 

    next_to_goal = bad_pass = 0; 

    start_x = last_x = x1; 
    start_y = last_y = y1; 

    x1 = last_x * 100 + 50 + v[0]; 
    y1 = last_y * 100 + 50 + v[1]; 

    next_x = x1 / 100; 
    next_y = y1 / 100; 
    if (next_to_goal = shot && (next_y == 12 || next_y == 0))
        next_x = 6;  
    distance_moved = query_distance(start_x, start_y, next_x, next_y); 


    /* And now the actual move loop */ 
    while (distance_moved <= kick_distance) {
        /* If there is a possible intercepted pass or saved shot, 
           work out whether it succeeds i.e. if the passage of the 
           ball stops here */ 
        if (in_play &&
            objectp(opponent = find_first_opponent(old_room, pl, pkd))) 
        {
            if (test)
                 bad_pass = 1;
            /* Successful interception?? */ 
            else if (opponent->resolve_task(next_to_goal ? 
                    TASK_SIMPLE + ((TASK_SIMPLE * 
                                   (kick_distance - distance_moved + 50)) 
                                   / 125) : 
                    TASK_ROUTINE + ((TASK_SIMPLE * 
                                    (kick_distance - distance_moved + 100)) 
                                   / 100), 
                    ({ TS_DEX })) > 0) 
            {
#ifdef NO_TELLS_FOR_NPCS
                if (interactive(opponent))
#endif
                tell_object(opponent, "You" + 
                            (next_to_goal ? " save!" : " intercept!") + "\n"); 
                tell_room(old_room, str = (QCTNAME(opponent) + 
                          (next_to_goal ? " saves!" : " intercepts!") + "\n"), 
                          opponent);
                report(old_room->short() + ": " + str, ({ old_room })); 
                opponent->command("$fcontrol");  
                return 1;
            } 
            /* Nope, a failed interception */ 
            else {
                if (next_to_goal) {
#ifdef NO_TELLS_FOR_NPCS
                    if (interactive(opponent))
#endif
                    tell_object(opponent, "You fail to save!\n");
                    tell_room(old_room, (str = QCTNAME(opponent) +
                                         " fails to save!\n"), 
                              opponent);
                    report(old_room->short() + ": " + str, ({ old_room })); 
                } 
                else {
#ifdef NO_TELLS_FOR_NPCS
                    if (interactive(opponent))
#endif
                    tell_object(opponent, "You fail to intercept.\n");
                    tell_room(old_room, QCTNAME(opponent) +
                                        " fails to intercept.\n", 
                              opponent);
                } 
            } 
        } 

        /* 
           If the next room is inside a goal net, we have to check if 
           a goal is scored, based on the kick distance and power 
           and stats of the player. 
         */ 
        if (next_to_goal) {
            /* 
               Check for a rebound of the ball against a wall 
               next to the goal.
            */
            if ((tmp = pl->resolve_task(TASK_SIMPLE + 
                         (TASK_SIMPLE * max(target_distance, shot / 2)) /
                          100, ({ TS_DEX }))) <= 0) { 
                if (tmp < -75)  
                    freport(old_room->short() + ": The ball impacts " +
                           "extremely wide of goal.\n", ({ })); 
                else if (tmp < -55) 
                    freport(old_room->short() + ": The ball impacts " +
                           "considerably wide of goal.\n", ({ })); 
                else if (tmp < -33) 
                    freport(old_room->short() + ": The ball impacts wide of " +
                           "goal.\n", ({ }));
                else if (tmp < -9)  
                    freport(old_room->short() + ": The ball impacts narrowly " +
                            "wide of goal!\n", ({ })); 
                else  
                    freport(old_room->short() + ": The ball hits the " + 
                            ({"left", "right"})[random(2)] + 
                            " goal post!\n", ({ }));

                /* As there was a rebound, recalculate the kick parameters */ 
                if ((kick_distance -= distance_moved) < 0) 
                   break;  
                start_x = last_x; 
                start_y = last_y; 
                v[1] = -v[1]; /* reflect vertically! */ 
                x1 = last_x * 100 + 50 + v[0]; 
                y1 = last_y * 100 + 50 + v[1]; 
                next_x = x1 / 100; 
                next_y = y1 / 100; 
                shot = 0; 
                next_to_goal = 0; 
                distance_moved = query_distance(start_x, start_y, 
                                                next_x, next_y); 
                continue; /* the move loop */ 
            } 
        } 
        else {
            /* 
               Check for a rebound of the ball against the wall around 
               the fire.
             */ 
            if (tmp = query_rebound(last_x, last_y, 
                                    next_x, next_y)) {
                if (test)
                    return 0; 
                freport(old_room->short() + ": The ball hits " +
                        "the wall around the fire.\n", ({old_room}));
                tell_room(old_room, "The ball hits the wall " +
                        "around the fire.\n");

                if ((kick_distance -= distance_moved) < 0)
                    break; 

                start_x = last_x; 
                start_y = last_y; 
                if (tmp & FIREBALL_REBOUND_X) 
                    v[0] = -v[0];
                if (tmp & FIREBALL_REBOUND_Y)  
                    v[1] = -v[1]; 
                x1 = last_x * 100 + 50 + v[0]; 
                y1 = last_y * 100 + 50 + v[1];
                next_x = x1 / 100; 
                next_y = y1 / 100; 
                distance_moved = query_distance(start_x, start_y, 
                                                next_x, next_y); 
                continue; /* the move loop */ 
            }
        } 

        next_room = query_arena_room_path(next_x, next_y)->get_this_object(); 

        /* If the ball can't be moved to the next room, return failure */ 
        if (!test && ball->move(next_room))
            return 0;

        /* Provide messages for the moving ball */ 
        if (!test) { 
            str = ""; 
            change_x = next_x - last_x; 
            change_y = next_y - last_y; 
            if (change_y > 0)
                str = "north"; 
            else if (change_y < 0) 
                str = "south"; 
            if (change_x > 0)
                str += "east"; 
            else if (change_x < 0) 
                str += "west"; 
            tell_room(old_room, "The ball rolls " + str + ".\n"); 
            tell_room(next_room, "The ball rolls in.\n"); 
        }

        /* If a goal was scored, report it and call the goal admin function */ 
        if (next_to_goal) {
            if (!stringp(match_substate) && 
                (match_state == FIREBALL_MS_FIRST_HALF ||
                 match_state == FIREBALL_MS_SECOND_HALF)) { 
                freport(sprintf("%70|s", "!! G O A L !!\n"), ({ })); 
                score_goal(pl);
                return 1;  
            } 
            else {  
                freport(sprintf("%70|s", "!! Practice goal !!\n"), ({ })); 
                freport(old_room->short() + ": " + (str = "A ball " + 
                       ({ "boy", "girl" })[random(2)] + " fetches " +
                       "the ball from the goal net.\n"), ({ old_room })); 
                tell_room(old_room, str); 
                ball->move(old_room); 
                return 1;  
            } 
        }
        old_room = next_room; 
        /* Find where to move to next and update remaining distance */ 
        last_x = next_x; 
        last_y = next_y; 
        x1 += v[0]; 
        y1 += v[1]; 
        next_x = x1 / 100; 
        next_y = y1 / 100; 
        if (next_to_goal = shot && (next_y == 12 || next_y == 0))
            next_x = 6;  
        distance_moved = query_distance(start_x, start_y, 
                                        next_x, next_y); 
    }

    if (test && bad_pass) 
        return -1; 

    /* Determine possible receivers of the ball. */ 
    if (!objectp(target) || !is_able_to_play(target) || 
        !objectp(present(target, next_room))) 
        target = find_first_team_mate(next_room, pl, pkd); 

    opponent = (in_play && find_first_opponent(next_room, pl, pkd)); 
    if (test) {
        if (objectp(opponent)) 
            return -1; 
        else
            return 1; 
    }

    /* Determine who controls the ball. */ 
    controller = 0; 
    if (objectp(target)) {
        if (objectp(opponent)) {
            if (opponent->resolve_task(TASK_DIFFICULT, 
                                      ({ TS_DEX, TS_WIS }),
                                      target, 
                                      ({ TS_DEX, TS_WIS })) > 0) { 
                controller = opponent;  
#ifdef NO_TELLS_FOR_NPCS
                if (interactive(opponent))
#endif
                tell_object(opponent, "You intercept!\n");  
                tell_room(next_room, 
                          str = (QCTNAME(opponent) + " intercepts!\n"),  
                          opponent);  
                report(next_room->short() + ": " + str, ({ next_room })); 
            } 
            else 
                controller = target;
        } 
        else 
            controller = target;
    } 
    else if (objectp(opponent)) 
        controller = opponent;

    /* Assign control */ 
    if (objectp(controller)) 
        controller->command("$fcontrol"); 
    else 
        freport(next_room->short() + ": The ball stops rolling.\n",  
               ({ next_room })); 

    made_kickoff(); 
    return 1;
}



/* 
 * Function:     do_kick
 * Description:  An action function. 
 *               Tries to execute a kick to a relative position.  
 */ 
int
do_kick(string str, int far)
{
    object tp, current_dribbler; 
    int x1, y1, x2, y2; 

    tp = this_player(); 

    if (!objectp(ball) || !present(ball, environment(tp))) { 
        notify_fail("The ball is not here!\n"); 
        return 0; 
    } 

    if (!objectp(current_dribbler = ball->query_current_dribbler()) ||
        current_dribbler != tp) {
        notify_fail("You need to be controlling the ball in " +
                    "order to kick it.\n"); 
        return 0;
    } 

    if (!stringp(str) || !strlen(str)) { 
        notify_fail("Kick the ball where?\n"); 
        return 0;
    } 

    if (sscanf(str, "%d %d", x2, y2) == 2) {
        x1 = environment(tp)->query_x(); 
        y1 = environment(tp)->query_y(); 
        return move_ball(x1, y1, x1 + x2, y1 + y2, 0, 0, 0, far);
    }

    notify_fail("Kick the ball where?\n"); 
    return 0; 
}



/* 
 * Function:     do_pass
 * Description:  An action function. 
 *               Tries to execute a pass to a specified team position
 *               (d(efence), l(eft), r(ight), a(ttack)) or to a named 
 *               team-mate or a specified co-ordinate. 
 */ 
int
do_pass(string str, int far)
{
    object tp = this_player(); 
    object *players, current_dribbler; 
    int e, k, x1, y1, x2, y2; 

    if (!objectp(ball) || !present(ball, environment(tp))) { 
        notify_fail("The ball is not here!\n"); 
        return 0; 
    } 

    if (!objectp(current_dribbler = ball->query_current_dribbler()) ||
        current_dribbler != tp) {
        notify_fail("You need to be controlling the ball in " +
                    "order to pass it.\n"); 
        return 0;
    } 

    if (!stringp(str) || !strlen(str)) { 
        notify_fail("Pass the ball where?\n"); 
        return 0;
    } 

    if (sscanf(str, "%d %d", x2, y2) == 2) {
        x1 = environment(tp)->query_x(); 
        y1 = environment(tp)->query_y(); 
        return move_ball(x1, y1, x2, y2, 0, 0, 0, far);
    }

    if (member_array(tp, home_players) > -1) 
        players = home_players; 
    else if (member_array(tp, away_players) > -1) 
        players = away_players; 
    else {
        notify_fail("You aren't a member of a fireball team.\n"); 
        return 0; 
    } 

    str = lower_case(str); 
    k = -1; 
    switch (str) {
        case "d"       : 
        case "defence" :  k = 0; 
                          break; 
        case "l"       : 
        case "left"    :  k = 1; 
                          break; 
        case "r"       : 
        case "right"   :  k = 2; 
                          break; 
        case "a"       : 
        case "attack"  :  k = 3; 
                          break; 
        default :
                   for (e = 0; e < 4; e++) {
                       if (players[e]->query_real_name() == str) {
                           k = e; 
                           break; 
                       } 
                   }
                   break; 
    }

    if (k == -1 || !objectp(players[k])) {
        notify_fail("There is no such player or position in your team.\n"); 
        return 0; 
    } 

    x1 = environment(tp)->query_x(); 
    y1 = environment(tp)->query_y(); 
    x2 = environment(players[k])->query_x(); 
    y2 = environment(players[k])->query_y(); 
    return move_ball(x1, y1, x2, y2, 0, players[k], 0, far); 
}


/* 
 * Function:     do_release
 * Description:  An action function to release control of the ball. 
 */ 
int
do_release(string str)
{ 
    object tp, env; 

    if (stringp(str)) {
        notify_fail("Releasing control of the ball requires no argument.\n"); 
        return 0;
    }

    if (!objectp(ball) || environment(ball) != 
                         (env = environment(tp = this_player()))) {
        notify_fail("The ball is not here.\n"); 
        return 0; 
    } 

    if (ball->query_current_dribbler() == tp) {
#ifdef NO_TELLS_FOR_NPCS
        if (interactive(tp))
#endif
        write("You stop controlling the ball.\n"); 
        say(QCTNAME(tp) + " stops controlling the ball.\n"); 
        ball->set_current_dribbler(0); 
        report(env->short() + ": " + QCTNAME(tp) + 
               " releases control of the ball.\n", ({ env })); 
        return 1;
    }

    notify_fail("You do not control the ball.\n"); 
    return 0;
}


/* 
 * Function:     do_control
 * Description:  An action function to control of the ball. 
 */ 
int
do_control(string str)
{ 
    object tp, current_dribbler, env; 

    if (stringp(str)) {
        notify_fail("Controlling of the ball requires no argument.\n"); 
        return 0;
    }

    if (!objectp(ball) || environment(ball) != 
                        (env = environment(tp = this_player()))) {
        notify_fail("The ball is not here.\n"); 
        return 0; 
    } 

    if ((member_array(tp, home_players) == -1) &&
        (member_array(tp, away_players) == -1)) {
        notify_fail("You aren't a member of a fireball team.\n"); 
        return 0; 
    } 

    if (objectp(current_dribbler = ball->query_current_dribbler())) {
        if (current_dribbler == tp) {
            notify_fail("You already control the ball!\n"); 
            return 0; 
        } 
        else {
            notify_fail("You will have to tackle the person currently " +
                        "controlling the ball first!\n"); 
            return 0;
        } 
    }
    else {
        if (!is_able_to_play(tp)) {
            notify_fail("You are too injured to control the " +
                        "ball!\n"); 
            return 0;
        } 

        ball->set_current_dribbler(tp); 
#ifdef NO_TELLS_FOR_NPCS
        if (interactive(tp))
#endif
        write("You control the ball.\n"); 
        say(QCTNAME(tp) + " controls the ball.\n"); 
        report(env->short() + ": " + QCTNAME(tp) + 
               " controls.\n", ({ env })); 
        return 1;
    } 
}


/* 
 * Function:     do_shoot
 * Description:  An action function to execute a shot on goal. 
 */ 
int
do_shoot(string str, int far)
{
    object tp, current_dribbler; 
    int p_kd, pwr; 
    int x1, y1, x2, y2; 

    tp = this_player(); 

    if (!objectp(ball) || !present(ball, environment(tp))) { 
        notify_fail("The ball is not here!\n"); 
        return 0; 
    } 

    if (!objectp(current_dribbler = ball->query_current_dribbler()) ||
        current_dribbler != tp) {
        notify_fail("You need to be controlling the ball in " +
                    "order to shoot.\n"); 
        return 0;
    } 

    if ((p_kd = tp->query_prop(FIREBALL_LIVE_I_KICK_DIRECTION)) == 
                FIREBALL_KICKING_NORTH) {
        y2 = 12; 
    }
    else if (p_kd == FIREBALL_KICKING_SOUTH)  {
        y2 = 0; 
    }
    else {
        notify_fail("You aren't a member of a fireball team.\n"); 
        return 0;
    } 
    x1 = environment(tp)->query_x(); 
    y1 = environment(tp)->query_y(); 

    if (str == "min")
        pwr = min(425, query_distance(x1, y1, 6, y2)); 
    else
        pwr = 425; 

    return move_ball(x1, y1, 6, y2, 0, 0, pwr, far); 
} 


/* 
 * Function:     do_tackle
 * Description:  An action function to tackle the player controlling 
 *               the fireball. 
 */ 
int
do_tackle(string str)
{
    object tackler = this_player(); 
    int v, c, rheight, power, rv, hitloc, impact; 
    string *hitloc_descs, hitloc_desc, *adverbs, adverb;
    mixed verb;  
    object current_dribbler = ball->query_current_dribbler(); 
    object room; 

    if (stringp(str)) {
        notify_fail("A fireball tackle requires no argument as only " +
                    "the person dribbling the ball may be tackled.\n"); 
        return 0;
    }

    if (!objectp(ball) || !present(ball, environment(tackler))) {
        notify_fail("The ball isn't here.\n"); 
        return 0;
    }    

    if (!objectp(current_dribbler = ball->query_current_dribbler())) {
        notify_fail("No-one is dribbling the ball.\n"); 
        return 0;
    } 

    if (current_dribbler == tackler) {
        notify_fail("You decide against tackling yourself.\n"); 
        return 0;
    }

    if ((member_array(tackler, home_players) == -1) &&
        (member_array(tackler, away_players) == -1)) {
        notify_fail("You aren't a member of a fireball team.\n"); 
        return 0; 
    } 

    if (tackler->query_prop(FIREBALL_LIVE_I_KICK_DIRECTION) == 
        current_dribbler->query_prop(FIREBALL_LIVE_I_KICK_DIRECTION)) {
        notify_fail("You decide against tackling a team-mate.\n"); 
        return 0;
    } 

    if (!is_able_to_play(tackler)) {  
        notify_fail("You are too injured to attempt a tackle.\n"); 
        return 0;
    } 

    /* 
       Relative height: 100 means tackler and target have 
       same height, 200 means tackler is twice as tall,  
       50 means half. This is used to select the description 
       of the relative move prior to tackling and the selection 
       of the tackle hitloc. 
     */ 
    rheight = ((tackler->query_prop(CONT_I_HEIGHT) * 100) / 
               current_dribbler->query_prop(CONT_I_HEIGHT)); 

    if (rheight >= 200) {
        if (random(2)) {
            impact = FIREBALL_IMPACT_KICK; 
            hitloc = ({ FIREBALL_HITLOC_CHEST, 
                        FIREBALL_HITLOC_ARMS, 
                        FIREBALL_HITLOC_HEAD })[random(3)]; 
        } 
        else { 
            impact = FIREBALL_IMPACT_PUNCH;
            hitloc = FIREBALL_HITLOC_HEAD; 
        }   
    } 
    else if (rheight >= 150) {
        if (random(2)) {
            impact = FIREBALL_IMPACT_KICK; 
            hitloc = ({ FIREBALL_HITLOC_WAIST, 
                        FIREBALL_HITLOC_CHEST, 
                        FIREBALL_HITLOC_ARMS })[random(3)]; 
        } 
        else { 
            impact = FIREBALL_IMPACT_PUNCH;
            hitloc = ({ FIREBALL_HITLOC_CHEST, 
                        FIREBALL_HITLOC_HEAD })[random(2)]; 
        }   
    } 
    else if (rheight <= 50) {
        switch (random(6)) {
            case 0 .. 1 : 
                impact = FIREBALL_IMPACT_KICK; 
                hitloc = FIREBALL_HITLOC_FEET; 
                break;
            case 2 .. 3 : 
                impact = FIREBALL_IMPACT_PUNCH; 
                hitloc = FIREBALL_HITLOC_LEGS; 
                break;
            case 4 .. 5 :
                impact = FIREBALL_IMPACT_BUTT; 
                hitloc = ({ FIREBALL_HITLOC_WAIST, 
                            FIREBALL_HITLOC_LEGS })[random(2)]; 
                break;
        } 
    } 
    else if (rheight <= 75) {
        switch (random(6)) {
            case 0 .. 1: 
                impact = FIREBALL_IMPACT_KICK; 
                hitloc = FIREBALL_HITLOC_LEGS; 
                break;
            case 2 .. 3 : 
                impact = FIREBALL_IMPACT_PUNCH; 
                hitloc = FIREBALL_HITLOC_WAIST; 
                break;
            case 4 .. 5 :
                impact = FIREBALL_IMPACT_BUTT; 
                hitloc = ({ FIREBALL_HITLOC_CHEST,
                            FIREBALL_HITLOC_WAIST,  
                            FIREBALL_HITLOC_ARMS })[random(3)]; 
                break;
        } 
    }  
    else {
        switch (random(5)) {
            case 0 .. 1 : 
                impact = FIREBALL_IMPACT_KICK; 
                hitloc = ({ FIREBALL_HITLOC_LEGS, 
                            FIREBALL_HITLOC_WAIST })[random(2)]; 
                break;
            case 2 .. 3 : 
                impact = FIREBALL_IMPACT_PUNCH; 
                hitloc = ({ FIREBALL_HITLOC_ARMS,
                            FIREBALL_HITLOC_CHEST, 
                            FIREBALL_HITLOC_HEAD })[random(3)]; 
                break;
            case 4 :
                impact = FIREBALL_IMPACT_BUTT; 
                hitloc = FIREBALL_HITLOC_HEAD; 
                break;
        } 
    } 

    verb = FIREBALL_IMPACT_VERB[impact];
    verb = verb[random(sizeof(verb))]; 

    adverbs = FIREBALL_IMPACT_ADVERB[impact];

    /* 
       Relative volume: 100 means tackler and target have 
       same basic volume, 200 means tackler is twice as voluminous,  
       50 means half. This is used in the selection of the  
       hitloc descriptions for tackles. 
     */ 
    rv = ((tackler->query_prop(CONT_I_VOLUME) * 100) / 
           current_dribbler->query_prop(CONT_I_VOLUME)); 

    if (rv >= 150) 
        hitloc_descs = FIREBALL_HITLOCS_BIGGER[hitloc]; 
    else if (rv < 65) 
        hitloc_descs = FIREBALL_HITLOCS_SMALLER[hitloc];  
    else 
        hitloc_descs = FIREBALL_HITLOCS_EQUAL[hitloc]; 

    hitloc_desc = hitloc_descs[random(sizeof(hitloc_descs))]; 

    room = environment(tackler); 

    if (random(tackler->query_stat(SS_DEX) + 
               tackler->query_stat(SS_DIS)) < 
        random(current_dribbler->query_stat(SS_DEX) + 
               current_dribbler->query_stat(SS_DIS) / 2)) {
        report(room->short() + ": " + 
              (str = (QCTNAME(tackler) + 
                     " fails to " + verb[0] + " " + 
                     QTNAME(current_dribbler) + ".\n")), 
              ({ room })); 
        tell_room(room, str, ({ tackler, current_dribbler }));
#ifdef NO_TELLS_FOR_NPCS
        if (interactive(tackler))
#endif
        tell_object(tackler, "You fail to " + verb[0] + " " + 
                    current_dribbler->query_the_name(tackler) + 
                    ".\n"); 
#ifdef NO_TELLS_FOR_NPCS
        if (interactive(current_dribbler))
#endif
        tell_object(current_dribbler, 
                    tackler->query_The_name(current_dribbler) +
                    " fails to " + verb[0] + " you.\n");  
        return 1;
    }

    c = min(max(15, (tackler->query_stat(SS_STR) * 2) / 5), 75); 
    v = min(max(20, (tackler->query_stat(SS_DIS) * 2) / 3), 100); 

    /* Power of the tackle */ 
    if (power = min(max_power - 1, random(F_PENMOD(c, v))))  
        current_dribbler->heal_hp(-power); 

    v = (power * sizeof(adverbs)) / max_power; 
    if (v == 0 && (power > (current_dribbler->query_hp() / 10))) 
        v = 1;  

    if (strlen(adverb = adverbs[v])) 
        adverb = " " + adverb;  

    report(room->short() + ": " + 
              (str = (QCTNAME(tackler) + 
              " " + verb[1] + " " + QTNAME(current_dribbler) +
              "'s " +  hitloc_desc + adverb + ".\n")),
               ({ room })); 
    tell_room(room, str, ({ tackler, current_dribbler })); 

#ifdef NO_TELLS_FOR_NPCS
    if (interactive(tackler))
#endif
    tell_object(tackler, "You " + verb[0] + " " + 
                         current_dribbler->query_the_name(tackler) + 
                         "'s " + hitloc_desc + adverb + ".\n"); 

#ifdef NO_TELLS_FOR_NPCS
    if (interactive(current_dribbler))
#endif
    tell_object(current_dribbler, 
                tackler->query_The_name(current_dribbler) + 
                " " + verb[1] + " your " + hitloc_desc + 
                adverb + ".\n"); 

    if (v) {
        present(FIREBALL_PLAYER_OBJ_ID, 
                current_dribbler)->set_recovering( 
                    ftoi(FIREBALL_TACKLE_STUN_INTERVAL), 1); 
        ball->set_current_dribbler(0); 
        tackler->command("$fcontrol"); 
    } 

    return 1; 
}


/* 
 * Function:      player_dribble
 * Description:   Action function for dribbling the ball
 */ 
int
do_player_dribble(object tp, string run_verb_fps, string run_verb_tps)
{
    int c; 
    object old_room, opponent;
    mixed exits, move_to; 
    string verb; 

    verb = query_verb(); 

    old_room = environment(tp); 
    exits = old_room->query_exit(); 

    move_to = 0; 
    for (c = 1; c < sizeof(exits); c += 3) {
        if (exits[c] == verb)
            move_to = exits[c-1];  
    }

    if (!move_to) { 
        notify_fail("You cannot " + run_verb_fps + 
                    " in that direction.\n"); 
        return 0;
    } 

    seteuid(getuid()); 
    move_to = move_to->get_this_object(); 

    if (!objectp(move_to) || !IS_FIREBALL_ARENA_ROOM(move_to)) { 
        notify_fail("You cannot " + run_verb_fps + 
                    " in that direction.\n"); 
        return 0; 
    } 

    tell_room(old_room, QCTNAME(tp) + " " + run_verb_tps + " " + 
                        verb + " dribbling the ball.\n", tp);
    ball->move(move_to); 
    tp->move_living("M", move_to);
    report(old_room->short() + ": " + QCTNAME(tp) + 
           " " + run_verb_tps + " " + verb + ".\n", 
           ({ old_room, move_to })); 
    tell_room(move_to, QCTNAME(tp) + " " + run_verb_tps + 
                       " in dribbling the ball.\n", tp); 

    if (in_play &&
        objectp(opponent = find_first_opponent(move_to, tp, 
                tp->query_prop(FIREBALL_LIVE_I_KICK_DIRECTION)))) 
        opponent->command("$ftackle"); 

    made_kickoff(); 

    return 1;
}


/* 
 * Function:     do_player_run
 * Description:  Action function to run in the arena.
 */ 
int
do_player_run(object tp, string run_verb_fps, string run_verb_tps)
{
    int c; 
    object old_room, current_dribbler; 
    mixed exits, move_to; 
    string verb = query_verb(); 

    old_room = environment(tp); 
    exits = old_room->query_exit(); 

    move_to = 0; 
    for (c = 1; c < sizeof(exits); c += 3) {
        if (exits[c] == verb)
            move_to = exits[c-1];  
    }

    if (!move_to) { 
        notify_fail("You cannot " + run_verb_fps + 
                    " in that direction.\n"); 
        return 0;
    } 

    seteuid(getuid()); 
    move_to = move_to->get_this_object(); 

    if (!objectp(move_to)) { 
        notify_fail("You cannot " + run_verb_fps + 
                    " in that direction.\n"); 
        return 0; 
    } 

    if (match_substate == FIREBALL_MSS_AWAITING_KICKOFF &&
        move_to->query_y() == 6) {
        notify_fail("You can't go there until kick off.\n"); 
        return 0;
    }

    if (!is_able_to_play(tp)) 
        run_verb_tps = "crawls"; 

    tell_room(old_room, QCTNAME(tp) + " " + run_verb_tps + " " +
                        verb + ".\n", tp); 
    tp->move_living("M", move_to); 
    tell_room(move_to, QCTNAME(tp) + " " + run_verb_tps + " in.\n", tp); 
    if (run_verb_tps != "crawls" && 
        objectp(present(ball, move_to))) {
        if (!objectp(current_dribbler = ball->query_current_dribbler()))
            tp->command("$fcontrol"); 
        else if (current_dribbler->query_prop(FIREBALL_LIVE_I_KICK_DIRECTION) 
                 != tp->query_prop(FIREBALL_LIVE_I_KICK_DIRECTION))
            tp->command("$ftackle"); 
    } 

    return 1;
}


/* 
 * Function:     do_player_move
 * Description:  Action function to move on the pitch, either running or  
 *               dribbling the ball. 
 */ 
int
do_player_move(string str, string run_verb_fps, string run_verb_tps)
{
    object tp, current_dribbler; 

    tp = this_player(); 

    if (!objectp(ball) || 
        !objectp(current_dribbler = ball->query_current_dribbler()) || 
        tp != current_dribbler)
        return do_player_run(tp, run_verb_fps, run_verb_tps); 

    return do_player_dribble(tp, run_verb_fps, run_verb_tps); 
}


/* 
 * Function:     do_shout
 * Description:  Action function to shout across the arena.
 */ 
int
do_shout(string str)
{
    object room = environment(this_player()); 

    if (!stringp(str) || !strlen(str)) { 
        notify_fail("Shout what?\n"); 
        return 0;
    } 

    if ((match_state == FIREBALL_MS_FIRST_HALF ||
         match_state == FIREBALL_MS_SECOND_HALF) &&
         !stringp(match_substate)) {
        notify_fail("Shouting during play won't carry as there is " +
                    "too much noise.\n"); 
        return 0;
    } 

#ifdef NO_TELLS_FOR_NPCS
    if (interactive(this_player()))
#endif
    write("You shout: " + str + "\n");  
    say(QCTNAME(this_player()) + " shouts: " + str + "\n"); 
    report(room->short() + ": " + 
           QCTNAME(this_player()) + " shouts: " + str + "\n", 
           ({ room })); 

    return 1;
}


/*
 * Function:     do_terminate_match
 * Description:  Action function to terminate the current match, an 
 *               emergency stop.  
 * 
 */ 
int
do_terminate_match(string reason)
{
    object tp = this_player(); 

    seteuid(getuid()); 

    if (!SECURITY->valid_write(file_name(this_object()), tp, write_file)) {
        notify_fail("You do not have the authority to do that!\n"); 
        return 0;
    }

    if (match_state == FIREBALL_MS_NO_MATCH) {
        notify_fail("There is no match to terminate!\n"); 
        return 0; 
    }

    reason = (stringp(reason) ? " Reason: " + reason + ".": ""); 
    freport(capitalize(tp->query_real_name()) + " terminates the " +
            "match." + reason + "\n", ({ })); 
    log_file("fireball", ctime(time()) + ": " + tp->query_real_name() + 
             " terminates match." + reason + "\n");
    reset_game(1); 
    return 1;
}


/*
 *  Function:     do_start_practice
 *  Description:  Action function, starts a practice. 
 */ 
int
do_start_practice()
{
    if (!SECURITY->valid_write(file_name(this_object()),
                               this_player(), write_file)) {
        notify_fail("You don't have the authority to do that.\n"); 
        return 0; 
    } 

    if (match_state != FIREBALL_MS_NO_MATCH) {
        notify_fail("There is a match in progress.\n"); 
        return 0; 
    } 

    seteuid(getuid()); 
    match_state = FIREBALL_MS_PRACTICE; 
    if (!objectp(ball)) {
        ball = clone_object(FIREBALL_OBJ + "ball");
        ball->set_active(); 
    } 

    this_player()->add_prop(FIREBALL_LIVE_I_KICK_DIRECTION, 
                            FIREBALL_KICKING_NORTH); 

    ball->move(query_arena_room_path(6, 4)); 
    home_players = ({ this_player() });        
    write("Ok. Remember to end the practice when you are done or " +
          "no-one will be able to play the game!\n"); 
    return 1;  
}


/*
 *  Function:     do_end_practice
 *  Description:  Action function, ends a practice. 
 */ 
int
do_end_practice()
{
    if (!SECURITY->valid_write(file_name(this_object()),
                               this_player(), write_file)) {
        notify_fail("You don't have the authority to do that.\n"); 
        return 0; 
    } 

    if (match_state != FIREBALL_MS_PRACTICE) {
        notify_fail("There is not a practice in progress.\n"); 
        return 0; 
    } 

    match_state = FIREBALL_MS_NO_MATCH;
    home_players->remove_prop(FIREBALL_LIVE_I_KICK_DIRECTION);  
    home_players = ({ });        
    write("Ok, practice over.\n"); 
    new_game(); 
    return 1;  
}


/*
 *  Function:     do_add_practicer
 *  Description:  Action function, adds a practicer. 
 */ 
int
do_add_practicer(string str)
{
    object pl; 

    if (!SECURITY->valid_write(file_name(this_object()),
                               this_player(), write_file)) {
        notify_fail("You don't have the authority to do that.\n"); 
        return 0; 
    } 

    if (match_state != FIREBALL_MS_PRACTICE) {
        notify_fail("There is not a practice in progress.\n"); 
        return 0; 
    } 

    if (!stringp(str) || !objectp(pl = find_player(lower_case(str)))) {
        notify_fail("No such player in the game!\n"); 
        return 0; 
    }

    if (member_array(pl, home_players) != -1) {
        notify_fail("That player is already allowed to practice.\n"); 
        return 0; 
    } 

    if (sizeof(home_players -= ({ 0 })) == 4) {
        notify_fail("Four players is the maximum for a practice.\n"); 
        return 0; 
    }  

    pl->add_prop(FIREBALL_LIVE_I_KICK_DIRECTION, FIREBALL_KICKING_NORTH); 
    home_players += ({ pl }); 
    write("Ok, you are kicking towards the north goal.\n"); 
    return 1; 
}


/*
 *  Function:     do_add_practicer
 *  Description:  Action function, adds a practicer. 
 */ 
int
do_patch_score(string str)
{
    string tn; 
    int new_score; 

    if (!stringp(str) || !strlen(str) || 
        sscanf(str, "%s = %d", tn, new_score) != 2) {
        notify_fail("Syntax: " + query_verb() + " <team> = <score>.\n"); 
        return 0; 
    } 

    if (!SECURITY->valid_write(file_name(this_object()),
                               this_player(), write_file)) {
        notify_fail("You don't have the authority to do that.\n"); 
        return 0; 
    } 

    if (match_state == FIREBALL_MS_NO_MATCH) {
        notify_fail("There is no current match!\n"); 
        return 0; 
    } 

    if (match_state == FIREBALL_MS_PRACTICE) {
        notify_fail("There is a practice going on, scores are irrelevant.\n"); 
        return 0; 
    } 

    if (match_state == FIREBALL_MS_POST_MATCH) {
        notify_fail("The match has ended.\n"); 
        return 0; 
    }  

    if (new_score < 0 || new_score > 50) {
        notify_fail("Please enter a score from 0 - 50.\n"); 
        return 0; 
    } 

    tn = query_proper_team_name(tn);
    if (tn == home_team_name) {
        home_score = new_score; 
        write("Ok.\n");  
        log_file("fireball", ctime(time()) + " " + 
                 this_player()->query_real_name() + 
                 " patched " + home_team_name + " score to " + 
                 home_score + ".\n");
        return 1; 
    } 
    else if (tn == away_team_name) {
        away_score = new_score; 
        write("Ok.\n"); 
        log_file("fireball", ctime(time()) + " " + 
                 this_player()->query_real_name() + 
                 " patched " + away_team_name + " score to " + 
                 away_score + ".\n"); 
        return 1; 
    } 

    notify_fail("No such team is currently playing.\n"); 
    return 0; 
}


/* 
 * Function:    do_change_formation 
 * Description: Action function to change the team formation of the  
 *              npcs in a player's team. 
 */ 
int
do_change_formation(string str)
{
    object tp = this_player(), *players; 
    string f; 
    int i, j; 

    if ((i = member_array(tp, home_players)) > -1) { 
        if (!npcs_home) { 
            write("There are no hired players in your team.\n"); 
            return 1; 
        } 

        if (!stringp(str)) { 
            write("The possible formations are: dagger, scorpion, " +
                  "sickle and arrow. Your current formation is " + 
                  query_home_team_manager()->query_name() + ".\n"); 
            return 1; 
        } 

        players = home_players; 
    } 
    else if ((i = member_array(tp, away_players)) > -1) {
        if (!npcs_away) { 
            write("There are no hired players in your team.\n"); 
            return 1; 
        } 
        if (!stringp(str)) {
            write("The possible formations are: dagger, scorpion, " +
                  "sickle and arrow. Your current formation is " + 
                  query_away_team_manager()->query_name() + ".\n"); 
            return 1; 
        } 
        players = away_players;  
    } 
    else {
        write("You aren't playing in a team!\n"); 
        return 1; 
    } 

    if ((match_state == FIREBALL_MS_FIRST_HALF ||
         match_state == FIREBALL_MS_SECOND_HALF) && 
         !stringp(match_substate)) { 
        write("You can't change your team's formation during play.\n"); 
        return 1;
    } 

    switch (str) {
        case FIREBALL_FORMATION_DAGGER : 
            f = FIREBALL_DAGGER_FORMATION_FILE; 
            break; 
        case FIREBALL_FORMATION_SCORPION : 
            f = FIREBALL_SCORPION_FORMATION_FILE; 
            break; 
        case FIREBALL_FORMATION_SICKLE : 
            f = FIREBALL_SICKLE_FORMATION_FILE; 
            break; 
        case FIREBALL_FORMATION_ARROW : 
            f = FIREBALL_ARROW_FORMATION_FILE; 
            break; 
        default : 
            write("No such formation known!\n");
            return 1; 
            break; 
    } 

    for (j = 0; j < 4; j++) {
        if (j == i) 
            write("You signal a change of formation to " + str + ".\n"); 
        else
#ifdef NO_TELLS_FOR_NPCS
            if (interactive(players[j])) 
#endif
                tell_object(players[j], 
                    tp->query_The_name(players[i]) + 
                    " signals a change of formation to " + str + ".\n");
    } 

    if (players == home_players) { 
        if (home_team_manager_file == f) {
            write("But that is your current formation!\n");
            return 1;  
        } 
        home_team_manager_file = f; 
        home_team_manager->remove_object(); 
    } 
    else {
        if (away_team_manager_file == f) {
            write("But that is your current formation!\n");
            return 1;  
        } 
        away_team_manager_file = f; 
        away_team_manager->remove_object(); 
    } 

    write("Your team formation is changed to " + str + ".\n"); 
    return 1;  
} 


/* 
 * Function:      exa_results 
 * Description:   An action function. Examines the results files available 
 *                in a given month or the results on a given day. 
 */ 
int
exa_results(string str)
{
    string *date_arr; 
    string dir, day, month, year; 

    if (!stringp(str) || !strlen(str) ||
         str == "today") {
        date_arr = time_to_path_arr(ctime(time())); 
        day = date_arr[2]; 
        month = date_arr[1]; 
        year = date_arr[0]; 
    } 
    else if (str == "yesterday") {
        date_arr = time_to_path_arr(ctime(time() - 86400)); 
        day = date_arr[2]; 
        month = date_arr[1]; 
        year = date_arr[0]; 
    } 
    else switch (sizeof(date_arr = explode(str, " "))) {
        case 1 : 
            day = month = 0; 
            year = date_arr[0]; 
            break; 
        case 2 : 
            day = 0;  
            month = capitalize(lower_case(date_arr[0])); 
            year = date_arr[1]; 
            break; 
        case 3 : 
            day = date_arr[0]; 
            month = capitalize(lower_case(date_arr[1])); 
            year = date_arr[2]; 
            break; 
        default : 
            write("There are no results in the year " + year +
                  ".\n"); 
            return 1;  
            break; 
    }

    if (file_size(dir = FIREBALL_RESULTS + year) != -2) {
        write("There are no results in the year " + year + ".\n");
        return 1; 
    }

    if (!stringp(month)) {
        if (!sizeof(date_arr = get_dir(dir += "/"))) {
            write("There are no results in the year " + year + 
                  ".\n"); 
            return 1; 
        } 
        this_player()->more("There are results " +
             "in the following months in the year " + year + 
             ":\n\n" + sprintf("%-#70s\n", implode(date_arr, "\n")) + 
             "\n");
        return 1;  
    } 
    else switch (file_size(dir += ("/" + month))) {
        case -1 : 
                  write("There are no results for the month " +
                        month + " in the year " + year + ".\n"); 
                  return 1; 
                  break; 

        case -2 : 
                  if (stringp(day)) {
                      if (file_size(dir += ("/" + day)) == -1)  {
                          write("There are no results on day " +
                                day + " of the month " + month + 
                                " in the year " + year + ".\n"); 
                          return 1; 
                      }
                      else {
                          this_player()->more(read_file(dir)); 
                          return 1; 
                      }  
                  } 
                  else {
                      if (!sizeof(date_arr = get_dir(dir += "/"))) {
                          write("There are no results for the month " +
                                month + " in the year " + year + ".\n"); 
                          return 1; 
                      }
                      this_player()->more("There are results " +
                          "on the following days in the month " +
                          month + " in the year " + year + ":\n\n" +
                          sprintf("%-#70s\n", implode(date_arr, "\n")) + 
                          "\n"); 
                      return 1; 
                  } 
                  break; 

        default : 
                  return 0; 
                  break; 
    }
}


/* 
 * Function:     check_match_score
 * Description:  An action function. Gives the score details of the current
 *               match to this_player(). 
 */ 
int
check_match_score(string str)
{
    write(query_match_description(1)); 
    return 1;
}


/* A C T I O N   F U N C T I O N S   E N D   H E R E */ 

