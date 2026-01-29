/*
 */

#pragma strict_types
#pragma save_binary
#pragma no_inherit

inherit "/std/shadow";

#include "../guild.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <filter_funs.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

public int
has_senses_shadow()
{
    return 1;
}

public void
remove_senses_shadow()
{
    remove_shadow();
}

void
init_senses_shadow()
{
    setuid();
    seteuid(getuid());
}

varargs string
notice_presence(int success = 0)
{
    string *message;
    
    /*
     * Switches message based on success percentage, can have empty
     * slots in case you want to lower the chance of it revealing
     * any information.
     */
    switch(success)
    {
        case  1..10:
        message =   ({
                    "",
                    "A faint rustle warns you of someones presence.\n",
                    "You glimpse a shadows flicker in the corner of your eye.\n",
                    });
            break;
        case 11..30:
        message =   ({
                    "",
                    "A faint rustle warns you of someones presence.\n",
                    "You glimpse a shadows flicker in the corner of your eye.\n",
                    });
            break;
        case 31..50:
        message =   ({
                    "",
                    "A faint rustle warns you of someones presence.\n",
                    "You glimpse a shadows flicker in the corner of your eye.\n",
                    });
            break;
        case 51..80:
        message =   ({
                    "",
                    "A faint rustle warns you of someones presence.\n",
                    "You glimpse a shadows flicker in the corner of your eye.\n",
                    });
            break;
        case 81..100:
        message =   ({
                    "A faint rustle warns you of someones presence.\n",
                    "You glimpse a shadows flicker in the corner of your eye.\n",
                    });
            break;
        default:
        message =   ({
                    "A faint rustle warns you of someones presence.\n",
                    "You glimpse a shadows flicker in the corner of your eye.\n",
                    });
            break;
    }
    
    return message[random(sizeof(message))];
} /* notice_presence */

varargs int
verify_seen(object target, int force = 0)
{
    int invis_mod, success;
    
    if (!objectp(target) || !living(target) || target->query_wiz_level())
        return 0;
    
    if (!force && target->check_seen(shadow_who))
        return 0;
        
    success = shadow_who->resolve_task(TASK_HARD,
              ({SS_FOCUS, TS_WIS, SS_AWARENESS}),
              target,
              ({SS_SNEAK, TS_WIS, SS_HIDE}));
    
    if ((invis_mod = target->query_prop(OBJ_I_INVIS)) && (success > 0))
        success = success / 2;
    
    if (success < 1)
        return 0;
    
    return success;
} /* verify_seen */


/*
 * Function name:   init
 * Description:     Tells us of new players in our neighborhood
 */
public void
init_living()
{
    int success;
    
    shadow_who->init_living();
    
    if (success = verify_seen(this_player()))
        notice_presence(success);
} /* init */