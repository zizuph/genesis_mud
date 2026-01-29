
/*
 * ghost_cat.c
 *
 * An undead ghost cat for the Undead Tunnels near
 * Eldoral
 *
 * Copyright (C): Jaacar (Mike Phipps), October 8th, 2003
 *
 * - Remove obsolete tell_watcher function (Petros)
 * 
 * Last update was 2008/07/25
 * 2010/09/03 white-furred              Lavellan
 * 2010/09/23 do_die write->catch_tell  Lavellan
 * 2010/09/24 add race                  Lavellan
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/domove";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Genesis/gems/gem.h"
#include "/d/Calia/sys/map.h"
#include "defs.h"

#define A_BITE  0
#define A_CLAWS 1

#define H_HEAD 0
#define H_BODY 1
#define H_TAIL 2
#define H_EYES 3

void
create_creature()
{
    object gem;

    set_name("ghost cat");
//    add_name("cat");
    set_race_name("cat");
    add_name("ghost");
    add_name("undead");
//    set_short("white furred ghost cat");
//    set_adj(({"white","furred"}));
    set_short("white-furred ghost cat");
    set_adj(({"white","furred", "white-furred"}));

//    set_long("This small creatures looks like a normal cat that you "+
    set_long("This small creature looks like a normal cat that you "+
        "might see living in a house except it has wings growing "+
        "out of its back. It is covered in white fur and has glowing "+
        "red eyes and sharp looking teeth and claws.\n");

    if (random(5))
    {
        gem=RANDOM_GEM_BY_RARITY(GEM_SLIGHTLY_COMMON);
        gem->move(TO);
    }

    set_act_time(90);
    add_act("emote sounds like it is purring.");
    add_act("emote licks its paw and wipes it on its face.");

    set_cact_time(15);
    add_cact("emote scratches at your eyes.");
    add_cact("emote jumps on your shoulders and bites your ear.");

    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(LIVE_I_UNDEAD,20);
    add_prop(LIVE_I_NO_CORPSE,1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_alignment(-200);
    set_gender(random(2));

    set_stats(({40,40,80,40,40,40}));

    set_skill(SS_UNARM_COMBAT, 60);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_DEFENCE, 40);

    set_attack_unarmed(A_BITE, 15,25,W_IMPALE,20,"teeth");
    set_attack_unarmed(A_CLAWS,25,65,W_SLASH, 80,"claws");
    set_hitloc_unarmed(A_HEAD, ({5,5,5,5}), 40, "head");
    set_hitloc_unarmed(H_TAIL, ({5,5,5,10}), 15, "tail");
    set_hitloc_unarmed(H_BODY, ({10,15,15,20}), 35, "body");
    set_hitloc_unarmed(H_EYES, ({10,5,10,5}), 10, "eyes");

}

void
attacked_by(object attacker)
{
    ::attacked_by(attacker);
    MAP_ATTACK(FIND_STR_IN_OBJECT("cats", environment()), attacker);
}

public void
do_die(object killer)
{
    killer->catch_tell("There is a bright flash of light as the body of the "+
        "ghost cat implodes upon itself.\n");
    ::do_die(killer);

}
