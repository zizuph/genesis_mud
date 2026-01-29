/*
 * Magic Missile spell used by lich 
 *
 * Written by Shanoga
 * Updated 2018.03.21
 */

#pragma strict_types

#include "defs.h"

inherit "/d/Genesis/specials/std/spells/harm";

public void
config_harm_spell()
{
    set_spell_name("magic_missile");
    set_spell_desc("up to 5 magical bolts into your enemy");
    set_spell_target(spell_target_one_present_enemy);
    set_spell_vocal(0);
    set_spell_visual(0);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(125.0);
    set_spell_resist(&spell_resist_damage_type(MAGIC_I_RES_MAGIC));
    set_spell_mana_factor(0.25);
    set_spell_task(TASK_ROUTINE);
    set_spell_time_factor(1.0);
    set_spell_ingredients(query_harm_ingredients);
    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    set_spell_form(SS_FORM_CONJURATION, 40);
}

public string *
query_harm_ingredients(object caster)
{
    return ({});
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if(caster->query_skill(SS_SPELLCRAFT) < 80)
    {
        caster->catch_tell("You need to be trained in spellcraft to at " +
          "least superior professional to cast this spell.\n");
        return 0;
    }

    return ::check_valid_action(caster, targets, arg, execute);
}

public int
query_spell_can_be_learned(object player)
{
    if (player->query_npc())
        return 1;
    
    return 0;
}

public void
concentrate_msg(object caster, mixed *targets, string arg)
{
    string caster_message, watcher_message;
    caster_message = "You open your mouth and a magical energy begins " +
      "to build from within.\n";
    watcher_message = QCTNAME(caster) + " opens its mouth and a magical " +
      "energy begins to build from within it.\n";
    caster->catch_msg(caster_message);
    tell_room(E(caster), watcher_message, caster);
}

public void
magic_missile_desc_cast(object caster, object target)
{
    string caster_message, target_message, watcher_message;
    caster_message = "A volley of missiles launch from your mouth toward " +
      QTNAME(target) + ".\n";
    watcher_message = "A volley of missiles launch from " + QTNAME(caster) +
      "'s mouth toward " + QTNAME(target) + ".\n";
    target_message = "A volley of missiles launch from " + QTNAME(caster) +
      "'s mouth toward you!\n";
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    caster->tell_watcher(watcher_message, target, ({ caster, target }));
}


public void
desc_harm_cast(object caster, object *targets)
{
    magic_missile_desc_cast(caster, targets[0]);
}

public mixed *
do_harm_damage(object caster, object target, int pen)
{
    if (caster->query_is_illusion())
    {
        pen = 0;
    }
    return ::do_harm_damage(caster, target, pen);
}

public void
resolve_harm_spell(object caster, object *targets, int *resist, int result)
{

}

public void
magic_missile_desc_damage(object caster, object target, int phurt,
  string hitloc_desc)
{
    int missiles = 0;
    string target_message, watcher_message, caster_message;
    if (caster->query_is_illusion())
    {
        target_message = "The missiles hurtle toward your " + hitloc_desc + 
          " but pass harmlessly through you.\n";
        caster_message = "The missiles hurtle toward " + QTNAME(target) + 
          "'s " + hitloc_desc + " but pass harmlessly through " +
          HIM(target) + ".\n";
        watcher_message = caster_message;
    }
    else
    {
        switch (phurt)
        {
            case 0:
                missiles = 0;
                break;
            case 1..10:
                missiles = 1;
                break;
            case 11..20:
                missiles = 2;
                break;
            case 21..30:
                missiles = 3;
                break;
            case 31..40:
                missiles = 4;
                break;
            default:
                missiles = 5;
                break;     
        }
        if (0 == missiles)
        {
            target_message = CAP(LANG_NUM2WORD(random(3)+2)) +
              " magical bolts of energy hurtle toward you and disperse " +
              "when they hit your " + hitloc_desc + ".\n";
            caster_message = CAP(LANG_NUM2WORD(random(3)+2)) +
              " magical bolts of energy hurtle toward " + QTNAME(target) +
              " and disperse when they hit " + HIS(target) + " " +
              hitloc_desc + ".\n";
            watcher_message = caster_message;
        }
        else
        {
            target_message = CAP(LANG_NUM2WORD(missiles)) +
              " of the missiles " + (missiles == 1 ? "slams" : "slam") +
              " into your " + hitloc_desc + "!\n";
            caster_message = CAP(LANG_NUM2WORD(missiles)) +
              " of the missiles " + (missiles == 1 ? "slams" : "slam") +
              " into " + QTNAME(target) + "'s " + hitloc_desc + "!\n";
            watcher_message = caster_message;
        }
    }
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    caster->tell_watcher(watcher_message, caster, target);
}

public void
desc_harm_damage(object caster, object target, mixed *result)
{
    magic_missile_desc_damage(caster, target, result[0], result[1]);
}

public void
hook_special_complete()
{
    write("Magic missile ready.\n");
}

public void
hook_special_in_cooldown()
{
    write("Magic missile on cooldown.\n");
}

public void
hook_already_active(object ability)
{
    write("Magic missile already casting.\n");
}

public void
list_spells()
{
    write(sprintf("%-15s %s\n", query_spell_name(), ::query_spell_desc()));
}
