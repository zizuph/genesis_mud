#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "../banedead.h";

inherit "/std/shadow";


void
remove_curse_shadow()
{
	
    shadow_who->remove_prop(I_AM_DCURSED);
    shadow_who->add_prop(LIVE_I_QUICKNESS,shadow_who->query_prop(LIVE_I_QUICKNESS) + 200);
    tell_object(shadow_who,"The curse wears off!\n");
    remove_shadow();
}


int
query_curse_shadow()
{
    return 1;
}

void
init_curse_shadow(int i)
{
	
    shadow_who->add_prop(I_AM_DCURSED, 1);
    tell_object(shadow_who,"The curse slows your limbs!\n");
    shadow_who->add_prop(LIVE_I_QUICKNESS,shadow_who->query_prop(LIVE_I_QUICKNESS) - 200);
    set_alarm(itof(i),0.0,&remove_curse_shadow());
}