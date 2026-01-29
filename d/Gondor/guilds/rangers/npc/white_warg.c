/* /d/Gondor/guilds/rangers/npc/white_warg.c
 * This is the white warg monster that
 * must be killed by one full ranger + apprentice
 * for the apprentice to complete the warrior task
 * --Tigerlily, Nov. 5, 2004
 * --           Dec. 28, 2004
 *
 *   Removed an old runtime error (Toby, 2006-12-05):
 *        if (num_weap >= 0 ) in line 200 is now:
 *        if (num_weap >= 0 && victim->query_weapon())
 *
 *   Changed stat config, it was insane before (Toby, 2007-02-11):
 *        old: set_stats(({ 200, 275, 300, 130, 100, 160 }))
 *        new: set_stats(({ 150, 200, 225, 130, 100, 200 }))
 */
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/trigaction";
inherit "/std/act/domove";
inherit "/std/act/attack";

#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <language.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"
#define RANGER_I_RECOGNIZE_BRAWL "_ranger_i_recognizing_brawl"

#define A_BITE 0
#define A_SLAM 1
#define A_CLAW 2
#define A_LPAW 3
#define A_RPAW 4

#define H_HEAD  0
#define H_BODY  1
#define H_LEGS  2
#define H_BELLY 3
#define H_REYE  4
#define H_LEYE  5

#define VICTIM_SKILLS   ({ TS_DEX, SKILL_AVG, SS_DEFENCE, SS_ANI_HANDL, SKILL_END })
#define WARG_SKILLS     ({ TS_DEX, SS_UNARM_COMBAT, SS_SPELLCRAFT  })


int     frq = 18;
string  poison_file = (RANGERS_OBJ + "poisons/warg_poison.c");

void
create_creature() 
{
    set_name("warg");
    set_pname("wargs");
    set_adj(({"great", "white"}));
    set_short("great white warg");
    set_pshort("great white wargs");
    set_race_name("warg"); 
    set_long("This is one of the most evil creatures " +
        "among the servants of Sauron. He looks like " +
        "a massive wolf, yet much larger with enormous " +
        "jaws, eerie red eyes, and long sharp bloody fangs.\n");
    set_gender(G_MALE);
    set_alignment(-800); 
    add_prop(CONT_I_WEIGHT,100000);
    add_prop(CONT_I_HEIGHT,300);
    add_prop(CONT_I_VOLUME,80000);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_leftover(RANGERS_OBJ + "warg_fang", "fang", 1, 0, 1, 0);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_I_SEE_DARK, 4);
    //crazy critter
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(LIVE_I_QUICKNESS, 15);
    add_prop(RANGER_I_RECOGNIZE_BRAWL, 45);

    set_stats(({ 150, 200, 225, 130, 100, 200 }));
    set_aggressive(1);
    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_SPELLCRAFT, 70);


    set_attack_unarmed( A_CLAW, 30, 45, W_IMPALE,    30, "claws");
    set_attack_unarmed( A_LPAW, 45, 35, W_BLUDGEON,  15, "left paw");
    set_attack_unarmed( A_RPAW, 55, 40, W_BLUDGEON,  15, "right paw");
    set_attack_unarmed( A_BITE, 60, 35, W_IMPALE,    30, "fangs");
    set_attack_unarmed( A_SLAM, 55, 35, W_BLUDGEON,  10, "massive head");

    set_hitloc_unarmed( H_HEAD,  ({ 10, 15, 1}), 25, "head");
    set_hitloc_unarmed( H_BODY,  ({ 30, 25, 1}), 20, "body");
    set_hitloc_unarmed( H_LEGS,  ({ 15, 15, 1}), 15, "legs");
    set_hitloc_unarmed( H_BELLY, ({ 25, 15, 1}), 20, "belly");
    set_hitloc_unarmed( H_REYE, ({ 25, 15, 1}), 10, "right eye");
    set_hitloc_unarmed( H_LEYE, ({ 25, 15, 1}), 10, "left eye");

    set_hp(query_max_hp());
    set_act_time(5);
    set_cact_time(5);
    add_cact("pace");
    add_cact("emote peers at you evilly with his blood-red eyes.");
    add_act("emote bares his yellow fangs at you threateningly.");
    add_act("emote throws his head back and howls!"); 
    add_cact("emote leaps over your head and appears behind you!");
    add_cact("emote growls menacingly as his blood-red eyes " +
        "begin to glow with pure evil.");
    add_cact("emote tries to enter an opening in the north wall but " +
        "is too large for the hole!");
    add_act("emote tries to enter an opening in the north wall but " +
        "is too large for the hole!");
}


varargs string
poison_eyes(object victim)
{
    object  spell;

    if (!objectp(victim))
        victim = TO->query_attack();

    if (!objectp(victim))
        return "";

    if (ENV(TO) != ENV(victim)) 
        return "";

    victim->catch_msg("The great white warg casts a spell upon you " +
        "with his evil blood-red eyes!\n");
    tell_room(ENV(TO), "The great white warg " +
        "casts a spell upon "+QTNAME(victim)
        + " with " + "his evil blood-red eyes!\n" , victim);
    seteuid(getuid(TO));
    spell = clone_object(poison_file);
    spell->move(victim);
    spell->start_poison();
    return "";
}

int
special_attack(object victim)
{
    int rand;
    object weap;
    int num_weap;

    // Regular unarmed attack (100-frq)% of the time
    if (random(100) >= frq)
    {
        // switch to smaller player periodically
        if (sizeof(victim->query_team_others()) && random(18) == 17)
        {
            if (victim->query_average_stat() >
                victim->query_team_others()[0]->query_average_stat())
            {
                // switch to smaller player
                victim->query_team_others()[0]->catch_msg("The great white " +
                    "warg suddenly turns to lunge savagely at your throat!\n");
                tell_room(ENV(TO), "The great white warg suddenly turns " +
                    "to lunge savagely at the the throat of " +
                    QTNAME(victim->query_team_others()[0]) + "!\n", 
                    victim->query_team_others()[0] );
                command("kill " + victim->query_team_others()[0]->query_real_name());
            }
        }
            return 0;
    }

    //Special attacks possibilities
    rand = random(12);
    switch(rand)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            //he can cast a spell to heal himself during one round
            if (query_hp() < (query_max_hp()*2/3))
            {
                tell_room(ENV(TO), "The great white warg's " +
                    "eyes glow bright red as he casts a spell " +
                    "to heal himself!\n");
                TO->heal_hp((query_max_hp() - query_hp())/3 + random(300));
                return 1;
            }
            else
            {
                tell_room(ENV(TO), "The great white warg's " + 
                    "eyes glow bright red as he tries to cast " +
                    "a spell!\n");
                return 1;
            }
            break;
        case 4:
        case 5:
            // or he can hit weapons
            //choose one of wielded weapons
            num_weap = random(sizeof(victim->query_weapon(-1)));
            if (num_weap >= 0 && victim->query_weapon())
            {
               weap = victim->query_weapon(-1)[num_weap];
            }
            // if player is unarmed, can get a bit hurt
            if (!objectp(weap))
            {
                victim->catch_msg("The great white warg " + 
                    "swats at you with his massive " +
                    "paw! You are hurt!\n");
                tell_room(ENV(TO), "The great white warg " + 
                    "angrily swats at " + QTNAME(victim) + 
                    " with his massive paw!\n", victim);
                victim->heal_hp(-50);
                return 1;
            }
          // else
            if (victim->resolve_task(
               TASK_ROUTINE, VICTIM_SKILLS, TO, WARG_SKILLS) > 0)
            {
                if (objectp(weap))
                {
                victim->catch_msg("The great white warg swats at " + 
                   LANG_THESHORT(weap) + " with his massive paw " +
                   "trying to force you to drop it!\n");
                tell_room(ENV(TO), "The great white warg " + 
                    "angrily swats at " + LANG_THESHORT(weap) + 
                    " with his massive paw, trying to get " + 
                    QTNAME(victim) + " to drop it!\n", victim);
                command("emote howls in pain and shakes his paw!");
                return 1;
                }
            }
            // else
            victim->catch_msg("The great white warg swats at " + 
                LANG_THESHORT(weap) + " with his massive paw " +
                "forcing you to drop it!\n");
            tell_room(ENV(TO), "The great white warg "+
                "angrily swats at " + QTNAME(victim) + " with his " +
                "massive paw, forcing " + victim->query_objective() +
                " to drop " + LANG_THESHORT(weap) + "!\n", victim);
            victim->command("$drop " + weap->query_name());
            return 1;
            break;
        case 6:
        case 7:
            // or he can maul the victim
            if (victim->resolve_task(
                TASK_ROUTINE, VICTIM_SKILLS, TO, WARG_SKILLS) > 0)
            {
                write("The great white warg " +
                    "suddenly leaps at your " +
                    "throat with his jaws snapping!\n " +
                    "He barely misses you!\n");
                tell_room(ENV(TO), "The great white warg " + 
                    "suddenly leaps at " +
                    "the throat of " + QTNAME(victim) + " with snapping " +
                    "jaws!\n", ({TO, victim }));
                return 1;
            }
            write("The great white warg " + 
               "suddenly leaps at your " +
               "throat!\nYou stagger back as he rips savagely " +
               "at you!\n");
            tell_room(ENV(TO), "The great white warg " + 
                "suddenly leaps at the throat of " + 
                QTNAME(victim) + "!\n" + QCTNAME(victim) + 
                " staggers back, clutching " + POSSESSIVE(victim) +
                " throat!\n", ({TO, victim }));
            TO->heal_hp((query_max_hp() - query_hp())/-8);
            return 1;
            break;
        default:
            //else he can 'cast a spell' to poison victim
            // can the victim evade the deadly eye spell?
            if (victim->resolve_task(
                TASK_ROUTINE, VICTIM_SKILLS, TO, WARG_SKILLS) > 0)
            {
                if (ENV(TO) == ENV(victim))
                {
                    write("The great white warg tries to place a " +
                        "spell on you with his evil blood-red eyes, but " +
                        "fails.\n");
                    tell_room(ENV(TO), "The great white warg " +
                        "tries to cast a spell " +
                        "on " + QTNAME(victim) + " with his evil blood-red " +
                        "eyes, but fails.\n", ({ TO, victim }) );
                }
            }
            else
                poison_eyes(victim);
            return 1;
            break;
        }
    return 1;
}

void
set_poison_file(string p)
{
    if (strlen(p) && ((file_size(p + ".c") > 0) || (file_size(p) > 0)))
        poison_file = p;
}

string
query_poison_file()
{
   return poison_file;
}
void
do_die(object killer)
{
    string team_name;

    if (sizeof(killer->query_team_others()))
    {
        team_name = lower_case(
            killer->query_team_others()[0]->query_real_name());
        killer->add_prop(WARG_S_TEAM, team_name);
        killer->query_team_others()[0]->add_prop(WARG_S_TEAM,
            lower_case(killer->query_real_name()));
    }

// log it
    log_file("warg_killers", capitalize(killer->query_real_name()) +
        " killed the great white warg, in team with " +
        capitalize(team_name) + ", " + ctime(time())+".\n");
    command("emote lifts back his head and howls loudly " +
        "as he falls to the ground!");
    ::do_die(killer);
}

