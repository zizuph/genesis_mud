#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "../nov.h";

inherit "/std/shadow";


void
remove_ghost_shadow()
{
	
    shadow_who->add_prop(LIVE_I_SEE_DARK, shadow_who->query_prop(LIVE_I_SEE_DARK) - 2);
    shadow_who->add_prop(LIVE_I_SEE_INVIS, shadow_who->query_prop(LIVE_I_SEE_INVIS) - 2);
    shadow_who->add_prop(OBJ_I_INVIS, shadow_who->query_prop(OBJ_I_INVIS) - 2);
    shadow_who->remove_prop(I_AM_NGHOST);
    tell_object(shadow_who,"You become visible again!\n");
    tell_room(environment(shadow_who), QCTNAME(shadow_who) + " suddently appears from nowhere!\n",
    ({shadow_who}));

    remove_shadow();
}

void
warn_ghost_shadow()
{
	tell_object(shadow_who,"You feel that you soon will become visible!\n");
	set_alarm(10.0,0.0,&remove_ghost_shadow());
}


void
attack_object(object ob)
{
    shadow_who->catch_msg("Your ghostform is interrupted because you engaged someone!\n");
    set_alarm(0.0,0.0, &remove_ghost_shadow());
    shadow_who->attack_object(ob);
}

void
attacked_by(object ob)
{
    tell_object(shadow_who,"Your ghostform is interrupted because you was attacked!\n");
    shadow_who->attacked_by(ob);
    set_alarm(0.0,0.0, &remove_ghost_shadow());
}


int
query_ghost_shadow()
{
    return 1;
}

void
init_ghost_shadow(int i)
{
    shadow_who->add_prop(LIVE_I_SEE_DARK, shadow_who->query_prop(LIVE_I_SEE_DARK) + 2);
    shadow_who->add_prop(LIVE_I_SEE_INVIS, shadow_who->query_prop(LIVE_I_SEE_INVIS) + 2);
    shadow_who->add_prop(OBJ_I_INVIS, shadow_who->query_prop(OBJ_I_INVIS) + 2);
    shadow_who->add_prop(I_AM_NGHOST, 1);
    set_alarm(itof(i),0.0,&warn_ghost_shadow());
}