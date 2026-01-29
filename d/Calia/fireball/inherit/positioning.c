
/*
 * ~Calia/fireball/special/positioning.c
 * 
 * Handy functions to position players in the arena and the
 * foyer. 
 *
 * Coded by Maniac@Genesis
 * 
 * Copyright (C) Miguel Leith 1997/1998/1999
 */ 

#include "defs.h"
#include FIREBALL_HEADER

inherit FIREBALL_UTILS;

/* 
 * Function:     position_player
 * Description:  position a fireball player in the specified room 
 *               with the specified leave message (e.g. "north").
 *               If last_arena_start is passed, this is updated for
 *               the player with the position he is moved to. 
 */ 
varargs void
position_player(object pl, string mstr, string room, 
                mapping last_arena_start = 0)
{
    object e, r; 

    if (!objectp(pl) || !stringp(room))
        return; 

    if (mappingp(last_arena_start)) 
        last_arena_start += ([ pl->query_real_name() : room ]);
 
    if (((e = environment(pl)) != (r = room->get_this_object())) 
        && (pl->query_npc() || IS_FIREBALL_ARENA_ROOM(e))) {
        tell_object(pl, "You leave " + mstr + ".\n"); 
        pl->move_living(mstr, r); 
    }
}

/* 
 * Function:     position_team
 * 
 * Description:  Positions players according to their
 *               team positions and the rooms specified
 *               in the parameter list. 
 */ 
void
position_team(object *players, int *coords)
{
    position_player(players[0], 
                    "for a defensive start position",
                    query_arena_room_path(coords[0], coords[1])); 
 
    position_player(players[1], 
                    "for a left midfield start position", 
                    query_arena_room_path(coords[2], coords[3])); 

    position_player(players[2], 
                    "for a right midfield start position", 
                    query_arena_room_path(coords[4], coords[5])); 

    position_player(players[3], 
                    "for an attacking start position", 
                    query_arena_room_path(coords[6], coords[7])); 
}


/* 
 * Function:     position_teams 
 * 
 * Description:  Positions players according to their 
 *               team positions and the rooms specified 
 *               in the parameter list. 
 */ 
void
position_teams(object *home_players, int *home_coords, 
               object *away_players, int *away_coords)
{
    position_team(home_players, home_coords); 
    position_team(away_players, away_coords); 
}




void
position_team_for_conference(object *players, int x, int y) 
{
    int i; 

    for (i = 0; i < sizeof(players); i++) 
        position_player(players[i], 
                        "for a team conference", 
                        query_arena_room_path(x, y)); 
}


void
position_teams_for_conference(object *home_players, object *away_players, 
                              int home_kicking)
{
    if (home_kicking == FIREBALL_KICKING_NORTH) {
        position_team_for_conference(home_players, 6, 4); 
        position_team_for_conference(away_players, 6, 8); 
    } 
    else {
        position_team_for_conference(home_players, 6, 8); 
        position_team_for_conference(away_players, 6, 4); 
    } 
}


void
move_players_to_locker_room(object *players)
{
    int c; 

    players = filter(players, objectp); 
    for (c = 0; c < sizeof(players); c++)  
        position_player(players[c], 
                        "for the locker room", 
                        FIREBALL_SURROUND+"locker_room"); 
}


/* 
 * Function:     position_home_kicking_north 
 * 
 * Description:  Position both teams in the arena ready for 
 *               kick-off so that the home team kicks north 
 *               and the away team kicks south. 
 */ 
void 
position_home_kicking_north(int home_centre, object ball, 
                            object *home_players, object *away_players) 
{
    if (home_centre) 
        ball->move(query_arena_room_path(6, 4)); 
    else 
        ball->move(query_arena_room_path(6, 8)); 

    position_teams(home_players, ({ 6, 1, 4, 5, 8, 5, 6, 4 }), 
                   away_players, ({ 6, 11, 8, 7, 4, 7, 6, 8 })); 
}


/* 
 * Function:     position_home_kicking_south 
 * Description:  Position both teams in the arena ready for 
 *               kick-off so that the home team kicks south 
 *               and the away team kicks north. 
 */ 
void
position_home_kicking_south(int home_centre, object ball, 
                            object *home_players, object *away_players)
{
    if (home_centre) 
        ball->move(query_arena_room_path(6, 8)); 
    else 
        ball->move(query_arena_room_path(6, 4)); 

    position_teams(home_players, 
                   ({ 6, 11, 8, 7, 4, 7, 6, 8 }), 
                   away_players, 
                   ({ 6, 1, 4, 5, 8, 5, 6, 4 })); 
}


/* 
 * Function:     query_next_coordinate_move
 * Description:  Return the next coordinate for an npc to get 
 *               from one coordinate of the arena to another and 
 *               the direction e.g. ({ 5, 4, "east" }) means 
 *               the next coordinate is (5, 4), can be reached 
 *               by going east.  
 */ 
mixed
query_next_coordinate_move(int x1, int y1, int x2, int y2)
{
    int x, y, tangent; 

    x = x2 - x1; 
    y = y2 - y1; 

    if (x == 0 && y == 0)
        return ({ 0, 0, 0 }); 

    if (y != 0) 
        tangent = ((x * 100) / y); 
    else
        tangent = 0; 

    /* move horizontally */ 
    if (y == 0 || tangent < -199 || tangent > 199) { 
        if (x < 0) {
            return ({ x1-1, y1, "west" }); 
        } 
        else {
            return ({ x1+1, y1, "east" }); 
        } 
    } 
    /* move vertically */ 
    else if (x == 0 || (tangent > -51 && tangent < 51)) {
        if (y < 0) {
            return ({ x1, y1-1, "south" });
        } 
        else {
            return ({ x1, y1+1, "north" });
        } 
    } 
    /* move diagonally */ 
    else { 
        if (x < 0) {
            if (y < 0) 
                return ({ x1-1, y1-1, "southwest" }); 
            else
                return ({ x1-1, y1+1, "northwest" });  
        } 
        else {
            if (y < 0)
                return ({ x1+1, y1-1, "southeast" });  
            else
                return ({ x1+1, y1+1, "northeast" }); 
        } 
    } 
}


/*
 * Function:     query_next_direction_move
 * Description:  Return the next direction to get from one 
 *               coordinate to another. If rnd is true the
 *               direction may be an indirect route in roughly
 *               the right direction, chosen randomly. 
 *               Note that this is for npc move commands, so if the 
 *               next direction would be in the fire, directions
 *               leading around the fire are returned. 
 */ 
string
query_next_direction_move(int x1, int y1, int x2, int y2, int rnd)
{
    mixed coords; 
    string *direcs; 

    coords = query_next_coordinate_move(x1, y1, x2, y2); 
    if (coords[0] == x2 && coords[1] == y2) 
        return coords[2];  

    if (file_size(query_arena_room_path(coords[0], coords[1])) != -1) 
        direcs = ({ coords[2] }); 
    else
        direcs = ({ }); 

    switch (coords[2]) {
        case "east" : 
            if (file_size(query_arena_room_path(coords[0], coords[1]+1)) != -1)
                direcs += ({ "northeast" }); 
            if (file_size(query_arena_room_path(coords[0], coords[1]-1)) != -1)
                direcs += ({ "southeast" }); 
            break; 
        case "west" :
            if (file_size(query_arena_room_path(coords[0], coords[1]+1)) != -1)
                direcs += ({ "northwest" }); 
            if (file_size(query_arena_room_path(coords[0], coords[1]-1)) != -1)
                direcs += ({ "southwest" }); 
            break; 
        case "north" : 
            if (file_size(query_arena_room_path(coords[0]-1, coords[1])) != -1)
                direcs += ({ "northwest" }); 
            if (file_size(query_arena_room_path(coords[0]+1, coords[1])) != -1)
                direcs += ({ "northeast" }); 
            break; 
        case "south" : 
            if (file_size(query_arena_room_path(coords[0]-1, coords[1])) != -1)
                direcs += ({ "southwest" }); 
            if (file_size(query_arena_room_path(coords[0]+1, coords[1])) != -1)
                direcs += ({ "southeast" }); 
            break; 
        case "northeast" : 
            if (file_size(query_arena_room_path(coords[0]-1, coords[1])) != -1)
                direcs += ({ "north" }); 
            if (file_size(query_arena_room_path(coords[0], coords[1]-1)) != -1)
                direcs += ({ "east" }); 
            /* get around the fire */ 
            if (!sizeof(direcs)) {
                if (random(2)) {
                    direcs = ({ "southeast" }); 
                } 
                else 
                    direcs = ({ "northwest" }); 
            } 
            break; 
        case "northwest" : 
            if (file_size(query_arena_room_path(coords[0]+1, coords[1])) != -1)
                direcs += ({ "north" }); 
            if (file_size(query_arena_room_path(coords[0], coords[1]-1)) != -1)
                direcs += ({ "west" }); 
            /* get around the fire */ 
            if (!sizeof(direcs)) {
                if (random(2)) {
                    direcs = ({ "northeast" }); 
                } 
                else 
                    direcs = ({ "southwest" }); 
            } 
            break; 
        case "southeast" : 
            if (file_size(query_arena_room_path(coords[0]-1, coords[1])) != -1)
                direcs += ({ "south" }); 
            if (file_size(query_arena_room_path(coords[0], coords[1]+1)) != -1)
                direcs += ({ "east" }); 
            /* get around the fire */ 
            if (!sizeof(direcs)) {
                if (random(2)) {
                    direcs = ({ "northeast" }); 
                } 
                else 
                    direcs = ({ "southwest" }); 
            } 
            break; 
        case "southwest" : 
            if (file_size(query_arena_room_path(coords[0]+1, coords[1])) != -1)
                direcs += ({ "south" }); 
            if (file_size(query_arena_room_path(coords[0], coords[1]+1)) != -1)
                direcs += ({ "west" }); 
            /* get around the fire */ 
            if (!sizeof(direcs)) {
                if (random(2)) {
                    direcs = ({ "southeast" }); 
                } 
                else 
                    direcs = ({ "northwest" }); 
            } 
            break; 
    } 
    if (rnd)
        return direcs[random(sizeof(direcs))]; 

    return direcs[0]; 
}
