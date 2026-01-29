#pragma strict_types

#include "../morgulmage.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "harm";

#define _NO_DEFAULT_CONCENTRATE_MESSAGE

#include "generic_functions.c"
#include "generic_hooks.c"
#include "rank_limitation.c"

public void
config_harm_spell()
{
    ::config_harm_spell();

    set_spell_name("gorothnatha");
    set_spell_desc("Dread Bite");
    
    set_spell_visual(0);
    set_spell_combat_aid(100);
    set_spell_element(SS_ELEMENT_DEATH, 25);
    set_spell_form(SS_FORM_ENCHANTMENT, 25);
}

/*
 * Function:    resolve_harm_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_harm_spell(object caster, object *targets, int *resist, int result)
{
    MORGUL_MASTER->increase_activity(caster, ACTIVITY_COMBAT_SPELL);
}

public void
desc_harm_cast(object caster, object *targets)
{
}

private string
describe_damage(int percentage)
{
    switch(percentage)
    {
        case   0..3: return "barely hurt";
        case   4..8: return "slightly hurt";
        case  9..12: return "somewhat hurt";
        case 13..16: return "rather hurt";
        case 17..20: return "hurt";
        case 21..25: return "very hurt";
        default    : return "extremely hurt";
     
    }
}

public string
query_body_part(object target, int attack_id)
{
    if (target->query_humanoid()) {
        switch(attack_id)
        {
            case W_LEFT:
                return "left arm";
            case W_RIGHT:
                return "right arm";
            case W_BOTH:
                return "arms";
            case W_FOOTR:
                return "right leg";
            case W_FOOTL:
                return "left leg";
        }
    }

    return 0;
}

public void
desc_harm_damage(object caster, object target, mixed *result)
{
    mixed data = caster->query_prop(MORGUL_M_GOROTHNATHA_DATA);    
    string how = describe_damage(result[0]);

    object target_cobj = target->query_combat_object();
    if (!sizeof(target_cobj->query_attack(data["attack_id"])))
    {    
        string desc1, desc2, desc3, desc4;
        switch(result[0]) {
            case 0..24: desc1 = "surprised"; 
                        desc2 = "affected";
                        desc3 = "an unexpected sting"; 
                        desc4 = "seemingly hurt";
                        break;
            case 25..49: desc1 = "shocked";
                         desc2 = "pained";
                         desc3 = "a sudden jolt";
                         desc4 = "appearently damaged";
                         break;
            case 50..74: desc1 = "to blanch";
                         desc2 = "wounded";
                         desc3 = "a hideous lash";
                         desc4 = "clearly wounded";
                         break;
            default: desc1 = "stricken";
                     desc2 = "severely maimed";
                     desc3 = "a shredding agony";
                     desc4 = "horribly maimed";
                     break;
        }

        caster->catch_tell(target->query_The_name(caster) + " seems suddenly "
            + desc1 + ", as if " + desc2 + " somehow by his contact with "
            + "you!\n");

        target->catch_tell("You feel " + desc3 + " and recoil from your last "
            + "strike, " + desc4 + " somehow by your contact with " 
            + caster->query_the_name(target) + "!\n");

        caster->tell_watcher(QCTNAME(target) + " seems suddenly " + desc1
            + ", as if " + desc2 + " by his contact with " + QTNAME(caster)
            + "!\n", target, ({ caster, target }));
        return; 
    }

    string attack_desc = target_cobj->cb_attack_desc(data["attack_id"]);
    string attack_part = query_body_part(target, data["attack_id"]);
    if (!stringp(attack_part)) attack_part = attack_desc;

    switch(random(4)) 
    {
        case 0:
        {
            caster->catch_tell(target->query_The_possessive_name(caster) 
                + " attack with " + target->query_possessive() + " " 
                + caster->check_call(attack_desc) + " strikes your unseen, "
                + "fell aura which seems to sting " 
                + target->query_objective() + " in retalliation.\n");

            target->catch_tell("Your attack on " 
                + caster->query_the_name(target) + " has left your "
                + target->check_call(attack_part) + " stinging.\n");

            caster->tell_watcher(QCTNAME(target) + " briefly rubs " 
                + target->query_possessive() + " " + attack_part 
                + " after " + target->query_possessive() + " contact "
                + "with " + QTNAME(caster) + ".\n", target, 
                ({ caster, target }));

            break;
        }
        case 1:
        {
            caster->catch_tell(target->query_The_possessive_name(caster) 
                + " attack with " + target->query_possessive() + " " 
                + caster->check_call(attack_desc) + " strikes your unseen, "
                + "fell aura which causes " + target->query_objective() 
                + " to recoil as if stricken by a viper.\n");

            target->catch_tell("Intense pain follows your attack on "
                + caster->query_the_name(target) + " as if you were bitten "
                + "by an unseen snake.\n");

            caster->tell_watcher(QCTNAME(target) + " suddenly recoils from " 
                + "an unseen assault after " + target->query_possessive() 
                + " contact with " + QTNAME(caster) + ".\n", 
                target, ({ caster, target }));
            break;
        }
        case 2:
        {
            caster->catch_tell(target->query_The_possessive_name(caster) 
                + " attack with " + target->query_possessive() + " " 
                + caster->check_call(attack_desc) + " strikes your unseen, "
                + "fell aura which causes " + target->query_objective() 
                + " to fall back under a barrage of reverberated attacks.\n");

            target->catch_tell("You helplessly retreat from a bombardment of "
                + "razor sharp teeth, obviously a direct result of your "
                + "attack on " + caster->query_the_name(target) + ".\n");

            caster->tell_watcher(QCTNAME(target) + " visibly collapses under "
                + "a percieved multitude of assaults after "
                + target->query_possessive() + " contact with " 
                + QTNAME(caster) + ".\n", target, ({ caster, target }));
            break;
        }
        case 3:
        {
            caster->catch_tell(target->query_The_possessive_name(caster) 
                + " attack with " + target->query_possessive() + " " 
                + caster->check_call(attack_desc) + " strikes your unseen, "
                + "fell aura which causes " + target->query_possessive() 
                + " whole body to wrack in agonizing pain.\n");

            target->catch_tell("Your attack on " 
                + caster->query_the_name(target) + " seems to immobilize "
                + "your entire body, encasing it in an unseen terror. "
                + "A sudden, severe pain agonizingly ends the eery "
                + "imprisonment!\n");

            caster->tell_watcher(QCTNAME(target) + " is striken completely "
                + "immoble after " + target->query_possessive() + " contact "
                + "with " + QTNAME(caster) + "; " + target->query_possessive()
                + " face is pale and painted with soundless scream.\n",
                target, ({ caster, target }));
            break;
        }
    }
}

public string *query_harm_ingredients(object caster)
{
    return ({  });
}
