/* 
 * Mortis 09.2014
 *
 * Lieutenant of the Tower of Arms, the Constabulary of Palanthas.
 *
 * If players can become Constable, these will change
 * to match their guild, but this is the default guard.
 *
 * I can see this guy as a quest. You attack him. He keeps fleeing, but he
 * tells you where he's going, "I gotta flee and get some tailored gloves!"
 * Locs are random. To get him, you have to track him down throughout the city
 * which involves familiarizing yourself with it.
 *
 */

#pragma strict_types

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>
#include "../../../local.h"

#define MY_CLOTHING       NOBLE + "arms/parmour"
#define MY_ARMOUR         MERCH + "arms/larmour"
#define MY_GENERAL        MERCH + "obj/lgeneral"

inherit TOA_GUARD;
inherit "/lib/unique";

int whimpy_times;

/*prototype*/
void arm_me();
void arm_me2();

void
create_toa_guard()
{
    seteuid(getuid(TO));

    set_name("skote");
    add_name(({"guard", "officer"}));
    add_adj(({"broad", "pauldroned", "broad-pauldroned"}));
    set_title("the Lieutenant of the Constabulary of Palanthas");
    set_introduce(1);

    set_short("broad-pauldroned officer");
    set_long("A young, platinum-blond haired officer of the city of "
    + "Palanthas sworn to uphold the laws and treat the citizenry with "
    + "respect. The officer's open white tunic bears " + "@@constable_symbol@@"
    + " above its left breast, and his pauldrons are broad with one yellow "
    + "chevron.\n");
    set_race_name("human");
    
    set_skill(SS_DEFENCE,      85);
    set_skill(SS_PARRY,        75);
    set_skill(SS_UNARM_COMBAT, 75);
    set_skill(SS_AWARENESS,    35);
    set_skill(SS_WEP_SWORD,    85);
    set_skill(SS_WEP_CLUB,     75);
    set_skill(SS_WEP_POLEARM,  80);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_HIDE,         30);

    set_stats((({150, 140, 130, 130, 130, 190})), 5);
    set_all_attack_unarmed(25, 10);
    set_all_hitloc_unarmed(20);

    set_whimpy(59);

    set_alignment(800);
    set_knight_prestige(-300);

    set_default_answer("asay confid I'm a Lieutenant in the Constabulary, but "
    + "I don't know everything. I have business to which to attend.");

    add_ask(({"lt", "lieutenant"}), "asay proud I'm no noble or anyone "
    + "important, but I do have an important role to play as a Lieutenant, "
    + "and I take that seriously. I will never abandon my post!", 1);

    set_alarm(1.0, 0.0, &arm_me());
    set_alarm(2.0, 0.0, &arm_me2());
}

void
arm_me()
{
    object ghead, gpauldrons, psword, tkey;

    // Guard's custom headware.
    ghead = clone_object(MY_ARMOUR);
    ghead->set_armour_data("glistening" + "&&"
                            + "grey" + "&&"
                            + "studded" + "&&"
                            + "helmet");
    ghead->move(TO);

    // Guard's custom pauldrons.
    gpauldrons = clone_object(MY_ARMOUR);
    gpauldrons->set_armour_data("glistening" + "&&"
                            + "grey" + "&&"
                            + "studded" + "&&"
                            + "pauldrons");
    gpauldrons->move(TO);

    // Guard's standard issue boots.
    clone_object(OBJ + "garmour_boots")->move(TO);

    // Guard's standard issue gloves.
    clone_object(OBJ + "garmour_gloves")->move(TO);

    // Guard's standard issue belt.
    clone_object(OBJ + "garmour_belt")->move(TO);

    // Guard's standard issue vest.
    clone_object(OBJ + "garmour_vest")->move(TO);

    // Guard's standard issue overcoat.
    clone_object(OBJ + "garmour_overcoat")->move(TO);

    // Lieutenant's magic greaves.
    clone_unique(TOA + "arms/toa_lieutenant_greaves", 3,
        OBJ + "garmour_greaves", 1, 100, 1)->move(TO);

    // Lieutenant's personally ordered sword/polearm/club.
    string ltwep = one_of_list(({"sabre", "partisan", "maul"}));
    if (ltwep == "sabre")
    {
        psword = clone_object(MERCH + "arms/smith_sword");
    }
    else if (ltwep == "partisan")
    {
        psword = clone_object(MERCH + "arms/smith_polearm");
    }
    else
    {
        psword = clone_object(MERCH + "arms/smith_club");
    }
        
    psword->set_weapon_data("shining" + "&&" + "shining" + "&&" + ltwep);
    psword->move(TO);

    // Guard's standard issue payment.
    MONEY_MAKE_GC(24 + random(27))->move(TO);

    // Routine to make sure door is closed and locked on reset.
    tkey = clone_object(TOA + "doors/toa_lieutenant_key");
    tkey->move(TO);
    
    command("close door");
    command("lock door with key");
}

void
arm_me2()
{
    command("wield all");
    command("wear all");
    command("unkeep all");
    command("keep greaves");
    set_gender(G_MALE);
}

public void run_away()
{
    if (whimpy_times == 0)
    {
        // Run to the northwest guard chamber for protection.
        command("emote reaches frantically into his pants and extracts "
        + "something small.");
        command("emote runs to the door to his chambers, unlocks it, throws "
        + "it open, and flees!");
        TO->move(TOA + "toa02");
        command("scream");
        command("n"); command("sw");
        set_whimpy(49);
    }
    else if (whimpy_times == 1)
    {
        // Run to Leiden's garden to hide.
        command("shout Sweet baby Paladine save me!");
        command("ne");
        command("shout Save me, baby Paladine!");
        command("s"); command("w"); command("w");
        command("sw"); command("s"); command("alley ne");
        command("hide");
        set_whimpy(0);
    }

    whimpy_times++;
//    ::run_away();
}

int
special_attack(object enemy)
{
    int pen, att, wloc, weptype, damtype;
    string hitloc, attack, how, how2, weapon;
    mixed hitres;
    object *wep = query_weapon(-1);

    if (!sizeof(wep))
    return 0;

    weapon = wep[0]->query_short();
    weptype = wep[0]->query_wt();

    switch (weptype)
    {
        case W_POLEARM:
            attack = "catch";
            damtype = W_IMPALE;
            hitloc = "body";
            wloc = A_TORSO;
            break;
        case W_SWORD:
            attack = "pierce";
            damtype = W_SLASH;
            hitloc = "body";
            wloc = A_TORSO;
            break;
        case W_CLUB:
            attack = "clobber";
            damtype = W_BLUDGEON;
            hitloc = "head";
            wloc = A_HEAD;
            break;
        default:
            attack = "strike";
            damtype = W_SLASH;
            hitloc = "legs";
            wloc = A_LEGS;
            break;
    }

    if (random(5) == 1)
    {
        pen = 325 + random(76);
        hitres = enemy->hit_me(pen, damtype, TO, -1, wloc);

        if (hitres[0] <= 0)
        {
            how = "but misses";
            how2 = how;
        }
        if(hitres[0] > 0)
        {
            how = "barely landing";
            how2 = how;
        }
        if(hitres[0] > 10)
        {
            how = "incapacitating you slightly";
            how2 = "incapacitating " + HIM(enemy) + " slightly";
        }
        if(hitres[0] > 20)
        {
            how = "incapacitating you greatly";
            how2 = "incapacitating " + HIM(enemy) + " greatly";
        }
        if (hitres[0] > 40)
        {
            how = "with well-trained power";
            how2 = how;
        }
        if (hitres[0] > 60)
        {
            how = "with deadening force";
            how2 = how;
        }

        enemy->catch_msg(QCTNAME(TO) + " attempts to " + attack + " your "
        + hitloc + " with " + HIS(TO) + " " + weapon + " " + how + ".\n");

        tell_room(E(TO), QCTNAME(TO) + " attempts to " + attack + " "
        + QTNAME(enemy) + "'s " + hitloc + " with " + HIS(TO) + " " + weapon
        + " " + how2 + ".\n", ({enemy, TO}));

        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(TO);
        }

        return 1;
    }

    return 0;
}
