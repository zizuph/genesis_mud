#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "../nov.h";

inherit "/std/shadow";

void
remove_ghostvision_shadow()
{
    shadow_who->tell_watcher(QCTNAME(shadow_who)+"'s eyes stops radiating the dull violet glow.\n");
    shadow_who->add_prop(LIVE_I_SEE_INVIS, shadow_who->query_prop(LIVE_I_SEE_INVIS) - 20);
    shadow_who->remove_prop(IHAVEGHOSTVISION);
    tell_object(shadow_who, "Your ghostvision wears off!\n");
    
    remove_shadow();
}


int
query_ghostvision_shadow()
{
    return 1;
}


void
init_ghostvision_shadow(int i)
{
      tell_object(shadow_who,"Your eyes suddently radiate a dull violet glow!\n");
      shadow_who->tell_watcher(QCTNAME(shadow_who)+"'s eyes suddently radiate a dull violet glow.\n");
      shadow_who->add_prop(LIVE_I_SEE_INVIS, shadow_who->query_prop(LIVE_I_SEE_INVIS) + 20);
      shadow_who->add_prop(IHAVEGHOSTVISION, 1);
    
      set_alarm(itof(i),0.0,&remove_ghostvision_shadow());
}