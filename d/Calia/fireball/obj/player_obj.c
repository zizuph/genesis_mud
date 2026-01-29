
/*
 *  /d/Calia/fireball/obj/player_obj.c
 *
 *  This is the object that's cloned and moved into the inventory of 
 *  players of fireball so that they can run, dribble, tackle, kick etc. 
 *  Handling the exits from here means the exit actions don't have to be 
 *  removed and added each time the player moves, which is the way 
 *  room code handles it. Also the actions in this object are checked 
 *  before all the player's souls are - players are far more likely to be
 *  carrying out a fireball action in the arena than any other - and 
 *  I'd rather achieve the short-cut this way than by making this a soul 
 *  and inserting it in the player's cmdsoul list before all the other 
 *  cmdsouls that the player has (messy). Note that npcs are assumed to 
 *  have an interval of 3 seconds between actions, so, as the recovery 
 *  alarms for fireball player actions are less than 3 seconds, I don't 
 *  need to set recovery alarms for npc actions. 
 *
 *  Coded by Maniac@Genesis, 1997/1998
 *
 *  Copyright (C) Miguel Leith 1997/1998
 */

#include "defs.h"
#include FIREBALL_HEADER

inherit FIREBALL_VIEW_SUPPORT; 
inherit FIREBALL_HELP_SUPPORT; 
inherit "/std/object";

#define NO_TELLS_FOR_NPCS

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include <std.h>
#include <filter_funs.h>
#include <adverbs.h>
#include <const.h>
#include <formulas.h>

int fcontrol(string str); 
int ftackle(string str); 

int rem_obj_alarm, recovery_alarm, move_alarm, stun; 
object player; 

string run_verb_tps, run_verb_fps; 


void
create_object()
{
    set_name(FIREBALL_PLAYER_OBJ_ID);
    set_short(FIREBALL_PLAYER_OBJ_ID); 
    set_long("");  
    set_no_show(); 
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    seteuid(getuid()); 
}


private void
unset_recovering()
{
    recovery_alarm = 0;  
    if (stun) { 
        stun = 0; 
        player->remove_prop(FIREBALL_LIVE_I_RECOVERING); 
#ifdef NO_TELLS_FOR_NPCS
        if (interactive(player)) 
#endif
        tell_object(player, "You are no longer stunned.\n"); 
    } 
    else 
#ifdef NO_TELLS_FOR_NPCS
        if (interactive(player)) 
#endif
        tell_object(player, "You are ready to kick or tackle again.\n"); 
}


void
set_recovering(int t, int make_stun)
{
    if (recovery_alarm)
        remove_alarm(recovery_alarm); 

    if (make_stun) { 
        player->add_prop(FIREBALL_LIVE_I_RECOVERING, 1); 
        stun = 1; 
    } 

    recovery_alarm = set_alarm(itof(t), 0.0, unset_recovering); 
}


private void
can_move_again()
{
    move_alarm = 0; 
    tell_object(player, "Go.\n"); 
}


int
remove_object_after_delay()
{
    rem_obj_alarm = set_alarm(0.0, 0.0, remove_object); 
}

void
cancel_remove_object_after_delay()
{
    if (rem_obj_alarm) {
        remove_alarm(rem_obj_alarm); 
        rem_obj_alarm = 0; 
    } 
}

/* Action function to move on the pitch, either running or  
   dribbling the fireball */ 
int
player_move(string str)
{
    int r; 

    if (stun) { 
        notify_fail("You are still stunned.\n"); 
        return 0; 
    }

    if (move_alarm) { 
        notify_fail("You aren't ready to continue running yet.\n"); 
        return 0; 
    } 

    if (r = FIREBALL_GAME_HANDLER->do_player_move(str, 
                                                 run_verb_fps, 
                                                 run_verb_tps)) 
        move_alarm = set_alarm(FIREBALL_PLAYER_MOVE_INTERVAL, 
                               0.0, can_move_again); 

    return r; 
}


int
npc_move(string str)
{
    if (stun) {
        notify_fail("You are still stunned.\n"); 
        return 0;
    }

    return FIREBALL_GAME_HANDLER->do_player_move(str, 
                                                 run_verb_fps, 
                                                 run_verb_tps); 
}


/* 
 * Kick the fireball to a coordinate relative to this one. 
 */ 
int
fkick(string str)
{
    int r; 

    if (stun) {
        notify_fail("You are still stunned.\n"); 
        return 0;
    }

    if (recovery_alarm) {
        notify_fail("You are not ready to kick or tackle again yet.\n"); 
        return 0;
    }
    
    if (r = FIREBALL_GAME_HANDLER->do_kick(str, query_verb() == "ffkick"))  
        recovery_alarm = set_alarm(FIREBALL_KICK_RECOVER_INTERVAL, 
                                   0.0, unset_recovering); 

    return r; 
}


int
npc_fkick(string str)
{
    if (stun) 
        return 0; 

    return FIREBALL_GAME_HANDLER->do_kick(str, query_verb() == "ffkick");   
}


/* 
 * Function: fpass 
 * Pass the fireball, may be to a specified pair of 
 * coordinates, a team position or a specified player. 
 */ 
int
fpass(string str)
{
    int r; 

    if (stun) { 
        notify_fail("You are still stunned.\n"); 
        return 0; 
    } 

    if (recovery_alarm) { 
        notify_fail("You are not ready to kick or tackle again yet.\n"); 
        return 0; 
    } 

    if (r = FIREBALL_GAME_HANDLER->do_pass(str, query_verb() == "ffpass")) 
        recovery_alarm = set_alarm(FIREBALL_PASS_RECOVER_INTERVAL, 
                                   0.0, unset_recovering); 
    return r; 
}


int
npc_fpass(string str)
{
    if (stun) 
        return 0;

    return FIREBALL_GAME_HANDLER->do_pass(str, query_verb() == "ffpass"); 
}



/* Control the fireball so you can pass it, dribble it or shoot. */ 
int
fcontrol(string str)
{
    if (stun) {
        notify_fail("You are still stunned.\n"); 
        return 0;
    }

    return FIREBALL_GAME_HANDLER->do_control(str); 
} 


/* Release control of the fireball. */ 
int
frelease(string str)
{
    if (stun) {
        notify_fail("You are still stunned.\n"); 
        return 0;
    }

    return FIREBALL_GAME_HANDLER->do_release(str); 
} 


/* 
 * Function: ftackle 
 * 
 * An action function, an attempt by one player to tackle another. 
 * A player must be dribbling the ball to be tackled. 
 */ 
int
ftackle(string str)
{
    int r; 

    if (stun) { 
        notify_fail("You are still stunned.\n"); 
        return 0; 
    } 

    if (recovery_alarm) { 
        notify_fail("You are not ready to kick or tackle again yet.\n"); 
        return 0; 
    } 

    if (r = FIREBALL_GAME_HANDLER->do_tackle(str)) 
        recovery_alarm = set_alarm(FIREBALL_TACKLE_RECOVER_INTERVAL, 
                                   0.0, unset_recovering); 
    return r; 
}

int
npc_ftackle(string str)
{
    if (stun) 
        return 0; 

    return FIREBALL_GAME_HANDLER->do_tackle(str); 
}

int
fshout(string str)
{
    return FIREBALL_GAME_HANDLER->do_shout(str); 
}


/* 
 * Function: fshoot
 * 
 * Action function, a shot on goal.  
 */ 
int
fshoot(string str)
{
    int r; 

    if (stun) { 
        notify_fail("You are still stunned.\n"); 
        return 0; 
    } 

    if (recovery_alarm) { 
        notify_fail("You are not ready to kick or tackle again yet.\n"); 
        return 0; 
    } 

    if (r = FIREBALL_GAME_HANDLER->do_shoot(str, query_verb() == "ffshoot")) 
        recovery_alarm = set_alarm(FIREBALL_PASS_RECOVER_INTERVAL, 
                                   0.0, unset_recovering); 
    return r; 
}


/* 
 * Function: fform
 * 
 * Action function, change formation.  
 */ 
int
fform(string str) 
{
    return FIREBALL_GAME_HANDLER->do_change_formation(str); 
}

int
npc_fshoot(string str)
{
    if (stun) 
        return 0;

    return FIREBALL_GAME_HANDLER->do_shoot(str, query_verb() == "ffshoot"); 
}


/* run verb third person singular */ 
string
query_run_verb_tps(object tp)
{
    string s;

    s = FIREBALL_RACE_MOVES[tp->query_race()]; 
    if (stringp(s)) 
        return s; 
    else 
        return "runs"; 
}


/* run verb first person singular */ 
string
query_run_verb_fps(object tp)
{
    string s;

    s = FIREBALL_RACE_MOVE[tp->query_race()]; 
    if (stringp(s)) 
        return s; 
    else 
        return "run"; 
}


void
leave_env(object old, object dest)
{
    ::leave_env(old, dest); 

    if (living(old) && player == old) 
        player->remove_prop(FIREBALL_LIVE_I_RECOVERING); 
}


void
enter_env(object dest, object old)
{
    ::enter_env(dest, old); 

    if (living(dest)) {
        player = dest; 
        run_verb_tps = query_run_verb_tps(dest); 
        run_verb_fps = query_run_verb_fps(dest); 
    } 
}


void
init()
{ 
    function f; 

    ::init(); 
    add_action(fshout, "fshout"); 
    add_action(fcontrol, "fcontrol");  
    add_action(frelease, "frelease"); 

    if (this_player()->query_npc()) {
        add_action(npc_fshoot, "fshoot"); 
        add_action(npc_fshoot, "ffshoot"); 
        add_action(npc_ftackle, "ftackle");
        add_action(npc_fkick, "fkick");  
        add_action(npc_fkick, "ffkick");    
        add_action(npc_fpass, "fpass");   
        add_action(npc_fpass, "ffpass"); 
        f = npc_move; 
    }
    else {
        add_action(fshoot, "fshoot"); 
        add_action(fshoot, "ffshoot"); 
        add_action(ftackle, "ftackle");
        add_action(fkick, "fkick");  
        add_action(fkick, "ffkick");    
        add_action(fpass, "fpass");   
        add_action(fpass, "ffpass"); 
        add_action(fform, "fform"); 
        f = player_move; 
    } 

    add_action(f, "north");   
    add_action(f, "south");   
    add_action(f, "east");   
    add_action(f, "west");   
    add_action(f, "northeast");   
    add_action(f, "southeast");   
    add_action(f, "northwest");   
    add_action(f, "southwest");   
    init_view_support(); 
    init_help_support(); 
}
