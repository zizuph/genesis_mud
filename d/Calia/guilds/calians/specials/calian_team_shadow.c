
/* 
  Shadow for team titles. 

  Coded by Maniac 11/1/96, thanks to Aridor for help.
*/

#include "defs.h"
#include CALIAN_HEADER

inherit "/std/shadow";


int
query_got_calian_team_shadow()
{
    return 1; 
}


void
remove_calian_team_shadow()
{
    remove_shadow();
}


string
query_guild_title_occ()
{
    object l;
    string t, to;

    if (sizeof(shadow_who->query_team())) {
        if (stringp(t = shadow_who->query_prop(CALIAN_S_TEAM_TITLE)))
            t = ("Proud Leader of " + t);
    }
    else {
        l = shadow_who->query_leader();
        if (!objectp(l)) 
            return shadow_who->query_guild_title_occ();

        if (stringp(t = l->query_prop(CALIAN_S_TEAM_TITLE)))
            t = ("Trusted Member of " + t);
    }

    to = shadow_who->query_guild_title_occ();
    if (!stringp(to) || !strlen(to))
        if (!stringp(t))
            return 0;
        else
            return t;
    else 
        if (!stringp(t))
             return to;
        else
            return (to + ", " + t);
}

