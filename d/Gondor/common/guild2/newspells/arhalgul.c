#include "spells.h"
#include <language.h>
#include <macros.h>
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

inherit SPELL_INHERIT;
inherit SPELL_IDENTIFY;

void
concentrate_msg( object caster, object *targets, string args )
{
    caster->catch_tell("You prepare to employ Dark Sorcery and draw upon "+
    	"the power of the Dark Lord.\n");
    can_see_caster(caster)->catch_msg(QCTNAME(caster) + " draws power "+
		"from the realm of the shadows.\n");
}


public void
resolve_spell( object caster, object *targets, int *resist, int result )
{
    if (check_mage( caster ))
    {
		return;
    }
    can_see_caster( caster )->catch_msg( "Employing Dark Sorcery, "+ 
    	QTNAME( caster )+ " casts a spell on "+ ((environment( targets[0] )
		== caster) ? "something" : LANG_THESHORT( targets[0] ))+
		" to reveal "+ ((living(targets[0])) ? targets[0]->
		query_possessive() : "its")+ " secrets.\n");
    caster->catch_tell( "Using the power the Dark Lord has bestowed upon "+
		"you, with the words \"Waro torgul! Arhalo furion rum!\", you "+
		"cast Arhalgul on " + LANG_THESHORT(targets[0]) + ".\n");
    if (targets[0]->id( "herb" ))
    {
		caster->catch_tell(targets[0]->query_id_long());
		return;
    }
    ::resolve_spell( caster, targets, resist, result );
    IDLENESS->increase_activity( caster, SMALL_SPELL );

}

public int
config_spell(object caster, object *targets, string args) 
{
    ::config_spell(caster, targets, args);

    set_spell_name("arhalgul");
    set_spell_desc("Attempt to reveal the secrets of an object.");
    set_spell_target(spell_target_one_present_object);
                                /*The spell is not being configured for   *
                                 *a casting attempt, and therefore should *
                                 *not return 1                            */
    if (!objectp(caster))
    {
        return 0;
    }

    if (!default_morgul_spell_setup( caster ))
    {
	return 1;
    }
    set_spell_element( SS_ELEMENT_AIR, 24 );
    set_spell_form( SS_FORM_ENCHANTMENT, 27 );
    set_spell_time(spell_resolve_time( caster->query_stat(SS_OCCUP),6,14 ));
    set_spell_peaceful( 1 );
    set_spell_mana( 40 );
    set_spell_task( 50 );
    set_spell_resist_task( TASK_IMPOSSIBLE );
	if (caster->query_wiz_level())
	{
	    set_spell_ingredients(0);
	}
	else
	{ 
    	set_spell_ingredients( ({ "arhalgul_ingr1" }) );
	}
    return 0;
}
