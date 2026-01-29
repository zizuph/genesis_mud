/*
 * The wraithform-spell for Nov.
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
       write("You prepare to cast wraithform on yourself!\n");
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
    	
    	if (caster->query_prop(IAMINWRAITHFORM))
    	{
    		write("But you are already in wraithform!\n");
    		return;
    	}
    	
    	
    	
    	if (random(100) < resist[0])
	{
		write("Your cast wraithform on yourself, but nothing happens.\n");
		return;
	}
    	
    	
         shadow = clone_object(NOV_DIR +"shadows/wraithform_sh");
         
         shadow->shadow_me(caster);
         
         shadow->init_wraithform_shadow(520 +random(320));
         
         

    }

}


int
create_spell()
{
    set_spell_name("wraithform");
    set_spell_desc(">Turns you into a black misty shape<");
    set_spell_time(5);
    set_spell_mana(100);
    set_spell_vocal(0);
    set_spell_visual(0);
    set_spell_ingredients(({"shard", "curugwath" }));
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