/*
 * pPain
 */

#pragma strict_types

inherit "/d/Genesis/specials/std/spells/stun";

#include "/d/Ansalon/common/defs.h"
#include "../spells.h"
#include "../guild.h"
#include <macros.h>
#include <tasks.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <composite.h>
#include <files.h>
#include <language.h>

inherit GUILDDIRSPELL + "common";

#define ACTIVE_CURSE "_pot_curse_active"
#define BLIND_CURSE "_pot_blind_curse"

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 12;
}

/*
 * Function name: ingredient_knife
 * Description:   Used to find a knife ingredient
 * Arguments:     object *possible - possible ingredients to check
 *                object *found    - ingredients already found
 * Returns:       pointer to valid ingredient object, or 0
 */
object
ingredient_knife(object *possible, object *found)
{
    object *list, tmp;
    int i;

    list = possible - found;
    for (i = 0; i < sizeof(list); i++)
    {
        tmp = list[i];
        if (tmp->check_weapon() &&
            tmp->query_wt() == W_KNIFE &&
            (tmp->query_pen()) >= 8)
        {
            return tmp;
        }
    }
    return 0;
}

/*
 * Function:    config_stun_spell
 * Description: Config function for stun spells. Redefine this in your
 *              own stun spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */

public void
config_stun_spell()
{
    set_spell_name("ppain");
    set_spell_desc("Paralyze your enemy with pain");

    set_spell_element(SS_ELEMENT_LIFE, 77);
    set_spell_form(SS_FORM_TRANSMUTATION, 77);

    set_spell_task(TASK_ROUTINE);
            
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(90.0);
    set_spell_object(PAIN_OBJ);

}

/*
 * Function:    query_stun_ingredients
 * Description: This function defines what components are required for
 *              this stun spell.
 */
public string *
query_stun_ingredients(object caster)
{
    return ({"green slime","elf heart",ingredient_knife});
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute)
{

    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    // harder to cast on when in poor standings
    if (caster->query_skill(PS_STANDING) < -900)
	set_spell_task(TASK_FORMIDABLE);
    else if (caster->query_skill(PS_STANDING) < -300) 
	set_spell_task(TASK_HARD);

    if(!caster->query_prop(DARK_LADY_ASPECT))
        set_spell_combat_aid(40.0);

    object *target;

    if(caster->query_prop(DARK_WARRIOR_ASPECT))
    {
        caster->catch_tell("While under the aspect of the Dark Warrior, you " +
           "cannot call upon this curse.\n");
        return 0;
    }

    if (sizeof(target = filter(targets[0]->query_stun_effects(),
        &operator(==)(, caster->query_real_name()) @ &->query_pot_stun())))
    {   
        if (target[0]->query_pot_active())
        {
            caster->catch_tell("You notice " + COMPOSITE_LIVE(targets) +
            " is already paralyzed with excrutiating pain.\n");
            find_player("arman")->catch_msg("[PoT] test\n");
            return 0;
        }
    }

    if (sizeof(target = filter(targets[0]->query_stun_effects(),
        &operator(==)(, caster->query_real_name()) @ &->query_pot_stun())))
    {   
        if (target[0]->query_pot_cooldown())
        {
            caster->catch_tell("It is too soon to call down the wrath of " +
             "Takhisis again! You risk drawing the ire of the goddess by " +
             "beseeching her too frequently!\n");
            return 0;
        }
    }

    if(caster->query_prop(DARK_LADY_ASPECT))
    {
       if (targets[0]->query_prop(ACTIVE_CURSE))
       {
        caster->catch_tell("A curse has already been cast " +
	    "upon "+ COMPOSITE_LIVE(targets) +". While aspected to " +
            "the Dark Lady you can only beseech the wrath " +
            "of Takhisis with a single curse at a time!\n");
        return 0;
       }
       if (targets[0]->query_prop(BLIND_CURSE))
       {
         caster->catch_tell("While under the aspect of the Dark Lady " +
           "you cannot summon the wrath of Takhisis on a foe affected " +
           "by pblind.\n");
        return 0;
       }
    }

    int c_aid = ftoi(query_spell_combat_aid());

    if(BETA_CAID_MOD)
        c_aid = (c_aid / 10) * 9;

    set_spell_combat_aid(c_aid);
    DEBUG("Ppain aid: " + c_aid);
 
    return 1;
}

/*
 * Function:    hook_describe_cast_stun
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_stun(object caster, object * targets)
{
    object target = targets[0];

    caster->catch_tell("You point at " + COMPOSITE_LIVE(targets) + " and say: " +
        "Feel the wrath of the Dark Queen!\n");
    target->catch_msg(QCTNAME(caster) + " points at you, saying: Feel the " +
        "wrath of the Dark Queen!\n");
    caster->tell_watcher(QCTNAME(caster) + " points at " +QTNAME(target)+
        " and says: Feel the wrath of the Dark Queen!\n", targets, 
        ({ caster }) + targets);
}

/*
 * Function:    hook_target_stun_resisted
 * Description: Called to show the messages of the targets that were not
 *              stunned because they resisted the spell.
 */
public void
hook_target_stun_resisted(object caster, object * targets)
{
    if (!sizeof(targets))
    {
        return;
    }
    
    caster->catch_tell("Takhisis doesn't answer your call to paralyze " + 
       COMPOSITE_LIVE(targets)+ " with pain.\n");
    targets->catch_tell("You resist the wrath of the dark goddess " +
       "Takhisis.\n"); 
}


/*
 * Function:    hook_target_stun_succeeded
 * Description: Called to show the messages of the targets that were
 *              affected by the stun. Part of the stun messages
 *              will also be described by the stun object itself. Note
 *              that it's entirely possible the stun spell may hit,
 *              but because of a cooldown period, the stun may not
 *              actually have any effect.
 */
public void
hook_target_stun_succeeded(object caster, object * targets)
{
    object tar = targets[0];

    if (!sizeof(targets))
    {
        return;
    }

    caster->catch_tell(C(HE(tar))+" cries out as a wave of pain "+
	"sears through "+HIS(tar)+" body.\n");
    tar->catch_tell("You cry out as a wave of pain sears through your body.\n");
    tell_room(environment(tar), QCTNAME(tar) + " cries out in pain.\n", 
        ({caster, tar}), tar);

}

public void
hook_use_ingredients(object *ingrs)
{
    int i, j;

    if (ingrs[0]->check_weapon())
        i = 0;
    else if (ingrs[1]->check_weapon())
        i = 1;
    else
        i = 2;

    if (ingrs[i + 1 % 3]->query_herbname() == "green slime")
        j = i + 1 % 3;
    else
        j = i + 2 % 3;
    write("As you stick " + LANG_THESHORT(ingrs[i]) + " into and " +
          "through the elven heart, you let the blood drip onto " +
          LANG_THESHORT(ingrs[j]) + ", making it burst into " +
          "flames, consuming the heart and blade.\n");
}

/*
 * Function name: query_casting_success
 * Description:   Determine if a spell is successfully cast
 * Returns:       The result as an integer indicating success or
 *                failure (0 indicating failure, positive integer
 *                indicating % success)
 */
static int
query_casting_success(object caster)
{
    object m = caster->query_armour(A_NECK);

    int ret = ::query_casting_success(caster);

    /* If we don't wear the medallion, there is only a 10% chance
     * the spell will actually go through
     */
    if (!m && !(m->id(MEDALLION_ID)))
    {
        caster->adjust_standing(RND_RANGE(-200, 50));
        if (random(10))
            return 0;
    }
    if (ret)
        caster->adjust_standing(random(8) ?
            RND_RANGE(TO->query_spell_level() * 3, 10) : RND_RANGE(-10, 10));
    else
        caster->adjust_standing(RND_RANGE(-5, 5));
        
    return ret;
}