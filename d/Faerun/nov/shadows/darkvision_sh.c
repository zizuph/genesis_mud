#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "../nov.h";

inherit "/std/shadow";

void
remove_darkvision_shadow()
{
    shadow_who->tell_watcher(QCTNAME(shadow_who)+"'s eyes stops radiating the dull red glow.\n");
    shadow_who->add_prop(LIVE_I_SEE_DARK, shadow_who->query_prop(LIVE_I_SEE_DARK) - 2);
    shadow_who->remove_prop(IHAVEDARKVISION);
    tell_object(shadow_who, "Your darkvision wears off!\n");
    
    remove_shadow();
}


int
query_darkvision_shadow()
{
    return 1;
}


void
init_darkvision_shadow(int i)
{
      tell_object(shadow_who,"Your eyes suddently radiate a dull red glow!\n");
      shadow_who->tell_watcher(QCTNAME(shadow_who)+"'s eyes suddently radiate a dull red glow.\n");
      shadow_who->add_prop(LIVE_I_SEE_DARK, shadow_who->query_prop(LIVE_I_SEE_DARK) + 2);
      shadow_who->add_prop(IHAVEDARKVISION, 1);
    
      set_alarm(itof(i),0.0,&remove_darkvision_shadow());
}