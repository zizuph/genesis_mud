/*
 *  large_rat.c
 *
 *  Britanica 160322
 */
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";   /* This gets us standard */
                                 /* unarmed routines */

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include "../include/cave_defs.h"

/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE 0

#define H_HEAD 0
#define H_BODY 1

/*
 * Function name: create_creature
 * Description  : constructor.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
create_creature()
{
    set_name("rat"); 
    set_race_name("rat");
    set_short("large rat");
    set_adj(({"nasty", "large" }));
    set_long("This nasty rat is large and could carry disease.\n");

    /* str, con, dex, int, wis, dis */
    set_stats(({ 5, 10, 13, 1, 1, 15}));
    set_hp(500);

    set_skill(SS_DEFENCE, 10);
    
    set_restrain_path(KOB_LAIR_PATH);
    set_random_move(60); 
    set_aggressive(1);

    set_attack_unarmed(A_BITE,  15, 15, W_IMPALE, 40, "teeth");
   
    set_hitloc_unarmed(H_HEAD, ({ 8, 5, 4, 5 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 8, 8, 6, 5 }), 80, "body");
}

