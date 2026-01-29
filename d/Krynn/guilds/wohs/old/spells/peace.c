/*
 * Peace
 *
 * Description: Make peace
 * Class:       2
 * Ingredients: a dove
 * Mana:        40 (1/3)
 * Tax:         N/A
 * Skills:      SS_ELEMENT_AIR     3
 *              SS_FORM_DIVINATION 4
 * Task:        TASK_ROUTINE
 * Restriction:
 *              the caster must not be gagged and the caster must
 *              have something to cast the spell on.
 */
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <tasks.h>
#include <language.h>

#include "../guild.h";
#include "/d/Krynn/common/defs.h"

#define DEBUG_ON    1
#define DEBUG_WIZ   "boron"
#define DEBUG(x)    find_living(DEBUG_WIZ)->catch_msg(x + "\n")

inherit SPELL_STD;

public varargs int
config_spell(object caster, object *targets, string arg)
{
    set_spell_name("featherfight");
    set_spell_desc("Cease fighting");

    set_spell_element(SS_ELEMENT_AIR, 3);
    set_spell_form(SS_FORM_DIVINATION, 4);

    set_spell_time(1);
    set_spell_task(TASK_ROUTINE);

    set_spell_mana(75);
    set_spell_target(spell_target_present_livings);
    set_spell_ingredients(({ "dove" }));

    set_spell_peaceful(0);
    set_spell_vocal(1);
}

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    object  *oblist;
    int     size;
    int     index = -1;

    if ( caster == targets[0] )
    {
        say(QCTNAME(this_player()) + " mumbles a few words, and white " +
            "feathers fly everywhere.\nSuddenly " + TP->query_pronoun() +
            " is at peace with " + TP->query_possessive() + " enemies.\n");
        write("As you mumble the magic words, the white dove takes off.\nSuddenly " +
            "it is gone and feathers are everywhere, and you are at peace " +
            "with your enemies.\n");
    }
    else
    {
        actor("As you mumble the magic words, the white dove takes off.\nSuddenly " +
              "it is gone, feathers are everywhere and you made peace for", ({ caster}) );

        target(" mumbles a few words, white feathers fly everywhere. " +
               "Suddenly you are at peace with your enemies.\n", targets);

        all2act(" mumbles a few words, and white feathers fly everywhere.\n" +
               "Suddenly " + TP->query_pronoun() + " made peace for", targets);
    }

    size = sizeof(targets);

    while(++index < size)
    {
        oblist = targets[index]->query_enemy(-1);

        targets[index]->stop_fight(oblist);
        oblist->stop_fight(targets[index]);
    }

}






