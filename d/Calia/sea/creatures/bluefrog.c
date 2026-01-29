// CREATURE:  blue frog (aka marine frog)

/* Calia Domain

    HISTORY

    [96-03-01] Created by Uhclem from [C:\CALIA\SEA\CREATURE\BLUEFROG.DOC].

    PURPOSE

    A general-purpose npc to populate the sea of west Calia. 

    Modifications by Maniac 9/8/96, 18/9/96, 28/9/96

*/

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia//std/sea_creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <formulas.h>
#include "defs.h"

// GLOBAL VARIABLES

object Frog = this_object();             /*  These are kept in globals      */
string Pronoun;                          /*  so they don't have to be       */
string Possess;                          /*  repeatedly queried in combat.  */

// FUNCTIONS

// Function:  special_attack

    /*

    Purpose:  Special frog attack on the enemy's ear.

    Arguments:  none.

    Returns:  0/1  (1 if the special attack is used, 0 if it is not so that the
    standard attack will be used instead)

    */

    int
    special_attack(object enemy)

        {

        mixed *hitresult;
        string his_her = enemy->query_possessive();
        object room = environment();

        /*  The number of elements in the following arrays is hard-coded into
            the statements that use them for efficiency's sake.  If you change
            the number of elements, you must change all the tell_watcher and
            catch_msg statements in this function!  */

        string *hitareas = ({"ear", "nose", "chin", "cheek", "eye"});

        string *hittypes = ({"mauls", "thrashes", "pounds", "buffets",
            "bludgeons"});


        if(random(10)) return 0;
            /* 10% chance the frog will use this attack. */

        hitresult = enemy->hit_me(5 + random(10), W_BLUDGEON, Frog, -1);

        if(!hitresult[0])  /*  No effect.  */

            {

            tell_watcher("The blue frog tries to get a grip on " +
                QTNAME(enemy) + "'s head but fails.\n", enemy);

            enemy->catch_msg("The blue frog tries to get a grip on your " +
                "head but fails.\n");

            }

        else if(hitresult[0] < 5)  /*  Slight damage.  */

            {

            tell_watcher("The blue frog momentarily gets a grip on " +
                QTNAME(enemy) + "'s head and " + hittypes[random(5)] + " " +
                his_her + " " + hitareas[random(5)] + " with " +
                Possess + " long muscular tongue!\n", enemy);

            enemy->catch_msg("The blue frog momentarily gets a grip on " +
                "your head and " + hittypes[random(5)] + " your " +
                hitareas[random(5)] + " with " +
                Possess + " long muscular tongue!\n");

            }

        else  /*  Significant damage.  */

            {

            tell_watcher("The blue frog gets a firm grip on " +
                QTNAME(enemy) + "'s head and tries to suck " +
                "some of " + his_her + " brains out through " + his_her +
                " ear-hole!\n", enemy);

            enemy->catch_msg("The blue frog gets a firm grip on your " +
                "head and sucks hard on your ear-hole.  " +
                "You feel your brains being pulled out!\n");

            }

        if(enemy->query_hp() <= 0)

            {

            tell_watcher("The blue frog sucks a big chunk of " +
                QTNAME(enemy) + "'s brain out of " + his_her +
                " head and swallows it!\n" +
                "The blue frog cackles with glee!\n", enemy);

            enemy->catch_msg("The blue frog sucks your brains out!\n");
            enemy->do_die(Frog);

            }

        return 1;

        }


// CREATURE DEFINITION

    create_creature()

        {

        set_name("frog");
        set_adj("blue"); 
        add_adj("marine"); 
        set_race_name("frog");

        set_short("blue frog"); 

        /*  Set the gender and appropriate pronouns.  These are put into global
            variables so we don't have to call the function repeatedly in
            combat.  */

        set_gender(random(2));
        Pronoun = query_pronoun();
        Possess = query_possessive();

        set_long("This is a stocky, muscular marine frog that looks " +
            "well suited to life in the sea. Blue on the top and " +
            "gray on the bottom, " + Pronoun + "'s easy " +
            "to overlook if you're not very observant.\n");

        /*  COMBAT ATTRIBUTES  */

        set_skill(SS_SWIM, 90 + random(20));
        set_skill(SS_UNARM_COMBAT, 10 + random(10));
        set_skill(SS_DEFENCE, 10 + random(10));

        set_attack_unarmed(0,5,5,W_SLASH,10,"tiny sharp teeth");
        set_attack_unarmed(1,10,10,W_BLUDGEON,50,"long muscular tongue");
        set_attack_unarmed(3,5,5,W_SLASH,10,"tiny sharp claws");
        set_attack_unarmed(4,10,10,W_BLUDGEON,30,"strong hind legs");
        set_hitloc_unarmed(0, 5, 20, "head");
        set_hitloc_unarmed(1, 10, 40, "body");
        set_hitloc_unarmed(2, 5, 25, "front legs");
        set_hitloc_unarmed(3, 5, 15, "hind legs");

        /*  PROPERTIES  */

        add_prop(CONT_I_VOLUME, 1000);
        add_prop(CONT_I_WEIGHT, 1000);
        add_prop(CONT_I_MAX_VOLUME, 1250);
        add_prop(CONT_I_MAX_WEIGHT, 1250);

        set_stats(({10,30,20,20,20,5}));

        add_prop(LIVE_I_NEVERKNOWN, 1);
        add_prop(NPC_I_NO_LOOKS, 1);
        set_alignment(75);
        set_whimpy(40); 

        /*  MOTION  */

        set_random_move(5); 
        set_restrain_path(SECTOR_PATH(0, 0, 0)); 

        /*  LEFTOVERS */ 

        add_leftover(SEA_LEFTOVERS+"frog_legs", "legs", 1, 0, 0, 1); 
   
        /*  EMOTES  */

        set_act_time(2);

        add_act("emote swims with strong kicks of " + Possess +
            " muscular hind legs.");

        add_act("emote circles as if " + Pronoun + " is stalking some prey.");

        add_act("emote strikes with " + Possess + " long muscular tongue, " +
            "snatches a small fish, and swallows it with a loud 'gulp!'");

        add_act("emote strikes at something with " + Possess +
            " long muscular tongue but misses.");

        add_act("emote sticks out " + Possess +
            " long muscular tongue at you menacingly.");

        add_act("kill fish");

        add_act("emote swims between your legs.");

        }
