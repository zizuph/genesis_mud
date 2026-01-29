#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "../nov.h";

inherit "/std/shadow";


void
remove_regen_shadow()
{
	
    shadow_who->remove_prop(I_AM_NREGEN);
    tell_object(shadow_who,"The regeneration wears off!\n");
    shadow_who->remove_prop(REGENSTOP);
    remove_shadow();
}

void
regen()
{
	
	
	if (shadow_who->query_prop(REGENSTOP))
	{
		tell_object(shadow_who,"You stop the regeneration!\n");
		remove_regen_shadow();
		return;
	}
	
	if (shadow_who->query_mana() < 35)
	{
		tell_object(shadow_who,"You dont have enough mana to sustain the " +
		"regeneration to continue!\n");
		remove_regen_shadow();
		return;
	}
	
	
	tell_object(shadow_who,"The necromantic energies regenerate your body!\n");
	tell_room(environment(shadow_who), "Some of the wounds on "+QCTNAME(shadow_who)+"'s " +
	"body closes.\n", ({shadow_who}));
	shadow_who->heal_hp(300);
	shadow_who->add_mana(-35);
	set_alarm(5.0,0.0, &regen());
}



int
query_regen_shadow()
{
    return 1;
}

void
init_regen_shadow(int i)
{
	
    shadow_who->add_prop(I_AM_NREGEN, 1);
    set_alarm(5.0,0.0,&regen());
    set_alarm(itof(i),0.0,&remove_regen_shadow());
}