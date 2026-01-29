/*
 * Navarre, September 19th 2006.
 *
 * The object behind the Scop Elefrinisi spell.
 * (Relieve Burden)
 *
 */
inherit "/std/object";
inherit "/d/Genesis/newmagic/spell_effect_object";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Krynn/common/defs.h"

function orig_weight_function;


void
create_object()
{
    ::create_object();
    set_name("_scop_elefrinisi_obj");
    set_no_show();

    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    add_prop(MAGIC_AM_MAGIC, ({"enchantment", 100}));
    add_prop(OBJ_S_WIZINFO, "The object behind the " +
                            "Scop confuse spell.\n");
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->catch_tell("You feel the spirits retreat and " +
                             "you are once again alone to carry " +
                             "your burden.\n");
    tell_room(environment(spell_target), QCTNAME(spell_target) +
              " looks as if something is weighing " + 
              HIM(spell_target) + " down.\n", spell_target);
    spell_target->add_prop(CONT_I_MAX_WEIGHT, orig_weight_function);
    remove_spell_effect_object();
}


public int
start()
{
    int gstat, wis, bonus_weight;

    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }
    spell_target->catch_msg("You feel as if a heavy burden has " +
                            "been lifted off your shoulders.\n");
   tell_room(environment(spell_target), QCTNAME(spell_target) +
             " looks as if a heavy burden has been lifted off " +
             HIS(spell_target) + " shoulder.\n", spell_target);
    bonus_weight = (spell_target->query_prop(CONT_I_MAX_WEIGHT) * 14/10) -
                    spell_target->query_prop(CONT_I_MAX_WEIGHT);


    orig_weight_function = spell_target->query_prop_setting(CONT_I_MAX_WEIGHT);

    spell_target->add_prop(CONT_I_MAX_WEIGHT,
                           spell_target->query_prop(CONT_I_MAX_WEIGHT) +
                           bonus_weight);

    gstat = spell_caster->query_stat(SS_OCCUP);
    wis = spell_caster->query_stat(SS_WIS);

    set_alarm(itof(900+3*(gstat+wis)), 0.0,
              &dispel_spell_effect(spell_target));

    return 1;
}
