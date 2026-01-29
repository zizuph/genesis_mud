
/* 
    ~Calia/fireball/inherit/team_manager.c 

    Default control code for npc fireball players. 

    Coded by Maniac@Genesis, 1998/1999. Separated
    from game handler by Maniac 15/1/2000

    Copyright (C) Miguel Leith 1998/1999
*/ 

#pragma strict_types
#pragma save_binary

#include "defs.h"
#include FIREBALL_HEADER
inherit FIREBALL_POSITIONING; 
inherit FIREBALL_FORMATION_FILE; 
inherit "/std/object"; 

#include <ss_types.h>
#include <files.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <formulas.h>
#include <tasks.h>


object *players, ball; 
int kick_dir, team_alarm; 


void
create_team_manager()
{
}

void
create_object()
{
    create_team_manager(); 
}


/*
 * Function:     check_move
 * Description:  Returns 1 if a room exists at the specified coordinates 
 *               and their are no npcs from an opposing team there, 
 *               otherwise returns 0. 
 * 
 */ 
int
check_move(int x1, int y1, object npc, int kick_dir)
{
    string r; 

    return ((file_size(r = query_arena_room_path(x1, y1)) != -1) && 
            !objectp(find_first_opponent(r->get_this_object(), npc, 
                                         kick_dir))); 
}


/*
 * Function:     query_best_direction_move
 * Description:  Return the best direction to get from one 
 *               coordinate to another for a particular npc, 
 *               i.e. one leading to a room containing no npcs 
 *               from the opposing team. 
 */ 
string 
query_best_direction_move(int x1, int y1, int x2, int y2, object npc,
                          int kick_dir)
{
    mixed coords; 
    string *direcs; 

    coords = query_next_coordinate_move(x1, y1, x2, y2); 
    if (check_move(coords[0], coords[1], npc, kick_dir)) 
        return coords[2];  

    direcs = ({ }); 

    switch (coords[2]) {
        case "east" : 
            if (check_move(coords[0], coords[1]+1, npc, kick_dir))
                direcs += ({ "northeast" }); 
            if (check_move(coords[0], coords[1]-1, npc, kick_dir))
                direcs += ({ "southeast" }); 
            break; 
        case "west" :
            if (check_move(coords[0], coords[1]+1, npc, kick_dir))
                direcs += ({ "northwest" }); 
            if (check_move(coords[0], coords[1]-1, npc, kick_dir))
                direcs += ({ "southwest" }); 
            break; 
        case "north" : 
            if (check_move(coords[0]-1, coords[1], npc, kick_dir))
                direcs += ({ "northwest" }); 
            if (check_move(coords[0]+1, coords[1], npc, kick_dir))
                direcs += ({ "northeast" }); 
            break; 
        case "south" : 
            if (check_move(coords[0]-1, coords[1], npc, kick_dir))
                direcs += ({ "southwest" }); 
            if (check_move(coords[0]+1, coords[1], npc, kick_dir))
                direcs += ({ "southeast" }); 
            break; 
        case "northeast" : 
            if (check_move(coords[0]-1, coords[1], npc, kick_dir))
                direcs += ({ "north" }); 
            if (check_move(coords[0], coords[1]-1, npc, kick_dir)) 
                direcs += ({ "east" }); 
            /* get around the fire */ 
            if (!sizeof(direcs)) {
                if (check_move(coords[0]-2, coords[1], npc, kick_dir))
                    direcs += ({ "northwest" });
                if (check_move(coords[0], coords[1]-2, npc, kick_dir))
                    direcs += ({ "southeast" });
            } 
            break; 
        case "northwest" : 
            if (check_move(coords[0]+1, coords[1], npc, kick_dir))
                direcs += ({ "north" }); 
            if (check_move(coords[0], coords[1]-1, npc, kick_dir))
                direcs += ({ "west" }); 
            /* get around the fire */ 
            if (!sizeof(direcs)) {
                if (check_move(coords[0]+2, coords[1], npc, kick_dir))
                    direcs += ({ "northeast" });
                if (check_move(coords[0], coords[1]-2, npc, kick_dir))
                    direcs += ({ "southwest" });
            } 
            break; 
        case "southeast" : 
            if (check_move(coords[0]-1, coords[1], npc, kick_dir))
                direcs += ({ "south" }); 
            if (check_move(coords[0], coords[1]+1, npc, kick_dir))
                direcs += ({ "east" }); 
            /* get around the fire */ 
            if (!sizeof(direcs)) {
                if (check_move(coords[0], coords[1]+2, npc, kick_dir))
                    direcs += ({ "northeast" });
                if (check_move(coords[0]-2, coords[1], npc, kick_dir))
                    direcs += ({ "southwest" });
            } 
            break; 
        case "southwest" : 
            if (check_move(coords[0]+1, coords[1], npc, kick_dir))
                direcs += ({ "south" }); 
            if (check_move(coords[0], coords[1]+1, npc, kick_dir))
                direcs += ({ "west" }); 
            /* get around the fire */ 
            if (!sizeof(direcs)) {
                if (check_move(coords[0], coords[1]+2, npc, kick_dir))
                    direcs += ({ "northwest" });
                if (check_move(coords[0]+2, coords[1], npc, kick_dir))
                    direcs += ({ "southeast" });
            } 
            break; 
    } 

    if (!sizeof(direcs))  
        return 0; 

    return direcs[random(sizeof(direcs))];
}


/*
 * Function:     continue_play_team
 * Description:  Make an npc team of fireball players continue playing
 *               in a match. 
 */ 
void
continue_play_team()
{
    int c, c2, mbm, attacking, possession, npc_x, npc_y, 
        ball_x, ball_y, to_x, to_y, goal_y, best_pass_rating,
        current_pass_rating, best_pass_npc, *move_arr, 
        default_loc_distance, goal_distance, ball_distance, 
        check_first; 
    object current_dribbler, npc, tp; 
    string sector, str; 

    tp = this_player(); 
    /* Call an npc action for each player in the team. */ 
    for (c = 3; c > -1; c--) {
        if (!team_alarm) /* a goal may have been scored */ 
            return; 

        if (!(npc = players[c])->query_npc())
            continue; 

        /* The more skillful the npc the more likely it is to make
           an optimal move. */ 
        check_first = (random(100) <     
                       (c2 = npc->query_fireball_skill())); 

        /* The less skillful an npc is the less likely it is to 
           do anything this turn. */ 
        if (!check_first && (random(140) >= c2 + 30)) 
            continue;    

        npc_x = environment(npc)->query_x(); 
        npc_y = environment(npc)->query_y(); 

        ball_x = environment(ball)->query_x(); 
        ball_y = environment(ball)->query_y(); 

        sector = environment(ball)->query_field_sector(); 

        if (objectp(current_dribbler = ball->query_current_dribbler())) {
            if (member_array(current_dribbler, players) > -1)
                attacking = 1; 
            else
                attacking = 0; 
        }
        else
            attacking = 0;  

        possession = (current_dribbler == npc); 

        /* 
            Determine the appropriate positional coordinates for the
            players in this team based on whether they are attacking
            and the direction they are kicking. 
        */ 
        if (attacking) {
            if (kick_dir == FIREBALL_KICKING_NORTH) {
                goal_y = 12; 
                move_arr = attack_north[sector]; 
            }  
            else {
                goal_y = 0; 
                move_arr = attack_south[sector]; 
            }  
        } 
        else {
            if (kick_dir == FIREBALL_KICKING_NORTH) {
                move_arr = defense_north[sector]; 
            } 
            else {
                move_arr = defense_south[sector]; 
            }  
        } 
        to_x = move_arr[c*2]; 
        to_y = move_arr[c*2+1]; 
        default_loc_distance = query_distance(npc_x, npc_y, to_x, to_y);
        ball_distance = query_distance(npc_x, npc_y, ball_x, ball_y); 

        if (attacking) {
            if (possession) {
                goal_distance = query_distance(npc_x, npc_y, 6, goal_y); 

                /* If close to goal, try a shot! */ 
                if (goal_distance <= (200 + random(100))) { 
                    if (objectp(find_first_opponent(
                          query_arena_room_path(6, goal_y == 12 ? 11 : 1)
                            ->get_this_object(), npc, kick_dir)))
                        npc->command("$fshoot");
                    else
                        npc->command("$fshoot min"); 
                } 
                /* If close to one's own goal, priority is to clear 
                   to avoid conceding a goal. */ 
                else if (c == 0 || goal_distance > 1000) {
                    if (random(2)) { 
                        if (npc_x >= 6) 
                            npc->command("$ffpass " + (11 - random(4)) + 
                                         " " + 6); 
                        else
                            npc->command("$ffpass " + (1 + random(4)) + 
                                         " " + 6); 
                    } 
                    else {
                        if (npc_x > 6) 
                            npc->command("$ffpass " + (11 - random(4)) + 
                                         " " + 6); 
                        else
                            npc->command("$ffpass " + (1 + random(4)) + 
                                         " " + 6); 
                    } 
                } 
                else {      
                    /* consider passing options and rate them */ 
                    best_pass_npc = -1; 
                    best_pass_rating = 0;
                    for (c2 = 0; c2 < 4; c2++) {
                        if ((c == c2) || 
                            (!is_able_to_play(players[c2])))
                            continue; 

                        npc_x = environment(players[c2])->query_x(); 
                        npc_y = environment(players[c2])->query_y(); 

                        if ((mbm = FIREBALL_GAME_HANDLER->move_ball(ball_x, 
                             ball_y, npc_x, npc_y, 1, players[c2], 0, 0)) == 0) 
                            continue; 

                        /* The better the npc's skill, the more likely he 
                           is to spot a bad pass and rule it out. */ 
                        if (check_first && mbm == -1) 
                            current_pass_rating = -300;  
                        else 
                            current_pass_rating = 0; 

                        current_pass_rating += (1100 - 
                               query_distance(npc_x, npc_y, 6, goal_y)); 

                        if ((current_pass_rating > best_pass_rating) ||
                            (current_pass_rating == best_pass_rating && 
                             random(2))) {
                            best_pass_rating = current_pass_rating; 
                            best_pass_npc = c2; 
                        } 
                    } 
                    if ((best_pass_npc == -1) ||
                        ((1100 - goal_distance) >= best_pass_rating)) {  
                        if (goal_distance <= 300 && (c != 3 || random(2))) {
                            if (objectp(find_first_opponent(
                                  query_arena_room_path(6, 
                                                        goal_y == 12 ? 11 : 1)
                                    ->get_this_object(), npc, kick_dir)))
                                npc->command("$fshoot");
                            else
                                npc->command("$fshoot min"); 
                        } 
                        /* Move an npc in a smart (opponent-free) 
                           direction if appropriate. */ 
                        else if (check_first && 
                                 random(goal_distance) < 525) {
                            if (query_distance(to_x, to_y, 6, goal_y) >=
                                 goal_distance &&
                                  stringp(str = 
                                      query_best_direction_move(
                                          ball_x, ball_y, 6, goal_y, 
                                          npc, kick_dir)))
                                npc->command(str); 
                            else if (stringp(str = 
                                         query_best_direction_move(
                                             ball_x, ball_y, to_x, to_y, 
                                             npc, kick_dir))) 
                                npc->command(str); 
                        } 
                        else if (check_first) {
                            if (FIREBALL_GAME_HANDLER->move_ball(ball_x, 
                                ball_y, 6, (goal_y == 12 ? 11 : 1), 1, 0,
                                0, 1))
                                npc->command("$ffshoot"); 
                            else if (kick_dir == FIREBALL_KICKING_NORTH) {
                                switch (environment(npc)->query_x()) {
                                    case 1 .. 5 : 
                                        to_x = -3; 
                                        to_y = 3; 
                                        break; 
                                    case 6 : 
                                        if (random(2)) 
                                            to_x = -3;
                                        else
                                            to_x = 3;  
                                        to_y = 3; 
                                        break;  
                                    case 7 .. 11 : 
                                        to_x = 3; 
                                        to_y = 3; 
                                        break; 
                                } 
                                npc->command("$ffkick " + to_x + " " + to_y); 
                            } 
                            else {
                                switch (environment(npc)->query_x()) {
                                    case 1 .. 5 : 
                                        to_x = -3; 
                                        to_y = -3;
                                        break;  
                                    case 6 : 
                                        if (random(2)) 
                                            to_x = -3;
                                        else
                                            to_x = 3;  
                                        to_y = -3; 
                                        break;  
                                    case 7 .. 11 : 
                                        to_x = 3; 
                                        to_y = -3; 
                                        break; 
                                } 
                                npc->command("$ffkick " + to_x + " " + to_y); 
                            } 
                        } 
                        /* Otherwise just run somewhere. */ 
                        else {
                            if (query_distance(to_x, to_y, 6, goal_y) >=
                                goal_distance) 
                                npc->command(query_next_direction_move(
                                         ball_x, ball_y, 6, goal_y, 1)); 
                            else 
                                npc->command(query_next_direction_move(
                                         ball_x, ball_y, to_x, to_y, 1));
                        }  
                    } 
                    else 
                        npc->command("$fpass " + 
                                    ({"d", "l", "r", "a"})[best_pass_npc]); 
                }  
            } 
            else { 
                if (!default_loc_distance) {
                    if (check_first && ball_distance &&  
                        objectp(find_first_opponent(environment(npc), 
                                                        npc, kick_dir)))
                        npc->command(query_next_direction_move(npc_x, npc_y, 
                                                           ball_x, ball_y, 1)); 
                } 
                else if (check_first && 
                         stringp(str = 
                                 query_best_direction_move(npc_x, npc_y, 
                                                to_x, to_y, npc, kick_dir)))
                    npc->command(str); 
                else 
                    npc->command(query_next_direction_move(npc_x, npc_y, 
                                                           to_x, to_y, 0));   
            } 
        } 
        else {
            if (!ball_distance) {
                if (objectp(current_dribbler)) 
                    npc->command("$ftackle"); 
                else 
                    npc->command("$fcontrol"); 
            } 
            else if ((c != 0 || !objectp(current_dribbler)) &&  
                     ball_distance < 200 &&
                     query_distance(to_x, to_y, ball_x, ball_y) < 200) {
                npc->command(query_next_direction_move(npc_x, npc_y, 
                                                   ball_x, ball_y, 0)); 
            } 
            else if (default_loc_distance) {
                if (check_first) 
                    npc->command(query_next_direction_move(npc_x, npc_y, 
                                                           to_x, to_y, 0));
                else 
                    npc->command(query_next_direction_move(npc_x, 
                                                npc_y, to_x, to_y, 1)); 
            } 
        } 
    } 
}



/*
 * Function:     stop_team
 * Description:  Stop the alarm for npc team actions.  
 */ 
nomask void
stop_team()
{
    if (!team_alarm)
        return; 

    remove_alarm(team_alarm); 
    team_alarm = 0; 
}


nomask void
team_heartbeat()
{
    continue_play_team(); 
    if (team_alarm) 
        team_alarm = set_alarm(FIREBALL_NPC_MOVE_INTERVAL, 0.0, 
                               team_heartbeat); 
}


/*
 * Function:     start_team
 * Description:  Start the alarm for npc team actions.  
 */ 
nomask void
start_team(object *the_players, int the_kick_dir, object the_ball)
{
    if (team_alarm) 
        return; 

    players = the_players; 
    kick_dir = the_kick_dir; 
    ball = the_ball; 
    team_alarm = set_alarm(FIREBALL_NPC_MOVE_INTERVAL, 0.0, 
                           team_heartbeat); 
}


/* 
 * Function:     npc_kickoff 
 * Description:  Makes an npc forward kick off. 
 */ 
void
npc_kickoff(object kicker, object *team, int kick_direction)
{
    int r; 

    kicker->command("$fcontrol"); 

    r = random(6); 

    if (r == 0 && !is_able_to_play(team[1])) 
        r = random(4) + 2; 
    else if (r == 1 && !is_able_to_play(team[2])) 
        r = random(4) + 2; 

    switch (r) { 
        case 0 : 
            kicker->command("$fpass l"); 
            break; 
        case 1 : 
            kicker->command("$fpass r"); 
            break; 
        case 2 : if (kick_direction == FIREBALL_KICKING_NORTH) 
                     kicker->command("$northwest"); 
                 else 
                     kicker->command("$southwest"); 
                 break; 
        case 3 : if (kick_direction == FIREBALL_KICKING_NORTH) 
                     kicker->command("$northeast"); 
                 else 
                     kicker->command("$southeast"); 
                 break; 
        case 4 : kicker->command("$east"); 
                 break; 
        case 5 : kicker->command("$west"); 
                 break; 
    } 
}

