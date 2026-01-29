/*
 * hen.c
 *
 * Used in nyreese/cadu_q5.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* A Hen , by Glindor */

#pragma save_binary
#pragma strict_types

inherit "/std/creature";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/combat/unarmed";

#include "defs.h"

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

void
create_creature()
{
    NEVERKNOWN;

    set_name("hen");
    set_gender(1);               
    set_race_name("hen");
    set_short("white hen");
    set_adj("white");
    set_long("An ordinary hen.\n");

    default_config_creature(10);

    set_attack_unarmed(0, 20, 5, W_SLASH, 50, "claw");
    set_attack_unarmed(1, 25, 5, W_IMPALE, 50, "bill");

    set_hitloc_unarmed(0, ({ 4 }), 20, "head");
    set_hitloc_unarmed(1, ({ 7 }), 80, "body");

    set_random_move(20);
    set_act_time(30);
    add_act("@@act");
    add_prop(LIVE_I_NO_CORPSE, 1);

    seteuid(getuid());
}

void
act()
{
    object egg;

    if (!random(10))
    {
        seteuid(getuid());
	egg = clone_object(ROKEDIR + "obj/egg");
	egg->move(E(TO));
	tell_room(E(TO),"The hen laid an egg.\n");
	return;
    }
    
    tell_room(E(TO),"The hen cackles.\n");
}

void
do_die(object killer)
{
    object corpse;
    if (query_hp() > 0) return;

    corpse = clone_object(ROKEDIR + "obj/deadhen");
    corpse->move(E(TO));
    
    ::do_die(killer);
}
