// -*-C++-*-
//              ~Avenir/common/holm/mon/snake_master
// file name:   ~Avenir/common/dark/mon/master_worm
// creator(s):  Boriska, July 1994
// last update: Boriska, Mar 29 1995 
// purpose:
//         Master worm object, manages several NPC, that together make
//         worm like creature, occupying several continious rooms.
//         Together they simulate the behaviour of a worm. They move
//         together, wounded parts heal using healthier parts' hps,
//         creature is considered dead after all parts are dead.
// note:   --Decided not to make thiss snake aggressive or follow.
// bug(s):
// to-do:     
//            add relative stuff from worm.h to holm.h
//
// Revision history:
// Sept 1994 - Updated to use LIVE_I_STUNNED instead of LIVE_I_ATTACK_DELAY
// --Boriska
// Lilith -2/1/97- Made alterations for use in a snake npc. Uses the smis
//                 reset_placed_functions to configure snake instead of 
//                 make_worm().

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "../holm.h"

#define SNAKE_OBJ 0
#define SNAKE_LOC 1
#define LOG_FILE     ("/d/Avenir/log/deaths/anaconda")
#define WRITE_LOG(x) (write_file(LOG_FILE, ctime(time()) +" "+(x)))
#define DEBUG

#ifdef DEBUG
#define D(x) find_player("Lilith")->catch_msg("SNAKE debug: " + (x))
#else
#define D(x) ;
#endif

inherit "/std/object";

void die (object killer);
int worm_is_there (mixed room);
int reset_placed_functions();
int one_only;
private int length;          // number of body parts
private mixed* worm;         // i, {obj, locaton}
private mixed *fragment;     // pair of indices for each worm fragment
private object to = this_object();
private int heal_alarm_id = 0;

private float heal_delay = 15.0;
private int heal_rate = 6;


void
create_object()
{
    if ( !IS_CLONE )
        return;
    set_name ("snake_master");
    set_long ("You find no snake_master.\n");
    set_no_show();
    add_prop (OBJ_M_NO_GET, "Get what?\n");
    add_prop (OBJ_M_NO_STEAL, "Steal what?\n");

    seteuid(getuid()); 
    reset_placed_functions();
}    

void
set_heal_delay( float dd )
{
    if ( dd > 0.0 )
        heal_delay = dd;
}

void
set_heal_rate( int rr )
{
    if (rr > 0)
        heal_rate = rr;
}

public int
create_worm( string* loc, string *body_type )
{
    int i;
    object body, room;
   
    length = sizeof(loc);
    worm = allocate(length+1);
  
  // 1 more in order to get rid of special cases in movement routines
    for ( i = 0; i < length; i++ ) 
    {
        body = clone_object (body_type[i]);
        body->set_index (i);    // let the body part know its number
        body->set_master (to);  // let the body know its master
    
        if ( !find_object (loc[i]))
            loc[i]->hjhj();
    
        if (!(room = find_object (loc[i]))) 
        {
            // one of rooms where body part should be won't load
            remove_object();  // will remove body parts cloned so far
            return 0; // calling room will know something went wrong
        }
    worm[i] = ({ body, room });
    set_alarm ( 2.0, 0.0 , "body_move", body, room );
    }
  
    worm[length] = ({ 0,0 });
    fragment = ({ ({0,length-1}) });
    return 1; // success
}

int
reset_placed_functions()
{

    string *parts = ({ HOLM_MON + "snake_head", HOLM_MON + "snake_coil",
                       HOLM_MON + "snake_tail" });
    string *locs = ({  JUNG + "lf6", JUNG + "lf9", JUNG + "lf12" });

    /* For now, I think one giant anaconda per reboot is quite enuf */
    if (one_only)
        return 0;        

    if (TO->create_worm(locs, parts))
    {
        set_heal_delay(30.0);
        set_heal_rate(6);
        one_only = 1;
    }
    return 1;
}


void
body_move( object body, object room )
{
    tell_room (room,
        "A rasping noise accompanies the movement of a giant anaconda.\n");
    body->move(room);
}

int
move( mixed to_dest )
{
    int i;
    mixed next_room, prev_room;
  
    // take care of all long body being moved properly
    if ( !environment() )  // loading...
        return ::move (to_dest);

    // head is dead. Not moving anywhere
    if ( fragment[0][0] != 0  || worm_is_there(to_dest) )
        return 7;    // as if move was unsuccesful
  
    next_room = to_dest;
    for ( i = 0; i <= fragment[0][1]; i++ ) 
    {
        worm[i][SNAKE_OBJ]->move_living ("M", next_room);
        prev_room = worm[i][SNAKE_LOC];
        worm[i][SNAKE_LOC] = next_room;
        next_room = prev_room;
    }
    return ::move (to_dest);
}

void
notify_attack(object obj)
{
    // a message from body part being attacked
    if ( !heal_alarm_id )
        heal_alarm_id = set_alarm ( heal_delay, heal_delay, "heal_me");
}

void
notify_death(int body_part, object killer)
{
    // get a message from body part being killed
    // split fragment entry on two
  
    int entry, start, finish;
  
    D("Got notify_death from " + body_part + "\n");

    if (!worm[body_part][SNAKE_LOC])
        return;
  
    worm[body_part][SNAKE_OBJ] = 0;
    worm[body_part][SNAKE_LOC] = 0;
  
    for ( entry = 0; entry < sizeof (fragment) ; entry++ )
    if ( body_part >= fragment [entry][0] &&
        body_part <= fragment [entry][1]  )
        break;
  
    start = fragment[entry][0];
    finish = fragment[entry][1];
   
    fragment -= ({ fragment[entry] });
  
    D ("Deleting fragment entry " + start + "-" + finish + "\n");
  
    if ( start == finish ) 
    {  // segment consisting of one body part killed
        if ( !sizeof (fragment) )  // worm is dead
            die(killer);
        return;
    }
  
    if ( body_part > 0 && start < body_part)
        fragment += ({ ({start, body_part-1}) });
  
    if ( body_part < length -1 && body_part < finish)
        fragment  += ({ ({body_part+1, finish }) });
  
    D(sizeof(fragment) + " entries left\n");
    return;
}

// called by rooms in worm lair to notify us about people
// moving around. Much better than using triggers for following ppl

void
notify_leave_env (object who, object where)
{
    D("notify_leave_env received.\n");

    //assuming notifying room code checked who and where being valid
    if (!sizeof(worm[0]) ||        // following only when head alive
                                   // following only player we fight
        member_array (who, worm[0][SNAKE_OBJ]->query_enemy(-1)) == -1  ||
                  // follow only to connected rooms, do not teleport
        member_array (file_name(where), 
            environment()->query_exit_rooms()) == -1)
    return;

    D ("moving...\n");
    move(where);
}

private void
heal_me()
{
    int fr, part, fully_healed = 1, len, diff_hp, new_hp;
    object worm_part;
    D( "healing...\n");
  
    // for each connected worm fragment
    for ( fr = 0; fr < sizeof(fragment); fr++ ) 
    {
        // calculate average hps
        new_hp = 0;
        for (part = fragment[fr][0]; part <=fragment[fr][1]; part++)
            new_hp+=worm[part][SNAKE_OBJ]->query_hp();
        len = fragment[fr][1] - fragment[fr][0] + 1;    
        new_hp /= len;
    
        // heal connected fragments according to their length
        for (part = fragment[fr][0]; part <=fragment[fr][1]; part++) 
        {
            worm_part = worm[part][SNAKE_OBJ];
            if ((worm_part->query_hp() < worm_part->query_max_hp()) &&
	        (diff_hp = new_hp - worm_part->query_hp()) > 0 ) 
                worm_part->heal_hp(diff_hp * len / heal_rate);            
    
            // not healed yet and still under attack ?
            if (worm_part->query_hp() < worm_part->query_max_hp() ||
	        worm_part->query_attack() )
                fully_healed = 0;
        }
    }
  
    if ( fully_healed )
    // All parts have full hp. Remove alarm
    {
        remove_alarm (heal_alarm_id);
        D("removing heal_alarm...\n");
        heal_alarm_id = 0;
    }
    return;
}

void
die (object killer)
{
    object *team = killer->query_team_others(); // killer team, for logging
    string to_log = "Anaconda killed by ";
  
    if (sizeof(team) > 0)
        to_log += COMPOSITE_LIVE(({killer})+team);
    else
        to_log += capitalize(killer->query_real_name());
        to_log +=".\n";
    WRITE_LOG(to_log);
      // give master worm some time to execute pending alarms set 
      // by remove_delay function. Make sure that timeout here is 
      // greater than biggest possible delay set by remove_delay.
  set_alarm (100.0, 0.0, "remove_object" );
}

void
remove_object ()
{
    int i;
    object obj;

    for ( i = 0; i < sizeof(worm); i ++ )
    if (sizeof(worm[i]))
        worm[i][SNAKE_OBJ]->remove_object();
    D( "Worm just died.\n");
    ::remove_object();
}

// for debug purposes while developing, remove_object() above
// might not work
void
remove_worm() { ::remove_object(); }
     
// test whether there's any worm segment in the room 
private int
worm_is_there(mixed room)
{
    int i;
  
    for (i = 0; i< length; i++ )
    if (worm[i][SNAKE_LOC] == room)
        return 1;
    return 0;
}

// Ensures reliable removal of a stun added by worm body special attack
// Stun should be removed by external object, otherwise the body
// might die before executing remove stun alarm.
void
remove_delay (int delay, object victim)
{
    set_alarm (itof(delay)*10.0, 0.0, "do_remove_delay", victim);
}

private void
do_remove_delay (object victim )
{
    victim->remove_stun();
    tell_room(environment(victim), QNAME(victim) + " regains " +
        victim->query_possessive() + " senses.\n", victim);
    victim->catch_msg ("You regain your senses.\n");
}
