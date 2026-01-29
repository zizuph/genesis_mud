
/* 
   This autoloading object is present on members of the Calian guild to 
   give them an alert if they try to team with an enemy of Calia. It does 
   not prevent teaming if the player really wants to. 

   Coded by Maniac, 19/3/96. 

   Added rack points reduction for fast logouts, Maniac, 22-23/5/01 
   Added glass medallion calls to council code, Maniac, 23-24/7/01
*/

#include <macros.h>
#include <stdproperties.h>
#include "defs.h"
#include COUNCIL_HEADER
#include CALIAN_HEADER

inherit "/std/object";
inherit CRPALACE_SPECIALS + "calian_code";

#define CALIAN_I_READY_TEAM_WITH "_calian_i_ready_team_with"


static int initial_rack_points; 


void 
create_object() 
{
    set_name(CALIAN_TEAM_OBJ); 
    set_no_show(); 
    remove_prop(OBJ_I_WEIGHT); 
    remove_prop(OBJ_I_VOLUME); 
    add_prop(OBJ_M_NO_DROP, "Drop what?\n"); 
}


int
calian_invite(string name)
{
    object tp = this_player();
    string n, lcn;

    if (!stringp(name))
        return 0;

    lcn = lower_case(name);
    n = capitalize(lcn); 

    if (!is_calian(tp)) {
        set_alarm(1.0, 0.0, remove_object);
        return 0;
    }

    if (!present(find_player(lcn), environment(tp)))
        return 0;

    if (tp->query_prop(CALIAN_I_READY_TEAM_WITH) == n) {     
        tp->remove_prop(CALIAN_I_READY_TEAM_WITH); 
        return 0;
    }

    seteuid(getuid());
    if (member_array(n, COUNCIL_CODE->query_enemy_list()) > -1) { 
         tell_object(tp, n + " is an enemy of Calia, confirm by " +
                       "inviting again if you still want to team.\n");
         tp->add_prop(CALIAN_I_READY_TEAM_WITH, n); 
         return 1;
    }

    return 0;
}


int 
calian_join(string name) 
{ 
    object tp = this_player(); 
    string n, lcn; 

    if (!stringp(name)) 
        return 0; 

    lcn = lower_case(name); 
    n = capitalize(lcn); 

    if (!is_calian(tp)) 
    { 
        set_alarm(1.0, 0.0, remove_object); 
        return 0; 
    } 

    if (!present(find_player(lcn), environment(tp))) 
        return 0; 

    if (tp->query_prop(CALIAN_I_READY_TEAM_WITH) == n) 
    { 
        tp->remove_prop(CALIAN_I_READY_TEAM_WITH); 
        return 0; 
    } 

    seteuid(getuid()); 
    if (member_array(n, COUNCIL_CODE->query_enemy_list()) > -1) 
    { 
         tell_object(tp, n + " is an enemy of Calia, confirm by " + 
                       "joining again if you still want to team.\n"); 
         tp->add_prop(CALIAN_I_READY_TEAM_WITH, n); 
         return 1; 
    } 

    return 0; 
}


/* 
 * Function:      check_glass_medallion 
 * Description:   Inform the council code of whether the 
 *                player has a glass medallion or not. 
 */ 
private void 
check_glass_medallion(object calian, int rack_points) 
{ 
    seteuid(getuid()); 
    if (rack_points < CALIAN_RACK_POINTS_MEDALLION_GLASS) 
        COUNCIL_CODE->add_has_glass_medallion(
                          capitalize(calian->query_real_name())); 
    else 
        COUNCIL_CODE->remove_has_glass_medallion(
                          capitalize(calian->query_real_name())); 
} 


/* 
 * Function:     restore_rack_points 
 * Description:  restores the Calian's rack points, called 
 *               by alarm when rack points are adjusted on 
 *               quitting, in case the quit command fails 
 *               for some reason, e.g. the player was 
 *               recently in combat. 
 */ 
private void 
restore_rack_points(object calian, int rp) 
{ 
    if (!objectp(calian)) 
        return; 

    calian->set_skill(CALIAN_RACK_POINTS, rp); 
    check_glass_medallion(calian, rp); 
} 


/* 
 * Function:     adjust_rack_points 
 * Description:  reduces rack points further if the player 
 *               borrowed during a brief login. This should 
 *               ONLY be called from the action function 
 *               "calian_quit". 
 * 
 */ 
private void 
adjust_rack_points(object calian)
{
    int t, crp, points_drop; 

    crp = calian->query_skill(CALIAN_RACK_POINTS); 

    if ((points_drop = initial_rack_points - crp) > 0 && 
        (t = time() - calian->query_login_time()) < 800) 
    { 
        if (t < 30) 
            points_drop *= 8; 
        else if (t < 60) 
            points_drop *= 6; 
        else if (t < 120) 
            points_drop *= 5; 
        else if (t < 180) 
            points_drop *= 4; 
        else if (t < 240) 
            points_drop *= 3; 
        else if (t < 300) 
            points_drop *= 2; 

        set_alarm(0.0, 0.0, &restore_rack_points(calian, crp)); 
        calian->set_skill(CALIAN_RACK_POINTS, crp = crp - points_drop); 
    } 

    check_glass_medallion(calian, crp); 
} 


/* 
 * Function name: enter_env 
 * Description  : This function is called each time this object enters a 
 *                new environment. This instance sets up the initial 
 *                rack points of the Calian destination. 
 * Arguments    : object dest - the destination we are entering. 
 *                object old  - the location we came from. This can be 0. 
 */ 
public void 
enter_env(object dest, object old) 
{ 
    ::enter_env(dest, old); 
    initial_rack_points = dest->query_skill(CALIAN_RACK_POINTS); 
} 


/* 
 * Function   : calian_quit 
 * Description: This instance invokes the "adjust_rack_points" 
 *              function. 
 */ 
public int 
calian_quit() 
{ 
    object calian; 

    if (living(calian = environment())) 
    { 
        seteuid(getuid()); 
        if (!(ARMAGEDDON->shutdown_active())) 
            adjust_rack_points(calian); 
        else 
            check_glass_medallion(calian, 
                calian->query_skill(CALIAN_RACK_POINTS)); 
    } 
    return 0; 
} 


void 
init() 
{
    ::init(); 
    add_action(calian_invite, "invite"); 
    add_action(calian_join, "join"); 
    add_action(calian_quit, "quit"); 
}
