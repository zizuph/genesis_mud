/**
 * Stun object.
 * This object is cloned into a victim when they are
 * the target of an awe attack.  It keeps track of their
 * stun and removes it.
 * Louie 2005
 */
 
inherit "/std/object";
//#include "../local.h"
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include <macros.h>

/** prototypes **/
public void start_stunning();
public void stop_stunning();

public void
create_object()
{
    set_name("dragon_stun_ob");
    set_short("dragon stun object");
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
    
    //who->catch_tell("You feel unable to concentra.\n");
    who->add_stun();
    
    set_alarm(itof(15+random(6)), 0.0, &stop_stunning());
}

public void
stop_stunning()
{
    object who = environment(this_object());
    who->catch_tell("You feel the awe fade.\n");
    tell_room(E(who),QCTNAME(who)+" appears to shake off the "+
        "effects of the awe.\n", who);
    who->remove_stun();
    set_alarm(0.5, 0.0, &remove_object());

}
