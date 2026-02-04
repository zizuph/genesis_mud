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
    set_name("salamander"); 
    set_race_name("lizard");
    set_short("small salamander");
    set_adj(({"quick", "small" }));
    set_long("A small quick moving salamander.\n");

    /* str, con, dex, int, wis, dis */
    set_stats(({ 5, 5, 45, 1, 1, 15}));
    set_hp(200);

    set_skill(SS_DEFENCE, 15);

    set_attack_unarmed(A_BITE,  20, 20, W_IMPALE, 60, "teeth");
   
    set_hitloc_unarmed(A_R_FOOT, ({ 8, 5, 4, 5 }), 20, "right foot");
    set_hitloc_unarmed(A_L_FOOT, ({ 8, 8, 6, 5 }), 80, "left foot");
    
    add_act( "emote quickly runs across the floor" );
}

/*
 * Function name: secure_room
 * Description  : constructor.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
secure_room()
{
    command("close door");
    command("lock door");
}