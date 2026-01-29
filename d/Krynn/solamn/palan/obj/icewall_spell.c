inherit "/d/Genesis/newmagic/spell";


#include "/d/Krynn/common/defs.h"
#include "../local.h"

#include <ss_types.h>
#include <tasks.h>
#include <macros.h>

public void
create_spell()
{
    /* We use the base config info */
    ::create_spell();

    set_spell_name("icewall_teleport");
    set_spell_desc("Teleport yourself to Icewall");
    set_spell_target(spell_target_caster);

    set_spell_time(25);
    set_spell_mana(75);
    set_spell_task(TASK_SIMPLE);

    set_spell_resist(spell_resist_beneficial);
    set_spell_peaceful(1);

    /* Override the difficulty and the ingredients */
    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_DIVINATION, 15);
    set_spell_ingredients(({ "icewall_teleport_scroll", "white_pearl" }));
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
    if ( resist[0] < (result+caster->query_skill(SS_SPELLCRAFT)))
    {
        if (!caster->move("/d/Krynn/icewall/castle/floor1/kitchen"))
        {
            say(QTNAME(caster) + " " + caster->query_mm_out());
            write("You feel yourself magically transferred.\n");

            log_file("potioneffect", ctime(time()) + " " +
            TP->query_name() + " got teleported to icewall.\n");
        }
    }
    else
        write("You are able to resist the magical effect of the spell.\n");
}
