inherit "/std/act/chat";
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <language.h>
#include <filter_funs.h>
#include "defs.h"

#define A_BITE       0
#define A_LCLAW      1
#define A_RCLAW      2
#define A_L_TENTACLE 3
#define A_R_TENTACLE 4

#define H_HEAD       0
#define H_BODY       1
#define H_TAIL       2
#define H_RARM       3
#define H_LARM       4
#define H_RLEG       5
#define H_LLEG       6
#define H_L_TENTACLE 7
#define H_R_TENTACLE 8

#define TENT_PEN     400

int always_hit;

/*
 * Function name: create_creature
 * Description  : Sets initial vars which turns this object into the
 *                beast of the ravine.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_creature()
{
    set_name("beast");
    set_race_name("beast");
    set_adj("sleek");
    add_adj("black"); 
    set_long("This creature is a terrible sight to behold. Sleek and " +
        "black, it vaguely resembles a monstrous cat, except for the " +
        "long, talon-tipped tentacles growing out of its shoulders, " +
        "and brightly burning green eyes. Its black fur ripples with " +
        "the slightest movement, suggesting muscles like steel bands " +
        "beneath its hide.\n");

    set_stats(({ 70, 100, 90, 90, 100, 100 }));

    set_hp(query_max_hp());

    set_skill(SS_DEFENCE, 80);
    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_BLIND_COMBAT, 80);

    set_attack_unarmed(A_BITE, 25, 45, W_IMPALE, 20, "jaws");
    set_attack_unarmed(A_LCLAW, 40, 40, W_SLASH, 15, "left claws");
    set_attack_unarmed(A_RCLAW, 40, 40, W_SLASH, 15, "right claws");
    set_attack_unarmed(A_L_TENTACLE, 35, 35, W_IMPALE, 25, "left tentacle");
    set_attack_unarmed(A_R_TENTACLE, 35, 35, W_IMPALE, 25, "right tentacle");

    set_hitloc_unarmed(H_HEAD, ({45, 40, 45, 50}), 11, "head");
    set_hitloc_unarmed(H_BODY, ({40, 35, 20, 50}), 50, "body");
    set_hitloc_unarmed(H_TAIL, ({40, 40, 40, 50}), 5, "tail");
    set_hitloc_unarmed(H_RARM, ({25, 25, 20, 50}), 5, "right foreleg");
    set_hitloc_unarmed(H_LARM, ({25, 25, 20, 50}), 5, "left foreleg");
    set_hitloc_unarmed(H_RLEG, ({30, 30, 25, 50}), 2, "right hind leg");
    set_hitloc_unarmed(H_LLEG, ({30, 30, 25, 50}), 2, "left hind leg");
    set_hitloc_unarmed(H_R_TENTACLE, ({25, 25, 20, 50}), 10,
        "right tentacle");
    set_hitloc_unarmed(H_L_TENTACLE, ({25, 25, 20, 50}), 10,
        "left tentacle");

    set_m_in("flashes past out of nowhere!");
    set_m_out("vanishes in a black blur");
    set_mm_in("comes screaming out of nowhere!");
    set_mm_out("vanishes like a shadow.");

    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(MAGIC_I_RES_FIRE, 100);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    set_alignment(-1200);

}

/*
 * Function name: special_attack
 * Description  : This function is called by heart_beat() in the
 *                combat object. It allows the possibility of a 
 *                special attack occurring rather than a normal
 *                attack. This particular special attack is just
 *                an enhanced damage attack.
 * Arguments    : enemy - Object pointer to the living to attack.
 * Returns      : 0 - Special attack no executed, proceed with normal
 *                    attack (one or the other may occur, not both).
 *                1 - Special attack executed. No further attack this
 *                    round.
 */
public int
special_attack(object enemy)
{
    mixed *hitresult;
    string how;

  /* 20% chance of using special attack */
    if (!always_hit)
    {
        if (random(5))
            return 0;
    }
    else
        always_hit = 0; 
    
    hitresult = enemy->hit_me(TENT_PEN, W_IMPALE, TO, -1, A_BODY);

    if (hitresult[0] == 0)
        how = "but misses entirely!";
    else if (hitresult[0] < 5)
        how = "but the talons leave little more than a scratch.";
    else if (hitresult[0] < 20)
        how = "but fortunately, the talons leave only a few deep " +
            "scratches.";
    else if (hitresult[0] < 50)
        how = "and the talons leave a hideous gash!";
    else if (hitresult[0] < 75)
        how = "and the talons tear a vicious wound!";
    else if (hitresult[0] < 99)
        how = "and the talons inflict a horrible amount of damage!";
    else
        how = "and the talons do massive damage, leaving a gaping " +
            "hole in their place!";

    if (enemy->query_hp() <= 0)
    {
        tell_object(enemy, "The tentacles of the beast lash forward " +
            "at the same time, from opposite sides, and close about " +
            "your body. The grip is perfect, and the beast " +
            "literally tears you in half!\n");
        tell_room(environment(enemy), "The tentacles of the beast " +
            "lash forward at " + QTNAME(enemy) + " at the same time, " +
            "from opposite sides, and close about " +
            enemy->query_possessive() + " body. The grip is " +
            "perfect, and the beast literally tears " +
            enemy->query_objective() + " in half!\n", ({enemy}));
        enemy->do_die(TO);
        return 1;
    }
    else
    {
        tell_object(enemy, "The tentacles of the beast lash out " +
            "at your body, slashing at you from opposite sides, " +
            how + "\n");
        enemy->tell_watcher("The tentacles of the beast " +
            "lash out at " + QTNAME(enemy) + "'s body, slashing at " +
            enemy->query_objective() + " from opposite sides, " +
            how + "\n", enemy);
        return 1;
    }            
}

/*
 * Function name: hunt_attack
 * Description  : This function forces a special_attack() call.
 *                It is called by the quest brain in the ravine
 *                as the beast stalks its target. The beast arrives,
 *                executes one special attack, and then attempts to
 *                escape in the brain code. Here, it just makes sure
 *                that it's possible to attack the player, and if
 *                so, do it.
 * Arguments    : who - Object pointer to the living to try and
 *                      attack.
 * Returns      : n/a
 */
public void
hunt_attack(object who)
{
  /* Make sure 'who' is a living player in this room. */
    if (!who || who->query_ghost() ||
        !present(who, environment()))
        return;

  /* Make sure the beast can see 'who'. */
    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, who))
        return;

  /* Make sure there are no 'no attack' props. */
    if (who->query_prop(OBJ_M_NO_ATTACK) ||
        environment()->query_prop(OBJ_M_NO_ATTACK))
        return;

  /* Make sure the beast isn't held in some way. */
    if (query_prop(LIVE_I_STUNNED))
        return;

  /* Ok, everything seems fine, force a 'special attack'. */
    always_hit = 1;
    special_attack(who);
}

/*
 * Function name: second_life
 * Description  : Called after a living dies. Here we do it to
 *                deliver a flashy death message, and move the
 *                eye of the beast into the room. The eye 'knows'
 *                who killed the beast, and is the object which
 *                must be returned as proof of its death.
 * Arguments    : killer - Object pointer to the living that
 *                         killed this object.
 * Returns      : 0 - Nothing happened, this object didn't really die.
 *                1 - Dead, gone, bye-bye, snuffed it, shuffled off
 *                    this mortal coil.
 */
public int
second_life(object killer)
{
    object eye;

    if (TO->query_hp() > 0)
        return 0;

    tell_room(environment(),"With a roar of rage, full of pain " +
        "and anguish, the beast dies. As the body collapses to " +
        "the ground, it slowly dissolves and disperses into a " +
        "black mist, which drifts away into the forest. Only " +
        "a single, green eye remains on the ground.\n");

    seteuid(getuid());

    eye = clone_object(OBJ + "beast_eye");
    eye->set_killer(killer->query_real_name());
    eye->move(environment());
    killer->add_prop(LIVE_I_KILLED_BEAST, 1);
    remove_object();
    return 1;
}
