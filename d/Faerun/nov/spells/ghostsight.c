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
#include "../banedead.h";

inherit "/d/Genesis/newmagic/spell";

public void
concentrate_msg(object caster, object *targets, string arg)
{
       write("You prepare to cast ghostsight on yourself!\n");
       say(QCTNAME(caster) + " does a magical gesture with "+caster->query_possessive()+" right talon.\n");
}


public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
        object shadow;
        int i;
       
        for (i = 0; i < sizeof(targets); i++)
    {
    	
    	if (caster->query_prop(IHAVEGHOSTSIGHT))
    	{
    		write("You already have the ghostsight active!\n");
    		return;
    	}
    	
    	
    	
    	if (random(100) < resist[0])
	{
		write("Your cast ghostsight on yourself, but nothing happens.\n");
		return;
	}
    	
         shadow = clone_object(BANEDEAD_DIR +"shadows/ghostsight_sh");
         shadow->shadow_me(caster);
         shadow->init_ghostsight_shadow(30);

    }

}


int
create_spell()
{
    set_spell_name("ghostsight");
    set_spell_desc(">See invisibility<");
    set_spell_time(3);
    set_spell_mana(150);
    set_spell_vocal(0);
    set_spell_ingredients(({ }));
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_DEATH, 30);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_resist(spell_resist_basic);
    set_spell_target_verify(spell_verify_present);
    set_spell_stationary(0);
    set_spell_offensive(0);
    
    set_spell_target(spell_target_caster);
   

}  