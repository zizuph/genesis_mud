
/*
 * syskotisi.c
 *
 * Syskotisi (Confusion) spell for the Spirit Circle of Psuchae
 *
 * Copyright (C): Navarre, October 8th, 2006
 *
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spell";

#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include <cmdparse.h>

#include "defs.h"
#include SPIRIT_HEADER

#define I_HAVE_BEEN_SPIRIT_CONFUSED "_i_have_been_spirit_confused"
#define TURN_LOG "spirit_circle/spirit_confusion_log"


string
query_spell_level()
{
    return "Master";
}

/*
 * A combination of spell_target_one_other_present_living
 * and spell_target_one_present_enemy
 */
public object*
confuse_target(object caster, string str)
{
    if (!stringp(str) || (str == ""))
        return spell_target_one_present_enemy(caster, str);
    else
        return spell_target_one_other_present_living(caster, str);
}



/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       1/0 - spell configured/not configured (cannot be cast)
 */
public varargs int
config_spell(object caster, object* targets, string argument)
{
    if (caster == 0)
    {
        set_spell_name("syskotisi");
        set_spell_desc("Confusion");
        set_spell_target(confuse_target);
        set_spell_target_verify(spell_verify_present);
        set_spell_time(6);
        set_spell_mana(216);
        set_spell_vocal(0);
        set_spell_offensive(1);
        set_spell_task(TASK_ROUTINE);
        set_spell_resist_task(TASK_FORMIDABLE);
        set_spell_element(SS_ELEMENT_SPIRIT, 40);
        set_spell_form(SS_FORM_DIVINATION, 40);
        set_spell_ingredients(({"iridescent opal", "skull"}));
        set_spell_object(SPIRIT_SPELLS+"syskotisi_obj");        

        add_element_resistance(SS_ELEMENT_SPIRIT, MAGIC_I_RES_LIFE);

    }
    else
    {
        if (present("_scop_confuse_obj", targets[0]))
        {
            caster->catch_tell("This target is already confused.\n");
            return 1;
        }

        if (caster->query_intoxicated())
        {
            caster->catch_tell("You cannot use Psuchae's gifts while intoxicated!\n");
            return 1;
        }
        if (caster->query_alignment() < 0)
        {
            caster->catch_tell("You cannot use Psuchae's gifts while you are not "+
                "good aligned.\n");
            return 1;
        }
        return 0;
    }
}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (object *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */

public void
concentrate_msg(object caster, object* targets, string arg)
{
    caster->catch_tell("You concentrate on the powers of Psuchae.\n");
    say(QCTNAME(caster) + " appears to be in deep concentration.\n");
    caster->attack_object(targets[0]);
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
resolve_spell(object caster, object* targets, int* resist, int result)
{
    int success, hitresult, pen;
    object spellob;
    object tar = targets[0];

    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but your target is" +
                           " unaffected.\n");
        return;
    }

    caster->catch_msg("In one fluid motion you gesture towards "+
                      QTNAME(tar) + " and shadowy tendrils " +
                      "erupts from your hand. The tendrils strikes " +
                      QTNAME(tar) + "'s face obfuscating " + HIS(tar) + 
                      " vision briefly and diminishing " + HIS(tar) +" self-control.\n");

    tar->catch_msg("In one fluid motion " + QTNAME(caster) +
                   " gestures towards you, and suddenly shadowly "+
                   "tendrils strikes your face. You feel the "+
                   "control of your mind slip.\n");
    tell_room(environment(caster), "In one fluid motion "+QTNAME(caster)+
              " gestures towards "+QTNAME(tar)+" and shadowy tendrils erupts from " +
              HIS(caster) + " hand. The tendrils strike "+QTNAME(tar) +
              " 's face obfuscating "+HIS(tar)+ " vision briefly.\n", ({tar, caster}));
    setuid();
    seteuid(getuid());
    make_spell_effect_object(query_spell_object(), caster, tar, resist[0], result)->move(tar, 1);
}
