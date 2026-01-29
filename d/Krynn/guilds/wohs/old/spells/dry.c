/* Stralle @ Genesis 030806
 *
 * Description: Dry oneself
 * Class:       0 (cantrip)
 * Ingredients: None
 * Mana:        20
 * Tax:         N/A
 * Skills:      SS_ELEMENT_FIRE     5
 *              SS_FORM_CONJURATION 5
 * Task:        TASK_SIMPLE
 */

#include <ss_types.h>
#include <tasks.h>
#include <cmdparse.h>
#include <macros.h>

#include "../guild.h"
#include "/d/Krynn/common/defs.h"

inherit SPELL_STD;

public object *
dry_target(object caster, string str)
{
    object *arr;
    
    if (!stringp(str))
    {
        if (caster->query_wet_shadow() != 666)
        {
            caster->catch_tell("You don't seem to be in a very bad need of drying.\n");
            return ({ });
        }
        return ({ caster });
    }
    
    parse_command(str, ({}), "[at] / [on] [the] %s", str);
    arr = PARSE_THIS(str, "%l");
    
    if (!sizeof(arr))
    {
        if (str == "me" || str == "myself" || str == caster->query_real_name())
        {
            if (caster->query_wet_shadow() != 666)
            {
                caster->catch_tell("You don't seem to be a in a very bad " +
                    "need of drying.\n");
                return ({ });
            }
            return ({ caster });
        }
        
        caster->catch_tell("There is no " + str + " here.\n");
        return ({ });
    }
    
    if (sizeof(arr) > 1)
    {
        caster->catch_tell("You will have to be more specific! You can " +
            "only select one target.\n");
        return ({ });
    }
    
    if (arr[0]->query_wet_shadow() != 666)
    {
        caster->catch_msg(QCTNAME(arr[0]) + " does not seem to be a in " +
            "a very bad need of drying.\n");
        return ({ });
    }
    
    return arr;
}

varargs int
config_spell(object caster, object *targets, string arg)
{
    set_spell_name("dry");
    set_spell_desc("Dry oneself");
    
    set_spell_element(SS_ELEMENT_AIR, 5);
    set_spell_form(SS_FORM_CONJURATION, 5);
    
    set_spell_time(1);
    set_spell_task(TASK_SIMPLE);
    
    set_spell_mana(20);
    set_spell_target(dry_target);
    set_spell_ingredients(({ }));
    
    set_spell_peaceful(1);
    set_spell_vocal(1);
}

void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    if (targets[0]->query_wet_shadow() != 666)
    {
        caster->catch_msg(QCTNAME(targets[0]) + " seem to have dryed " +
            "off fine without your assistance.\n");
        return;
    }
    
    if (caster != targets[0])
    {
        caster->catch_msg("You put your hands in a cup before you and " +
            "speak some arcane words of magic. Suddenly a sphere of fire " +
            "form in your hands which you blow at " + QTNAME(targets[0]) +
            " effectivelly drying " + HIM(targets[0]) + " off.\n");
        targets[0]->catch_msg(QCTNAME(caster) + " puts " + HIS(caster) +
            " hands in a cup before " + HIM(caster) + " and speaks some " +
            "arcane words of magic. Suddenly a sphere of fire forms in " +
            HIS(caster) + " hands which " + HE(caster) + " blows at " +
            "you effectivelly drying you off.\n");
        tell_room(E(caster), QCTNAME(caster) + " puts " + HIS(caster) +
            " hands in a cup before " + HIM(caster) + " and speaks some " +
            "arcane words of magic. Suddenly a sphere of fire forms in " +
            HIS(caster) + " hands which " + HE(caster) + " blows at " +
            QTNAME(targets[0]) + " effectivelly drying " + HIM(targets[0]) +
            " off.\n", ({ caster, targets[0] }));
    }
    else
    {
        caster->catch_msg("You put your hands in a cup in front of you " +
            "and speak some arcane words of magic. Suddenly a sphere of " +
            "fire form in your hands which you blow at effectivelly " +
            "drying you off.\n");
        tell_room(E(caster), QCTNAME(caster) + " puts " + HIS(caster) +
            " hands in a cup infront of " + HIM(caster) + " and speaks " +
            "some arcane words of magic. Suddenly a sphere of fire forms " +
            "in " + HIS(caster) + " hands which " + HE(caster) + " blows " +
            "at " + HIM(caster) + "self effectivelly drying " + HIM(caster) +
            " off.\n", ({ caster }));
    }
    
    targets[0]->remove_wet_shadow();
}
