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
       write("You prepare to summon a skeleton mage!\n");
       say(QCTNAME(caster) + " does a magical gesture with "+caster->query_possessive()+" hands.\n");
}


public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
        object pet;
        object pl;

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
 
        caster->catch_tell("You summon a skeleton mage!\n");
        
        tell_room(environment(caster),"A skeleton appears from nowhere!\n",
      ({caster,targets[0]}));
 
        pl=caster;
           
        pet=clone_object(NOV_DIR +"obj/skel_mage");
        pet->init_pet(pl);
        pet->move_living("M",environment(pl));


    }

}


int
create_spell()
{
    set_spell_name("bonemagus");
    set_spell_desc(">Summons a skeletal mage<");
    set_spell_time(5);
    set_spell_mana(50);
    set_spell_vocal(0);
    set_spell_visual(0);
    set_spell_ingredients(({"skull", "rib", "kneecap", "thighbone", "shard"}));
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