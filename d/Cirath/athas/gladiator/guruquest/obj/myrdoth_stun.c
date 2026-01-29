/* This is myrdoth's stunning mental assault.
   Code (c) 1998 Damian Horton (bka Dethraine).     
   This code is heavily based upon Serpine's temphold.c 
   Redone for Raumdor, March 2001
 */
 
#pragma strict_types
 
inherit "/std/object";

#include "/d/Cirath/defs.h"
#include <stdproperties.h>
#include <macros.h>
 
int remove_time; //time before the stun expires
 
void
create_object()
{
    set_name("_myrdoth_stun_");
 
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_INVIS, 100);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_M_NO_DROP, 1);
    set_no_show();
}
 
void set_remove_time(int setting) 
{ 
    remove_time = setting;
}
 
void
init()
{
    ENV(TO)->add_attack_delay(remove_time, 1);
    set_alarm (itof(remove_time), 0.0, "end_stun");
}

void 
end_stun()
{
    ENV(TO)->catch_tell("You finally manage to force Myrdoth from your "+
        "mind, and are once again free to combat on a physical level.\n");  
    ENV(TO)->tell_watcher(QCTNAME(ENV(TO))+" seems to have recovered "+    
        "from some sort of internal struggle.\n", ENV(TO));
    remove_object();
}

