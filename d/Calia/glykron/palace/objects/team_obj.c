
/* 
   This autoloading object is present on members of the Calian guild to 
   give them an alert if they try to team with an enemy of Calia. It does 
   not prevent teaming if the player really wants to.  

   Coded by Maniac, 19/3/96. 
*/

#include <macros.h>
#include <stdproperties.h>
#include "defs.h"
#include COUNCIL_HEADER

inherit "/std/object";
inherit GLYKRON_SPECIALS + "calian_code";

#define CALIAN_I_READY_TEAM_WITH "_calian_i_ready_team_with"


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
                       "joining again if you still want to team.\n");
         tp->add_prop(CALIAN_I_READY_TEAM_WITH, n); 
         return 1;
    }

    return 0;
}


void
init()
{
    ::init();
    add_action(calian_invite, "invite");
    add_action(calian_join, "join");
}

