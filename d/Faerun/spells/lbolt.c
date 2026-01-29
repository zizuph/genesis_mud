/*
 * Fireball for Karg priestess, Midnight Feb 2004
 * Reformatted code, Finwe 2017
 */
inherit "/d/Genesis/newmagic/spells/bolt";

#include "/d/Faerun/defs.h"
#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <formulas.h>

#define MANA_COST 50
#define FIREBALL_BASE_PEN 50
#define SPELL_NAME  "lightning bolt"

public void
create_bolt()
{
    set_spell_time(5);
    set_spell_mana(MANA_COST);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_FIRE, 60);
    set_spell_form(SS_FORM_CONJURATION, 40);
    set_bolt_desc("lightning bolt");
    set_spell_name("lbolt");
    set_spell_desc("Summon a lightning bolt.");
}


void
desc_bolt_damage(object caster, object target, mixed *result)
{
    string cast_msg;

    cast_msg =  QCTNAME(caster) + " extends " + HIS_HER(caster) + 
        " hands outwards. Energy gathers " + "between them, which begins " +
        "to glow and crackle. ";
//    target->catch_msg(QCTNAME(caster)+ " extends " + 
//        HIS_HER(caster) + " hands outwards. Energy gathers " +
//        "between them, which begins to glow and crackle. " + 
//        CAP(HE_SHE(caster)) + " turns to you and releases it.\n");
//    tell_watcher(QCTNAME(caster)+ " extends " + 
//        HIS_HER(caster) + " hands outwards. Energy gathers " +
//        "between them, which begins to glow and crackle. Suddenly, " + 
//        HE_SHE(caster) + " turns towards " + QTNAME(target) + 
//        " and releases it.\n");
        

    switch(result[0])
    {
        case 0:
            target->catch_msg(cast_msg + QCTPNAME(caster) + " weak " + 
                SPELL_NAME + " fizzles and dies out " + "before hitting you.");
            caster->tell_watcher(cast_msg + QCTPNAME(caster) + " weak " + 
                SPELL_NAME + " fizzles and dies " + "out before hitting " + 
                QTNAME(target) + ". ", target);
            break;
        case 1..3:
            target->catch_msg(cast_msg + QCTPNAME(caster) + " " + SPELL_NAME + 
                " barely grazes you.");
            caster->tell_watcher(cast_msg + QCTPNAME(caster) + " " + 
                SPELL_NAME + " barely grazes " + QTNAME(target) + ". ", target);
            break;
        case 4..6:
            target->catch_msg(cast_msg + QCTPNAME(caster) + " " + SPELL_NAME + 
                " hits you and burns you painfully.");
            caster->tell_watcher(cast_msg + QCTPNAME(caster) + " " + 
                SPELL_NAME + " hits " + QTNAME(target) + " and leaves an " +
                "ugly red burn.", target);
            break;
        case 7..9:
            target->catch_msg(cast_msg + QCTPNAME(caster) + " " + SPELL_NAME + 
                " slams right into your chest.");
            caster->tell_watcher(cast_msg + QCTPNAME(caster) + " " + 
                SPELL_NAME + " slams into " + QTNAME(target) + ".", target);
            break;
        case 10..12:      
            target->catch_msg(cast_msg + QCTPNAME(caster) + " " + SPELL_NAME + 
                " hits you extremely hard and leaves you charred.");
            caster->tell_watcher(cast_msg + QCTPNAME(caster) + " " + 
                SPELL_NAME + " hits " + QTNAME(target) + " extremely hard " +
                "and leaves " + QTNAME(target) + " a charred form. ", target);
            break;
        default:
            target->catch_msg(cast_msg + QCTPNAME(caster) + " terrifying " + 
                SPELL_NAME + " hits you with a tremendous force and leaves " +
                "you engulfed in wisps of energy!");
            caster->tell_watcher(cast_msg + QCTPNAME(caster) + " terrifying " + 
                SPELL_NAME + " hits " + QTNAME(target) + " with a " +
                    "tremendous force and leaves " + QTNAME(target) + 
                    " engulfed in wisps of energy! ", target);
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
//    caster->catch_msg("You extend your hands out before. Energy gathers " +
//        "between them and begins to glow and crackle. You release the " +
//        "energy and direct it at " + QTNAME(targets[0]) + " .\n");
//    targets[0]->catch_msg(QCTNAME(caster)+ " extends " + 
//        HIS_HER(caster) + " hands outwards. Energy gathers " +
//        "between them, which begins to glow and crackle. " + 
//        CAP(HE_SHE(caster)) + " turns to you and releases it.\n");
//    caster->tell_watcher(QCTNAME(caster)+ " extends " + 
//        HIS_HER(caster) + " hands outwards. Energy gathers " +
//        "between them, which begins to glow and crackle. Suddenly, " + 
//        HE_SHE(caster) + " turns towards you and releases it.\n");
//        
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

