
/* 
 * The room where Calians may get permission to train maul. 
 * 
 * Coded by Maniac 5-6/12/96. 
 * 
 * Updated to remove Calians who haven't been around for 
 * a long time, Maniac, 22/12/00 
 * 
 */ 

#pragma save_binary
#pragma no_inherit

#include <macros.h>
#include <stdproperties.h>
#include <std.h>
#include <money.h>
#include <composite.h>
#include <time.h> 

#include "defs.h"

#include COUNCIL_HEADER
#include CALIAN_HEADER


inherit "/std/room"; 
inherit CRPALACE_SPECIALS + "calian_code"; 

string *maulers = ({ }); 
string *swarmers = ({ }); 

static mapping backed = ([ ]); 

/* After 50 days since last login a player can be deregistered 
   as a swarmer or mauler */ 
static int time_to_allow_deregister = (3600 * 24 * 40); 
static int time_to_force_deregister = (3600 * 24 * 65); 
int query_time_since_last_login(string pn); 


int
can_be_registered(string pl, object sec)
{
    if (sec->query_wiz_rank(pl) || 
        !sec->exist_player(pl) || 
        (query_time_since_last_login(pl) > 
         time_to_force_deregister)) 
        return 0; 

    return 1; 
}


void
swarmer_check()
{
    object sec;

    sec = find_object(SECURITY); 

    swarmers = filter(swarmers, &can_be_registered(,sec)); 
    save_object(MAUL_SAVE); 
}


void
mauler_check()
{
    object sec;

    sec = find_object(SECURITY); 
    maulers = filter(maulers, &can_be_registered(,sec)); 
    set_alarm(1.0, 0.0, swarmer_check); 
}


void
create_room()
{
    set_short("Maul learning room"); 
    set_long("Here it is possible to <learn maul> to " + 
             "the first level, provided certain requirements " + 
             "are met, after which the skill can be improved " + 
             "downstairs. To qualify, an aspiring mauler must " + 
             "have been rewarded at least once by the Council, " + 
             "and be supported (<maulback>ed) by two specialist " + 
             "swarmers. Generally there also have to be at " + 
             "least twice as many <swarmers> as <maulers> " + 
             "<register>ed here. " + 
             "Swarmers may <deregister>, and the Council may " + 
             "deregister anyone who has not visited the realms " + 
             "for a long time.\n"); 

    add_prop(ROOM_I_INSIDE, 1); 

    add_exit(CRPALACE_LIGHT_ROOMS + "boardroom", "southeast"); 

    restore_object(MAUL_SAVE); 

    set_alarm(1.0, 0.0, mauler_check); 
}


int
query_prevent_shadow()
{
    return 1;
}


int
too_many_maulers()
{
    if ((sizeof(swarmers) / 2) <= sizeof(maulers)) 
        return 1;
    else
        return 0;
}


string *
query_maulers()
{
    return maulers;
}


string *
query_swarmers()
{
    return swarmers;
}


int
is_swarmer(string str)
{
    if (member_array(lower_case(str), swarmers) > -1)
        return 1;
    else
        return 0;
}


int
is_mauler(string str)
{
    if (member_array(lower_case(str), maulers) > -1)
        return 1;
    else
        return 0;
}


void
player_left_guild(object tp)
{
    string str = tp->query_real_name(); 

    if (!stringp(str)) 
        return; 

    maulers -= ({ str }); 
    swarmers -= ({ str }); 
    save_object(MAUL_SAVE); 
}


int
add_swarmer(string str)
{
    if (is_swarmer(str))
        return 0;

    if (is_mauler(str)) 
        maulers -= ({ str });  

    swarmers += ({ str }); 
    save_object(MAUL_SAVE); 
    return 1;
}


int
add_mauler(string str)
{
    if (is_mauler(str))
        return 0;

    if (is_swarmer(str)) 
        swarmers -= ({ str });  

    maulers += ({ str }); 
    save_object(MAUL_SAVE); 
    return 1;
}


private void
do_register(object tp)
{
    string pn;

    if (tp->query_wiz_level()) { 
        tell_object(tp, "Wizards may not register.\n"); 
        return; 
    } 

    pn = tp->query_real_name(); 
    if (tp->query_skill(SS_MAUL))  { 
        if (add_mauler(pn)) 
            tell_object(tp, "You are now registered as a mauler.\n"); 
        else 
            tell_object(tp, "You were registered as a mauler, " + 
                        "which is correct.\n"); 
    } 
    else if (tp->query_skill(SS_SWARM)) { 
        if (add_swarmer(pn)) 
            tell_object(tp, "You are now registered as a swarmer.\n"); 
        else 
            tell_object(tp, "You were registered as a swarmer, " + 
                        "which is correct.\n"); 
    } 
    else if (is_swarmer(pn)) { 
         swarmers -= ({ pn }); 
         save_object(MAUL_SAVE); 
         tell_object(tp, "You are no longer registered as a swarmer.\n"); 
    } 
    else if (is_mauler(pn)) { 
         maulers -= ({ pn }); 
         save_object(MAUL_SAVE); 
         tell_object(tp, "You are no longer registered as a mauler.\n"); 
    } 
    else 
         tell_object(tp, "You are unskilled as a swarmer or mauler.\n"); 
}


/* 
 * Function: register
 * Description: Action function to register a player as whatever
 *              form of fighting they specialise in, swarmer or
 *              mauler. 
 * 
 */ 
int
register()
{
    do_register(this_player()); 
    return 1; 
}


int
is_rewarded(object tp)
{
    if (tp->query_skill(REWARD) < 1) 
       return 0;
    else
       return 1;
}


/* 
 * Function:     back_mauler 
 * Description:  Action function to allow a special swarmer to back 
 *               someone to train maul 
 * 
 */ 
int 
back_mauler(string str)
{
    mixed bd; 
    object tp, sw; 
    string pn; 
 
    if (!stringp(str)) {  
        notify_fail("Maulback whom?\n"); 
        return 0; 
    } 

    if (!is_calian(tp = this_player())) { 
        notify_fail("You are not a Calian!\n"); 
        return 0;
    } 

    sw = present(str = lower_case(str), this_object()); 

    if (!objectp(sw) || !interactive(sw)) { 
        notify_fail("You don't see that person here!\n");  
        return 0;
    } 

    if (tp == sw) { 
        notify_fail("Back yourself? Yeah, you'd make a " + 
                    "great team!\n"); 
        return 0; 
    } 

    if (!is_calian(sw)) { 
        notify_fail("That person is not a Calian!\n"); 
        return 0;
    } 

    if (tp->query_wiz_level()) { 
        notify_fail("Wizards may not back someone.\n"); 
        return 0; 
    } 

    str = sw->query_real_name(); 
    pn = tp->query_real_name(); 
    bd = backed[str]; 

    if (sizeof(bd) == 2) { 
        notify_fail("That person is already backed by two swarmers!\n"); 
        return 0;
    } 
    else if (pointerp(bd) && (member_array(pn, bd) > -1))  {  
        notify_fail("You already back that person!\n"); 
        return 0;
    } 

    if (sw->query_skill(SS_MAUL)) { 
        notify_fail("That person is already trained in maul!\n"); 
        return 0;
    } 

    if (!is_rewarded(sw)) { 
        notify_fail("That player has not been rewarded by the Council.\n"); 
        return 0;
    } 

    if (tp->query_skill(SS_MAUL) || !tp->query_skill(SS_SWARM)) { 
        notify_fail("You are not a specialist swarmer!\n"); 
        return 0; 
    } 

    tell_object(tp, "Checking your registration..\n"); 
    do_register(tp); 

    if (!pointerp(bd)) 
        bd = ({ pn }); 
    else 
        bd += ({ pn }); 

    backed = m_delete(backed, str); 
    backed += ([ str : bd ]); 

    tell_object(tp, "You now back " + sw->query_the_name(tp) + ".\n"); 
    if (too_many_maulers()) 
         tell_object(tp, "Oh no! There are currently too many " + 
                     "registered maulers!\n"); 
    return 1; 
}


/* 
 * Function:     learn_maul 
 * Description:  Action function to enable someone to learn one 
 *               level of maul if they meet the necessary 
 *               criteria 
 * 
 */ 
int
learn_maul(string str)
{
    object tp = this_player(); 
    string pn; 
    mixed bd;

    str = lower_case(str); 

    if (str != "maul") { 
        notify_fail("Learn what? Maul?\n"); 
        return 0;
    } 

    if (!is_rewarded(tp)) { 
        notify_fail("You have not been rewarded by the Council.\n"); 
        return 0;
    } 

    pn = tp->query_real_name(); 

    bd = backed[pn]; 

    if (sizeof(bd) < 2) { 
        notify_fail("You have not been backed by two specialist swarmers!\n");  
        return 0; 
    } 

    if (too_many_maulers()) {   
         notify_fail("There are currently too many registered maulers!\n"); 
         return 0;
    } 

    if (tp->query_skill(SS_MAUL)) { 
        notify_fail("You are already trained in maul!\n"); 
        return 0;
    } 

    if (is_swarmer(pn)) { 
        notify_fail("You will have to <deregister> from being " +
                    "a swarmer first.\n"); 
        return 0;
    } 

    if (!MONEY_ADD(tp, -1)) {  
        notify_fail("You need at least a copper coin!\n"); 
        return 0; 
    } 

    tp->set_skill(SS_MAUL, 1); 
    tell_object(tp, 
         "You have now learned your first level of maul, " + 
         "and may improve it in the training room!\n"); 
    tell_room(this_object(), QCTNAME(tp) + " learns a level " + 
         "of the maul skill!\n", tp); 
    do_register(tp); 

    if (tp->query_skill(SS_SWARM) == 100) { 
        tp->set_skill(SS_SWARM, 99); 
        tell_object(tp, 
             "Your swarm skill is reduced by one level.\n"); 
    } 

    return 1; 
}


/* 
 * Function: check_swarmers 
 * Description: Action function to list the Calians who are registered 
 *              as swarmers
 */ 
int
check_swarmers()
{
    this_player()->more("The following Calians are registered as swarmers:\n" + 
    (sizeof(swarmers) ? COMPOSITE_WORDS(map(swarmers, capitalize)) : "None") + 
                   ".\n"); 
    return 1;
}


/* 
 * Function: check_maulers 
 * Description: Action function to list the Calians who are registered 
 *              as maulers 
 */ 
int
check_maulers()
{
    this_player()->more("The following Calians are registered as maulers:\n" + 
    (sizeof(maulers) ? COMPOSITE_WORDS(map(maulers, capitalize)) : "None") + 
                   ".\n"); 
    return 1; 
}


/* 
 * Function:  query_time_since_last_login 
 * Description:  returns the time since the specified player 
 *               last logged in, or -1 if s/he doesn't exist 
 * Arguments: pn, the name of the player 
 */ 
int
query_time_since_last_login(string pn)
{
    object pl; 
    int t; 

    if (!objectp(pl = SECURITY->finger_player(pn)) || 
        !(t = pl->query_login_time())) 
        return -1; 
    return (time() - t); 
}


/* 
 * Function: deregister 
 * Description: Action function enabling a Calian to deregister 
 *              him/herself from swarm, or the Council to 
 *              deregister a Calian who hasn't logged in for 
 *              a long time from swarm or maul. 
 * 
 */ 
int
deregister(string str)
{
    object tp = this_player(); 
    string pn = tp->query_real_name(); 

    if (stringp(str) && strlen(str)) { 
        if (COUNCIL_CODE->is_council_member(pn) || 
            SECURITY->valid_write(file_name(this_object()), 
                                  tp, "write_file")) { 
            if (is_swarmer(str = lower_case(str))) { 
                if (query_time_since_last_login(str) > 
                    time_to_allow_deregister) { 
                    swarmers -= ({ str }); 
                    save_object(MAUL_SAVE); 
                    write("Ok.\n"); 
                    return 1; 
                } 
                notify_fail("It is not yet " + 
                            CONVTIME(time_to_allow_deregister) + 
                            " since that person last visited the " +
                            "realms.\n"); 
                return 0; 
            } 
            else if (is_mauler(str)) { 
                if (query_time_since_last_login(str) > 
                    time_to_allow_deregister) { 
                    maulers -= ({ str }); 
                    save_object(MAUL_SAVE); 
                    write("Ok.\n"); 
                    return 1; 
                } 
                notify_fail("It is not yet " + 
                    CONVTIME(time_to_allow_deregister) + 
                    " since that person last visited the realms.\n"); 
                return 0; 
            } 
            notify_fail("No person of that name is registered " + 
                        "here as a swarmer or mauler.\n"); 
            return 0; 
        } 
        notify_fail("You do not have the authority to deregister " + 
                    "someone else here!\n"); 
        return 0; 
    } 

    if (!is_swarmer(pn)) { 
        notify_fail("You are not registered as a swarmer!\n"); 
        return 0; 
    } 

    swarmers -= ({ pn }); 
    save_object(MAUL_SAVE); 
    tell_object(tp, "Ok, you are no longer registered as a swarmer.\n"); 
    return 1; 
}


void
init()
{
    ::init(); 
    add_action(learn_maul, "learn"); 
    add_action(back_mauler, "maulback"); 
    add_action(register, "register"); 
    add_action(deregister, "deregister"); 
    add_action(check_swarmers, "swarmers"); 
    add_action(check_maulers, "maulers"); 
}
