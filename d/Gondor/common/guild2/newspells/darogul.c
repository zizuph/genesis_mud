/*
 * /d/Gondor/common/guild2/newspells/darogul.c
 *
 */

#include "spells.h"
#include <files.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

inherit SPELL_RESIST;
inherit SPELL_INHERIT;

#define HE(x)   (x)->query_pronoun()
#define HIS(x)  (x)->query_possessive()
#define NAME(x) (x->query_npc() ? file_name(x) : x->query_cap_name())

string effect;

void
resolve_spell( object caster, object *targets, int *resist, int result )
{
	object spell_ob;

    if (check_mage( caster ))
    {
        return;
    }

	// General messages
	caster->catch_tell("You position your hands in front of your chest " +
		"with the palms facing toward your robe. Raising your arms " +
		"quickly and flicking your wrists with a snap, you cast Darogul.\n");
    tell_room( environment( caster ), QCTNAME( caster ) + " positions " +
		HIS(caster) + " hands in front of " + HIS(caster) + " chest with " +
		"the palms facing toward " + HIS(caster) + " robe. Raising " +
		HIS(caster) + " arms quickly and flicking " + HIS(caster) + 
		" wrists with a snap, " + HE(caster) + " casts a spell.\n", 
		({ caster }) );

	switch(effect)
	{
		case "mortirio":
		{
			// Check for Mortirio
			if(targets[0]->query_mortirio_effect())
			{
				targets[0]->catch_tell("Your vision blurs momentarily.\n");

				// Dispell the effect
				targets[0]->dispel_mortirio(caster);
	
				// Reward the caster
				IDLENESS->increase_activity( caster, RARE_SPELL );

				return;
			}
			break;
		}
		case "ringurth":
		{
			// Check for Ringurth casted by mage self
			spell_ob = present("_morgul_aura", targets[0]);
			if(objectp(spell_ob) && 
			   (spell_ob->query_spell_effect_caster() == caster))
			{
				targets[0]->catch_tell("The cold, comforting shadow " +
					"surrounding your body gradually fades from view.\n");

				// Dispell the effect
				spell_ob->dispel_ringurth(caster);

				// Reward the caster
				IDLENESS->increase_activity( caster, RARE_SPELL );

				return;
			}
			break;
		}
		case "ephessul":
		{
			// Check for Ringurth casted by mage self
			spell_ob = present("Morgul_Ephessul_Object", targets[0]);
			if(objectp(spell_ob) && 
			   (spell_ob->query_spell_effect_caster() == caster))
			{
				// Dispell the effect
				spell_ob->dispel_ephessul(caster);

				// Reward the caster
				IDLENESS->increase_activity( caster, RARE_SPELL );

				return;
			}
			break;
		}
	}

	caster->catch_tell("Your spell has no effect.\n");
}

object *spell_target_darogul( object caster, string str )
{
    if (!strlen( str ))
    {
        caster->catch_tell( "Which effect do you want to dispell?\n" );
        return ({});
    }

	if(member_array(str, ({ "mortirio", "ringurth", "ephessul" }) ) == -1)
	{
        caster->catch_tell( "Which effect do you want to dispell?\n" );
        return ({});
	}

	// Store the effect for later use
	effect = str;
	return ({ caster });
}

public varargs int
config_spell( object caster, object *targets, string argument )
{
    set_spell_name( "darogul" );
    set_spell_desc( "Stop magic" );
    set_spell_target( spell_target_darogul );

	/*The spell is not being configured for   *
	 *a casting attempt, and therefore should *
	 *not return 1                            */
	if (!objectp( caster ))
    {
        return 0;
    }

    if (!default_morgul_spell_setup( caster ))
    {
        return 1;
    }
    
    if (caster->query_wiz_level())
    {
        set_spell_ingredients( 0 );
    }
    else
    {
        set_spell_ingredients( ({ "mortirio_ingr1" }) );
    }

    set_spell_resist( spell_resist_beneficial );
    set_spell_peaceful( 1 );
    set_spell_visual( 0 );
    set_spell_time(spell_resolve_time( caster->query_stat(SS_OCCUP),5,11 ));
    set_spell_mana( 30 );
    set_spell_task( TASK_HARD );
    set_spell_element( SS_ELEMENT_AIR, 25 );
    set_spell_form( SS_FORM_ENCHANTMENT, 25 );

	return 0;
}
