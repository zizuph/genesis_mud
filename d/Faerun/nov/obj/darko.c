#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <stdproperties.h>
#include "../nov.h";

inherit "/std/object";

void
create_object()
{
    set_name("darkob");
    add_name("_darko");
    set_short("dark_object");
    set_long("Invis thingy.\n");
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_M_NO_STEAL,1);
    add_prop(OBJ_M_NO_DROP,1);
    add_prop(OBJ_I_LIGHT,-2);
    
    set_no_show();

    
}


void
remove_dark()
{
 
    
        tell_room(environment(this_object()),"Your aura of darkness fades away.\n");
        tell_room(environment(environment(this_object())),"The darkness suddently fades away!\n");
   
         remove_object();
}

void
set_dark_remove_time(int i)
{
    set_alarm(itof(i),0.0, &remove_dark());
}