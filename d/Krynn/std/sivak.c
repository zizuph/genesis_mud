/* Original by ?
 * 
 * Updated 000912 by Stralle @ Genesis: Changed the formula in their
 *                                      special attack.
 */

#pragma save_binary
#pragma strict_types

#include "/d/Krynn/common/defs.h"
#include "draconian.h"
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

inherit DRACONIAN;

/*
 * Function name: set_sivak_skills
 * Description:   Calc and set the stats and skills for the draconian.
 */
nomask static void
set_sivak_skills()
{
    int i, level;

    for (i = 0; i < 6; i++) /* 70 - 126 */
        set_base_stat(i, (random(6) + 4) * 10 + 30 + random(7));

    level = query_draconian_level();

    set_skill(SS_2H_COMBAT,   80 + random(21));
    set_skill(SS_DEFENCE,     level * 6 + random(20) + 20);
    set_skill(SS_PARRY,       level * 6 + random(8) + 20);
    set_skill(SS_WEP_SWORD,   level * 6 + random(8) + 20);
    set_skill(SS_WEP_KNIFE,   level * 6 + random(8) + 20);
    set_skill(SS_WEP_CLUB,    level * 6 + random(8) + 20);
    set_skill(SS_WEP_POLEARM, level * 6 + random(8) + 20);
    set_skill(SS_WEP_JAVELIN, level * 6 + random(8) + 20);
    set_skill(SS_WEP_AXE,     level * 6 + random(8) + 20);
    set_skill(SS_AWARENESS,   level * 5);

    set_draconian_alignment();
}

/*
 * Function name: create_sivak
 * Description:
 */
public void
create_sivak()
{
}

/*
 * Function name: create_draconian
 * Description:
 */
nomask public void
create_draconian()
{
    int i;

    set_sivak_skills();
    set_draconian_type(SIVAK);
    set_smart_fighting();

    create_sivak();

    if (!query_long())
        set_default_long();

    set_name("sivak");

    set_exp_factor(130);
    add_prop(OBJ_I_RES_FIRE, 100);
    add_prop(OBJ_I_RES_ACID, 80);    

    /*
	add_act("emote flaps its wings, making some dust swirl around.");
    */
}

/*
 * Function name: special_draconian_attack
 * Description:   Called from the draconian special_attack
 *                routine. By redefining this, draconians can easily attack
 *                with spells or take special actions when engaged
 *                in combat.
 * Arguments:     victim (the one we are fighting right now)
 * Returns:       0 - if we want the round to continue
 *                1 - if we are done with this round
 */
public int
special_draconian_attack(object victim)
{
    object *wep;
    string how, ohow;
    mixed *hit_result;
/*    mixed tmp; */

    tell_room(E(TO), QCTNAME(TO) + " starts to flap its wings and stirs" +
        " the dust around you.\n");

    /* Stralle @ Genesis: The original used random(15) + 15 as
     * pen value. Can that be anything other than redicilous?
     */
    hit_result = victim->hit_me(F_PENMOD(((TO->query_stat(SS_STR) /
        query_draconian_level()) * (2 + random(4))),
        query_draconian_level() * 5 + random(10)), W_IMPALE, TO, -1);

    switch (hit_result[0])
    {
        case 70..100:
            how = "you can feel claws digging deep into your flesh";
            ohow = "claws digs deeply into " +
                victim->query_possessive() + " flesh";
            break;
        case 40..69:
            how = "scratching you badly";
            ohow = "scratches " + victim->query_objective() + " badly";
            break;
        case 20..39:
            how = "scratching you";
            ohow = "scratches " + victim->query_objective();
            break;
        default:
            how = "grazing you";
            ohow = "grazes " + victim->query_objective();
            break;
    }
            
    victim->catch_msg("Before you are able to react, " + QTNAME(TO) +
        " is behind you and hits you in the back. You can feel claws " +
        how + ".\n");
    tell_room(E(TO), "Before " + QTNAME(victim) + " is able to react " +
        QTNAME(TO) + " has flown past " + victim->query_objective() +
        " and hits " + victim->query_objective() + " in the back " +
        "where claws " + ohow + ".\n", victim);

    /*    wep = query_weapon(-1);

	if (pointerp(wep))
        tmp = victim->hit_me(wep[0]->query_pen(), wep[0]->query_dt(), TO, -1);
    */

    return 1;
}

/*
 * Function name: second_life
 * Description:
 * Arguments:     killer - 
 * Returns:
 */
public int
second_life(object killer)
{
    object corpse, *team;

    if (living(killer))
    {
        team = killer->query_team_others();
        tell_room(E(TO),"The draconian bursts into flames!\n");

        corpse = clone_object(FLAMES);
        corpse->set_my_victims(({killer}) + team);
        corpse->move(E(TO));
    }
}

/*
 * Function name:
 * Description:
 * Arguments:
 * Returns:
 */
