/**
 * Sap stun object.
 * This object is cloned into a victim when they are
 * the target of a tsap ability.  It keeps track of their
 * stun and removes it.
 * Louie 2004
 */

/**
 * Navarre Jan 21th 2007, added checks for who in start
 * and stop stunning to avoid runtime errors when who
 * is not present.
 */ 

 
inherit "/std/object";
//#include "../local.h"
#include <stdproperties.h>
#include <macros.h>

/** prototypes **/
public void start_stunning();
public void stop_stunning(object o);

public void
create_object()
{
    set_name("sap_stun_ob");
    set_short("sap stun object");
    set_long("You shouldn't see this.\n");
    set_no_show();
    
    set_alarm(1.5, 0.0, &start_stunning());

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_WEIGHT, 1);
    
}

public void
start_stunning()
{
    object who = environment(this_object());
    
    if(who && objectp(who))
    {
        who->catch_tell("You feel quite dizzy.\n");
        tell_room(environment(who), QCTNAME(who)+
                  " looks quite dizzy.\n", who, who);
        who->add_stun();
    }
    set_alarm(itof(5+random(11)), 0.0, &stop_stunning(who));
}

public void
stop_stunning(object who)
{
    if(who && objectp(who))
    {
        if (living(who))
        {
            who->catch_tell("You no longer feel as dizzy.\n");
            tell_room(environment(who), QCTNAME(who) +
                      " seems less dizzy.\n", who, who);
        }
        who->remove_stun();
    }
    set_alarm(0.5, 0.0, &remove_object());
}
