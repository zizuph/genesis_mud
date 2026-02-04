/*
 *  giant_rat.c
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
public void
create_creature()
{
    set_name("rat"); 
    set_race_name("rat");
    set_short("giant rat");
    set_adj(({"nasty", "huge", "giant" }));
    set_long("This nasty rat is huge and could carry disease.\n");

    /* str, con, dex, int, wis, dis */
    set_stats(({ 5, 15, 18, 1, 1, 15}));
    set_hp(1000);

    set_skill(SS_DEFENCE, 15);
    set_aggressive(1);

    set_attack_unarmed(A_BITE,  20, 20, W_IMPALE, 60, "teeth");
   
    set_hitloc_unarmed(H_HEAD, ({ 8, 5, 4, 5 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 8, 8, 6, 5 }), 80, "body");
}