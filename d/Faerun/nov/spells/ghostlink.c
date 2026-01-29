/*
 * The ghostlink-spell for the Nov.
 *
 * 15/10/2004   -- Tilorop.
 */
#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include "../nov.h";

inherit "/d/Genesis/newmagic/spell";

// The prop we add to players.
#define SPELL_O_GHOSTLINK "_spell_o_ghostlink"

public void
concentrate_msg(object caster, object *targets, string arg)
{
    write("You prepare to cast ghostlink!\n");
    say(QCTNAME(caster) + " does a magical gesture with "+
	caster->query_possessive()+" hands.\n");
}

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    object pet, pet2;
    object target = targets[0];

    if (caster->query_alignment() > -100)
        {
                caster->write("Your alignment has surpassed the limit of " +
                "what is acceptable for those dabbling in the black arts.\n");
                return;
            
        }

    if (!query_interactive(target)) 
    {
	caster->catch_tell(
	    "There is no creature of that name within the realms!\n");
	return;
    }

    if (objectp(target->query_prop(SPELL_O_GHOSTLINK)))
    {
	caster->catch_tell(
	    "That person is already in communication with another.\n");
	return;
    }

    caster->catch_tell("You etablish an ethereal link to your target!\n");
    say(QCTNAME(caster) +" etablishes an ethereal link to someone.\n");

    pet = clone_object(NOV_DIR +"obj/murray");           
    pet->init_skull(target, 0);
    pet->move_living("M", environment(target), 1, 1);
    tell_room(environment(target),
	"A floating ghostly skull materializes from nowhere!\n");

    /* See if the caster already has a skull. */
    if (!objectp(pet2 = caster->query_prop(SPELL_O_GHOSTLINK)))
    {
	pet2 = clone_object(NOV_DIR +"obj/murray");
	pet2->init_skull(caster, 1);
	pet2->move_living("M", environment(caster), 1, 1);
	tell_room(environment(caster),
	    "A floating black skull materializes from nowhere!\n");
    }

    pet->link_skull(pet2);
    pet2->link_skull(pet);
}

public int
create_spell(void)
{
    setuid();
    seteuid(getuid());

    set_spell_name("ghostlink");
    set_spell_desc(">Ghostlink<");
    set_spell_time(3);
    set_spell_mana(50);
    set_spell_vocal(0);
    set_spell_visual(0);
    set_spell_ingredients(({ }));
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_DEATH, 10);
    set_spell_form(SS_FORM_CONJURATION, 10);
    set_spell_resist(spell_resist_basic);
    //set_spell_target_verify(spell_verify_present);
    set_spell_stationary(0);
    set_spell_offensive(0);

    set_spell_target(spell_target_one_distant_living);
}  
