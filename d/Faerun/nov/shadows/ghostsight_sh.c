#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "../banedead.h";

inherit "/std/shadow";

void
remove_ghostsight_shadow()
{
    shadow_who->tell_watcher(QCTNAME(shadow_who)+"'s eyes stops radiating the dull violet glow.\n");
    shadow_who->add_prop(LIVE_I_SEE_INVIS, shadow_who->query_prop(LIVE_I_SEE_INVIS) - 20);
    shadow_who->remove_prop(IHAVEGHOSTSIGHT);
    tell_object(shadow_who, "Your ghostsight wears off!\n");
    
    remove_shadow();
}


int
query_ghostsight_shadow()
{
    return 1;
}


void
init_ghostsight_shadow(int i)
{
      tell_object(shadow_who,"Your eyes suddently radiate a dull violet glow!\n");
      shadow_who->tell_watcher(QCTNAME(shadow_who)+"'s eyes suddently radiate a dull violet glow.\n");
      shadow_who->add_prop(LIVE_I_SEE_INVIS, shadow_who->query_prop(LIVE_I_SEE_INVIS) + 20);
      shadow_who->add_prop(IHAVEGHOSTSIGHT, 1);
    
      set_alarm(itof(i),0.0,&remove_ghostsight_shadow());
}