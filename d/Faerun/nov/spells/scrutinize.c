/*
 * The scrutinize-spell for the Nov.
 *
 * 23/4/2004   -- Tilorop.
 */



#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "../nov.h";

inherit "/d/Genesis/newmagic/spell";

public void
concentrate_msg(object caster, object *targets, string arg)
{
       write("You prepare to cast scrutinize!\n");
       say(QCTNAME(caster) + " does a magical gesture with "+caster->query_possessive()+" hands.\n");
}


void describe_room(object room)
{
   
    write(room->long());
    write(capitalize(FO_COMPOSITE_LIVE(FILTER_CAN_SEE(FILTER_LIVE(all_inventory(room)),this_player()),this_player()))+"\n");
    write(capitalize(FO_COMPOSITE_DEAD(FILTER_CAN_SEE(FILTER_DEAD(all_inventory(room)),this_player()),this_player())+"\n"));
  
}





public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
        object dest, t;
        object target = targets[0];
        string v;
   	
   	
   	
   	 if (caster->query_alignment() > -100)
        {
                caster->write("Your alignment has surpassed the limit of " +
                "what is acceptable for those dabbling in the black arts.\n");
                return;
            
        }
    	 
         if (!interactive(target)) 
         {
            caster->catch_msg("There is no creature of that name within the realms!\n");
            return;
         }
         

        
	 dest = environment(target);
	
	 caster->catch_tell("Black negative energy veils your eyes for a " +
	 "moment, and you see:\n\n");
	 set_alarm(0.0,0.0, &describe_room(dest));
	 //set_alarm(5.0,0.0, &describe_room(dest));
	 //set_alarm(10.0,0.0, &describe_room(dest));
       
         tell_room(environment(caster), QCTNAME(caster)+"'s eyes flashes for a " +
         "moment with black negative energy.\n",({caster}));
         
         tell_room(environment(target), "A floating skull crashes in from the shadows!\n",({caster}));
         
         clone_object(NOV_DIR +"obj/scryskull")->move(environment(target));
         
         
         
 
}


int
create_spell()
{
    set_spell_name("scrutinize");
    set_spell_desc(">Scrying a distant target<");
    set_spell_time(3);
    set_spell_mana(50);
    set_spell_vocal(0);
    set_spell_visual(0);
    set_spell_ingredients(({"skull"}));
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_DEATH, 30);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_resist(spell_resist_basic);
    //set_spell_target_verify(spell_verify_present);
    set_spell_stationary(1);
    set_spell_offensive(0);
    
    set_spell_target(spell_target_one_distant_living);
    
    setuid();
    seteuid(getuid());
   

}  