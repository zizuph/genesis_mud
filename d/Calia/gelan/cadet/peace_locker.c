
/*
 *  A clonable locker for storing the weapons of cadets or
 *  graduates who visit the hall of peace.  
 *   
 *  Coded by Maniac@Genesis, May 15 1999
 *
 */ 

#include "cadet.h"

inherit "/std/container"; 

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <files.h>

int expire_alarm; 

void
create_container()
{
    set_name("locker"); 
    set_adj("peace"); 
    set_long("A peace locker.\n"); 
    add_prop(CONT_I_WEIGHT, 10000); 
    add_prop(CONT_I_MAX_WEIGHT, 400000); 
    add_prop(CONT_I_VOLUME, 10000); 
    add_prop(CONT_I_MAX_VOLUME, 400000); 
    add_prop(OBJ_M_NO_GET, 1); 
}


void
reset_locker_time()
{
    if (expire_alarm) 
        remove_alarm(expire_alarm);  
    expire_alarm = set_alarm(1200.0, 0.0, remove_object); 
}

