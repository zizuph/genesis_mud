
/* 
   This is the room where kroug raids on the palace are started.
   Only Calian wizards, arches or keepers may start a kroug raid.

   Coded by Maniac, adapted from old raid room early May 1996. 
*/

#pragma save_binary

inherit "/std/room";
#include "/d/Calia/sys/kroug.h"
#include <macros.h>
#include <stdproperties.h>
#include <std.h>

#define CCMD "/d/Calia/glykron/palace/specials/calian_cmdsoul"
#define PALACE "/d/Calia/glykron/palace/rooms/light/"
#define CROAD "/d/Calia/mountain/croad/"


void
create_room()
{
    set_short("Palace raid control room");
    set_long("This is the room where kroug raids on the palace are " + 
        "configured, started and monitored. Only wizards of Calia, " +
        "Arches and Keepers may start one. The commands here are: " +
        "<raidhelp>, <warriors>, <raidtest>, <raidstr>, <raidgroup>, " +
        "<raidwarn>, <raidcheck>, <raidreset>, <raidstart>, " +
        "<raidwhere>, <raidscore> and <terminate>. A " +
        "running commentary will appear in this room while raids " +
        "are in progress.\n");

    add_exit(PALACE+"gold", "gold"); 
    add_exit(PALACE+"entrance", "entrance");
    add_exit(CROAD+"croad26", "hurn");
    add_exit(CROAD+"croad20", "highroad");
    add_exit(CROAD+"croad10", "medroad");
    add_exit(CROAD+"croad0", "lowroad");

    add_prop(ROOM_I_INSIDE, 1);

    seteuid(getuid()); 
}


int
security_check(object tp, string what)
{
    string n, d;
    int i, t; 
    string * gms;
    
    tell_room(this_object(), QCTNAME(tp) + " attempts to " + what + 
              ".\n", tp); 
    tp->catch_msg("You attempt to " + what + ".\n");

    n = tp->query_real_name();
    d = SECURITY->query_wiz_dom(n);
    t = WIZ_CHECK;
    gms = SECURITY->query_guild_masters("calian");
    
    if ((t != WIZ_KEEPER) && (t != WIZ_ARCH) && (d != "Calia") && (d != "Promotion")
        && !IN_ARRAY(n, gms)) {
        tell_room(this_object(), "Not allowed to do that, naughty " +
                                 "naughty!\n"); 
        return 0;
    }

    return 1;
}



/* Action to start a raid. */ 
int
start_raid()
{
    int r; 

    if (!security_check(this_player(), "commence a kroug raid")) {
         notify_fail("Heh.\n"); 
         tell_room(this_object(), "Action failed.\n"); 
         return 0;
    }

    r = PALACE_RAID_OB->start_raid(); 
    if (r) 
        tell_room(this_object(), "Action successful.\n"); 
    else
        tell_room(this_object(), "Action failed.\n"); 
    return r; 
}


int
set_number_groups(string str)
{
    int r; 

    if (!security_check(this_player(), "set the number of groups")) {
         notify_fail("Heh.\n"); 
         tell_room(this_object(), "Action failed.\n"); 
         return 0;
    }

    r = PALACE_RAID_OB->set_number_groups(str); 
    if (r) 
        tell_room(this_object(), "Action successful.\n"); 
    else
        tell_room(this_object(), "Action failed.\n"); 
    return r; 
}


int
set_warning_dur(string str)
{
    int r; 

    if (!security_check(this_player(), "set the warning duration")) {
         notify_fail("Heh.\n"); 
         tell_room(this_object(), "Action failed.\n"); 
         return 0;
    }

    r = PALACE_RAID_OB->set_warning_dur(str); 
    if (r) 
        tell_room(this_object(), "Action successful.\n"); 
    else
        tell_room(this_object(), "Action failed.\n"); 
    return r; 
}


int
set_strength(string str)
{
    int r; 

    if (!security_check(this_player(), "set the attack strength")) {
         notify_fail("Heh.\n"); 
         tell_room(this_object(), "Action failed.\n"); 
         return 0;
    }

    r = PALACE_RAID_OB->set_strength(str); 
    if (r) 
        tell_room(this_object(), "Action successful.\n"); 
    else
        tell_room(this_object(), "Action failed.\n"); 
    return r; 
}


int
do_test(string str)
{
    int r; 

    if (!security_check(this_player(), "test maximum kroug strength")) {
         notify_fail("Heh.\n"); 
         tell_room(this_object(), "Action failed.\n"); 
         return 0;
    }

    r = PALACE_RAID_OB->do_test(str); 
    if (r) 
        tell_room(this_object(), "Action successful.\n"); 
    else
        tell_room(this_object(), "Action failed.\n"); 
    return r; 
}



int
check_configuration()
{
    return PALACE_RAID_OB->check_configuration(); 
}



int
warriors()
{
    return CCMD->list_active_calians();
}


int
whereabouts(string str)
{
    return PALACE_RAID_OB->whereabouts(str); 
}


int
check_scores(string str)
{
    return PALACE_RAID_OB->check_scores(str); 
}

int
terminate(string str)
{
    int r;

    if (!security_check(this_player(), "terminate a kroug raid")) {
         notify_fail("Heh.\n"); 
         tell_room(this_object(), "Action failed.\n"); 
         return 0;
    }

    r = PALACE_RAID_OB->terminate(str); 

    if (r) 
        tell_room(this_object(), "Action successful.\n"); 
    else
        tell_room(this_object(), "Action failed.\n"); 
    return r; 
}


int
do_reset(string str)
{
    int r;

    if (!security_check(this_player(), "reset the raid status")) {
         notify_fail("Heh.\n"); 
         tell_room(this_object(), "Action failed.\n"); 
         return 0;
    }

    r = PALACE_RAID_OB->do_reset(str); 

    if (r) 
        tell_room(this_object(), "Action successful.\n"); 
    else
        tell_room(this_object(), "Action failed.\n"); 
    return r; 
}


int
raidhelp()
{
     this_player()->more(read_file(RAID_HELP)); 
     return 1;
}

void
init()
{
    ::init();
    add_action(whereabouts, "raidwhere"); 
    add_action(do_test, "raidtest"); 
    add_action(set_strength, "raidstr"); 
    add_action(set_warning_dur, "raidwarn"); 
    add_action(set_number_groups, "raidgroup"); 
    add_action(check_configuration, "raidcheck"); 
    add_action(start_raid, "raidstart"); 
    add_action(warriors, "warriors");
    add_action(terminate, "terminate"); 
    add_action(do_reset, "raidreset"); 
    add_action(check_scores, "raidscore"); 
    add_action(raidhelp, "raidhelp"); 
}

