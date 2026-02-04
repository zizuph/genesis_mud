inherit "/d/Genesis/newmagic/spell";

#include "spells.h"
#include <macros.h>
#include <filter_funs.h>
#include <language.h>



inherit SPELL_INHERIT;


void drain_mana(int response, object drainer, object *targets);

int
resolve_spell(object caster, object *targets, int *resist, int success)
{

    object source, yn_ob;
    source = targets[0];
   

    if (random(100) < resist[0])
    {
	caster->catch_tell(targets[0]->query_The_name(caster) +" resists your "+
	  "attempt to heal "+HIM_HER(targets[0])+".\n");
	return 1;
    }
  
    setuid();
    seteuid(getuid());

    // Ask the target if he will give mana.
    if (yn_ob = clone_object("/d/Terel/std/yes_no"))
    {
        /* When yn_ob gets a "yes" or "no" answer, or it times out,
         * it reports back to this object with the answer
         */
        if (!yn_ob->get_answer(source, &drain_mana(, caster, targets), 20.0))
        {
            // something failed in yn_ob...remove it.
            yn_ob->remove_object();
            return 0;
        }
        else
        {
          caster->catch_tell("You ask to borrow some mana from " +
            (targets[0]->notmet_me(caster) ? targets[0]->query_nonmet_name() :
	      targets[0]->query_met_name()) +".\n");
          targets[0]->catch_tell(caster->query_The_name(targets[0]) +
              " asks to borrow some mana? (Yes / No)\n");
          caster->tell_watchers(QCTNAME(caster)+"Takes " +(QTNAME(targets[0]))+" aside "+
              " and asks them something.\n");
          return 1;
	} 
         return 1;
    }     
}


void
drain_mana(int response, object caster, object* targets)
{
 
    int skill;
    object source;
    source = targets[0];
    
caster->catch_tell("RETURN:  " + response + "\n");

    if (!response)
    {
        caster->catch_tell((QTNAME(targets[0]))+" denied your request for mana.\n");
        return;
    }

    if (response < 0)
    {
        caster->catch_tell((QTNAME(targets[0]))+" failed to respond to your request " +
            "for mana.\n");
        return;
    }

       caster->catch_tell("You lay your hands upon " +(QTNAME(targets[0]))+ 
         ".\n");
       targets[0]->catch_tell(caster->query_The_name(targets[0]) +
         " lays "+HIS_HER(caster)+" hands upon your temples. A  "+
         "wonderous glow surrounds "+HIM_HER(caster)+"\n");
       caster->tell_watchers(QCTNAME(caster)+" lays "+HIS_HER(caster)+
         "hands on "+query_The_name(targets[0])+" temples "+
         "which transfers the glow to "+HIM_HER(targets[0])+
         ", which then fades quicky.\n", targets[0]);
// add in guildstat check to the skill var.
         skill = caster->query_skill(SS_ELEMENT_AIR);
         source->set_mana(-skill);
         caster->set_mana(skill * (3 + random(4)));
         return;
}



int
config_spell(object caster, object *targets, string argument)
{
    set_spell_name("transfer");
    set_spell_desc("transfer mana from a known target");
    set_spell_target(spell_target_one_distant_known_living);
    set_spell_time(5);
    set_spell_mana(10);
    set_spell_element(SS_ELEMENT_AIR, 35);
    set_spell_form(SS_FORM_TRANSMUTATION, 30);
    set_spell_resist(spell_resist_beneficial);

}







