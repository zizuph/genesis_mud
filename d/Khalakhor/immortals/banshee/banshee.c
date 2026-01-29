#pragma strict_type

inherit "/std/monster";

#include <composite.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <const.h>
#include <composite.h>

#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/immortals/banshee/banshee.h"
#include "/d/Khalakhor/immortals/banshee/banshee_drain.c"
#include "/d/Khalakhor/immortals/banshee/banshee_wail.c"
#include "/d/Khalakhor/immortals/banshee/banshee_freeze.c"
   
public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id)
{
    object *temp;
    int i;

#ifdef UNDEAD_DEBUG
    tell_object(attacker, "WCPEN = " + wcpen + "\n");
#endif

    if (wcpen > MIN_PEN_TOHIT || dt == MAGIC_DT)
        return ::hit_me(wcpen, dt, attacker, attack_id);
    temp = attacker->query_weapon(-1);
    for (i = 0; i < sizeof(temp); i++)
    {
        if (temp[i]->query_attack_id() == attack_id)
        {
            if (temp[i]->query_prop(OBJ_I_IS_MAGIC_WEAPON))
                return ::hit_me(wcpen, dt, attacker, attack_id);
            else
            {
                tell_object(attacker, "Your " + temp[i]->query_name() +
                    " passes harmlessly through the " + short() +
                    "!\n");
                tell_room(environment(), QCTNAME(attacker) + "'s " +
                    temp[i]->query_name() + " passes harmlessly " +
                    "through the " + short() + "!\n", attacker);
                return ({0, 0, 0, 0});
            }
        }
    }
    tell_object(attacker, "Your " + 
        attacker->cr_attack_desc(attack_id) + " passes " +
        "harmlessly through the " + short() + "!\n");
    tell_room(environment(), QCTNAME(attacker) + "'s " +
        attacker->cr_attack_desc(attack_id) + " passes " +
        "harmlessly through the " + short() + "!\n", attacker);
    return ({0, 0, 0, 0});
}

public object
get_random_player()
{
    object *players,
           who;

    if (!environment(TO))
        return 0;

    players = all_inventory(environment(TO));
    players = FILTER_PLAYERS(players);
    players = filter(players, &not() @ &->query_wiz_level());
    players = FILTER_CAN_SEE(players, TO);

    if (!sizeof(players))
        return 0;

    who = players[random(sizeof(players))];

    return who;
}
    
public void
summon_player()
{
    object who = get_random_player();

    if (!who)
        return;

    if (who->query_gender() == G_FEMALE)
        command("emote whispers: " + who->query_met_name() + "...my sweet " +
            "princess...come to me.");
    else
        command("emote whispers: " + who->query_met_name() + "...my darling..." +
            "come join me in death.");
}

public void
soul_claim()
{
    object who = get_random_player();

    if (!who)
        return;

    command("emote wails: Your soul is mine, " +
        get_random_player()->query_met_name() + "!");
}

public void
create_monster()
{
    set_name(({"apparition","banshee","ghost","spirit"}));
    set_adj(({"glowing","transluscent"}));
    set_long("The apparition before you is that of a beautiful woman, " +
        "though her face distorted into a mask of pain and loathing. " +
        "Transluscent and pulsing with a sickly green glow, her tattered " +
        "robes flow about her as if on an unseen wind as she hovers above " +
        "the ground.\n");

  /* Set up stats, all stats to 300 */  
    default_config_npc(300);

  /* Set aggressive, npc will autoattack. */
    set_aggressive(0);

  /* Set up skills. */
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENSE, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_BLIND_COMBAT, 100);

    set_skill(SS_SPELLCRAFT, 100);
    set_skill(SS_FORM_ILLUSION, 100);
    set_skill(SS_FORM_CONJURATION, 100);
    set_skill(SS_ELEMENT_FIRE, 100);
    set_skill(SS_ELEMENT_LIFE, 100);
    set_skill(SS_ELEMENT_DEATH, 100);

  /* Set up props */
    add_prop(LIVE_I_UNDEAD, 100);    // A banshee's about as undead as it gets.
    add_prop(LIVE_I_NO_CORPSE, 1);   // No real body, no corpse.
    add_prop(LIVE_I_SEE_DARK, 100);  // Can see in dark.
    add_prop(LIVE_I_SEE_INVIS, 100); // Can see invis.
    add_prop(LIVE_I_NEVERKNOWN, 1);  // No players can ever know it's name.

    add_prop(OBJ_I_RES_POISON, 100); // No body, hardly susceptible to poison.
    add_prop(OBJ_I_RES_DEATH, 100);  // Already dead, death magic pointless.
    add_prop(OBJ_I_RES_MAGIC, 75);   // High natural resistance to all magic.
    add_prop(OBJ_I_RES_LIFE, 75);
    add_prop(OBJ_I_RES_FIRE, 75);
    add_prop(OBJ_I_RES_EARTH, 25);
    add_prop(OBJ_I_RES_COLD, 100);
    add_prop(OBJ_I_RES_ELECTRICITY, 100);

    add_prop(NPC_I_NO_RUN_AWAY, 1);  // Nothing will scare this thing off.
    add_prop(NPC_I_NO_FEAR, 1);      // No dis check to attack.
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_HEIGHT, 300);
  
  /* Some custom movement messages.
    set_m_in("shimmers into view with a horrifying wail!");
    set_mm_in("fades from view with a horrifying wail!");
    set_m_out("glides out of the room to the");
    set_mm_out("glides into the room with a deafening shriek!");

  /* A bit of work on it's appearance. */
    set_race_name("human");
    set_size_descs("extremely tall", "lean");
    set_race_name("apparition");
    set_gender(G_FEMALE);
    set_appearance_offset(50);     // Make it nasty looking
    set_alignment(-1200);

    set_aggressive(1);

    set_act_time(10);
    add_act("emote curls her thin lips back from pale teeth and smiles " +
        "at you with a cold, rictous expression.");
    add_act("emote stares at you, a cold flame burning within her " +
        "eyes.");
    add_act("emote beckons you towards her with a gentle motion " +
        "of her hands.");
    add_act("@@summon_player@@");
    add_act("emote throws her head back and utters a laugh that " +
        "reminds you of bones rattling in an overturned coffin.");
    add_act("emote raises her hands above her head, and her robes " +
        "flutter about her on an unseen wind with renewed vigour.");

    set_cact_time(5);
    add_cact("emote howls in rage.");
    add_cact("emote seems to grow in size, her eyes burning with a " +
        "sickly green flame.");
    add_cact("@@soul_claim@@");

}

public int
special_attack(object enemy)
{
    int attack = random(10);

    if (attack < 6)
        return 0;

    if (attack == 6)
        wail();
    else if (attack == 7)
        freeze(enemy);
    else if (attack == 8)
        drain(enemy);
    else if (attack == 9)
        wail();

    return 1;
}

/*
 * Function name: add_stun
 * Description  : Masked so the banshee can't be stunned.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
add_stun()
{
    return 0;
}

/*
 * Function name: add_prop
 * Description  : Masked to intercept direct prop setting stun
 *                attempts.
 * Arguments    : prop - Property to be set.
 *                val  - Value to set the property to.
 * Returns      : n/a
 */
public void
add_prop(string prop, mixed val)
{
    if (prop == LIVE_I_STUNNED)
        return 0;

    ::add_prop(prop, val);
}

public void
attack_object(object who)
{
    who->catch_tell(query_The_name(who) + " emits a piercing howl and lunges " +
        "towards you!\n");
    tell_room(environment(TO), QCTNAME(TO) + " emits a piercing howl and " +
        "lunges towards " + QTNAME(who) + "!\n", ({who, TO}));
    ::attack_object(who);
}

public void
notify_you_killed_me(object who)
{
    who->catch_tell("The last sound you hear is the sound of the banshee's " +
        "wail as darkness consumes you!\n");
    tell_room(environment(TO), QCTNAME(TO) + " throws back her head and " +
        "wails in triumph over " + QTNAME(who) + "'s corpse!\n", ({TO,who}));
    log_file(BANSHEE_DEATH, "Banshee killed " + who->query_name() + 
        " on " + ctime(time()) + ". Statave: " + who->query_average_stat() +
        ".\n");
}

public int
second_life(object killer)
{
    string *killers = (killer->query_team_others())->query_name();

    log_file(BANSHEE_DEATH, "Banshee slain by " + killer->query_name() + 
        " on " + ctime(time()) + " together with " +
        COMPOSITE_WORDS(killers) + "!\n");

    return 0;
}
