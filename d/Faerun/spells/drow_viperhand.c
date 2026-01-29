/*
 * Viperhand spell for Sorcere Master, Midnight Feb 2004
 *
 */
inherit "/d/Genesis/newmagic/spells/bolt";

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <formulas.h>
#include "defs.h"
#include "/d/Faerun/defs.h"

#define MANA_COST 50
#define VIPER_BASE_PEN 50


public void
create_bolt()
{
  set_spell_time(8);
  set_spell_mana(MANA_COST);
  set_spell_task(TASK_ROUTINE);
  set_spell_form(SS_FORM_CONJURATION, 60);
  set_bolt_desc("drow_viperhand");
  set_spell_name("drow_viperhand");
  set_spell_desc("The wizard conjures a poisonous snake to replace his arm.");
}


void
desc_bolt_damage(object caster, object target, mixed *result)
{
  object poison;
  switch(result[0])
    {
    case 0:
      caster->catch_msg("You roar in frustration and shake your hand vigorously, " +
                        "wrathfully cursing the unexpected result.");
      target->catch_msg(QCTNAME(caster) + " roars in frustration and shakes " +
                        caster->query_possessive() + " hand vigorously, " +
                        "wrathfully cursing the unexpected result.");
      caster->tell_watcher(QCTNAME(caster) + " roars in frustration and shakes " +
                        caster->query_possessive() + " hand vigorously, " +
                        "wrathfully cursing the unexpected result.", target);
      break;
    case 1..3:
      caster->catch_msg("You thrust your hand towards " + QTNAME(target) + 
                        " and a small green snake rapidply grows out from " +
                        "your extended palm and coils back to quickly " +
                        "lash out to bite " + QTNAME(target) + ". ");
      target->catch_msg(QCTNAME(caster) + " thrusts " + caster->query_possessive() +
                        " hand towards you and a small green " +
                        "snake rapidly grows out from " + 
                        caster->query_possessive() + "extended palm " +
                        "and coils back to quickly lash out to bite " + 
                        "you.");
      caster->tell_watcher(QCTNAME(caster) + " thrusts " + caster->query_possessive() +
                        " hand towards " + QTNAME(target) + " and a small green " +
                        "snake rapidly grows out from " + 
                        caster->query_possessive() + "extended palm " +
                        "and coils back to quickly lash out to bite " + 
                        QTNAME(target) + ". ", target);
      break;
    case 4..6:
      caster->catch_msg("Your arm suddenly transformes into a large dark " +
                        "green snake which wriggles about and coils back to " +
                        "strike viciously at " + QTNAME(target) + ". " +
                        "The snake bites " + QTNAME(target) + " painfully.");
      target->catch_msg(QCTPNAME(caster) + " arm suddenly transformes " +
                        "into a large dark green snake which wriggles about " +
                        "and coils back to strike viciously at you. " +
                        "The snake bites you painfully.");
      caster->tell_watcher(QCTPNAME(caster) + " arm suddenly transformes " +
                        "into a large dark green snake which wriggles about " +
                        "and coils back to strike viciously at " + 
                         QTNAME(target) + ". " +
                        "The snake bites " + QTNAME(target) + " painfully.", target);
      break;
    case 7..9:
      caster->catch_msg("A terrifying poisonous green snake grows out as a " + 
                        "deadly extension of your arm. " +
                        "It moves with a tremendous speed against " +
                        QTNAME(target) + " and delivers a painful bite! ");
      target->catch_msg("A terrifying poisonous green snake grows out as a " + 
                        "deadly extension of " + QTPNAME(caster) + " arm. " +
                        "It moves with a tremendous speed against " +
                        "you and delivers a painful bite! ");
      caster->tell_watcher("A terrifying poisonous green snake grows out as a " + 
                        "deadly extension of " + QTPNAME(caster) + " arm. " +
                        "It moves with a tremendous speed against " +
                        QTNAME(target) + " and delivers a painful bite! ", target);
                        
      
      seteuid(getuid());
      poison = clone_object(P_FAERUN_SPELLS + "snake_poison");
      poison->move(target);
      poison->start_poison(target);
     
      break;
    case 10..12:      
      caster->catch_msg("You raise your hand upwards and scream victoriously when " + 
                        "your arm is transformed to a gigantic dark green snake! " +
                        "Your fiery red eyes turn bright green as the snake " + 
                        "coils back with a threatening hiss and looms over " +
                         QTNAME(target) + ", ready to deliver a deadly strike. " +
                        "Poison drips from its sharp fang as it sinks into " + 
                        QTNAME(target) + "'s skin. ");
      target->catch_msg(QCTNAME(caster) + " raises " + caster->query_possessive() +
                        " hand upwards and screams victoriously when " + 
                        caster->query_possessive() +  " arm is transformed to a " +
                        "gigantic dark green snake! " +
                        QCTPNAME(caster) + " fiery red eyes turn bright green " +
                        "as the snake coils back with a threatening hiss and looms " +
                        "over you, ready to deliver a deadly strike. " +
                        "Poison drips from its sharp fang as it sinks into " + 
                        "your skin. ");
      caster->tell_watcher(QCTNAME(caster) + " raises " + caster->query_possessive() +
                        " hand upwards and screams victoriously when " + 
                        caster->query_possessive() +  " arm is transformed to a " +
                        "gigantic dark green snake! " +
                        QCTPNAME(caster) + " fiery red eyes turn bright green " +
                        "as the snake coils back with a threatening hiss and looms " +
                        "over " + QTNAME(target) + ", ready to deliver a deadly strike. " +
                        " Poison drips from its sharp fang as it sinks into " + 
                        QTNAME(target) + "'s skin. ", target);
      seteuid(getuid());
      poison = clone_object(FAERUN_SPELLS + "snake_poison");
      poison->move(target);
      poison->start_poison(target);
      break;
    default:
      caster->catch_msg("You raise your hand upwards and scream victoriously when " + 
                        "your arm is transformed to a gigantic dark green snake! " +
                        "Your fiery red eyes turn bright green as the snake " + 
                        "coils back with a threatening hiss and looms over " +
                         QTNAME(target) + ", ready to deliver a deadly strike. " +
                        "Poison drips from its sharp fang as it sinks into " + 
                        QTPNAME(target) + " skin. ");
      target->catch_msg(QCTNAME(caster) + " raises " + caster->query_possessive() +
                        " hand upwards and screams victoriously when " + 
                        caster->query_possessive() +  "arm is transformed to a " +
                        "gigantic dark green snake! " +
                        QCTPNAME(caster) + " fiery red eyes turn bright green " +
                        "as the snake coils back with a threatening hiss and looms " +
                        "over you, ready to deliver a deadly strike. " +
                        "Poison drips from its sharp fang as it sinks into " + 
                        "your skin. ");
      caster->tell_watcher(QCTNAME(caster) + " raises " + caster->query_possessive() +
                        " hand upwards and screams victoriously when " + 
                        caster->query_possessive() +  "arm is transformed to a " +
                        "gigantic dark green snake! " +
                        QCTPNAME(caster) + " fiery red eyes turn bright green " +
                        "as the snake coils back with a threatening hiss and looms " +
                        "over " + QTNAME(target) + ", ready to deliver a deadly strike. " +
                        " Poison drips from its sharp fang as it sinks into " + 
                        QTPNAME(target) + " skin. ", target);
      seteuid(getuid());
      poison = clone_object(FAERUN_SPELLS + "snake_poison");
      poison->move(target);
      poison->start_poison(target);
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
  object poison;

  caster->catch_msg("With a vicious gleam in your eyes, you point at " +
                    QTNAME(targets[0]) + " while mumbling a powerful arcane " +
                    "chant. A loud hissing sound surrounding you grows stronger!\n");
  targets[0]->catch_msg("With a vicious gleam in " + caster->query_possessive()+ 
                     " eyes, " + QTNAME(caster) + " points at you" +
                     " while mumbling a powerful arcane chant. A loud hissing " +
                     "sound surrounding " + QTNAME(caster) + " grows stronger!\n");
  caster->tell_watcher("With a vicious gleam in " + caster->query_possessive()+ 
                     " eyes, " + QTNAME(caster) + " points at " + QTNAME(targets[0]) +
                     " while mumbling a powerful arcane chant. A loud hissing " +
                     "sound surrounding " + QTNAME(caster) + " grows stronger!\n",targets[0]);
                       
  hurt = F_PENMOD(10, (caster->query_skill(SS_FORM_CONJURATION) +
        caster->query_stat(SS_INT)) + random(50));
  hurt -= (100 - caster->query_skill(SS_SPELLCRAFT)) * hurt / 100;
  hurt -= hurt * targets[0]->query_magic_res(MAGIC_I_RES_POISON) / 100;
  hurt -= hurt * targets[0]->query_magic_res(MAGIC_I_RES_MAGIC) / 100;
  
 /* if (hurt <= 500) 
     {
      seteuid(getuid());
      poison = clone_object(P_FAERUN_SPELLS + "snake_poison");
      poison->move(targets[0]);
      poison->start_poison(targets[0]);
     }*/
  
  hitresult = do_bolt_damage(caster, targets[0], hurt);
      
  desc_bolt_damage(caster, targets[0], hitresult);
  
  if (targets[0]->query_hp() <= 0)
     {
       targets[0]->do_die(caster);
     }
}


    
