
/* 

   obsolete, removes itself

   Coded by Maniac, 11/6/97

 */ 

inherit "/std/object"; 

#include <stdproperties.h>
#include <macros.h>
#include "object.h"

void
create_object()
{
    set_name(DOUBLE_EMOTE_OB_ID); 
    set_no_show(); 
    add_prop(OBJ_M_NO_DROP, 1); 
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0); 
}


void
init()
{
    ::init();
    set_alarm(1.0, 0.0, remove_object); 
}

