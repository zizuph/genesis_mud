/*
 *
 *  Constrict
 *
 *  For spell effect description, see doc/constrict.txt
 *
 *  Created May 2008, by Novo
 *
 *  Modifications:
 *  Lilith Jan 2008
 *   -Changed damage calc from relying on guild stat to using 'mentals' stats
 *
 */

#include "../guild.h";

inherit SPELL_DIR+"blood_spell";

#include <stdproperties.h>
#include <tasks.h>
#include <ss_types.h>
#include <language.h>
#include <macros.h>
#include <formulas.h>

public varargs int
config_spell(object caster, object *targets, string argument)
{
    if (::config_spell(caster,targets,argument))
        return 1;

    set_spell_name("constrict");
    set_spell_mana(36);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR, 60);
    set_spell_form(SS_FORM_CONJURATION, 60);

    set_blood_cost(2);
    
    set_min_guild_stat(80);
    
    set_spell_resist(spell_resist_basic);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    
    set_ability_target(target_one_other_present_living_or_enemy);

    set_spell_desc("Use telekinesis to crush a foe");
    
    return 0;
}


public void special_did_hit(int aid, string hdesc, int hid, 
                int phurt, object enemy, int dt,int phit, 
                int dam)
{
    string type;
    
    switch (phurt)
    {
        case 0..1:
            type="a slight tingling";
            break;
        case 2..3:
            type="a swift puslation";
            break;
        case 4..5:
            type="a slight unease";
            break;
        case 6..10:
            type="mild discomfort";
            break;
        case 11..20:
            type="perturbing discomfort";
            break;
        case 21..30:
            type="painful discomfort";
            break;
        case 31..40:
            type="abrupt ache";
            break;
        case 41..60:
            type="intense pain";
            break;
        case 61..80:
            type="atrocious pain";
            break;
        default:
            type="excruciating pain";              
            
    }

    TP->catch_msg("You picture the "+hdesc+ " of " + QTNAME(enemy) +
    " in your mind's eye and envision a crushing effect. You then sense "+
    type + " coming from "+OBJ(enemy)+".\n");

    object * watchers = WATCHERS(enemy) - ({ TP });
    
    watchers->catch_msg(QCTNAME(enemy)+" has an expression as on "+
    POSS(enemy) + " face as if "+ PRO(enemy)+
    " is undergoing some sort of internal trauma.\n");
    
    enemy->catch_msg("You feel a slight numbing in your "+hdesc+
    ", which grows into "+type+", as if you are under attack by "+
    "unseen forces.\n");
 
    if (enemy->query_hp()<=0)
    {
        enemy->catch_msg("You fall down in a crumpled heap.\n");
        watchers->catch_msg(QCTNAME(enemy) + " falls down in a crumpled "+
        "heap.\n");
        TP->catch_msg(QCTNAME(enemy) + " falls down in a crumpled "+
        "heap.\n");
        enemy->do_die(TP);
    }
    
}


public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    if (result==0)
    {
        write(query_ability_fail());
        return;
    }
    
    if (result>200)
        result=200;

    if (result<100)
        result=100;
    
    int pen=(caster->query_skill(SS_ELEMENT_AIR)+
    caster->query_skill(SS_FORM_CONJURATION))/2;

// This old formula with guild stat gave results higher than desired.
//    int damage=F_PENMOD(pen,result) * 
//        F_STR_FACTOR(caster->query_vamp_stat())/100;

    // New formula for damage calc
    int damage=F_PENMOD(pen,result) *
        F_STR_FACTOR((caster->query_stat(SS_INT) + caster->query_stat(SS_WIS))/2)/100;
    
    //Factor in resistance
    damage-=(damage * resist[0] / 100);
    
    mixed hitresult=targets[0]->hit_me(damage,MAGIC_DT,caster,-1);
    
    special_did_hit(-1, hitresult[1], hitresult[4], 
        hitresult[0], targets[0], MAGIC_DT, hitresult[2], 
        hitresult[3]);
    
}


/*
 * Function name: check_valid_action
 * Description:   Perform ability-specific checks
 * Arguments:     1. (object) The actor
 *                2. (mixed *) The targets
 *                3. (string) Arguments passed to the command
 *                4. (int) Actual spell execution
 * Returns:       (int) 1 if we can continue, 0 if failure
 */
static int check_valid_action(object actor,mixed * targets,string arg,int 
                                execute = 0)
{
    object diamond;
    if (!::check_valid_action(actor,targets,arg,execute))
    {
        return 0;
    }

    if (!(diamond=present("_swallowed_diamond",actor)))
    {
        actor->catch_tell("You do not have a focal diamond within "+
            "your body.\n");
        return 0;
    }
    if (execute)
    {
        diamond->reduce_charges();
    }
    return 1;
}
