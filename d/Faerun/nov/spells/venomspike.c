/*
 * The venomspike spell for Nov.
 *
 * 16/6/2004   -- Tilorop.
 */



#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../nov.h";

inherit "/d/Genesis/newmagic/spell";

public void
concentrate_msg(object caster, object *targets, string arg)
{
       write("You prepare to cast venomspike!\n");
       say(QCTNAME(caster) + " does a magical gesture with "+caster->query_possessive()+" hands.\n");
}



public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
        int pen;
        int i;
       
        for (i = 0; i < sizeof(targets); i++)
    {
    	
    	if (caster->query_alignment() > -100)
        {
                caster->write("Your alignment has surpassed the limit of " +
                "what is acceptable for those dabbling in the black arts.\n");
                return;
            
        }
        
        if (random(100) < targets[i]->query_prop(OBJ_I_RES_DEATH))
        {
   
                write(QTNAME(targets[i])+" resists your venomspike!\n");
                
                tell_room(environment(caster), QTNAME(targets[i]) +" resists " +
                ""+QCTNAME(caster)+"'s venomspike!\n",({caster,targets[i]}));
                
                targets[i]->catch_tell("You resist "+caster->query_The_name(targets[i])+"'s " +
                "venomspike!\n");
 
                return;
        }
        
        if (random(100) < targets[i]->query_prop(MAGIC_I_RES_DEATH))
        {
   
                write(QTNAME(targets[i])+" resists your venomspike!\n");
                
                tell_room(environment(caster), QTNAME(targets[i]) +" resists " +
                ""+QCTNAME(caster)+"'s venomspike!\n",({caster,targets[i]}));
                
                targets[i]->catch_tell("You resist "+caster->query_The_name(targets[i])+"'s " +
                "venomspike!\n");
 
                return;
        }
        
        if (random(100) < targets[i]->query_prop(MAGIC_I_RES_MAGIC))
        {
   
                write(QTNAME(targets[i])+" resists your venomspike!\n");
                
                tell_room(environment(caster), QTNAME(targets[i]) +" resists " +
                ""+QCTNAME(caster)+"'s venomspike!\n",({caster,targets[i]}));
                
                targets[i]->catch_tell("You resist "+caster->query_The_name(targets[i])+"'s " +
                "venomspike!\n");
 
                return;
        }
    


        
       
       	 pen = 270;
    	
         caster->catch_tell("You shoot a green spear-shaped poisonous fog " +
         "at "+targets[i]->query_The_name(caster)+"!\n");
       
         tell_room(environment(caster), QCTNAME(caster)+" shoots a green spear-shaped " +
         "poisonous fog at "+QTNAME(targets[i])+"!\n",({caster,targets[i]}));
         
         targets[i]->catch_tell(caster->query_The_name(targets[i])+" shoots a green " +
         "spear-shaped poisonous fog at you!\n\nYou are poisoned!\n");
   
         targets[i]->hit_me(pen, MAGIC_DT, caster, -1);
         targets[i]->set_intoxicated(10);
       

     
    }

}


int
create_spell()
{
    set_spell_name("venomspike");
    set_spell_desc(">A spike of venom<");
    set_spell_time(3);
    set_spell_mana(50);
    set_spell_vocal(0);
    set_spell_visual(0);
    set_spell_ingredients(({"hemlock", "_methyl"}));
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_WATER, 40);
    set_spell_form(SS_FORM_CONJURATION, 30);
    set_spell_resist(spell_resist_basic);
    set_spell_target_verify(spell_verify_present);
    set_spell_stationary(0);
    set_spell_offensive(1);
    
    set_spell_target(spell_target_one_other_present_living);
    
    setuid();
    seteuid(getuid());
   

}  