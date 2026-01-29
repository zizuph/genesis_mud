/*
 * pSummon
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/spells/std_pot_spell";

#include "/d/Ansalon/common/defs.h"
#include "../spells.h"
#include "../guild.h"
#include <macros.h>
#include <cmdparse.h>
#include <tasks.h>  
#include <wa_types.h>

#define ROOM_M_DA_DRAGONSTEED_NO_LAND "_room_m_da_dragonsteed_no_land"


/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 7;
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
    object ob, tar = targets[0];

    caster->catch_tell("You raise your voice to the skies and cry " +
        "out the name of Takhisis, the Dragon Queen.\n");
    all_msgbb(QCTNAME(caster) + " raises " + HIS(caster) + " voice " +
        "to the skies and cry out the name of Takhisis, the Dragon Queen.\n",
        caster);

    setuid();
    seteuid(getuid());
    ob = make_spell_effect_object(DRAGON_OBJ, caster, tar, resist, result);
    ob->set_result(result);
}

public object *
spell_target_environment(object caster, string str)
{
    string msg;

    if (environment(caster)->query_prop(ROOM_I_INSIDE))
    {
        write("You need the nearness of the skies to make your summons.\n");
        return ({ });
    }

    if ((msg = (environment(caster)->query_prop(ROOM_M_NO_TELEPORT))) ||
        (msg = (environment(caster)->query_prop(ROOM_M_NO_TELEPORT_FROM))) ||
        (msg = (environment(caster)->query_prop(ROOM_M_DA_DRAGONSTEED_NO_LAND))))
    {
        if (stringp(msg))
            write(msg);
        else
            write("Something nerves you about this place, you better " +
                "find a more suitable location for summons.\n");
        
        return ({ });
    }
    
    if (environment(caster)->query_prop(ROOM_IN_WATER) ||
        environment(caster)->query_prop(ROOM_UNDER_WATER) ||
        environment(caster)->query_prop(ROOM_IN_AIR))
    {
        write("Surely you would not think your summons would be heard in " +
            "this area?\n");
        return ({ });
    }
    
    return ({ environment(caster) });
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
config_spell(object caster, object *targets, string arg)
{
    set_spell_name("psummon");
    set_spell_desc("Summon");

    set_spell_time(6);
    set_spell_element(SS_ELEMENT_AIR, 50);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_mana(222);
    set_spell_task(TASK_ROUTINE);
    set_spell_resist(spell_resist_beneficial);
    set_spell_target(spell_target_environment);
//    set_spell_target_verify(spell_verify_present);

#ifndef NO_INGREDIENTS
    set_spell_ingredients(({"rib", "rib", "dragonbrew"}));
#endif

    set_spell_vocal(1);

    return 0;
}
