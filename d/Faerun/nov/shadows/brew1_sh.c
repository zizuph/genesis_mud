#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "../nov.h";

inherit "/std/shadow";

void
remove_brew1_shadow()
{
    
    shadow_who->remove_prop(IHAVEBREW1);
    tell_object(shadow_who, "The brew of lifestealing wears off!\n");
    
    remove_shadow();
}


int
query_brew1_shadow()
{
    return 1;
}


void
init_brew1_shadow(int i)
{

      shadow_who->add_prop(IHAVEBREW1, 1);
    
      set_alarm(itof(i),0.0,&remove_brew1_shadow());
}