#include "spells.h"
#include <composite.h>
#include <macros.h>
#include <formulas.h>
#include <ss_types.h>
#include <tasks.h>
#include <wa_types.h>
#include "/std/combat/combat.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "obj/morgul_corpse.h"

#define HIS(x)  (x)->query_possessive()
#define NAME(x) (x->query_npc() ? file_name(x) : x->query_cap_name())
#define GENESIS_BALANCE_RESIST "/d/Genesis/specials/resist"

inherit SPELL_INHERIT;

#include "/d/Genesis/specials/debugger/debugger_tell.h"

static int bolt_pen;
static string bolt_desc;

public void set_bolt_pen(int pen);
public void set_bolt_desc(string desc);
void desc_bolt_damage(object caster, object target, mixed *result);
void desc_bolt_cast(object caster, object *targets);
int calculate_thunaur_pen(object caster);
public mixed *do_bolt_damage(object caster, object target, int pen);
public void desc_bolt_miss(object caster, object target);
public int try_to_hit(object caster, object target);
public int spell_resist_thunaur(object caster, object target, int element, int difficulty);

public int
query_spell_pretarget()
{
    return 0;
}

void
hook_targets_gone()
{
    write("Unable to focus Thunaur at anything you send it at void.\n");
}

/*
 * Function name: set_bolt_pen
 * Description:   Set the "pen" for the attack.  Damage is calculated
 *                from this value.
 * Arguments:     int pen - the pen value
 */
public void
set_bolt_pen(int pen)
{
    bolt_pen = pen;
}

/*
 * Function name: set_bolt_desc
 * Description:   Set the description or type of the bolt (ice, water,
 *                fire, etc.)
 * Arguments:     string desc - the bolt description
 */
public void
set_bolt_desc(string desc)
{
    bolt_desc = desc;
    set_spell_name(desc+ "bolt");
    set_spell_desc("Shoot a bolt of "+ desc+ " at a target.");
}

void
desc_bolt_damage(object caster, object target, mixed *result)
{
 string flame, how;

    switch (result[0])
    {
    case -1..5:
        how = "lick";
        break;
    case 6..15:
        how = "scorch";
        break;
    case 16..30:
        how = "burn";
        break;
    case 31..50:
        how = "wither";
        break;
    case 51..90:
        how = "shrivel";
        break;
    default:
        how = "consume";
        break;
    }
    if (result[3] >= 600)
    {
        flame = "fierce white-hot flames";
    }
    else
    {
        flame = "fierce flames";
    }
    caster->catch_tell("You inhale deeply and then spout forth "+
        flame+ " from your mouth. The flames "+ how+ " "+
        target->query_the_name(caster)+ ".\n");
    target->catch_tell(caster->query_The_name(target)+ " inhales "+
        "deeply and then spouts forth "+ flame+ " from "+ HIS(caster)+
        " mouth. The flames "+ how+ " you.\n");
    caster->tell_watcher(QCTNAME(caster)+ " inhales deeply and then "+
        "spouts forth "+ flame+ " from "+ HIS(caster)+ " mouth. The "+
        "flames "+ how+ " "+ QTNAME(target)+ ".\n", target);

    log_spell("thunaur", caster->query_name()+ " creates a "+ bolt_pen+
        " pen bolt, which did " + result[3] + " damage to "+
        NAME(target));
    if (!(target->query_npc()))
    {
        log_spell("thunaur", caster->query_name()+ " creates a "+ bolt_pen+
            " pen bolt, which did "+ result[3]+ " damage to "+
            target->query_cap_name());
    }
    IDLENESS->increase_activity(caster, COMBAT_SPELL);
}

void desc_bolt_cast(object caster, object *targets)
{
    caster->catch_tell(one_of_list( ({
        "With the power the Dark Lord has bestowed upon you, you call the Firebreath!\n",
        "With the power of the Dark Lord flowing through you, you call the Firebreath!\n",
        "The power of the Black Master courses through you as you call the Firebreath!\n",
        }) ) );

}

int calculate_thunaur_pen(object caster)
{
    return F_PENMOD(100+ random(26),
        caster->query_skill(SS_ELEMENT_FIRE)+
        caster->query_skill(SS_FORM_CONJURATION)+
        caster->query_stat(SS_OCCUP));
}

public mixed *do_bolt_damage(object caster, object target, int pen)
{
 int ran, i, j, hit, *hloc_ids, ac;
 object cob;
 mixed *hloc;

    /* Pick a hitlocation and apply armour mod to pen */
    ran = random(100);

    cob = target->query_combat_object();
    hloc_ids = cob->query_hitloc_id();
    hit = -1;
    j = 0;
    
    for (i = 0; i < sizeof(hloc_ids); i++)
    {
        hloc = cob->query_hitloc(hloc_ids[i]);
    
        j += hloc[HIT_PHIT];
        if (j >= ran)
        {
            hit = hloc_ids[i];
            ac = (intp(hloc[HIT_AC]) ? 
                hloc[HIT_AC] : hloc[HIT_AC][random(sizeof(hloc[HIT_AC]))]);
            pen -= random(ac / 2);
            break;
        }
    }

    return target->hit_me(pen, MAGIC_DT, caster, hit);
}

/*
 * Function name: desc_bolt_miss
 * Description:   Write out some text describing the missed attack.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_bolt_miss(object caster, object target)
{
    string bolt = "The bolt of "+ bolt_desc+ " misses ";

    target->catch_tell(bolt+ "you.\n");
    caster->catch_tell(bolt+ target->query_the_name(caster)+ ".\n");
    caster->tell_watcher_miss(bolt+ QCTNAME(target)+ ".\n", target);
}


public int
try_to_hit(object caster, object target)
{

    return (target->resolve_task(TASK_FORMIDABLE, ({TS_DEX, SS_DEFENSE}),
    caster, ({SKILL_AVG, TS_INT, TS_WIS, SKILL_END, SS_FORM_CONJURATION}))
      < 0);
}


/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
 object corpse_sh;
 int i, magic_attack;
 mixed *hitresult;

    if (targets[0]->id("_Morgul_Sulambar_Cloud"))
    {
        caster->catch_tell("You send a wide cone of fire aiming at the "+
            targets[0]->short()+ ".\n");
        tell_room(environment(caster), QCTNAME(caster)+ " sends a "+
            "wide cone of fire aiming at the "+ targets[0]->short()+ ".\n",
            caster);
        targets[0]->dispel_spell_effect(caster);
        return;
    }
    desc_bolt_cast(caster, targets);

    for (i=0;i<sizeof(targets);i++)
    {
        if (!try_to_hit(caster, targets[i]))
        {
            desc_bolt_miss(caster, targets[i]);
            continue;
        }

        magic_attack = bolt_pen- bolt_pen* resist[i]/ 100;
        if (bolt_pen != magic_attack)
        {
            send_debug_message("thunaur", capitalize(caster->query_real_name())
                + " casting thunaur with original bolt pen of " + bolt_pen
                + " changed to " + magic_attack + " from resistance.");
        }
        else
        {
            send_debug_message("thunaur", capitalize(caster->query_real_name())
                + " casting thunaur with bolt pen of " + bolt_pen);
        }
        
        hitresult = do_bolt_damage(caster, targets[i], magic_attack);

        desc_bolt_damage(caster, targets[i], hitresult);

        if (targets[i]->query_hp() <= 0)
        {
            if (random(100) < 50)
            {
                targets[0]->catch_tell("You become a living torch!\n");
                tell_room(environment(targets[0]), QCTNAME(targets[0])+
                    " becomes a living torch!\n", targets[0],
                    this_object());
                targets[0]->command("$scream");
                targets[0]->run_away();
            }
            corpse_sh = clone_object(MORGUL_DEATH_SHADOW);
            corpse_sh->shadow_me(targets[0]);
            corpse_sh->set_death_cause(THUNAUR_CS);
            corpse_sh->set_death_variant(random(THUNAUR_VR));
            targets[0]->do_die(caster);
            corpse_sh->remove_shadow();
        }
    }
}

int
config_spell(object caster, object *targets, string arg)
{
    set_bolt_desc("fire");
    set_spell_name("thunaur");
    set_spell_desc("Flames of Destruction.");
    set_spell_target(my_spell_target_one_valid_enemy);

    /*The spell is not being configured for   *
     *a casting attempt, and therefore should *
     *not return 1                            */
    if (!objectp(caster))
    {
        return 0;
    }
    set_free_hands(0);

    /*Special configuration for morgul npcs.  */
    if (caster->query_npc())
    {
        set_spell_stationary(0);
        set_spell_time(spell_resolve_time(caster->query_stat(SS_OCCUP),
            3, 12));
        set_spell_mana(85);
        set_spell_task(TASK_SIMPLE);
           set_spell_element(SS_ELEMENT_FIRE, 40);
        set_spell_form(SS_FORM_CONJURATION, 70);
        bolt_pen = calculate_thunaur_pen(caster);
        set_spell_ingredients(0);
        set_spell_offensive(1);
        set_spell_resist(spell_resist_thunaur);
        set_spell_resist_task(TASK_EXACTING);
        set_spell_visual(0);
        set_spell_vocal(0);
        return 0;
    }

    if (!default_morgul_spell_setup(caster))
    {
        return 1;
    }
    set_spell_time( max(spell_resolve_time(caster->query_stat(SS_OCCUP),
        3, 12), COMBAT_SPELL_I_MIN_PREP_TIME) );
    set_spell_mana(85);
    set_spell_task(TASK_SIMPLE + 150);
    set_spell_element(SS_ELEMENT_FIRE, 40);
    set_spell_form(SS_FORM_CONJURATION, 70);
    set_spell_visual(0);
    set_spell_vocal(0);
    bolt_pen = calculate_thunaur_pen(caster);
    if (caster->query_wiz_level())
    {
        set_spell_ingredients(0);
    }
    else
    {
        set_spell_ingredients(({ "leftover", "thunaur_ingr2" }));
    }
    set_spell_offensive(1);
    set_spell_resist(spell_resist_thunaur);
    set_spell_resist_task(TASK_EXACTING);
}

/*
 * Function:    spell_resist_thunaur
 * Description: This is the resistance function for the thunaur spell.
 *              It checks both fire resistance and death resistance. It
 *              also uses the Genesis Balance approved resistance function
 *              which takes into account the player's inherent ability to
 *              resist.
 */
public int 
spell_resist_thunaur(object caster, object target, int element, int difficulty)
{
    int * resistances = ({ SS_ELEMENT_FIRE, SS_ELEMENT_DEATH });
    if (!IN_ARRAY(element, resistances))
    {
        resistances += ({ element });
    }
    int res = GENESIS_BALANCE_RESIST->spell_resist(caster, target,
        resistances, difficulty);
    
    send_debug_message("thunaur", target->short() + " has resistance "
        + "of " + res + " against thunaur.");
        
    return res;
}
