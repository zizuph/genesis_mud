
/* 
    ~Calia/gelan/cadet/cadet_pushup_ob.c 

    A paralyze object for when cadets are doing pushups, which 
    is one of their emotes. 

    Coded by Maniac@Genesis, April 1997 

    Copyright (C) Miguel Leith 1997 

    Updated by Maniac, 25/1/2001
*/ 

inherit "/std/paralyze"; 

#include <language.h> 
#include <stdproperties.h> 
#include <ss_types.h> 
#include <macros.h> 

#define CADET_I_PUSHUPS "_cadet_i_pushups" 

void pushups(); 
int stop_pushups(string str); 


void 
create_paralyze() 
{ 
     set_fail_message("You must <stop> doing pushups first!\n"); 
     set_stop_object(this_object()); 
     set_stop_fun("stop_pushups"); 
     set_stop_verb("stop"); 
} 


int 
stop_pushups(string str) 
{ 
    object tp = this_player(); 

    if (objectp(tp)) { 
        write("You stop doing pushups and stand up.\n"); 
        say(QCTNAME(tp) + " stops doing pushups and stands up.\n"); 
        tp->remove_prop(CADET_I_PUSHUPS); 
        tp->remove_prop(LIVE_S_EXTRA_SHORT); 
        return 0; /* paralyze object will disappear */ 
    } 
    return 1; /* paralyze object will stay */ 
} 


/* 
 * Function:     pushups 
 * Description:  Continues doing pushups 
 * 
 */ 
void
pushups()
{
    object player;
    int num, tnum;
    string wnum;

    player = environment(); 

    if (!objectp(player)) { 
        remove_object(); 
        return;
    } 

    if (objectp(player->query_attack())) { 
        stop_pushups(""); 
        remove_object(); 
        return;
    } 

    if (player->query_fatigue() < 10) { 
        tell_object(player, "You collapse, unable to do more pushups.\n"); 
        tell_room(environment(player), QCTNAME(player) + " collapses, " + 
                   "unable to do more pushups.\n", player); 
        player->remove_prop(CADET_I_PUSHUPS); 
        player->remove_prop(LIVE_S_EXTRA_SHORT); 
        remove_object(); 
        return; 
    } 

    num = random(player->query_stat(SS_STR) + 
                 player->query_stat(SS_CON) + 
                 player->query_fatigue()) + 20; 

    num = num / 10; 
    tnum = player->query_prop(CADET_I_PUSHUPS); 
    tnum += num; 
    player->add_prop(CADET_I_PUSHUPS, tnum); 
    player->add_fatigue(-10); 

    tell_object(player, "You do " + LANG_WNUM(num) + " more pushups, " + 
                "making a total of " + LANG_WNUM(tnum) + " so far.\n"); 

    tell_room(environment(player), 
          QCTNAME(player) + " does " + LANG_WNUM(num) + " more pushups, " + 
          "making a total of " + LANG_WNUM(tnum) + " so far.\n", player); 
    set_alarm(5.0, 0.0, &pushups()); 
}


void 
start_pushups() 
{ 
    object e = environment(); 

    if (!objectp(e) || !interactive(e)) {
        remove_object(); 
        return; 
    } 

    e->add_prop(LIVE_S_EXTRA_SHORT, " is doing pushups"); 

    set_alarm(5.0, 0.0, &pushups()); 
} 
