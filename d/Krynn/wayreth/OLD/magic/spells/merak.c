/*
 * Merak
 *
 * Description: A simple light spell
 * Class:       2
 * Ingredients: two copper coins
 * Mana:        40 (1/3)
 * Tax:         0.1
 * Skills:      SS_ELEMENT_FIRE     3
 *              SS_FORM_CONJURATION 4
 * Task:        TASK_SIMPLE
 * Restriction: Must be member and not engaged in combat,
 *              the caster must not be gagged and the caster must
 *              have something to cast the spell on, at lower level
 *              the object will disappear.
 */
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>
#include <language.h>

#define MERAK_OBJ "/d/Krynn/wayreth/magic/obj/merak"

public void merak_message(object caster, object *targets);

public int
create_spell_merak(string arg)
{
    if (!stringp(arg) || arg == "")
    {
        write("What do you want to cast the spell on?\n");
	return 1;
    }

    if (check_gagged())
        return 1;

    if (check_combat())
        return 1;

    set_spell_element(SS_ELEMENT_FIRE, 3);
    set_spell_form(SS_FORM_CONJURATION, 4);

    set_spell_time(3);
    set_spell_task(TASK_SIMPLE);

    set_spell_mana(40);
    set_find_target(find_dead_object);
    set_spell_message(merak_message);
    set_spell_object(MERAK_OBJ);
}

public int
do_merak(string str)
{
    return cast_spell();
}

public void
merak_message(object caster, object *targets)
{
    object tar = targets[0];
    object *effects = tar->query_magic_effects();
    int t = query_spell_result()[0];
    int size = sizeof(effects);
    
    while(size--)
    {
        if (MASTER_OB(effects[size]) == MERAK_OBJ)
	{
	    caster->catch_msg("Too late you discover that the " +
			      tar->query_name() + " already was " +
			      "affected by another halo spell.\n");
	    tell_room(E(caster), "The " + tar->query_name() +
		      " disappears in a puff of smoke.\n");
	    tar->remove_object();
	    set_spell_object(0);
	    return;
	}
    }

    tell_room(E(caster), QCTNAME(caster) + " starts to form a glowing " +
	      "halo around the " + tar->short() + ".\n", caster); 

    caster->catch_msg("You form a glowing halo around the " + 
		      tar->short() + ".\n");

    if (tar->query_prop(OBJ_M_NO_GET) || tar->query_prop(OBJ_M_NO_DROP) ||
	tar->query_prop(OBJ_I_HIDE) || tar->query_prop(OBJ_I_INVIS) ||
	tar->query_prop(OBJ_I_NO_MAGIC))
    {
        tell_room(E(caster), "The halo vanishes as soon as it is " +
		  "complete.\n");
	set_spell_object(0);
    }

    set_spell_duration(240 + (t > 1000 ? 1000 : t) * 2);
}






