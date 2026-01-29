/*
 * The ghostsight-spell for the Banedead.
 *
 * 23/4/2004   -- Tilorop.
 */



#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <stdproperties.h>
#include "../nov.h";

inherit "/d/Genesis/newmagic/spell";

public void
concentrate_msg(object caster, object *targets, string arg)
{
       write("You prepare to cast purge on yourself!\n");
       say(QCTNAME(caster) + " does a magical gesture with "+caster->query_possessive()+" hands.\n");
}


public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
        object shadow;
        int i;
       
        for (i = 0; i < sizeof(targets); i++)
    {
    	
    	if (caster->query_alignment() > -100)
        {
                caster->write("Your alignment have surpassed what is tolerable " +
                "for anyone who serve Velsharoon, thus this spell will not " +
                "work until its corrected.\n");
                return;
            
        }
    	
    	if (caster->query_prop(I_AM_NPURGED))
    	{
    		write("Your are already affected by the purge!\n");
    		return;
    	}
    	
    	if (random(100) < resist[0])
	{
		write("Your cast purge on yourself, but nothing happens.\n");
		return;
	}
	
	caster->catch_tell("A jolt of negative energy suddently courses through " +
	"your body!\nYou feel healthier and more agitated!\n");
       
        tell_room(environment(caster), QCTNAME(caster)+" suddently looks " +
        "more agitated and healthier!\n",({caster}));
	

	shadow = clone_object(NOV_DIR +"shadows/purge_sh");
        shadow->shadow_me(caster);
        shadow->init_purge_shadow(60 + random(20));
	
    }

}


int
create_spell()
{
    set_spell_name("purge");
    set_spell_desc(">Replentish fatigue and heal some<");
    set_spell_time(1);
    set_spell_mana(100);
    set_spell_vocal(0);
    set_spell_ingredients(({ }));
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_DEATH, 30);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_resist(spell_resist_basic);
    set_spell_target_verify(spell_verify_present);
    set_spell_stationary(1);
    set_spell_offensive(0);
    
    set_spell_target(spell_target_caster);
   

}  