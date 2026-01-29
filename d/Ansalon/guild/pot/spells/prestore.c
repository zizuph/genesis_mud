/*
 * pRestore
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/spells/std_pot_spell";

#include "/d/Ansalon/common/defs.h"
#include "../spells.h"
#include <macros.h>
#include <tasks.h>
#include <files.h>
#include "../guild.h"

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 10;
}
 
int
is_poison(object ob)
{
    return (function_exists("create_object",ob) == POISON_OBJECT);
}

public void
concentrate_msg(object caster, object *targets, string arg)
{
    object old_tp = TP;

    set_this_player(caster);
    caster->catch_tell("You bow your head in prayer.\n");
    all_msgbb(QCTNAME(caster) + " bows " + HIS(caster) + " head " +
        "in prayer.\n", caster);
    set_this_player(old_tp);
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    object tar = targets[0];
    int max_to_heal, use_fatigue, use_stuffed, pois_res;
    string *s;
    object *poisons;

    if (tar->query_alignment() > 100)
    {
    	if (tar == caster)
    	{
    	    caster->catch_tell("You sense that the Dark Queen refuses to " +
    	    "heal you!\n");
    	    return;
    	}
    	else
    	{
    	    caster->catch_tell("Takhisis refuses to heal " +
    	    tar->query_the_name(caster) + "!\n");
    	    return;
    	}
    }

    max_to_heal = tar->query_max_hp() - tar->query_hp();
    if (max_to_heal > 750)
        max_to_heal = 750;

    /* result is multiplied by 7, making it in range 7 - 385 */
    result *= 17;

    find_player("stralle")->catch_tell("#prestore# max_to_heal " + max_to_heal + ", result " + result + "\n");

    if (result < max_to_heal)
    {
        /* Use some fatigue from the target. One fatigue is worth
           1/2 hp */

        use_fatigue = 2 * (max_to_heal - result);
        if (use_fatigue >= tar->query_fatigue())
            use_fatigue = tar->query_fatigue();

        result += use_fatigue / 2;
        tar->add_fatigue(-use_fatigue);
    }

    if (result < max_to_heal)
    {
        /* Use some of the stuffed (food) of the target 
            10 grams of food is worth one hp */

        use_stuffed = 10 * (max_to_heal - result);
        if (use_stuffed >= tar->query_stuffed())
            use_stuffed = tar->query_stuffed();

        result += use_stuffed / 10;
        tar->eat_food(-use_stuffed);
    }

    if (result > 750)
        result = 750;

    pois_res = 0;
    /* 65 per cent chance of success for a maxed priest
     */
    if (random(100) < (caster->query_priest_level() * 10 +
        caster->query_skill(SS_ELEMENT_LIFE) / 2))
    {
    	if (sizeof(poisons = filter(all_inventory(tar),is_poison)))
    	{
    	    pois_res = poisons[0]->cure_poison(({"all"}),
    	        (random(40) +
    	        caster->query_priest_level() * 10) * 2);

            /* If we do not manage to cure it, we weaken it by
             * lowering the strength with 15-30% of the current
             * strength.
             */
            if (!pois_res && !poisons[0]->query_no_cleanse())
            {
                poisons[0]->set_strength((poisons[0]->query_strength() *
                    100) / (115 + random(15)));
                poisons[0]->set_interval((poisons[0]->query_interval() *
                    100) / (90 - random(10)));
                pois_res = -1;
            }
    	}
    }

    tar->heal_hp(result);
    max_to_heal = tar->query_max_hp() - tar->query_hp();

    if (tar == caster)
    {
        s = ({ "You whisper a prayer to the Queen of Darkness, and you " +
        "feel new health infusing your body",
        QCTNAME(caster) + " straightens up, looking more hale.\n" });
        
        if (result >= max_to_heal)
            s[0] += ", restoring you to full health. ";
        else
            s[0] += ", partially restoring your health. ";

        if (pois_res > 0)
            s[0] += "You flush some poison out of your body. ";
        else if (pois_res == -1)
            s[0] += "You feel a poison weakening somewhat. ";

        if (use_fatigue)
            if (use_stuffed)
                s[0] += "The effort of healing leaves you tired " +
                "and hungry. ";
            else
                s[0] += "The effort of healing leaves you tired. ";

        caster->catch_tell(s[0] + "\n");
        all_msgbb(s[1], caster);
    }
    else
    {
        s = ({ "You place your hands on " + tar->query_the_name(caster) +
        ", and whisper a prayer to the Queen of Darkness. " +
        tar->query_The_name(caster) + " shivers as ",

        caster->query_The_name(tar) + " places " + HIS(caster) + " hands " +
        "on you, and whisper a prayer. You shiver as ",

        QCTNAME(caster) + " places " + HIS(caster) + " hands on " +
        QTNAME(tar) + ", and whisper a prayer. " + QCTNAME(tar) +
        " shivers as " + HIS(tar) + " wounds are healed.\n"
        });

        if (result >= max_to_heal)
        {
            s[0] += "all " + HIS(tar) + " wounds are healed";

            s[1] += "all your wounds are healed, restoring you to full " +
            "health";
        }
        else
        {
            s[0] += "some of " + HIS(tar) + " wounds are healed";

            s[1] += "some of your wounds are healed";
        }

        if (use_fatigue)
            if (use_stuffed)
                s[1] += ", leaving you more tired and hungry than before";
            else
                s[1] += ", leaving you more tired than before";

        s[1] += ".";

        if (pois_res > 0)
        {
            s[0] += " You flush some poison out of " + HIS(tar) + " body. ";
            s[1] += " You feel cleansed from some poison. ";
        }
        else if (pois_res == -1)
        {
            s[0] += " You weakened some poison in " + HIS(tar) + " body. ";
            s[1] += " You feel a poison in your body weakening. ";
        }

        caster->catch_tell(s[0] + "\n");
        all_msgbb(s[2], caster, tar);
        tar->catch_tell(s[1] + "\n");
    }
}

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       0/1 - spell configured/not configured (cannot be cast)
 */
public varargs int
config_spell(object caster, object *targets, string argument)
{
    set_spell_name("prestore");
    set_spell_desc("Major healing of yourself or others");

    set_spell_element(SS_ELEMENT_LIFE, 55);
    set_spell_form(SS_FORM_TRANSMUTATION, 40);

    set_spell_time(10);
    set_spell_mana(110);

    set_spell_task(TASK_ROUTINE);

    set_spell_resist(spell_resist_healing);
    set_spell_target(spell_target_one_present_living);
    set_spell_target_verify(spell_verify_present);

#ifndef NO_INGREDIENTS
    set_spell_ingredients(({"rib", "pearl"}));
#endif

    set_spell_vocal(1);
    set_spell_stationary(1);
    set_spell_peaceful(1);

    return 0;
}
