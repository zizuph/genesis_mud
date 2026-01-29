/*
 * File         : /d/Genesis/start/hobbit/npc/seagull.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/28/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        This seagull is meant to fly around in the harbour area and doing
 *        things like land on the pier, sound a lot, fly by etc. I figure
 *        there should be a small crowd of them. Also, a sitting one could
 *        actually be hit and killed.
 * 
 * TODO         :

 *
 * Modifications:
 *     N.B. This file is generated from templates hosted elsewhere and
 *     if someone corrects something in this file, please mail Seaweed
 * 
 */

/* directives */
#pragma strict_types
/* includes */
#include <stdproperties.h> 
#include <macros.h> 
#include <wa_types.h> 
#include <ss_types.h>
#include "../hobbit.h"
/* inherits */
inherit "/std/creature";
inherit "/std/act/action";
inherit EX_LIB + "grid";
inherit "/std/combat/unarmed";

/* defines */
// NPC states (bit values)
#define FISH           1
#define SITTING        2

// Combat attack types
#define A_BEAK         1

// Combat hit locations
#define H_BODY         1

/* prototypes */
void create_creature();
void seagull_actions();


/* globals */
int     Status;
int     Fishes;
string  Sittingplace;


/*
 * Function name:       create_creature
 * Description  :       set up the non-humanoid
 */
void
create_creature()
{
    set_name("seagull");
    set_short("seagull");
    set_long(
      "@@seagull_long_description@@\n");
    add_prop(CONT_I_HEIGHT, 300);
    add_prop(CONT_I_VOLUME, 2000);
    add_prop(CONT_I_WEIGHT, 700);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/28/99.\n");
    
    set_act_time(2);
    add_act("@@seagull_actions@@");
    set_gender(G_NEUTER);
    set_stats(({ 5, 5, 5, 5, 5, 5 }));
    remove_prop(OBJ_M_NO_GET);
    set_race_name("bird");
    set_pname("seagulls");
    set_adj(({"yelling"}));
    set_short("seagull");
    set_pshort("seagulls");
    set_mm_in("gently glides closer looking for food.");
    set_mm_out("gently glides away looking for more food.");
    set_skill(SS_DEFENCE, 5);
    set_attack_unarmed(A_BEAK,  5, 5, W_IMPALE, 100, "beak");
    set_hitloc_unarmed(H_BODY, ({ 5, 5, 5}), 100, "body");
    
    
}

/*
 * Function name: seagull_actions()
 * Description  :  Keep track of NPC actions
 */
void
seagull_actions()
{
    int i;
    i = random(6);
    switch(i) 
    {
        case 0: // Excrement or yell
        {
            if (SITTING & Status)
            {
                command("emote yells loudly.");
            }
            else
            {
                command("emote relieves itself high up in the air " +
                        "above your head and almost hits you."); 
            }
            break;
        }
        case 1: // If sitting:take off, otherwise:land
        {
            if(SITTING & Status)
            {
                command("emote suddenly takes off up into the sky.");
                Status &= ~SITTING;
            }
            else
            {
                string *sarray; // Places available in the room
                sarray = environment()->query_prop(HOBBIT_SL_S_SEAGULL_LP);
                if (sizeof(sarray))
                {
                    Sittingplace = sarray[random(sizeof(sarray))];
                }
                else // If the property is not set (we wimped?)
                {
                    Sittingplace = "calmly";
                }
                command("emote lands " + Sittingplace + " nearby.");
                Status |= SITTING;
            }
            break;
        }
        case 2: // Catch a fish or peer around
        {
            if (SITTING & Status)
            {
                command("peer");
            }
            else
            {
                if (FISH & Status)
                {
                    command("emote dives into the water and catches one more fish.");
                }
                else
                {
                    command("emote dives into the water and catches a fish.");
                }
                Status |= FISH;
                Fishes++;
            }
            break;
        }
        case 3: // Eat fish or look for food
        {
            if (FISH & Status)
            {
                if (SITTING & Status)
                {
                    command("emote swallows a small fish at once.");
                }
                else
                {
                    command("emote swallows a small fish while flying.");
                }
                Fishes--;
                if (Fishes == 0)
                {
                    Status &=  ~FISH;
                }
            }
            else
            {
                command("emote searches hungrily for food.");
            }
            break;
        }
        case 4: // Yell
        {
            command("emote yells loudly.");
            break;
        }
        case 5: // Fly away
        {
            if ((SITTING & Status) == 0)
            {
                grid_move_it(); // Take a walk
            }
            break;
        }
        default:
        {
            command("emote does something totally unexpected.");
        }
    }
}

/*
 * Function name: seagull_long_description()
 * Description  :  Keep track of NPC long description.
 */
string
seagull_long_description()
{
    string s;
    s = "The seagull is ";
    if (SITTING & Status)
    {
        s += "sitting " + Sittingplace;
    }
    else
    {
        s += "flying in the sky";
    }
    if (FISH & Status)
    {
        if (Fishes == 1)
        {
            s += " with a fish in its beak.";
        }
        else
        {
            s += " with " + Fishes + " fishes in its beak.";
        }
    }
    else
    {
        s += ".";
    }
    return s;
}
/*
 * Here we redefine the special_attack function which is called from
 * within the combat system. If we return 1 then there will be no
 * additional ordinary attack.
 *
 */
int
special_attack(object enemy)
{
    object clone;
    mixed *hitresult;
    string how;
    
    // Only do special attack every fifth hit
    if (random(5))
    {
        return 0;
    }
    
    // The special attack will not do any *physical* harm
    clone = clone_object(EX_OBJ + "guano_blob");
    clone->set_no_show(); // Let the attacker remain smeared 
    clone->move(enemy);
    enemy->catch_tell(query_The_name(enemy) + 
        " dives from above and relieves itself.\n"+
        "You are hit by a blob of guano!\n");
    tell_watcher(QCTNAME(TO) + 
        " makes a dive and relieves itself!\n" +
        capitalize(QCTNAME(enemy)) + 
        " is hit by a blob of guano.\n", enemy);
    return 1;
}

// By redefining this function we get a chance to clone
// the fishes that was caught by the seagull and drop them
// on the ground just before it dies.
void
do_die(object killer)
{
    object clone;
    while(Fishes--)
    {
        clone = clone_object(EX_OBJ + "dead_fish");
        clone->move(TO);
    }
    TO->command("drop fishes");
    ::do_die(killer);
}

