/*  file:  /d/Calia/sea/creatures/larva.c
 *  description:  A creature for cave area (/d/Calia/sea/beach/caves/)
 *                that can be used for a brief time as a light
 *                source.  When a player picks it up, the larva will
 *                continue to glow for a few minutes, then its light will
 *                go out.  
 *  coder:  Tigerlily
 *  date:  2002-09-03
 */

#pragma strict_types

inherit "/std/creature"; 
inherit "/std/act/domove"; 
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <const.h>
#include "defs.h"


#define A_FANG 0
#define A_TAIL  1
#define H_BODY 2

int taken = 0;
int lights_out();

void
create_creature()
{
    set_name("larva");
    set_adj(({"glowing", "slimy"}));
    set_pname("larvae");
    set_race_name("larva");
    set_long("This is the larva of some"+
      " creature of the dark. It is a soft green colour"+
      " and is covered in some sort of putrescent slime.\n");

    set_gender(G_NEUTER);
    set_stats(({15, 15, 15, 15, 15, 15}));
    set_hp(query_max_hp()); 
    set_skill(SS_UNARM_COMBAT, 15);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);

    // small light source
    add_prop(CONT_I_LIGHT, 1);
    add_prop(OBJ_M_NO_GET, 0);

    set_attack_unarmed(A_FANG, 10, 10, W_IMPALE, 30, "fang");
    set_attack_unarmed(A_TAIL, 10, 10, W_IMPALE, 30, "tail");

    set_hitloc_unarmed(H_BODY, ({5,30,30,30}), 100, "body");

    add_prop(LIVE_I_NEVERKNOWN, 1); 
    add_prop(CONT_I_HEIGHT, 1);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(CONT_I_WEIGHT, 5);
    add_prop(CONT_I_VOLUME, 3);
    add_prop(OBJ_I_HIDE, 10);
    add_act("emote emits a small sound like 'eep' and"+
      " curls into a ball.");
    add_act("emote curls into a ball."); 
    add_prop(NPC_I_NO_LOOKS, 1);
    set_cact_time(20);
    set_act_time(10);  
    set_m_in("wriggles in");
    set_m_out("leaves a trail of slime as it crawls away");
    set_random_move(30,0);
    set_restrain_path(CAVE_ROOM);
}


/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 */
void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    if (interactive(dest))
    {
	taken = 1;
	set_alarm(750.0, 0.0, &lights_out());
    }
    return;
}

/*
 * Function name: lights_out()
 * Description  : This function is called to allow the larva
 *                 to turn off its light after a period of time
 *                   if it has been held by player
 * Returns      : 1 if successful
 */
int
lights_out()
{
    command("emote emits a small 'eep' and stops glowing.");
    change_prop(CONT_I_LIGHT, 0);
    remove_adj("glowing");
    add_adj("dark");
    return 1;
}
