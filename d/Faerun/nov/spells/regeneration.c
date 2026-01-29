/*
 * The ghostsight-spell for the Nov.
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
       write("You prepare to cast regeneration on yourself!\n");
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
                caster->write("Your alignment has surpassed the limit of " +
                "what is acceptable for those dabbling in the black arts.\n");
                return;
            
        }
    	
    	if (!this_player()->query_prop(IHAVEBREW2))
    	{
    		write("You are not prepared to cast this spell!\n");
    		return;
    	}
    	
    	if (caster->query_prop(I_AM_NREGEN))
    	{
    		write("Your are already affected by regeneration!\n");
    		return;
    	}
    	
    	if (random(100) < resist[0])
	{
		write("Your cast regeneration on yourself, but nothing happens.\n");
		return;
	}
	
	caster->catch_tell("You summon negative energies to regenerate your body!\n");
       
        tell_room(environment(caster), QCTNAME(caster)+" begins to regenerate!\n",({caster}));
	

	shadow = clone_object(NOV_DIR +"shadows/regen_sh");
        shadow->shadow_me(caster);
        shadow->init_regen_shadow(2000);
	
    }

}


int
create_spell()
{
    set_spell_name("regeneration");
    set_spell_desc(">Unholy regeneration<");
    set_spell_time(3);
    set_spell_mana(50);
    set_spell_vocal(0);
    set_spell_visual(0);
    set_spell_ingredients(({"shard"}));
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_DEATH, 30);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_resist(spell_resist_basic);
    set_spell_target_verify(spell_verify_present);
    set_spell_stationary(1);
    set_spell_offensive(0);
    
    set_spell_target(spell_target_caster);
    
    setuid();
    seteuid(getuid());
   

}  