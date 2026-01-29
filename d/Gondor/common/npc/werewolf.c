/*
 *  A werewolf made by Arren October 95 
 *  Thanks to Olorin for valuable help.
 *
 *  Only silver weapons, bludgeon and magic hits the werewolf.
 *  I added bludgeon as Finrod Felagund was able to kill a 
 *  werewolf with his bare hands. 
 */
#pragma strict_types

inherit "/std/creature.c";
inherit "/std/combat/unarmed.c";
inherit "/std/act/attack";

#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define A_BITE    0
#define A_R_CLAW  1
#define A_L_CLAW  2

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

void
create_creature()
{
    set_name("werewolf");
    add_name("wolf");
    set_race_name("werewolf");
    set_adj(({ "dark", "enormous", }));

    set_short("enormous dark wolf");
    set_long(BSN(
        "A dark and fell beast, with a glossy black fur. "
      + "His eyes are glowing like crimson coals."));

    set_base_stat(SS_STR, 110 + random(10));
    set_base_stat(SS_DEX, 110 + random(10));
    set_base_stat(SS_CON, 110 + random(10));
    set_base_stat(SS_INT,  90 + random(10));
    set_base_stat(SS_WIS,  95 + random(10));
    set_base_stat(SS_DIS, 100 + random(10));

    set_alignment(-500 - random(200));
    set_gender(G_MALE);
    set_aggressive(1);

    set_skill(SS_DEFENCE, 95);
    set_skill(SS_UNARM_COMBAT, 90);
    set_skill(SS_BLIND_COMBAT, 80); /* Good sense of smell */
    set_skill(SS_AWARENESS, 90);

    set_attack_unarmed(A_BITE,   60, 60, W_IMPALE, 50, "terrible jaws");
    set_attack_unarmed(A_R_CLAW, 42, 37, W_SLASH,  30, "right claw");
    set_attack_unarmed(A_L_CLAW, 42, 37, W_SLASH,  30, "left claw");

    set_hitloc_unarmed(H_HEAD, ({ 55, 55, 55 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 55, 55, 55 }), 60, "body");
    set_hitloc_unarmed(H_LEGS, ({ 55, 55, 55 }), 20, "legs");

    set_learn_pref(({ 2, 2, 2, 1, 1, 1 }));

    add_prop(CONT_I_HEIGHT, 150);
    add_prop(CONT_I_WEIGHT, 80000);
    add_prop(CONT_I_VOLUME, 80000);
    add_prop(LIVE_I_SEE_DARK, 4);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
}

int
query_knight_prestige()
{
    int     stat = TO->query_average_stat();   

    return stat*stat/10;
}

public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id)
{
    mixed   result;
    object  weapon = attacker->query_weapon(attack_id);

/* silver weapons, bludgeon and magic hits the werewolf */
    if (weapon->adjectiv_id("silver") ||
        (dt & W_BLUDGEON) || (dt & MAGIC_DT))
    {
attacker->catch_msg("DEBUG: hit with silver weapon, or with magic or "
  + "bludgeon damage type!\n");
        return ::hit_me(wcpen, dt, attacker, attack_id);
    }

/* all other attacks do extremely little damage */
    else
        return ::hit_me(wcpen/25, dt, attacker, attack_id);
}

public int
special_attack(object enemy)
{
    object  me = TO;
    mixed  *hitresult;
    string  how;

    if (random(10))
        return 0;

    hitresult = enemy->hit_me(F_PENMOD(50, 50), W_SLASH, me, -1);

    switch(hitresult[0])
    {
        case -1 .. 0:
            how = "unharmed";
            break;
        case 1 .. 5:
            how = "nicked by the claws";
            break;
        case 6 .. 15:
            how = "raked by the claws";
            break;
        case 16 .. 30:
            how = "mangled by the claws";
            break;
        case 31 .. 50:
            how = "grievously injured by the claws";
            break;
        case 51 .. 90:
            how = "overborne and mangled";
            break;
        default:
            how = "overborne and ripped apart";
            break;
    }

    enemy->catch_msg(me->query_The_name(enemy) + " leaps ferociously upon "
      + "you. You are " + how + ".\n");
    tell_watcher(QCTNAME(me) + " leaps ferociously upon " + QTNAME(enemy)
      + ". " + CAP(PRONOUN(enemy)) + " is " + how + ".\n", me, enemy);

    if (enemy->query_hp() <= 0)
        enemy->do_die(me);

    return 1;
}
