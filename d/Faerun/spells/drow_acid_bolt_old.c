/*
 *  faerun/underdark/upper/menzo/sorcere/obj/acid_bolt.c
 *
 *  An Acid Bolt spell used by drows in Underdark
 *
 *  Created by Midnight, 18-2-2004
 */


inherit "/d/Genesis/newmagic/spells/bolt";

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>

#define MANA_COST 50
#define ACIDBOLT_BASE_PEN 50


public void
create_bolt()
{
  set_spell_time(5);
  set_spell_mana(MANA_COST);
  set_spell_task(TASK_ROUTINE);
  set_spell_element(SS_ELEMENT_WATER, 60);
  set_spell_form(SS_FORM_CONJURATION, 40);
  set_bolt_desc("acidbolt");
  set_spell_name("acidbolt");
  set_spell_desc("Summon an acid bolt directed at target, " +
                 "splashes hit nearby people.");
}


void
desc_bolt_damage(object caster, object target, mixed *result)
{

  switch(result[0])
    {
    case 0:
      caster->catch_msg("Your thin stream of acid does not reach " 
                        + QTNAME(target) + ". ");
      target->catch_msg(QCTPNAME(caster) + " thin stream of acid " +
                        "does not reach you.");
      caster->tell_watcher(QCTPNAME(caster) + " thin stream of " +
                          "acid does not reach " + 
                          QTNAME(target) + ". ", target);
      break;
    case 1..3:
      caster->catch_msg("Your stream of acid forms a shimmering sphere in " +
                        "front of "  + QTNAME(target) + ". It starts " +
                        "spinning in rapid circular motions and a deep humming " +
                        "noice can he heard from within the sphere of acid, " +
                        "just before it bursts into a vicious cascade of acid. " +
                        "Drops of acid covers " + QTNAME(target) + ". ");
      target->catch_msg("The stream of acid forms a shimmering sphere of " +
                        "acid in front of you, It starts spinning in rapid " +
                        "circular motions and a deep humming noice can be heard " +
                        "from within the sphere of acid, just before it bursts " +
                        "into a vicious cascade of acid. Drops of acid covers you .");
      caster->tell_watcher("The stream of acid forms a shimmering sphere of " +
                           "acid in front of  " + QTNAME(target) + ". It " +
                           "starts spinning in rapid circular motions and a deep " +
                           "humming noice can he heard from within the sphere " +
                           "of acid, just before it bursts into a vicious " +
                           "cascade of acid. Drops of acid covers " +
                           QTNAME(target) + ". ", target);
      break;
    case 4..6:
      caster->catch_msg("The steady stream of acid forms a large " +
                        "shimmering sphere around " + QTNAME(target) + 
                        ". The sphere expands visibly and starts spinning " +
                        "rapidly to envelop " + QTNAME(target) + " in an " +
                        "enormous globe of shimmering death. " +
                        "It start to pulse violently with a deep humming " +
                        "sound just before exploding with a brutal force " +
                        "to cover " + QTNAME(target) + " with a shower of " +
                        "acid fluid. " + QTNAME(target) + " is drenched in acid.");
      target->catch_msg("The steady stream of acid forms a large " +
                        "shimmering sphere of acid around you. The sphere " + 
                        "expands visibly and starts spinning rapidly to " +
                        "envelop you in an enormous globe of shimmering " +
                        "death. It start to pulse violently with " +
                        "a deep humming sound just before exploding " +
                        "with a brutal force to cover you with a shower of " +
                        "acid fluid. You are drenched in acid.");
      caster->tell_watcher("The steady stream of acid forms a large " +
                        "shimmering sphere of acid around " + QTNAME(target) +  
                        "and a. The sphere expands visibly and starts spinning " +
                        "rapidly to envelop " + QTNAME(target) + " in an " +
                        "enormous globe of shimmering death. " +
                        "It start to pulse violently with a deep humming " +
                        "sound just before exploding with a brutal force " +
                        "to cover " + QTNAME(target) + " with a shower of " +
                        "acid fluid. " + QTNAME(target) + 
                        " is drenched in acid.", target);
      break;
    case 7..9:
      caster->catch_msg("Your powerful stream of acid hits " + 
                        QTNAME(target) + " with a tremendous force " +
                        "and the momentum of the acid stream forms an " +
                        "impressive swirling sphere of acid, which " +
                        "envelops " + QTNAME(target) + "completely. " +
                        "The impressive spehere starts spinning around " +
                        QTNAME(target) + " with an incredible speed. A deep"  +  
                        "humming noice is built up to a deafening roar from " +
                        "within the spere before it explodes with a grand force. " +
                        QTNAME(target) + " is covered by a thick sizzling " +
                        "layer of acid.");
      target->catch_msg("The powerful stream of acid hits " + 
                        "you with a tremendous force " +
                        "and the momentum of the acid stream forms an " +
                        "impressive swirling sphere of acid, which " +
                        "envelops you completely. " +
                        "The impressive spehere starts spinning around " +
                        "you with an incredible speed. A deep"  +  
                        "humming noice is built up to a deafening roar from " +
                        "within the spere before it explodes with a grand force. " +
                        "You are covered by a thick sizzling " +
                        "layer of acid.");
      caster->tell_watcher("The powerful stream of acid hits " + 
                        QTNAME(target) + " with a tremendous force " +
                        "and the momentum of the acid stream forms an " +
                        "impressive swirling sphere of acid, which " +
                        "envelops " + QTNAME(target) + "completely. " +
                        "The impressive spehere starts spinning around " +
                        QTNAME(target) + " with an incredible speed. A deep"  +  
                        "humming noice is built up to a deafening roar from " +
                        "within the spere before it explodes with a grand force. " +
                        QTNAME(target) + " is covered by a thick sizzling " +
                        "layer of acid.", target);
      break;
    case 10..12:      
      caster->catch_msg("Your terrifying stream of shimmering acid slams " +
                        "into " + QTNAME(target) + " and forms " +
                        "a magnificent globe of sizzling acid. " + QTNAME(target) + 
                        "is completely swallowed up by the terrible globe of " +
                        "death. You hear his terrified screams from within " +
                        "the globe, but the scream is soon transformed to " +
                        "and eerie deep humming sound which grows stronger " +
                        "and stronger until it's all that can be heard. " +
                        "Suddenly the acid globe explodes with an incredible " +
                        "force and " + QTNAME(target) + 
                        " is soaked in deadly amounts of acid.");
      target->catch_msg("The terrifying stream of shimmering acid slams " +
                        "into you and forms " +
                        "a magnificent globe of sizzling acid. You " + 
                        "are completely swallowed up by the terrible globe of " +
                        "death. You hear your own terrified scream when " +
                        "the globe closes completely about you, but the scream " +
                        "is soon drenched by eerie deep humming sound which grows " +
                        "stronger and stronger until it's all that can be heard. " +
                        "Suddenly the acid globe explodes with an incredible " +
                        "force and you are soaked in deadly amounts of acid.");
      caster->tell_watcher("The terrifying stream of shimmering acid slams " +
                        "into " + QTNAME(target) + " and forms " +
                        "a magnificent globe of sizzling acid. " + QTNAME(target) + 
                        "is completely swallowed up by the terrible globe of " +
                        "death. You hear his terrified screams from within " +
                        "the globe, but the scream is soon transformed to " +
                        "and eerie deep humming sound which grows stronger " +
                        "and stronger until it's all that can be heard. " +
                        "Suddenly the acid globe explodes with an incredible " +
                        "force and " + QTNAME(target) + 
                        " is soaked in deadly amounts of acid.", target);
      break;
    default:
      caster->catch_msg("Your terrifying stream of shimmering acid slams " +
                        "into " + QTNAME(target) + " and forms " +
                        "a magnificent globe of sizzling acid. " + QTNAME(target) + 
                        "is completely swallowed up by the terrible globe of " +
                        "death. You hear his terrified screams from within " +
                        "the globe, but the scream is soon transformed to " +
                        "and eerie deep humming sound which grows stronger " +
                        "and stronger until it's all that can be heard. " +
                        "Suddenly the acid globe explodes with an incredible " +
                        "force and " + QTNAME(target) + 
                        " is soaked in deadly amounts of acid.");
      target->catch_msg("The terrifying stream of shimmering acid slams " +
                        "into you and forms " +
                        "a magnificent globe of sizzling acid. You " + 
                        "are completely swallowed up by the terrible globe of " +
                        "death. You hear your own terrified scream when " +
                        "the globe closes completely about you, but the scream " +
                        "is soon drenched by eerie deep humming sound which grows " +
                        "stronger and stronger until it's all that can be heard. " +
                        "Suddenly the acid globe explodes with an incredible " +
                        "force and you are soaked in deadly amounts of acid.");
      caster->tell_watcher("The terrifying stream of shimmering acid slams " +
                        "into " + QTNAME(target) + " and forms " +
                        "a magnificent globe of sizzling acid. " + QTNAME(target) + 
                        "is completely swallowed up by the terrible globe of " +
                        "death. You hear his terrified screams from within " +
                        "the globe, but the scream is soon transformed to " +
                        "and eerie deep humming sound which grows stronger " +
                        "and stronger until it's all that can be heard. " +
                        "Suddenly the acid globe explodes with an incredible " +
                        "force and " + QTNAME(target) + 
                        " is soaked in deadly amounts of acid.", target);
      break;
    }

  
  caster->catch_msg("\n");
  target->catch_msg("\n");
  caster->tell_watcher("\n", target);
}
/*
public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
  int hurt;
  mixed *hitresult;
  object *obs;

  caster->catch_msg( "You chant some ancient arcane words and draw a " +
                     "drowish rune in the air with one finger and " +
                     "with a fluid motion you let your closed hand " +
                     "continue towards " + QTNAME(targets[0]) +
                     ". Your eyes burn with a rage of a thousand fires " +
                     "when you with a final chant open up your hand " +
                     "and create a continuous straight stream of shimmering " +
                     "liquid which emerges from your palm.\n");
  targets[0]->catch_msg(QCTNAME(caster)+ " chants some ancient arcane words " +
                     "and draw a drowish rune in the air with one finger and " + 
                     "with a fluid motion " + QCTNAME(caster) + " lets " +
                     caster->query_possessive()+ " closed hand continue towards " +
                     "you. " + caster->query_possessive() + " eyes burn with " +
                     "a rage of a thousand fires when " + QCTNAME(caster) + 
                     "with a final chant open up " + caster->query_possessive() +
                     " hand and creates a continuous straight stream of shimmering " +
                     "liquid which emerges from "  + caster->query_possessive() +
                     " palm.\n");
  caster->tell_watcher(QCTNAME(caster)+ " chants some ancient arcane words " +
                     "and draw a drowish rune in the air with one finger and " + 
                     "with a fluid motion " + QCTNAME(caster) + "lets " +
                     caster->query_possessive()+ " closed hand continue towards " +
                     QTNAME(targets[0]) + ". " + caster->query_possessive() + 
                     " eyes burn with a rage of a thousand fires when " 
                     + QCTNAME(caster) +  " with a final chant open up " 
                     + caster->query_possessive() + " hand and creates a " +
                     "continuous straight stream of shimmering " +
                     "liquid which emerges from "  + caster->query_possessive() +
                     " palm.\n",targets[0]);
                       
  hurt = F_PENMOD(10, (caster->query_skill(SS_ELEMENT_FIRE) +
        caster->query_stat(SS_INT)) + 200 + random(100));
  hurt -= (100 - caster->query_skill(SS_SPELLCRAFT)) * hurt / 100;
  hurt -= hurt * targets[0]->query_magic_res(MAGIC_I_RES_ACID) / 100;
  hurt -= hurt * targets[0]->query_magic_res(MAGIC_I_RES_MAGIC) / 100;
  
  hitresult = do_bolt_damage(caster, targets[0], hurt);
  
  if hurt<100
     {
     // Splashes of the acid bolt hurts the people nearby
     obs = FILTER_LIVE(all_inventory(environment(this_object() ) ) );
     obs->catch_msg("You are struck by slashes from the explosion of the " +
                    "acid sphere and it sizzles painfully on your skin.\n");
     hurt = -100;               
     hurt = hurt + (hurt * obs->query_magic_res(MAGIC_I_RES_ACID) / 100);               
     obs->add_hp(hurt);
     }

  desc_bolt_damage(caster, targets[0], hitresult);
  if (targets[0]->query_hp() <= 0)
     {
       targets[0]->do_die(caster);
     }
}
*/

/*
 * Function name: desc_bolt_cast
 * Description:   Describe casting of the spell, not including damage messages.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_bolt_cast(object caster, object *targets)
{
  caster->catch_msg( "You chant some ancient arcane words and draw a " +
                     "drowish rune in the air with one finger and " +
                     "with a fluid motion you let your closed hand " +
                     "continue towards " + QTNAME(targets[0]) +
                     ". Your eyes burn with a rage of a thousand fires " +
                     "when you with a final chant open up your hand " +
                     "and create a continuous straight stream of shimmering " +
                     "liquid which emerges from your palm.\n");
  targets[0]->catch_msg(QCTNAME(caster)+ " chants some ancient arcane words " +
                     "and draw a drowish rune in the air with one finger and " + 
                     "with a fluid motion " + QCTNAME(caster) + " lets " +
                     caster->query_possessive()+ " closed hand continue towards " +
                     "you. " + caster->query_possessive() + " eyes burn with " +
                     "a rage of a thousand fires when " + QCTNAME(caster) + 
                     "with a final chant open up " + caster->query_possessive() +
                     " hand and creates a continuous straight stream of shimmering " +
                     "liquid which emerges from "  + caster->query_possessive() +
                     " palm.\n");
  caster->tell_watcher(QCTNAME(caster)+ " chants some ancient arcane words " +
                     "and draw a drowish rune in the air with one finger and " + 
                     "with a fluid motion " + QCTNAME(caster) + "lets " +
                     caster->query_possessive()+ " closed hand continue towards " +
                     QTNAME(targets[0]) + ". " + caster->query_possessive() + 
                     " eyes burn with a rage of a thousand fires when " 
                     + QCTNAME(caster) +  " with a final chant open up " 
                     + caster->query_possessive() + " hand and creates a " +
                     "continuous straight stream of shimmering " +
                     "liquid which emerges from "  + caster->query_possessive() +
                     " palm.\n",targets[0]);

}