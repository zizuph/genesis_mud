/**********************************************************************
 * - aura.c                                                         - *
 * - Eil-Galiath alignment spell                                    - *
 * - Created by Damaris 2/2002                                      - *
 * - Recoded by Damaris 6/2003                                      - *
 **********************************************************************/ 
#pragma strict_types

#include "spells.h"
#include "../guild.h"
#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
inherit "/d/Genesis/newmagic/spell";
inherit SPELL_INHERIT;

public void
create_spell()
{
    object caster;
    set_spell_name("aura");
    set_spell_desc("Identify someone's aura.");
    set_spell_target(spell_target_one_present_living);
    set_spell_time(5);
    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE - (caster->query_stat(SS_RACE) / 2));
    set_spell_ingredients(0);
    set_spell_element(SS_ELEMENT_LIFE, 20);
    set_spell_form(SS_FORM_DIVINATION, 20);

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
    int align;

    if (resist[0] > random(100))
    {
	caster->catch_tell(targets[0]->query_The_name(caster) + " "+
	"resists your magic.\n");
	return;
    }

    align = targets[0]->query_align_text();
    switch (align)
    {
    case "damned":
         caster->catch_tell(targets[0]->query_The_name(caster) +
         " walks the paths of the damned.\n");
	  break;
    case "demonic":
         caster->catch_tell(targets[0]->query_The_name(caster) +
         " is demonic to the core.\n");
	  break;
    case "beastly":
         caster->catch_tell(targets[0]->query_The_name(caster) +
         " follows a beastly path.\n");
	  break;
    case "malevolent":
         caster->catch_tell(targets[0]->query_The_name(caster) +
         " reeks malevolence.\n");
	  break;
    case "evil":
         caster->catch_tell(targets[0]->query_The_name(caster) +
         " shimmers with evilness.\n");
	  break;
    case "foul":
         caster->catch_tell(targets[0]->query_The_name(caster) +
         " is foul with darkness.\n");
	  break;
    case "nasty":
         caster->catch_tell(targets[0]->query_The_name(caster) +
         " grasps the strands of nastiness.\n");
	  break;
    case "wicked":
         caster->catch_tell(targets[0]->query_The_name(caster) +
         " walks a wicked path.\n");
	  break;
    case "sinister":
         caster->catch_tell(targets[0]->query_The_name(caster) +
         " is sinister through and through.\n");
	  break;
    case "unsympathetic":
         caster->catch_tell(targets[0]->query_The_name(caster) +
         " is unsympathetic within their darkness.\n");
	  break;
    case "untrustworthy":
         caster->catch_tell(targets[0]->query_The_name(caster) +
         " is untrusting and closed.\n");
	  break;
    case "disagreeable":
         caster->catch_tell(targets[0]->query_The_name(caster) +
         " is disagreeable and tends towards the darkness.\n");
	  break;
    case "neutral":
         caster->catch_tell(targets[0]->query_The_name(caster) +
         " walks the neutral path.\n");
	  break;
    case "agreeable":
         caster->catch_tell(targets[0]->query_The_name(caster) +
         " is agreeable and tends towards the light.\n");
	  break;
    case "trustworthy":
         caster->catch_tell(targets[0]->query_The_name(caster) +
         " is trusting and open.\n");
	  break;
    case "sympathetic":
         caster->catch_tell(targets[0]->query_The_name(caster) +
         " is sympathetic and seeking the light.\n");
	  break;
    case "nice":
         caster->catch_tell(targets[0]->query_The_name(caster) +
         " is nice in nature and given to light.\n");
	  break;
    case "sweet":
         caster->catch_tell(targets[0]->query_The_name(caster) +
         " is sweetly illuminated by light.\n");
	  break;
    case "good":
         caster->catch_tell(targets[0]->query_The_name(caster) +
         " is shimmering with goodness.\n");
	  break;
    case "devout":
         caster->catch_tell(targets[0]->query_The_name(caster) +
         " is enshrouded with devotedness.\n");
	  break;
    case "blessed":
         caster->catch_tell(targets[0]->query_The_name(caster) +
         " follows the true light of being blessed.\n");
	  break;
    case "saintly":
         caster->catch_tell(targets[0]->query_The_name(caster) +
         " is a saint of pure light and goodness.\n");
	  break;
    case "holy":
         caster->catch_tell(targets[0]->query_The_name(caster) +
         " walks the paths of holiness.\n");
	  break;
    default:
         caster->catch_tell(targets[0]->query_The_name(caster) +
         " baffles you.\n");
	break;
    }
}


