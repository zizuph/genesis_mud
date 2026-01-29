#pragma strict_types
#include "/d/Avenir/common/common.h"
#include "/d/Avenir/include/relation.h"
#include "../defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <tasks.h>

inherit "/std/creature";
inherit "/std/act/action.c";
inherit "/std/combat/unarmed";

#define A_BUTT    TS_HEAD
#define A_LHOOF   TS_LHAND
#define A_RHOOF   TS_RHAND
#define A_RRHOOF  TS_RFOOT
#define A_RLHOOF  TS_RFOOT

/* These define what will be -hit- on the animal when it is
 * fighting. Deer don't have hands and feet, so we will
 * define what they do have ;)  */

#define H_HEAD   TS_HEAD
#define H_BODY   TS_TORSO
#define H_RHOOF  TS_RARM
#define H_LHOOF  TS_LARM
#define H_RLHOOF TS_LFOOT
#define H_RRHOOF TS_RFOOT

public void panic();
int bull1(object ob);
int bull2(object ob);
int bull3(object ob);
int bull4(object ob);
int bull5(object ob);


void
create_creature()
{
    set_name("bull");
    add_name("_bull");
    set_race_name("bull");
    add_adj("huge");
    set_living_name("Ceasar");
    set_long("This is a huge bull with wild staring eyes and " +
        "a big nose ring stuck in his nose. Judging his size " +
        "one do not want to end up in clinch with him even if " +
        "he seems to be tied to a bolt in the ground with a " +
        "long iron chain.\n");
    set_stats(({200, 200, 300, 27, 27, 157}));
    add_act("command fume");
    set_act_time(10);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_PARRY, 80);
    add_prop(LIVE_I_QUICKNESS, 100);
    add_prop(LIVE_M_NO_ACCEPT_GIVE, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    //                'weapon', hit,pen,  damage type,%use,desc
    set_attack_unarmed(A_BUTT,   40, 60,  W_IMPALE,   40,  "horns");
    set_attack_unarmed(A_LHOOF,  25, 25,  W_SLASH,    10,  "left front hoof");
    set_attack_unarmed(A_RHOOF,  25, 25,  W_SLASH,    10,  "right front hoof");
    set_attack_unarmed(A_RRHOOF, 25, 25,  W_BLUDGEON, 20,  "right rear hoof");
    set_attack_unarmed(A_RLHOOF, 25, 25,  W_BLUDGEON, 20,  "left rear hoof");
    //  Everything in this column should add up to   100 ---^


    //Remove default hit locations before implementing new ones
        for (int i = 0; i < 5; i++)
        remove_hitloc(i);

    //                 where,       ac,  %hit,   desc
    set_hitloc_unarmed(H_HEAD,   ({ 90 }), 10,   "head");
    set_hitloc_unarmed(H_BODY,   ({ 90 }), 50,   "body");
    set_hitloc_unarmed(H_RRHOOF, ({ 90 }), 10,   "right rear hoof");
    set_hitloc_unarmed(H_RLHOOF, ({ 90 }), 10,   "left rear hoof");
    set_hitloc_unarmed(H_LHOOF,  ({ 90 }), 10,   "left fore hoof");
    set_hitloc_unarmed(H_RHOOF,  ({ 90 }), 10,   "right fore hoof");
    //  The sum of this column should be  100 -^
}


public void
attacked_by(object attacker)
{
    ::attacked_by(attacker);

    if (attacker->id("_giant_wasp"))
        panic();
}

public void
panic()
{
    object yard, chain;

    tell_room(environment(this_object()), "The bull panics " +
        "and leave the field! You hear a loud snap when the " +
        "chain that held him breaks and falls to the ground.\n");
    yard = find_object("../yard");
    if (yard)
        tell_room(yard, "You hear a loud roar from the " +
            "small grass field.\n");
    chain = clone_object(THIS_DIR + "obj/chain");
    ENV(TO)->remove_item("chain");
    chain->move(ENV(TO));
    remove_object();
}

int
react_cloth(object matador)
{
    int counter;

    counter = random(5);
    switch(counter)
    {
        case 0:
            command("fume angrily ");
            break;
        case 1:
            command("glare angrily ");
            break;
        case 2:
            command("stare angrily ");
            break;
        case 3:
            command("emote stomps his hooves");
            break;
        case 4:
            command("emote shakes his head back and forth ");
            break;
    }
}


public int
special_attack(object victim)
{
    if (!(random(10)))
    {
        victim->catch_msg("The bull butts you EXTREMELY hard! You " +
            "fly over the fence in a nice curve caused by the " +
            "brutal strike from the bull.\n");
        victim->set_hp(victim->query_hp() / 2);
victim->move_living("M", THIS_DIR + "yard", 1);
tell_room(environment(this_object()), "The bull sends " +
    COMPOSITE_LIVE(victim) + " over the fence with a " +
    "brutal headbutt!\n");
if (present("_labal", environment(victim)))
{
    object labal = (present("_labal", environment(victim)));
    labal->smirk_ceasar();
        }
    }

}

int
bull1(object matador)
{
    command("emote looks up when he sees the red table cloth " +
        "beeing waved in his direction!");
    set_alarm(3.0, 0.0, &bull2(matador));
    return 1;
}

int
bull2(object matador)
{
    if (present(matador, environment(this_object())))
    {
        command("emote stomps his hooves in the ground and " +
            "lowers his head.");
        set_alarm(3.0, 0.0, &bull3(matador));
    return 1;
    }
    return 0;
}

int
bull3(object matador)
{
    if (present(matador, environment(this_object())))
    {
        command("emote raises his head and looks FURIOUS!");
        set_alarm(3.0, 0.0, &bull4(matador));
        return 1;
    }
    return 0;
}

int
bull4(object matador)
{
    if (present(matador, environment(this_object())))
    {
        tell_room(ENV(TO), "The bull runs towards " +
            QTNAME(matador) + " with lowered " +
            "head.\n", matador);
        matador->catch_msg("The bull starts to run in your " +
            "direction with his head lowered!\n");
        set_alarm(3.0, 0.0, &bull5(matador));
        return 1;
    }
    return 0;
}

int
bull5(object matador)
{
    if (present(matador, environment(this_object())))
    {

        if (random(3))
        {
            tell_room(environment(this_object()), "The bull is wild " +
                "and butts " + QTNAME(matador) + " hard with " +
                "his long horns.\n", matador);
            matador->catch_msg("You are hit hard by the bull and " +
                "you fly in a nice curve over the fence back into " +
                "the yard!\n");
            matador->move_living("M", THIS_DIR + "yard", 1);
            tell_room(environment(this_object()), QCTNAME(matador) +
                " flies with a nice curve over the fence.\n");
            if (present("_labal", environment(matador)))
            {
                object labal = (present("_labal", environment(matador)));
                labal->smirk_ceasar();
            }
            return 1;
        }
        else
        {
            matador->catch_msg("With a smart move with the cloth " +
               "and a nimble jump you avoid the charging bull. Olé!\n");
            tell_room(ENV(TO), "The bull passes " + QTNAME(matador) +
                " who smarly jumps aside while distracting the bull" +
                " with the red cloth. OLÉ!!\n", matador);
            return 1;
        }

    }
    return 0;
}


void
do_die(object killer)
{
    object chain;

    ::do_die();
        chain = clone_object(THIS_DIR + "obj/chain");
        chain->move(TO);
        ENV(TO)->remove_item("chain");
}

void
scared_bull()
{
    tell_room(ENV(TO), "The bull looks terrified at the " +
    "wasp nest. Slowly he backs away from it " +
    "so you cannot get any closer, but he " +
    "keeps staring at it with a wild " +
    "expression in his eyes.\n");
}
