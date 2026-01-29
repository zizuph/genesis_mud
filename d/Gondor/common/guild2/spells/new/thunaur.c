/*
 * /d/Gondor/common/guild2/spells/new/thunaur.c
 *
 *     This is the object that executes the attack when the spell
 *     'thunaur' is cast by a Morgul Mage
 *
 * Attack spell
 * (thunaur = fire breath) but I don't know exactly how Olorin though :)
 * 
 * Class 2 or 3 damage spell
 * Element Fire; Form Conjuration
 * Area of effect: living target
 *
 * Ingredient: leftover
 * Mana: 60..90
 * Skills: SS_ELEMENT_FIRE, SS_FORM_CONJURATION, SS_SPELLCRAFT
 * Description: F_PENMOD(75 + 25..50, 100 + 100..200)
 * Requirements: Morgul Mage, Guild level >= 14
 *               mage robe must be present
 *               mage must have quaffed nennaur potion
 *
 * Arren, 25 july 1994
 * Modification log:
 * Olorin, 29-Oct-1995: rewritten to conform to the new magic system
 */

#define MS_THUNA_INGR     ({ "leftover", })
#define MS_THUNA_MANA     30
#define MS_THUNA_TASK     TASK_SIMPLE
#define MS_THUNA_LIST     ({SKILL_AVG, SS_SPELLCRAFT, SS_FORM_CONJURATION, \
                            SKILL_END, \
                            SKILL_AVG, SS_ELEMENT_FIRE, SS_ELEMENT_AIR, \
                            SKILL_END, })
#define MS_THUNA_TARGET   ({ SS_ELEMENT_EARTH, SS_FORM_ABJURATION, })
#define MS_THUNA_PEN_MIN  75

#undef  DEBUG
#define DEBUG 1

//	Prototypes
public void    thunaur_message(object caster, object target, mixed hitresults);
public mixed   thunaur_success(object caster, object *targets);
public int     thunaur_damage(object caster, object target, int result);
public int     thunaur_resist(object target);

public int
create_spell_thunaur(string arg)
{
    set_element(SS_ELEMENT_FIRE, 10);
    set_form(SS_FORM_CONJURATION, 10);

    set_spell_time(MS_THUNA_TIME);
    set_spell_attack();
    set_damage_type(MAGIC_DT);
    set_mana_spell(MS_THUNA_MANA);

    set_find_target(find_one_combat_target);
    set_spell_message(thunaur_message);
    set_spell_success(thunaur_success);
    set_spell_damage(thunaur_damage);
    set_spell_resist(thunaur_resist);

    set_ingredients(MS_THUNA_INGR);

    return 0;
}

public mixed
do_thunaur(string str)
{
   if ((!objectp(present(MORGUL_S_NENNAUR_EFFECT_NAME, TP))) &&
        (!TP->query_npc()))
        return "You are not properly prepared to cast this spell!\n";

    TP->catch_msg("With the power the Dark Lord has bestowed "+
        "upon you, you call the Firebreath.\n");
    
    return cast_spell();
}

public mixed
thunaur_success(object attacker, object *targets)
{
    int     result;

    if ((result = attacker->resolve_task(
        MS_THUNA_TASK, MS_THUNA_LIST, targets[0], MS_THUNA_TARGET)) <= 0)
        return 0;
#if DEBUG
    attacker->catch_msg("DEBUG thunaur object: result = " + result + ".\n");
#endif
    if (result < 100)
        result = 100;

    return result;
}

public int
thunaur_damage(object attacker, object target, int result)
{
/*
 *  mana is already reduced in cast_spell()
 *  this is the additional mana reduction for successful spell
 */ 
    attacker->add_mana(- (MS_THUNA_MANA * result / 100) );
    return F_PENMOD(MS_THUNA_PEN_MIN + result/4,
                    attacker->query_skill(SS_SPELLCRAFT) + result);
}

public int
thunaur_resist(object target)
{
    return target->query_magic_res(MAGIC_I_RES_FIRE);
}

public void
thunaur_message(object attacker, object target, mixed hitresult)
{
    int    dam = hitresult[3];
    string flame = "a stab of fire, ",
           how = "miss ";

#if DEBUG
attacker->catch_msg("DEBUG: spell_message: hitresult[0] = "+hitresult[0]+", dam = "+dam+"\n");
#endif

    switch(hitresult[0])
    {
        case 0..5:
            how = "lick "; break;
        case 6..15:
            how = "scorch "; break;
        case 16..30:
            how = "burn "; break;
        case 31..50:
            how = "wither "; break;
        case 51..90:
            how = "shrivel "; break;
        case 91..1000:
            how = "consume "; break;
    }
    if (dam > 600)
        flame = "fierce white-hot flames, ";
    else if (dam > 300)
        flame = "fierce flames, ";
  
    attacker->catch_msg("You inhale deeply and then spout forth " + flame
      + "the flames " + how + QTNAME(target) + ".\n");
    target->catch_msg(QCTNAME(attacker) + " inhales deeply and then spouts "
      + "forth " + flame + "the flames " + how + "you.\n");
    tell_room(ENV(attacker), QCTNAME(attacker) + " inhales deeply and then "
      + "spouts forth " + flame + "the flames " + how + QTNAME(target) + ".\n",
        ({ attacker, target, }) );
}

