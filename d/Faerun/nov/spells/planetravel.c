/*
 * The Planetravel spell for the Nov.
 *
 * 23/6/2004   -- Tilorop.
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
       write("You prepare to summon a portal to the Astral plane!\n");
       say(QCTNAME(caster) + " does a magical gesture with "+caster->query_possessive()+" hands.\n");
}


int
resolve_spell(object caster, object *targets, int *resist, int result)
{
        
        write("With magic flowing from your index finger you draw a large orange-glowing " +
        "pentagram in the middle of the air.\n");
        tell_room(environment(caster), "With magic flowing from "+caster->query_possessive()+" index " +
        "finger, "+caster->query_name() + " draws a large " +
        "orange-glowing pentagram in the middle of the air.\n", caster);
        clone_object(NOV_DIR +"obj/nportal3")->move(environment(caster), 1); 
        
        return 1;

}


int
create_spell()
{
    set_spell_name("planetravel");
    set_spell_desc(">Planar travel, summons a portal to temple<");
    set_spell_time(120);
    set_spell_mana(50);
    set_spell_vocal(0);
    set_spell_visual(0);
    set_spell_ingredients(({ }));
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