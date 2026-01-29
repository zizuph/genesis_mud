/*
 * Spiderweb spell for the Masters of Sorcere
 * Midnight march 2004
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
#define SPIDERWEB_BASE_PEN 40

public void
create_bolt()
{
  set_spell_time(5);
  set_spell_mana(MANA_COST);
  set_spell_task(TASK_ROUTINE);
  set_spell_element(SS_ELEMENT_AIR, 55);
  set_spell_form(SS_FORM_CONJURATION, 45);
  set_bolt_desc("spiderweb");
  set_spell_name("spiderweb");
  set_spell_desc("Conjures a sticky spiderweb, which prevent " +
                 "the target from moving.");
}

void
desc_bolt_damage(object caster, object target, mixed *result)
{
  object web;
  switch(result[0])
    {
    case 0:
      caster->catch_msg("You roar in frustration and clench your fist in anger, " +
                        "wrathfully cursing the unexpected result.");
      target->catch_msg(QCTNAME(caster) + " roars in frustration and clenches " +
                        caster->query_possessive() + " fist in anger, " +
                        "wrathfully cursing the unexpected result.");
      caster->tell_watcher(QCTNAME(caster) + " roars in frustration and clenches " +
                        caster->query_possessive() + " fist in anger, " +
                        "wrathfully cursing the unexpected result.", target);
      break;
    case 1..3:
      caster->catch_msg("You thrust your hand towards " + QTNAME(target) + 
                        " and a small sticky spiderweb shoots out " +
                        "to slam into " + QTNAME(target) + " and cover " +
                        QTNAME(target) + " with it's sticky mass. " +
                        "However, " + QTNAME(target) + " manages to break free " +
                        " at once.");
      target->catch_msg(QCTNAME(caster) + " thrusts " + caster->query_possessive() +
                        " hand towards you and a small sticky spiderweb shoots out " +
                        "to slam into you and cover you with it's sticky mass. " + 
                        "However, you manage to break free at once. ");
      caster->tell_watcher(QCTNAME(caster) + " thrusts " + caster->query_possessive() +
                        " hand towards " + QTNAME(target) + " and a small sticky " +
                        "spiderweb shoots out to slam into " + QTNAME(target) +
                        " and cover " + QTNAME(target) + " with it's sticky mass. " +
                        "However, " + QTNAME(target) + "manages to break free at " +
                        "once. ", target);
      break;
    case 4..6:
      caster->catch_msg("A large glistening black spiderweb shoots out from " +
                        "your extended hand and flies with an impressive speed " +
                        "at " + QTNAME(target) + "! " +
                        QTNAME(target) + " is covered with it's sticky mass, but " +
                        "succeeds in tearing through the sticky web.");
      target->catch_msg("A large glistening black spiderweb shoots out from "  +
                        QTPNAME(caster) + " extended hand and flies with an " +
                        "impressive speed towards you! " +
                        "You are covered with it's sticky mass, but you succeed " +
                        "in tearing through the sticky web.");
      caster->tell_watcher("A large glistening black spiderweb shoots out from "  +
                        QTPNAME(caster) + " extended hand and flies with an " +
                        "impressive speed towards " +  QTNAME(target) + "! " +
                        QTNAME(target) + " is covered with it's sticky mass, but " +
                        "succeeds in tearing through the sticky web.", target);
      break;
    case 7..9:
      caster->catch_msg("A strong enourmous spiderweb shoots out from your " + 
                        "crooked fingers. The sticky web is covered with " +
                        "crawling fast moving dark, red spiders. The web " +
                        "envelops " + QTNAME(target) + " completely! ");
      target->catch_msg("A strong enourmous spiderweb shoots out from " + 
                        QTPNAME(caster) + " crooked fingers. The sticky " +
                        "web is covered with crawling fast moving dark, red " +
                        "spiders. The web envelops you completely! ");
      caster->tell_watcher("A strong enourmous spiderweb shoots out from " + 
                           QTPNAME(caster) + " crooked fingers. The sticky " +
                           "web is covered with crawling fast moving dark, red " +
                           "spiders. The web envelops " + QTNAME(target) + 
                           " completely! ", target);
                        
      setuid();
      seteuid(getuid());
      web = clone_object(FAERUN_SPELLS + "stun");
      web->set_restrict_movement(1);
      web->move(target);
      web->stun_player(20);
                        
     
      break;
    case 10..12:      
      caster->catch_msg("You raise your hand upwards and scream victoriously when " + 
                        "a gigantic glistening spiderweb shoots out from your hand! " +
                        QTNAME(target) + " is completely covered in the sticky mass, " +
                        "which moves with a life of its own. Thousands of spiders " + 
                        "quickly mend every hole " + QTNAME(target) + " tries " +
                        "to make in the sticky web. ");
      target->catch_msg(QCTNAME(caster) + " raises " + caster->query_possessive() +
                        " hand upwards and screams victoriously when " + 
                        "a gigantic glistening spiderweb shoots out from " +
                        caster->query_possessive() +  " hand! " +
                        "You are completely covered in the sticky mass, " +
                        "which moves with a life of its own. Thousands of spiders " + 
                        "quickly mend every hole you try " +
                        "to make in the sticky web. ");
      caster->tell_watcher(QCTNAME(caster) + " raises " + caster->query_possessive() +
                        " hand upwards and screams victoriously when " + 
                        "a gigantic glistening spiderweb shoots out from " +
                        caster->query_possessive() +  " hand! " +
                        QTNAME(target) + " is completely covered in the sticky mass, " +
                        "which moves with a life of its own. Thousands of spiders " + 
                        "quickly mend every hole " + QTNAME(target) + " tries " +
                        "to make in the sticky web.", target);
                        
      setuid();
      seteuid(getuid());
      web = clone_object(FAERUN_SPELLS + "stun");
      web->set_restrict_movement(1);
      web->move(target);
      web->stun_player(30);
      
    default:
      caster->catch_msg("You raise your hand upwards and scream victoriously when " + 
                        "a gigantic glistening spiderweb shoots out from your hand! " +
                        QTNAME(target) + " is completely covered in the sticky mass, " +
                        "which moves with a life of its own. Thousands of spiders " + 
                        "quickly mend every hole " + QTNAME(target) + " tries " +
                        "to make in the sticky web. ");
      target->catch_msg(QCTNAME(caster) + " raises " + caster->query_possessive() +
                        " hand upwards and screams victoriously when " + 
                        "a gigantic glistening spiderweb shoots out from " +
                        caster->query_possessive() +  " hand! " +
                        "You are completely covered in the sticky mass, " +
                        "which moves with a life of its own. Thousands of spiders " + 
                        "quickly mend every hole you try " +
                        "to make in the sticky web. ");
      caster->tell_watcher(QCTNAME(caster) + " raises " + caster->query_possessive() +
                        " hand upwards and screams victoriously when " + 
                        "a gigantic glistening spiderweb shoots out from " +
                        caster->query_possessive() +  " hand! " +
                        QTNAME(target) + " is completely covered in the sticky mass, " +
                        "which moves with a life of its own. Thousands of spiders " + 
                        "quickly mend every hole " + QTNAME(target) + " tries " +
                        "to make in the sticky web.", target);
      setuid();
      seteuid(getuid());
      web = clone_object(FAERUN_SPELLS + "stun");
      web->set_restrict_movement(1);
      web->move(target);
      web->stun_player(30);
      
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
                    "chant. An evil cackle echoes through the room!\n");
  targets[0]->catch_msg("With a vicious gleam in " + caster->query_possessive()+ 
                     " eyes, " + QTNAME(caster) + " points at you" +
                     " while mumbling a powerful arcane chant. An evil cackle " +
                     "echoes through the room!\n");
  caster->tell_watcher("With a vicious gleam in " + caster->query_possessive()+ 
                     " eyes, " + QTNAME(caster) + " points at " + QTNAME(targets[0]) +
                     " while mumbling a powerful arcane chant. An evil cackle " +
                     "echoes through the room!\n",targets[0]);
                       
  hurt = F_PENMOD(10, (caster->query_skill(SS_FORM_CONJURATION) +
        caster->query_stat(SS_INT)));
  hurt -= (100 - caster->query_skill(SS_SPELLCRAFT)) * hurt / 100;
  hurt -= hurt * targets[0]->query_magic_res(MAGIC_I_RES_MAGIC) / 100;
  
  
  hitresult = do_bolt_damage(caster, targets[0], hurt);
      
  desc_bolt_damage(caster, targets[0], hitresult);
  
  if (targets[0]->query_hp() <= 0)
     {
       targets[0]->do_die(caster);
     }
}