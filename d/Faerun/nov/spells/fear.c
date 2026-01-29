/*
 * The Fear-spell for Nov.
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
       write("You prepare to cast fear on your target!\n");
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
    	
    	
    	if (random(100) < resist[i])
	{
		write("Your target resists the spell!\n");
		return;
	}
	
	 caster->catch_tell("You unleash the unholy terror of vile " +
	 "darkness at "+targets[i]->query_The_name(caster)+".\n");
       
         tell_room(environment(caster), QCTNAME(caster)+" unleashes a ray " +
         "of unholy terror of vile darkness at "+QTNAME(targets[i])+".\n",({caster,targets[i]}));
         
         targets[i]->catch_tell(caster->query_The_name(targets[i])+" suddently fills you " +
         "with raw, unholy vile terror! Your heart nearly stops for a moment, and " +
         "your instincts suddently takes over as you loose control of your feet!\n");
    	
         shadow = clone_object(NOV_DIR +"shadows/fear_sh");
         shadow->shadow_me(targets[i]);
         shadow->init_fear_shadow(5 + random(3));

    }

}


int
create_spell()
{
    set_spell_name("fear");
    set_spell_desc(">Scares a target away<");
    set_spell_time(3);
    set_spell_mana(50);
    set_spell_vocal(0);
    set_spell_visual(0);
    set_spell_ingredients(({"skull", "kneecap"}));
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_DEATH, 30);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_resist(spell_resist_basic);
    set_spell_target_verify(spell_verify_present);
    set_spell_stationary(1);
    set_spell_offensive(1);
    
    set_spell_target(spell_target_one_other_present_living);
    
    setuid();
    seteuid(getuid());
   

}  