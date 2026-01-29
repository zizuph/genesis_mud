/*
 *  /d/Gondor/anorien/druedain/amon-din/npc/din_guard.c
 *
 *  This is the attendant of the Beacon Hill. He is a toughy.
 *
 *  July 1995 by Gorboth
 */

inherit "/std/monster";
inherit "/d/Gondor/common/lib/friend_or_foe.c";

#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

#include "/d/Gondor/defs.h"

#define FALLROOM	AMON_DIR + "fallroom1"

/*
 *  Prototypes
 */
varargs mixed counterweight(object victim);
varargs mixed skewer(object victim);

void
create_monster()
{
    set_name("attendant");
    set_pname(({"men","dunedain","attendants"}));
    set_pshort("attendants");
    add_name(({"man", "soldier", "dunadan"}));
    add_adj(({"aged", "black-haired"}));
    set_short("beacon attendant");
    set_race_name("human");
    set_long(BSN(
        "Proud and stalwart, this aged Dunadan looks to be one who"
      + " has seen both the fields of battle and the courts of"
      + " nobility. His countenance is that of grim determination"
      + " and fierce loyalty. This is most certainly a capable member"
      + " of the Steward's Army."));
    set_alignment(300+10*random(24));
    default_config_npc(random(20)+115);
    set_base_stat(SS_DIS,random(10)+100);
    set_base_stat(SS_WIS, random(10)+80);
    set_base_stat(SS_DEX,random(10)+144);
    set_skill(SS_BLIND_COMBAT, random(7) + 20);
    set_skill(SS_WEP_POLEARM, random(15)+90);
    if (TO->query_skill(SS_WEP_POLEARM) > 100)
    {
        set_skill(SS_WEP_POLEARM, 100);
    }
    set_skill(SS_AWARENESS, 70 + random(20));
    set_skill(SS_PARRY, 95);
    set_skill(SS_DEFENCE, 95);
    
    set_chat_time(25 + random(15));
    add_chat("Fuel has run low, and deliveries are late once again.");
    add_chat("How can the Steward expect a signal, if there is no fuel?");
    add_chat("I grow weary of this hilltop!");

    set_cchat_time(5 + random(10));
    add_cchat("Louse! Your foul errand stops now!");
    add_cchat("Enough of this foolishness! Leave or be slain!");
    add_cchat("As long as I stand, you shall not touch the woodstores!");

    set_act_time(15 + random(15));
    add_act("peer .");
    add_act("grumble");
    add_act("frown");

    set_cact_time(3 + random(2));
    add_cact("shout The tower is set upon by the enemy! To arms!");
}

void
arm_me()
{
    object  wep, arm;
    FIX_EUID
    clone_object(AMON_DIR + "wep/long_hal")->move(TO);
    command("wield all");
    clone_object(AMON_DIR + "arm/silverplate")->move(TO);
    clone_object(AMON_DIR + "arm/schain_gloves")->move(TO);
    clone_object(AMON_DIR + "arm/schain_leggings")->move(TO);
    clone_object(ARM_DIR + "winghelm")->move(TO);
    clone_object(AMON_DIR + "arm/white_cape")->move(TO);
    command("wear all");
}

// Dont forget about Solamnian prestige!

void
init_attack()
{
    object  victim;

    if (objectp(query_attack()))
        return;

    if ((victim = TP)->query_npc())
        return;

    if (query_friend_or_foe(victim) > -1 || !CAN_SEE_IN_ROOM(TO) ||
        !CAN_SEE(TO, victim))
        return;

    set_alarm(2.0, 0.0, "do_attack", victim);
}

void
do_attack(object victim)
{
    command("kill "+victim->query_real_name());
}

int
special_attack(object enemy)
{
    int     attack_type = random(20);

    if (!sizeof(query_weapon(-1)))
    {
        if (!query_skill(SS_UNARM_COMBAT))
        {
            set_skill(SS_UNARM_COMBAT, 80 + random(15));
            return 0;
        }
        return 0;
    }

    if (query_skill(SS_UNARM_COMBAT))
    {
        remove_skill(SS_UNARM_COMBAT);
    }

// *** The above lines regarding skills are to prevent a disarming
//     tactic by an enemy from rendering the attendant helpless, but
//     to also guarantee that he is not hindered by an unnecessary
//     unarmed combat reduction in the way he handles his halberd if
//     it is wielded.

    if (attack_type > 16)
    {
        enemy->catch_msg("The " +TO->query_short()+ " reverses his"
          + " grip on the long-shafted steel halberd and"
          + " swings its heavy counterweight directly at you!\n");
        tell_room(environment(TO), "The " +TO->query_short() 
          + " reverses his grip on the long-shafted steel halberd"
          + " and swings its heavy counterweight at " +QTNAME(enemy)
          + "!\n", enemy);

        set_alarm(0.0, 0.0, &counterweight(enemy));
        return 1;
    }

    if (attack_type < 3)
    {
        set_alarm(0.0, 0.0, &skewer(enemy));
        return 1;
    }

    return 0;
}

varargs int
counterweight(object victim)
{
    object *enemies = FILTER_PRESENT_LIVE(query_enemy(-1));
    mixed  *ouch;
    int     wloc;
    string *hitloc;

    hitloc = ({ "right leg", "left leg", "body", "head", "right arm",
                "left arm" });

    if (!objectp(victim) && !sizeof(enemies))
        return 1;

    if (!objectp(victim))
    {
        victim = enemies[random(sizeof(enemies))];
    }

    if (ENV(victim) != ENV(TO))
    {
        return 1;
    }

    ouch = victim->hit_me(F_PENMOD(50, 100), W_BLUDGEON, TO, -1);
    wloc = random(6);

    if (ouch[0] < 0)
    {
    victim->catch_msg("The heavy counterweight passes dangerously"
          + " close as you manage to twist out of its path.\n");
        say(QCTNAME(victim) + " barely manages to twist out of the path"
          + " of the heavy counterweight.\n", victim);
    }

    else if (ouch[0] < 5)
    {
        victim->catch_msg("The heavy counterweight slams into your "
          + hitloc[wloc] + ", knocking you aside!\n");
        say(QCTNAME(victim) + " is sent reeling as the heavy"
          + " counterweight slams into " +victim->query_possessive()+" "
          + hitloc[wloc] + "!\n", victim);
    }

    else if (ouch[0] < 100)
    {
        victim->catch_msg("The heavy counterweight slams into you with"
          + " incredible force, sending you flying down the slope of"
          + " the hilltop!\n");
        say("The heavy counterweight slams into " + QTNAME(victim)
          + ", sending " +victim->query_objective()+ " tumbling down the"
          + " side of the hilltop!\n", victim);
        victim->move_living("M", FALLROOM, 1, 0);
    }

    else
    {
        victim->catch_msg("Before you can react, the heavy counterweight"
          + " makes full contact with the side of your head. The last"
          + " thing you remember are strong arms casting you down the"
          + " side of Amon Din.\n");
        say("The heavy counterweight makes perfect contact with the"
          + " side of " + QTNAME(victim) + "'s head, who falls limply"
          + " to the ground. The beacon attendant quickly grabs"
          +victim->query_possessive()+" body, and throws it down the side"
          + " of the hilltop!\n", victim);

        victim->move_living("M", FALLROOM, 1, 0);
    }

    return 1;
}

varargs int
skewer(object victim)
{
    object *enemies = FILTER_PRESENT_LIVE(query_enemy(-1));
    mixed  *sdam;
    int     wloc = random(5);
    string *hitloc;

    hitloc = ({ "neck", "right shoulder", "left shoulder",
                "right thigh", "left thigh", "abdomen" });

    if (!objectp(victim) && !sizeof(enemies))
        return 1;

    if (!objectp(victim))
    {
        victim = enemies[random(sizeof(enemies))];
    }

    if (ENV(victim) != ENV(TO))
    {
        return 1;
    }

    sdam = victim->hit_me(F_PENMOD(60, 100), W_IMPALE, TO, -1);

    switch(sdam[0])
    {
        case 0:
            victim->catch_msg("The beacon attendant makes a sudden"
              + " lunge at you with his long-shafted steel halberd,"
              + " but you manage to leap aside!\n");
            say("The beacon attendant makes a sudden lunge for "
              + QTNAME(victim) + " with his long-shafted steel halberd,"
              + " but misses " + victim->query_objective() + " by"
              + " inches!\n", victim);
            break;
        case 1..5:
            victim->catch_msg("The beacon attendant makes a sudden"
              + " lunge at you with his long-shafted steel halberd,"
              + " nicking a small groove in your " + hitloc[wloc]
              + "!\n");
            say("The beacon attendant makes a sudden lunge at "
              + QTNAME(victim) + " with his long-shafted steel halberd,"
              + " nicking a small groove in " +victim->query_possessive()
              + " " + hitloc[wloc] + "!\n", victim);
            break;
        case 6..20:
            victim->catch_msg("The beacon attendant makes a sudden"
              + " lunge at you with his long-shafted steel halberd,"
              + " slicing a long cut in your " + hitloc[wloc] + "!\n");
            say("The beacon attendant makes a sudden lunge at "
              + QTNAME(victim) + " with his long-shafted steel halberd,"
              + " slicing a long cut in " + victim->query_possessive()
              + " " + hitloc[wloc] + "!\n", victim);
            break;
        case 21..50:
            victim->catch_msg("The beacon attendant makes a sudden"
              + " lunge at you with his long-shafted steel halberd,"
              + " cutting a deep wound in your " + hitloc[wloc] + "!\n");
            say("The beacon attendant makes a sudden lunge at "
              + QTNAME(victim) + " with his long-shafted steel halberd,"
              + " cutting a deep wound in " + victim->query_possessive()
              + " " + hitloc[wloc] + "!\n", victim);
            break;
        case 51..99:
            victim->catch_msg("The beacon attendant makes a sudden"
              + " lunge at you with his long-shafted steel halberd,"
              + " cutting so deeply into your " + hitloc[wloc]
              + " that he strikes the bone!\n");
            say("The beacon attendant makes a sudden lunge at "
              + QTNAME(victim) + " with his long-shafted steel halberd,"
              + " cutting so deeply into " + victim->query_possessive()
              + " " + hitloc[wloc] + " that he strikes the bone!\n",
                victim);
            break;
        default:
            victim->catch_msg("The beacon attendant makes a sudden"
              + " lunge at you with his long-shafted steel halberd,"
              + " punching through your intestines with the blade and"
              + " skewering you on the shaft of the weapon!\n");
            say("The beacon attendant makes a sudden lunge at "
              + QTNAME(victim) + " with his long-shafted steel halberd,"
              + " ramming the blade through " + victim->query_possessive()
              + " abdomen and skewering " + victim->query_objective()
              + " on the shaft of the weapon!\n", victim);
            break;
    }

    if (victim->query_hp() == 0)
    {
        victim->do_die(TO);
    }

    return 1;
}
