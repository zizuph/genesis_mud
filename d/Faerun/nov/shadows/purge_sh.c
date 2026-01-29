#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "../nov.h";

inherit "/std/shadow";


void
remove_purge_shadow()
{
	
    shadow_who->remove_prop(I_AM_NPURGED);
    tell_object(shadow_who,"The purge wears off!\n");
    remove_shadow();
}

void
purge()
{
	tell_object(shadow_who,"You feel the raging force of the negative energy course through you!\n");
	shadow_who->add_fatigue(10);
}



int
query_purge_shadow()
{
    return 1;
}

void
init_purge_shadow(int i)
{
	
    shadow_who->add_prop(I_AM_NPURGED, 1);
    set_alarm(5.0,5.0,&purge());
    set_alarm(itof(i),0.0,&remove_purge_shadow());
}