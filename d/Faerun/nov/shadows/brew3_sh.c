#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "../nov.h";

inherit "/std/shadow";

void
remove_brew3_shadow()
{
    
    shadow_who->remove_prop(IHAVEBREW3);
    tell_object(shadow_who, "The brew of the night wears off!\n");
    
    remove_shadow();
}


int
query_brew3_shadow()
{
    return 1;
}


void
init_brew3_shadow(int i)
{

      shadow_who->add_prop(IHAVEBREW3, 1);
    
      set_alarm(itof(i),0.0,&remove_brew3_shadow());
}