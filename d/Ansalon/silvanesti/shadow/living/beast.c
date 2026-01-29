
inherit "/std/creature";
inherit "/std/monster";
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/silvanesti/shadow/local.h"

/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE  1
#define A_LCLAW 2
#define A_RCLAW 4
#define A_LTENT 3
#define A_RTENT 5

#define H_HEAD 1
#define H_BODY 2
#define H_LEGS 3
#define H_LTENT 4
#define H_RTENT 5

create_krynn_monster()
{
    set_name("beast");
    set_race_name("displacer beast");
    set_short("black-furred beast");
    set_adj(({"black-furred","displacer"}));
    set_long("@@long_desc");

    /* str, con, dex, int, wis, dis */
    set_stats(({ 130, 130, 130, 80, 80, 130}));

    set_skill(22,60);
    set_skill(SS_DEFENCE, 60);

    set_aggressive(1);
    /* Give the tiger some attacks */

    /* Arguments to set_attack_unarmed: 
     *   attack id, hit, pen, damage type, percent usage, description
     */
    set_attack_unarmed(A_BITE, 30, 30, W_IMPALE, 10, "bite");
    set_attack_unarmed(A_LCLAW, 33, 33, W_SLASH, 20, "left claw");
    set_attack_unarmed(A_RCLAW, 33, 33, W_SLASH, 20, "right claw");
    set_attack_unarmed(A_LTENT, 37, 37, W_SLASH, 25, "left tentacle");
    set_attack_unarmed(A_RTENT, 37, 37, W_SLASH, 25, "right tentacle");
   
    /* Give the tiger some hit locations */

    /* Arguments to set_hitloc_unarmed:
     *   hit location id, ac, percent hit, description
     */
    set_hitloc_unarmed(H_HEAD, 30, 15, "head");
    set_hitloc_unarmed(H_BODY, 40, 65, "body");
    set_hitloc_unarmed(H_LEGS, 30, 10, "legs");
    set_hitloc_unarmed(H_LTENT, 25, 5, "left tentacle");
    set_hitloc_unarmed(H_RTENT, 25, 5, "right tentacle");
    set_alignment(-100);
    add_prop(LIVE_I_NEVERKNOWN,1);
}

/*
 * Here we redefine the special_attack function which is called from
 * within the combat system. If we return 1 then there will be no
 * additional ordinary attack.
 *
 */
int
special_attack(object enemy)
{
    object me;
    mixed *hitresult;
    string how;

    /* Only execute the special attack 1 in 10 rounds */
    if (random(10))
    {
	return 0;  /* Continue with the normal attacks */
    }

    hitresult = enemy->hit_me(20+random(30), W_IMPALE, me, -1);
    switch (hitresult[0])
    {
        case 0:
            how = "unwounded";
            break;
        case 1..10:
            how = "barely wounded";
            break;
        case 11..20:
            how = "wounded";
            break;
        default:
            how = "seriously wounded";
            break;
    }

    enemy->catch_msg(QCTNAME(TO) + " lashes at you with its tentacles.\n" +
      "You are " + how + " by the sharp spines.\n");
    tell_room(QCTNAME(TO) + " lashes at " + QTNAME(enemy) + " with its " +
      "tentacles.\n" + QCTNAME(enemy) + " appears " + how + ".\n");

    if (enemy->query_hp() <= 0)
    {
	enemy->do_die(this_object());
    }
    
    return 1; /*  Important! Should not have two attacks in a round. */
}

string
long_desc()
{
  return "A displacer beast.. yummy!\n";
}
