
/* 
   Coded by Glykron & Maniac
   These are racks to keep things tidy, they do not have a save
   feature.  

   History:
           23/7/03    Readjusted code for Thalassia        Jaacar
           2/12/02    Added indication of recoverability   Maniac
           27/8/99    appraise handling more efficient     Maniac
          25/11/97    updated enter/leave handling         Maniac
           20/6/96    made more efficient                  Maniac
             5/9/95   modified                             Maniac
            20.3.95   LANG_THESHORT used for shorts        Maniac
*/

#pragma save_binary

#include <macros.h>
#include <config.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <language.h>
#include <wa_types.h>
#include <std.h>
#include "defs.h"

inherit "/std/container";

object this;

void
create_rack()
{
}

nomask void
create_container()
{
    set_name("rack");
    add_prop(OBJ_M_NO_GET, "It is attached to the floor.\n");
    add_prop(CONT_I_VOLUME, 10000);
    add_prop(CONT_I_WEIGHT, 10000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);
    add_prop(CONT_I_MAX_WEIGHT, 1000000);

    this = THIS;
    create_rack();
    seteuid(getuid()); 
}

int
fits(object ob)
{
    return 1;
}

/* 
 * Function: prevent_enter
 * Stops an object being put in a rack if it doesn't fit, by returning 1;  
 */ 
int
prevent_enter(object ob)
{
    if (fits(ob)) 
        return 0;

    write(capitalize(LANG_THESHORT(ob)) + " won't fit in " + 
          LANG_THESHORT(this_object()) + ".\n");  
    return 1;
}


int
appraise(string str)
{
    object *obs, ob;

    if (sizeof(obs = FIND_STR_IN_OBJECT(str, this))) {
        ob = obs[0];
        this_player()->catch_msg("You peer at " + LANG_THESHORT(ob) + 
                      " inside " + LANG_THESHORT(this_object()) + 
                      ".\n");
        ob->appraise_object();
        return 1;
    } 
    return 0;
}


int
reject_object(object ob, object env)
{
    if (ob->move(env) == 0) {  
        tell_room(env, 
                  capitalize(LANG_THESHORT(ob)) + " falls off " + 
                  LANG_THESHORT(this_object()) + ".\n"); 
        return 1; 
    } 
    return 0; 
}


void
recoverable_check(object ob, object env, object tp)
{
    if (ob->check_recoverable()) 
        return;
 
}

void
init()
{
    ::init();
    add_action(appraise, "appraise");
}

