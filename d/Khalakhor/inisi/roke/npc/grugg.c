/*
 * grugg.c
 *
 * Used in carisca/c2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 *
 * Updated and added limbs to be cut off in battle and leftovers
 * Merged the two old files grugg.c and grugg2.c
 * - Treacher Sep 2021
 */

/* a nasty grugg - gresolle -92 */

#pragma save_binary
#pragma strict_types

inherit "/std/creature";
inherit "/std/act/action";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

#define LIMB                ROKEDIR + "obj/grugg-limb"
#define MAX_SEVERED_LIMBS   5
#define MAX_LEFTOVER_LIMBS  3


int limbs = 0;
int eqid;

void equip_myself();

void
default_config_npc(int i)
{
    int j;
    for (j = 0; j < 6; j++)
        set_base_stat(j, i);
}

void
create_creature()
{
    default_config_npc(75);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    NEVERKNOWN;
    set_gender(G_NEUTER);

    set_name("grugg");
    set_race_name("grugg");
    set_short("nasty grugg");
    set_adj("nasty");

    set_long("This is a nasty grugg from the boiling inside of the earth. " +
             "It looks like a huge centipede with lots of grotesque limbs, " +
             "except for the smoke coming from its mouth.\n");

    set_alignment(-500);

    set_skill(SS_DEFENCE, 50);
    set_skill(SS_UNARM_COMBAT, 50);

    add_act("emote gruggs: grugg!");
    add_act("emote makes a clicking sounds when it moves with several limbs at the same time.");
    add_act("emote rubs its feet with dust.");
    add_act("emote rubs its feet with dust."); // Quest hint, adding it again for extra exec
    set_act_time(3);
    set_random_move(3);

    set_attack_unarmed(0, 25, 25, W_IMPALE, 60, "jaws");
    set_attack_unarmed(1, 25, 25, W_BLUDGEON, 60, "breath");

    set_hitloc_unarmed(A_HEAD, 50, 10, "head");
    set_hitloc_unarmed(A_BODY, 50, 60, "body");
    set_hitloc_unarmed(A_FEET, 40, 30, "limb");

    eqid = set_alarm(1.0, 0.0, equip_myself);

    add_leftover(ROKEDIR + "obj/skin", "skin", 1, "", 1, 1);

    // 1 to MAX_LEFTOVER_LIMBS limbs as leftover
    add_leftover(LIMB, "limb", random(MAX_LEFTOVER_LIMBS) + 1, "", 1, 0);
    // Grugg can drop 1 to MAX_SEVERED_LIMBS number of limbs during battle
    limbs = random(MAX_SEVERED_LIMBS) + 1;
}
void
equip_myself()
{
    eqid = 0;
    seteuid(getuid());
    clone_object(ROKEDIR + "obj/dust")->move(TO);
}

void
react_spit()
{
    command("scream");
    command("drop dust");
    tell_room(ENV(TO), "A small puff of smoke comes from the grugg!\n");
    run_away();

    heal_hp(-10);
    if (!eqid)
        eqid = set_alarm(300.0, 0.0, equip_myself);
}

public void
emote_hook(string emote, object actor, string adverb,
           object *oblist, int cmd_attr, int target)
{
    if (emote != "spit") return;

    if (target)
        set_alarm(1.0, 0.0, &react_spit());
    else
        set_alarm(1.0, 0.0, &command("shiver fear"));
}

public void
emote_hook_onlooker(string emote, object actor, string adverb,
                    object *oblist, int cmd_attr)
{
    if (emote != "spit") return;
    set_alarm(1.0, 0.0, &command("shiver fear"));
}

void
scream(string s)
{
    tell_room(ENV(TO), s);
}

void
bomb(object ob)
{
    ob->remove_object();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (!from)
        return;

    set_alarm(itof(5 + random(4)), 0.0,
              &scream("The grugg eats the " + ob->query_name() +
                      " and seems to grow a little.\n"));

    set_alarm(1.0, 0.0, &bomb(ob));
    default_config_npc(query_average_stat() + 1);
}

mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int target_hitloc)
{
    // 20% chance each hit will sever a limb
    if(random(100) < 20 && limbs > 0)
    {
        set_alarm(0.5, 0.0, &command("emote shrugs in pain by the blow and a severed limb drops to the ground."));
        clone_object(LIMB)->move(environment(TO));
        limbs -= 1;
    }
    return (::hit_me(wcpen, dt, attacker, attack_id, target_hitloc));
}