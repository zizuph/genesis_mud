/*
 * The glitterdust-spell for the Banedead.
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
       write("You prepare to cast bonedust!\n");
       say(QCTNAME(caster) + " does a magical gesture with "+caster->query_possessive()+" hands.\n");
}


public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
        object dust;
        int i;
       
       
       tell_room(environment(caster), "Suddently, a wave of glowing " +
        "dust blasts out from "+QCTNAME(caster)+"'s hands! The dust " +
        "quickly spreads everywhere, covering the whole area in the blink of an eye.\n",({caster}));
        
    targets = all_inventory(environment(caster));

    for (i = 0; i < sizeof(targets); i++)
    {
        
        
        
        
         if ((targets[i]->query_prop(OBJ_I_INVIS)) && (!targets[i]->query_prop(IHAVEBONEDUST)))
         {
        
           
 
           setuid();
           seteuid(getuid());
      
           dust = clone_object(NOV_DIR +"shadows/bdust_sh");
           dust->shadow_me(targets[i]);           
           dust->init_glitterdust_shadow(200);
               
           
        }
        
        tell_object(targets[i], "You are suddently covered by thousands of glowing bone particles!\n");
        tell_room(environment(caster), QTNAME(targets[i]) + " is covered by thousands of glowing " +
        "bone particles!\n", ({targets[i]}));
            
    }

}


int
create_spell()
{
    set_spell_name("bonedust");
    set_spell_desc(">Spreads the area with dust from bones<");
    set_spell_time(3);
    set_spell_mana(40);
    set_spell_visual(0);
    set_spell_vocal(0);
    set_spell_ingredients(({"_bonep", "_onyxd" }));
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_DEATH, 30);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_resist(spell_resist_basic);
    set_spell_target_verify(spell_verify_present);
    set_spell_stationary(0);
    set_spell_offensive(0);
    
    set_spell_target(spell_target_caster);
    
    setuid();
    seteuid(getuid());
   

}  