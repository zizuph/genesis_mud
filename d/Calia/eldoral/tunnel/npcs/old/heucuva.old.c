
/*
 * heucuva.c
 *
 * An undead Heucuva for the Undead Tunnels near
 * Eldoral
 *
 * Copyright (C): Jaacar (Mike Phipps), October 13th, 2003
 *
 * - Removed obsolete tell_watcher function (Petros)
 */


inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <formulas.h>
#include <composite.h>
#include "/d/Calia/sys/map.h"
#include "defs.h"

#define A_LEFT_HAND  0

#define H_HEAD 0
#define H_BODY 1

void
create_creature()
{
    set_name("heucuva");
	add_name("undead");
    set_short("robed heucuva");
    set_adj(({"robed"}));
    set_race_name("heucuva");
    set_long("This is an undead spirit similar in appearance to a "+
        "skeleton, but appears to be much more dangerous. It appears "+
        "to be a humanoid skeleton of normal size wearing a tattered robe. "+
        "It is the restless spirit of a monastic priest who was less than "+
        "faithful to their holy vows. As punishment, it roams the realms "+
        "as undead.\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    set_alignment(-1100);
    set_gender(G_NEUTER);
    MONEY_MAKE_GC(random(2)+2)->move(this_object());
    add_prop(MAGIC_I_RES_MAGIC,50);
    add_prop(LIVE_I_UNDEAD,50);
    add_prop(LIVE_I_NO_CORPSE,1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    set_aggressive(1);

    set_stats(({(100+random(20)),(100+random(20)),
        (100+random(20)),(30+random(20)),
        (30+random(20)),(100+random(20))}));

    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_DEFENCE, 100);

    set_attack_unarmed(A_LEFT_HAND, 40,40,W_SLASH,50,"boney left hand");
        
    set_hitloc_unarmed(H_BODY, ({40,40,40,40}), 80, "body");
    set_hitloc_unarmed(H_HEAD, ({15,15,15,15}), 20, "head");
}

void
attacked_by(object attacker)
{
    object * heucuvas;
    
    ::attacked_by(attacker);

    heucuvas = FIND_STR_IN_OBJECT("heucuvas", environment());
    heucuvas -= ({ this_object(), attacker });
    
    if (sizeof(heucuvas))
    {
        MAP_ATTACK(heucuvas, attacker);
    }
}

public void
do_die(object killer)
{
    write("There is a bright flash of light as the heucuva implodes upon "+
        "itself.\n");
    ::do_die(killer);

}
