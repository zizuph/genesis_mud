/*
 * Shadow for the amulet of newbieness
 *
 */

#pragma strict_types
#include <macros.h>

inherit "/std/shadow";

#include "/d/Genesis/specials/debugger/debugger_tell.h"


/* Definitions */
#define     SKILLS      ({ 0, 1, 2, 3, 4, 5, 6, 20, 21, 22, 23, 24 })


/* Global Variables */
int             active = 0;
int             *statbase = allocate(6);
int             *statorig = allocate(6);
int             *stataddo = allocate(6);
int             *stataddd = allocate(6);
int             *stataddn = allocate(6);

/* Prototypes */
public void     worn(object obj);
public void     removed();
public void     die();
public int      query_active();
public int      set_active(int a);
//public int      query_stat(int stat);
public int      query_skill(int skill);
public int      wearing_amulet() { return 1; }


public void
worn(object obj)
{
    int i;
    mapping d = ([ "/d/Sparkle" : "S", "/d/Genesis" : "G", "/w" : "W" ]);
    shadow_me(obj);
    if (!match_path( d, file_name(environment(obj))))
        return;
    if (obj->query_average() >= 40) {
        set_alarm(2.0, 0.0, &obj->catch_tell("You feel strange!\n"));
        active = 1;
        for (i = 0; i < 6; i++)
        {
            statbase[i] = obj->query_base_stat(i);
            statorig[i] = obj->query_stat(i);
            stataddo[i] = obj->query_stat_extra(i);
            if (statorig[i] > 20)
            {
                stataddn[i] = 20 - statbase[i];
                stataddd[i] = stataddn[i] - stataddo[i];
                obj->set_stat_extra(i, stataddn[i]);
            }
            else
            {
                stataddn[i] = stataddo[i];
                stataddd[i] = 0;
            }
        }
    }
} /* worn */


public void
removed()
{
    int i, d, c;
    if (!active)
        return;
    active = 0;
    set_alarm(2.0, 0.0, die);
        for (i = 0; i < 6; i++)
        {
            //statbase[i] = obj->query_base_stat(i);
            //statorig[i] = obj->query_stat(i);
            //stataddo[i] = obj->query_stat_extra(i);
            if (stataddd[i] != 0)
            {
                d = shadow_who->query_stat_extra(i) - stataddd[i];
                
                shadow_who->set_stat_extra(i, d);
            }
            c = shadow_who->query_stat(i);
            if (c != statorig[i])
                send_debug_message("Amulet", shadow_who->query_real_name() +
                    " stat " + i + " was " + statorig[i] + " but now " + c +
                    "! Base was " + statbase[i] + " now " +
                    shadow_who->query_base_stat(i) + ".");
        }
} /* removed */


public void
die()
{
    shadow_who->catch_tell("You no longer feel strange!\n");
    remove_shadow();
} /* die */


public int
query_active()
{
    return active;
} /* query_active */


public int
set_active(int a)
{
    active = a;
    return a;
} /* set_active */


#if 0
public int
query_stat(int stat)
{
    if (!active)
        return shadow_who->query_stat(stat);
    
    return min(20, shadow_who->query_stat(stat));
} /* query_stat */
#endif

public int
query_skill(int skill)
{
    if (!active)
        return shadow_who->query_skill(skill);
    
    if (member_array(skill, SKILLS) >=0)
    {
        return min(20, shadow_who->query_skill(skill));
    }
    else
    {
        return shadow_who->query_skill(skill);
    }
} /* query_skill */