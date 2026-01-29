/*
 * gargoyle.c
 *
 * The guardians for the black tower north of Port Macdunn.
 * These gargoyles remain stone normally, however will animate
 * and attack anyone attempting to enter the tower grounds
 * (though they won't hunt). This can be negated by carrying
 * a special object that can be found in a shipwreck to the
 * southwest.
 *
 * Khail - July 7/97
 */
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <language.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"
#include "npc.h"

#define A_BITE 0
#define A_LCLAW 1
#define A_RCLAW 2
#define A_TAIL 3

#define H_HEAD 0
#define H_BODY 1
#define H_TAIL 2
#define H_RARM 3
#define H_LARM 4
#define H_RLEG 5
#define H_LLEG 6
#define H_RWING 7
#define H_LWING 8

int animated;

void
create_creature()
{
    set_name("gargoyle");
    set_pname("gargoyles");
    add_name("citadel_gargoyle");
    set_race_name("gargoyle");
    set_short("gargoyle");
    set_pshort("gargoyles"); 
    set_long("@@gargoyle_long@@");

    set_stats(({ 180, 300, 200, 120, 120, 250 }));

    set_hp(query_max_hp());

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 100);

    set_attack_unarmed(A_BITE, 50, 90, W_IMPALE, 30, "jaws");
    set_attack_unarmed(A_LCLAW, 80, 80, W_SLASH, 30, "left claws");
    set_attack_unarmed(A_RCLAW, 80, 80, W_SLASH, 30, "right claws");
    set_attack_unarmed(A_TAIL, 75, 90, W_BLUDGEON, 10, "tail");

    set_hitloc_unarmed(H_HEAD, ({90, 80, 90, 100}), 10, "head");
    set_hitloc_unarmed(H_BODY, ({80, 70, 40, 100}), 50, "body");
    set_hitloc_unarmed(H_TAIL, ({80, 80, 80, 100}), 6, "tail");
    set_hitloc_unarmed(H_RARM, ({50, 50, 40, 100}), 10, "right arm");
    set_hitloc_unarmed(H_LARM, ({50, 50, 40, 100}), 10, "left arm");
    set_hitloc_unarmed(H_RLEG, ({60, 60, 50, 100}), 7, "right leg");
    set_hitloc_unarmed(H_LLEG, ({60, 60, 50, 100}), 7, "left leg");
    set_hitloc_unarmed(H_RWING, ({50, 50, 40, 100}), 10, "right wing");
    set_hitloc_unarmed(H_LWING, ({50, 50, 40, 100}), 10, "left wing");

    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);  
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(OBJ_I_RES_FIRE, 100);
    add_prop(OBJ_I_RES_POISON, 80);
    add_prop(OBJ_M_NO_ATTACK,"@@check_attack@@");

    set_appearance_offset(50);
    set_alignment(0);
}

mixed
check_attack()
{
    if (!animated)
        return "The gargoyle is only a statue, pointless to attack.\n";
    else
        return 0;
}

string
gargoyle_long()
{
    if (!animated)
        return "Large and grim, the gargoyle is a statue of " +
            "a brutal creature of legend, some of which would " +
            "willingly serve the masters of castles and " +
            "strongholds to help defend their homes.\n";
  else
        return "Large and grim, the gargoyle is a terror " +
            "straight out of legend. A beaked, reptilian " +
            "face sits atop muscular shoulders from which " +
            "sprout large batlike wings. Its hands and feet " +
            "end in massive claws that look as sharp as " +
            "any sword.\n";
}

void
animate_gargoyle()
{
    if(animated)
        return;

    animated = 1;

    tell_room(environment(),"Suddenly, the stone crumbles " +
        "from the gargoyle 'statue' and with a terrible roar " +
        "it awakens and stretchs to a fearsome height and " +
        "spreads its wings.\n");
}

void
unanimate_gargoyle()
{
    if(!animated)
        return;

    tell_room(environment(TO),"It's job done, the gargoyle " +
        "glares about one final time then spreads it's wings " +
        "and leaps back to its perch. As you watch, a stone " +
        "skin magically enshrouds it, and the gargoyle becomes " +
        "a statue once again.\n");

    animated = 0;
}

int
special_attack(object enemy)
{
    object me,
           weapon,
           *weparr,
           old_player;
    mixed *hitresult;
    string how,
           a,
           b;
    int attack_style;

    attack_style = random(100) + 1;

    if(attack_style <= 70)
        return 0;

    if(attack_style <= 90)    /*The 'leap' special*/
    {
        hitresult = enemy->hit_me(200 + random(50), W_IMPALE,
           TO, -1, A_BODY);

        how = "barely touches";
        if (hitresult[0] > 0)
            how = "dig deep into";
        else if (hitresult[0] > 10)
            how = "horribly rend";
        else if (hitresult[0] > 20)
            how = "viciously tear";
        else if (hitresult[0] > 30)
            how = "unspeakably mangle";

        tell_object(enemy, "The gargoyle suddenly leaps high " +
            "into the air, driving down upon you with both " +
            "claws and a horrifying snarl, which " + how + 
            " your body!\n");
        tell_room(environment(), "The gargoyle suddenly leaps " +
            "high into the air, driving down upon " + 
            QTNAME(enemy) + " with a horrifying snarl as " +
            "its claws " + how + " " + HIS_HER(enemy) + 
            " body!\n", ({enemy}));

        if(enemy->query_hp() <= 0)
            enemy->do_die(me);

        return 1;
    }

  /*Gargoyle tries to disarm*/
    if (!sizeof(weparr = enemy->query_weapon(-1)))
        return 1;

    if(enemy->query_stat(SS_DEX) > query_stat(SS_DEX))
    {
        tell_object(enemy, "The gargoyle dives past your " +
            "defences and slaps your weapon to one side. " +
            "Its tail whips around it, but you manage to " +
            "pull it free again just in time.\n");
        tell_room(environment(), "The gargoyle dives past " +
            QTNAME(enemy) + "'s defences and slaps " +
            HIS_HER(enemy) + " weapon to one side. " +
            "Its tail whips around it, but " + QTNAME(enemy) +
            " pulls it free just in time.\n", ({enemy}));
        return 1;
    }

    weapon = weparr[random(sizeof(weparr))];

    enemy->catch_msg("The gargoyle dives past your defences " +
        "and slaps your " + weapon->short() + " to one side. " +
        "Its tail whips around the weapon, and before you can react " +
        "the gargoyle pulls the " + weapon->short() + " from " +
        "your grasp and casts it into the brush!\n");
    tell_room(environment(), "The gargoyle dives past " +
        QTNAME(enemy) + "'s defences and slaps " + 
        HIS_HER(enemy) + " " + weapon->short() + " to one side. " +
        "Its tail whips around the weapon, and before " + 
        QTNAME(enemy) + " can react, the gargoyle pulls it " +
        "from " + HIS_HER(enemy) + " grasp, then casts it " +
        "into the brush!\n", ({enemy}));
    old_player = this_player();
    set_this_player(enemy);
    weapon->unwield_me();
    set_this_player(old_player);
    if (weapon->query_wielded() == enemy)
    {
        enemy->catch_msg("Strangely enough, the " + 
            weapon->short() + " reappears in your hand!\n");
        tell_room(environment(), "Strangely enough, the " +
            weapon->short() + " reappears in " + QTNAME(enemy) +
            "'s hand!\n", ({enemy}));
    }
    else
        weapon->remove_object();
    return 1;
}

int
second_life(object killer)
{
    tell_room(environment(),"With a roar of rage, full of pain " +
        "and anguish, the gargoyle dies. Before it's body hits " +
        "the ground, it reverts to solid stone, which shatters " +
        "into rubble when it hits the gound.\n");
    reset_euid();
    clone_object(OBJ + "garg_rubble")->move(environment(), 1);
    return 0;
}
