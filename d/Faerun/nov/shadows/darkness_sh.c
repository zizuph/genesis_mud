#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "../nov.h";

inherit "/std/shadow";

void
remove_darkness_shadow()
{
    shadow_who->tell_watcher(QCTNAME(shadow_who)+"'s body stops radiating darkness.\n");
    shadow_who->add_prop(OBJ_I_LIGHT, shadow_who->query_prop(OBJ_I_LIGHT) + 2);
    shadow_who->remove_prop(IHAVEDARKNESS);
    tell_object(shadow_who, "You stop radiating darkness!\n");
    
    remove_shadow();
}


int
query_darkness_shadow()
{
    return 1;
}


void
init_darkness_shadow(int i)
{
      tell_object(shadow_who,"Your body starts radiating darkness!\n");
      shadow_who->tell_watcher(QCTNAME(shadow_who)+"'s body starts radiating darkness!\n");
      shadow_who->add_prop(OBJ_I_LIGHT, shadow_who->query_prop(OBJ_I_LIGHT) - 2);
      shadow_who->add_prop(IHAVEDARKNESS, 1);
    
      set_alarm(itof(i),0.0,&remove_darkness_shadow());
}