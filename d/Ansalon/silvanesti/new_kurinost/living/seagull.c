/*
 * seagull.c
 *
 * The seagull of the Silvanesti coast.
 *
 * Copyright (C): Kellon, november 2010
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include "/d/Krynn/common/defs.h"
#include "local.h"

/* Inherit the Krynn creature */
inherit C_FILE

/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE  1
#define A_CLAWS 2

#define H_HEAD 1
#define H_BODY 2
#define H_LEGS 4

// G L O B A L   V A R S

// P R O T O T Y P E S

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : create_creature
 *  Arguments: none
 *  Returns  : void
 * 
 *  Creates the seagull.
 *
 */
public void
create_creature()
{
    string adj1 = ONE_OF(GULLCOLOURS);
    string adj2 = ONE_OF(GULLADJS);

    set_name(({ "gull", "seagull", GULLNAME }));
    set_long("Large grey feathers cover most of the long wings of " +
        "this seagull, with only a few black feathers at the tips " +
        "breaking the colour. Spanning atleast 70-80 centimeters, " +
        "the wings of this predator give the gull great speed and " +
        "maneuverability in the air. The beak and feet are yellow " +
        "and the rest of the large bird is covered in white " +
        "feathers. Known for its ferocity and daring, the seagull " +
        "will eat almost anything that can be eaten.\n");

    set_race_name("gull");
    add_adj(adj1);
    add_adj(adj2);

    set_short(adj1 + " " + adj2 + " gull");

    add_prop(CONT_I_HEIGHT, 35);
    add_prop(CONT_I_WEIGHT, 1500);
    add_prop(NPC_I_NO_LOOKS, 1);

    NEVERKNOWN;

    set_stats(({ 50, 50, 50, 10, 10, 80}));

    set_alignment(0);
    set_knight_prestige(1);

    set_skill(SS_DEFENCE, 40 + random(10));
    set_skill(SS_AWARENESS, 50);

    set_attack_unarmed(A_BITE, 50, 50, W_IMPALE, 90, "beak");
    set_attack_unarmed(A_CLAWS, 45, 45, W_SLASH, 10, "feet");

    set_hitloc_unarmed(H_HEAD, 30, 30, "head");
    set_hitloc_unarmed(H_BODY, 40, 55, "body");
    set_hitloc_unarmed(H_LEGS, 25, 15, "legs");
}


/*
 *  FUNCTION : special_attack
 *  Arguments: object - the enemy.
 *  Returns  : int - 1 as this is a special attack.
 * 
 *  The gulls attack in packs if possible.
 *
 */
public int
special_attack(object enemy)
{
    object *gulls = filter(all_inventory(E(TO)), &->id(GULLNAME)) -
        ({ TO });
    mixed *hitresult;
    string hit_desc = "", watcher_desc = "";
    int gullcount = sizeof(gulls);

    if (!random(10))
    {
        hitresult = enemy->hit_me((20 + random(20) + (gullcount * 10)),
                                  W_IMPALE, TO, -1);

        if (gullcount > 0)
        {
            hit_desc = "With spendid cooperation, the seagulls " +
                "work together to distract you. One gull feints " +
                "for an attack from your side as another prepares " +
                "for the real attack.\n";
            watcher_desc = "With spendid cooperation, the " +
                "seagulls work together to distract " +
                QTNAME(enemy) + ". One gull feints for an attack " +
                "from " + QTNAME(enemy) + "'s side as another " +
                "prepares for the real attack.\n";
        }

        if (hitresult[0] > 20)
        {
            hit_desc = hit_desc + "Flying above you to gain " +
                "altitude, the " + TO->query_short() + " suddenly " +
                "drops with amazing speed and cuts you deeply " +
                "with a hit from its beak.\n";
            watcher_desc = watcher_desc + "Flying above " +
                QTNAME(enemy) + " to gain altitude, the " +
                TO->query_short() + " suddenly drops with amazing " +
                "speed and cuts " + QTNAME(enemy) + " deeply with " +
                "a hit from its beak.\n";
        }
        else
        if (hitresult[0] > 10)
        {
            hit_desc = hit_desc + "Flying about you in broad " +
                "circles, the " + TO->query_short() + " suddenly " +
                "turns towards you sharply and cuts you with its " +
                "beak.\n";
            watcher_desc = watcher_desc + "Flying about " +
                QTNAME(enemy) + " in broad circles, the " +
                TO->query_short() + " suddenly turns towards " +
                QTNAME(enemy) + " sharply and cuts " + HIM(enemy) +
                " with its beak.\n";
        }
        else
        if (hitresult[0] > 0)
        {
            hit_desc = hit_desc + "Comming in for a quick strike, " +
                "the " + TO->query_short() + " gashes you lightly " +
                "with its beak.\n";
            watcher_desc = watcher_desc + "Comming in for a quick " +
                "strike, the " + TO->query_short() + " gashes " +
                QTNAME(enemy) + " lightly with its beak.\n";
        }
        else
        if (hitresult[0] < 1)
        {
            hit_desc = hit_desc + "Throwing itself into a dive, " +
                "the " + TO->query_short() + " lashes out against " +
                "you, but misses.\n";
            watcher_desc = watcher_desc + "Throwing itself into a " +
                "dive, the " + TO->query_short() + " lashes out " +
                "against " + QTNAME(enemy) + ", but misses.\n";
        }

        enemy->catch_msg(hit_desc);
        tell_watcher(watcher_desc, enemy);

        if (enemy->query_hp() < 1)
        {
            enemy->do_die(TO);
        }
    }

    return 1;
}


/*
 *  FUNCTION : attack_my_enemy
 *  Arguments: string - name of enemy to attack.
 *  Returns  : void
 * 
 *  Attacks an enemy.
 *
 */
public void
attack_my_enemy(string enemy_name)
{
    command("kill " + enemy_name);
}


/*
 *  FUNCTION : retaliate
 *  Arguments: object - the enemy
 *             int - delay in seconds before the attack.
 *  Returns  : void
 * 
 *  Called by the nest when someone steals an egg or by another gull
 *  when it is attacked.
 *
 */
public varargs void
retaliate(object enemy, int delay = 0)
{
    if (delay)
    {
        set_alarm(itof(delay), 0.0,
                  &attack_my_enemy(enemy->query_name()));
    }
    else
    {
        attack_my_enemy(enemy->query_name());
    }
}


/*
 *  FUNCTION : attacked_by
 *  Arguments: object - the attacker.
 *  Returns  : void
 * 
 *  This is called when someone attacks this gull.
 *
 */
public void
attacked_by(object enemy)
{
    object *gulls = filter(all_inventory(E(TO)), &->id(GULLNAME)) -
        ({ TO });
    int index;

    ::attacked_by(enemy);

    tell_room(E(TO), "Squawking loudly in alarm, the " +
        TO->short() + " quickly spreads its wings and prepares to " +
        "defend itself.\n");
    
    if (sizeof(gulls))
    {
        for (index = 0; index < sizeof(gulls); index++)
        {
            if (!random(3))
            {
                enemy->catch_msg("Hearing the hoarse cries of " +
                    "alarm, the " + TO->short() + " spreads its " +
                    "great wings and take to the skies, heading " +
                    "your way.\n");
                gulls[index]->retaliate(enemy, 10);
            }
            else
            {
                gulls[index]->retaliate(enemy);
            }
            
        }
    }
}

