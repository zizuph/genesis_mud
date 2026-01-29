/*
 * The darkness-spell for Nov.
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
       write("You prepare to cast ghostvision on yourself!\n");
       say(QCTNAME(caster) + " does a magical gesture with "+caster->query_possessive()+" hands.\n");
}


void
rem_darko(object caster)
{

       caster->remove_prop(IHAVEDARKNESS);
       write("The darkness around you fades away!\n");
}

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
        object dark;
        int i, time;
       
        for (i = 0; i < sizeof(targets); i++)
    {
    	
    	if (caster->query_alignment() > -100)
        {
                caster->write("Your alignment have surpassed what is tolerable " +
                "for anyone who serve Velsharoon, thus this spell will not " +
                "work until its corrected.\n");
                return;
            
        }
    	
    	
    	if (caster->query_prop(IHAVEDARKNESS))
    	{
    		write("You already have the ghostvision active!\n");
    		return;
    	}
    	
    	
    	
    	if (random(100) < resist[0])
	{
		write("Your cast ghostvision on yourself, but nothing happens.\n");
		return;
	}
    	
         time = 300 + random(200);
    	
         dark = clone_object(NOV_DIR +"obj/darko");
         dark->set_dark_remove_time(time);
         dark->move(caster, 1);
         
         write("You cast darkness upon yourself!\n");         
         caster->add_prop(IHAVEDARKNESS, 1);
         set_alarm(itof(time),0.0, &rem_darko());

    }

}


int
create_spell()
{
    set_spell_name("darkness");
    set_spell_desc(">Darkness aura<");
    set_spell_time(3);
    set_spell_mana(50);
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