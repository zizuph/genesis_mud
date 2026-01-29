/*
 *Fireball for Karg priestess, Midnight Feb 2004
 *
 */
inherit "/d/Genesis/newmagic/spells/bolt";

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <formulas.h>

#define MANA_COST 50
#define FIREBALL_BASE_PEN 50


public void
create_bolt()
{
  set_spell_time(5);
  set_spell_mana(MANA_COST);
  set_spell_task(TASK_ROUTINE);
  set_spell_element(SS_ELEMENT_FIRE, 60);
  set_spell_form(SS_FORM_CONJURATION, 40);
  set_bolt_desc("fireball");
  set_spell_name("fireball");
  set_spell_desc("Summon a fireball directed at target.");
}


void
desc_bolt_damage(object caster, object target, mixed *result)
{

  switch(result[0])
    {
    case 0:
      caster->catch_msg("Your weak sphere of fire fizzles and dies out before hitting " 
                        + QTNAME(target) + ". ");
      target->catch_msg(QCTPNAME(caster) + " weak sphere of fire fizzles and dies out " +
                        "before hitting you.");
      caster->tell_watcher(QCTPNAME(caster) + " weak sphere of fire fizzles and dies " +
                       "out before hitting " + QTNAME(target) + ". ", target);
      break;
    case 1..3:
      caster->catch_msg("Your orb of flames barely grazes " + QTNAME(target) + ". ");
      target->catch_msg(QCTPNAME(caster) + " orb of flames barely grazes you.");
      caster->tell_watcher(QCTPNAME(caster) + " orb of flames barely grazes " +
                           QTNAME(target) + ". ", target);
      break;
    case 4..6:
      caster->catch_msg("Your flaming sphere of fire hits " + QTNAME(target) + " and " +
                        "burns " + QTNAME(target) + " painfully.");
      target->catch_msg(QCTPNAME(caster) + " flaming sphere of fire hits you and " +
                        "burns you painfully.");
      caster->tell_watcher(QCTPNAME(caster) + " flaming sphere of fire hits " +
                           QTNAME(target) + " and leaves an ugly red burn. ", target);
      break;
    case 7..9:
      caster->catch_msg("Your blazing flames of wrath slams into " + QTNAME(target) +
                        ".");
      target->catch_msg(QCTPNAME(caster) + " blazing flames of wrath slams right " +
                        "into your chest and the pain is almost unbearable.");
      caster->tell_watcher(QCTPNAME(caster) + " blazing flames of wrath slams into "  +
                           QTNAME(target) + ".", target);
      break;
    case 10..12:      
      caster->catch_msg("Your giant burning sphere of flames hits " + QTNAME(target) + 
                        " extremely hard and leaves " + QTNAME(target) + 
                        " charred by flames.");
      target->catch_msg(QCTPNAME(caster) + " giant burning sphere of flames hits " +
                        "you extremely hard and leave you charred by flames.");
      caster->tell_watcher(QCTPNAME(caster) + " burning sphere of flames hits " +
                           QTNAME(target) + " extremely hard and leaves " +
                           QTNAME(target) + " charred by flames. ", target);
      break;
    default:
      caster->catch_msg("Your terrifying flaming globe of nature's fury hits " + QTNAME(target) + 
                        " with a tremendous force and leaves " + QTNAME(target) + 
                        " engulfed in flames!");
      target->catch_msg(QCTPNAME(caster) + " terrifying  flaming globe of nature's fury hits " +
                        "you with a tremendous force and leave you engulfed in flames!");
      caster->tell_watcher(QCTPNAME(caster) + " terrifying flaming globe of nature's fury hits " +
                           QTNAME(target) + " with a tremendous force and leaves " +
                           QTNAME(target) + " engulfed in flames! ", target);
      break;
    }

  
  caster->catch_msg("\n");
  target->catch_msg("\n");
  caster->tell_watcher("\n", target);
}

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
  int hurt;
  mixed *hitresult;

  caster->catch_msg("You extend your hands towards the sky to draw upon the " +
                     "nature's fury. Bright blue sparks shoot out from your " +
                     "fingertips as the swirling orb of purple sorceress fire " +
                     "takes form between your cupped hands. The air fills with " +
                     "the echoes of chilling laughter. With a quick snap of " +
                     "your wrists, you send your flaming globe of wrath " +
                     "in a rapid spiral dance towards the " + QTNAME(targets[0]) + " .\n");
  targets[0]->catch_msg(QCTNAME(caster)+ " extends " + caster->query_possessive()+ " hands " +
                     "towards the sky to draw upon the nature's fury. " +
                     "Bright blue sparks shoot out from " + caster->query_possessive() +
                     "fingertips as the swirling orb of purple sorceress fire " +
                     "takes form between the cupped hands. The air fills with " +
                     "the echoes of chilling laughter. With a quick snap of " +
                      caster->query_possessive() + " wrists, " + QCTNAME(caster) +
                     " sends the flaming globe of wrath in a rapid spiral dance towards you. ");
  caster->tell_watcher(QCTNAME(caster)+ " extends " + caster->query_possessive() + 
                     " hands towards the sky to draw upon the nature's fury. " +
                     "Bright blue sparks shoot out from " + caster->query_possessive() +
                     "fingertips as the swirling orb of purple sorceress fire " +
                     "takes form between " + caster->query_possessive()+ " cupped hands. " +
                     "The air fills with the echoes of chilling laughter. " +
                     "With a quick snap of " + caster->query_possessive() + " wrists, in " + 
                      QCTNAME(caster)+ " sends the flaming globe of wrath " + 
                     "a rapid spiral dance towards " + QTNAME(targets[0]) +  ".\n",targets[0]);
                       
  hurt = F_PENMOD(10, (caster->query_skill(SS_ELEMENT_FIRE) +
        caster->query_stat(SS_INT)) + 200 + random(100));
  hurt -= (100 - caster->query_skill(SS_SPELLCRAFT)) * hurt / 100;
  hurt -= hurt * targets[0]->query_magic_res(MAGIC_I_RES_FIRE) / 100;
  hurt -= hurt * targets[0]->query_magic_res(MAGIC_I_RES_MAGIC) / 100;
  
  hitresult = do_bolt_damage(caster, targets[0], hurt);
      
  desc_bolt_damage(caster, targets[0], hitresult);
  if (targets[0]->query_hp() <= 0)
     {
       targets[0]->do_die(caster);
     }
}


