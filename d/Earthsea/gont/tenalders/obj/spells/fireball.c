/*
 * Ckrik 9/2003
 * Fireball spell for Karg priestesses
 *
 */

inherit "/d/Genesis/newmagic/spells/bolt";

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <formulas.h>

#define MANA_COST 50
#define BASE_PEN 30

static string size;

public void
create_bolt()
{
    set_spell_time(2);
    set_spell_mana(MANA_COST);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_FIRE, 55);
    set_spell_form(SS_FORM_CONJURATION, 45);
    set_spell_target(spell_target_one_present_enemy);
    set_bolt_desc("fireball");
    set_spell_name("fireball");
    set_spell_visual(0);
    set_spell_vocal(0);
    set_spell_desc("Summon a fireball to strike at an enemy.");
}

void
desc_bolt_damage(object caster, object target, mixed *result)
{
    switch (result[0])
    {
    case -1..5:
        caster->catch_msg("Unfortunately " + QTNAME(target) +
            " is only barely grazed by the " +
            size + ".\n");
        target->catch_msg("Fortunately you are only barely grazed by the " +
            size + ".\n");
        caster->tell_watcher(QCTNAME(target) + 
            " is only barely grazed by the " +
            size + ".\n", target);
    break;
    case 6..10:
        caster->catch_msg("The " + size + " hits " + QTNAME(target) +
            " squarely in the chest.\n");
        target->catch_msg("The " + size + " hits you squarely in the " +
            "chest and burns painfully.\n");
        caster->tell_watcher("The " + size + " hits " + QTNAME(target) +
            " squarely in the chest.\n", target);
    break;
    case 11..25:
        caster->catch_msg("The " + size + " strikes and consumes " +
            QTNAME(target) + ", leaving " + target->query_objective() +
            " reeling in pain.\n");
        target->catch_msg("The " + size + " strikes and consumes you, " +
            "leaving you reeling in pain.\n");
        caster->tell_watcher("The " + size + " strikes and consumes " +
            QTNAME(target) + ", leaving " + target->query_objective() +
            " reeling in pain.\n", target);
    break;
    default:
        caster->catch_msg("The " + size + " smashes hard into " +
            QTNAME(target) + ", enveloping " + target->query_objective() +
            " completely. " + capitalize(target->query_pronoun()) +
            " shrivels as " + target->query_possessive() +
            " body burns to a char.\n");
        target->catch_msg("The " + size + " smashes hard into you, " +
            "enveloping you completely. You shrivel " +
            "as your body burns to a char.\n");
        caster->tell_watcher("The " + size + " smashes hard into " +
            QTNAME(target) + ", enveloping " + target->query_objective() +
            " completely. " + capitalize(target->query_pronoun()) +
            " shrivels as " + target->query_possessive() +
            " body burns to a char.\n", target);
    break;
    }
}

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    int pen;
    mixed *hitresult;
    object corpse;
    object target = targets[0];

    pen = F_PENMOD(BASE_PEN + random(30), 
        caster->query_skill(SS_ELEMENT_FIRE) +
        caster->query_skill(SS_FORM_CONJURATION) +
        caster->query_stat(SS_INT));
    /* Modified by spellcraft */
    pen -= (100 - caster->query_skill(SS_SPELLCRAFT)) * pen / 100;

    switch (pen)
    {
    case 0..200:
        size = "small redish fireball";
        break;
    case 201..400:
        size = "medium bright-yellow fireball";
        break;
    case 401..600:
        size = "large white-hot fireball";
        break;
    default:
        size = "enormous fierce-blue fireball";
        break;
    }
    
    caster->catch_msg("You raise your fist " +
        "in the air and slowly open your palm, revealing a " +
        "glowing mass of flame! Before " +
        QTNAME(target) + " is able to get " +
        "out of the way, you launches the " + size +
        " right at " + target->query_objective() + ".\n");
    target->catch_msg(QCTNAME(caster) + 
        " raises " + caster->query_possessive() + " fist " +
        "in the air and slowly opens " +
        caster->query_possessive() + " palm, revealing a " +
        "glowing mass of flame! Before you are able to get " +
        "out of the way, " + caster->query_pronoun() +
        " launches the " + size + " right at you.\n");
    caster->tell_watcher(QCTNAME(caster) + 
        " raises " + caster->query_possessive() + " fist " +
        "in the air and slowly opens " +
        caster->query_possessive() + " palm, revealing a " +
        "glowing mass of flame! Before " +
        QTNAME(target) + " is able to get " +
        "out of the way, " + caster->query_pronoun() +
        " launches the " + size + " right at " +
        target->query_objective() + ".\n", target);

    pen -= resist[0] * pen / 100;

    hitresult = do_bolt_damage(caster, target, pen);

    desc_bolt_damage(caster, target, hitresult);
    if (target->query_hp() <= 0)
    {
        target->do_die(caster);
        corpse = present("corpse", environment(caster));
        if(corpse)
        {
            corpse->set_short("charred " + corpse->short());
        }
    }
}

