/*
 * pPain
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/spells/std_pot_spell";

#include "/d/Ansalon/common/defs.h"
#include "../spells.h"
#include "../guild.h"
#include <macros.h>
#include <tasks.h>
#include <wa_types.h>

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 12;
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
    object ob;

    caster->command("point at "+OB_NAME(tar));
    caster->command("say Feel the wrath of the Dark Queen!");

    result = ((100 - resist[0]) * result) / 100;
    if (result < 1 || P(PAIN_ID,tar))
    {
        return;
    }

    caster->catch_tell(C(HE(tar))+" cries out as a wave of pain "+
	"sears through "+HIS(tar)+" body.\n");
    tar->catch_tell("You cry out as a wave of pain sears through your body.\n");
    all_msg(QCTNAME(tar) + " cries out in pain.\n", caster, tar);

    GUILD_ADMIN->log(caster, "ppain", tar->query_real_name() + " (" +
        file_name(tar) + "): " + result + ", resist: " + resist[0]);

    setuid();
    seteuid(getuid());
    ob = make_spell_effect_object(PAIN_OBJ, caster, tar, resist, result);
    ob->set_ppain_time(result);
}

/*
 * Function name: ingredient_knife
 * Description:   Used to find a knife ingredient
 * Arguments:     object *possible - possible ingredients to check
 *                object *found    - ingredients already found
 * Returns:       pointer to valid ingredient object, or 0
 */
object
ingredient_knife(object *possible, object *found)
{
    object *list, tmp;
    int i;

    list = possible - found;
    for (i = 0; i < sizeof(list); i++)
    {
        tmp = list[i];
        if (tmp->check_weapon() &&
            tmp->query_wt() == W_KNIFE &&
            (tmp->query_pen()) >= 8)
        {
            return tmp;
        }
    }
    return 0;
}

/*
 * ppain_target: a combination of spell_target_one_other_present_living
 * and spell_target_one_present_enemy
 */
public object *
ppain_target(object caster, string str)
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
 * Returns:       0/1 - spell configured/not configured (cannot be cast)
 */
public varargs int
config_spell(object caster, object *targets, string argument)
{
    set_spell_name("ppain");
    set_spell_desc("Paralyze your enemy with pain");

    set_spell_time(4);
    set_spell_element(SS_ELEMENT_LIFE, 77);
    set_spell_form(SS_FORM_TRANSMUTATION, 77);
    set_spell_mana(117);
    set_spell_task(TASK_ROUTINE);
    set_spell_target(ppain_target);
//    set_spell_target_verify(ppain_target);
    set_spell_target_verify(spell_verify_present);
            
    set_spell_stationary(0);
    set_spell_offensive(1);

#ifndef NO_INGREDIENTS
    set_spell_ingredients(({"green slime","elf heart",ingredient_knife}));
#endif

    return 0;
}

