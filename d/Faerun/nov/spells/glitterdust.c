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
       write("You prepare to cast glitterdust!\n");
       say(QCTNAME(caster) + " chants a few words.\n");
}


public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
        object dust;
        int i;
       
       
       tell_room(environment(caster), "Suddently, a wave of glittering " +
        "dust blasts out from "+QCTNAME(caster)+"'s body! The glitterdust " +
        "quickly spreads everywhere, covering the whole area in the blink of an eye.\n",({caster}));
        
    targets = all_inventory(environment(caster));

    for (i = 0; i < sizeof(targets); i++)
    {
        
        
        
        
         if (!targets[i]->query_prop(IHAVEGLITTERDUST))
         {
        
           tell_object(targets[i], "You are suddently covered by thousands of tiny sparkling shards!\n");
           tell_room(environment(caster), QTNAME(targets[i]) + " is covered by thousands of tiny " +
           "sparkling shards!\n", ({targets[i]}));
 
           setuid();
           seteuid(getuid());
      
           dust = clone_object(NOV_DIR +"shadows/glitter_sh");
           dust->shadow_me(targets[i]);           
           dust->init_glitterdust_shadow(200);
               
           
            }
            
    }

}


int
create_spell()
{
    set_spell_name("glitterdust");
    set_spell_desc(">Summons a blast of glittering dust<");
    set_spell_time(3);
    set_spell_mana(40);
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