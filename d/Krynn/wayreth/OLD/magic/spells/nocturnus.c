/*
 * Nocturnus
 *
 * Description: A darkness spell, creates a globe of darkness
		which can be manipulated like any other object.
 * Class:       2
 * Ingredients: nightshade and a torch
 * Mana:        50 (1/3)
 * Tax:         0.3
 * Skills:      SS_ELEMENT_FIRE     5 ?
 *              SS_FORM_CONJURATION 7 ?
 * Task:        TASK_SIMPLE
 * Restriction: Must be member and may not be in combat,
 *              the caster must not be gagged.
 */
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>
#include <language.h>


#define NOCTURNUS_OBJ "/d/Krynn/wayreth/magic/obj/nocturnus"

public void nocturnus_message(object caster, object *targets);


public int
create_spell_nocturnus(string arg)
{
    if (stringp(arg) && arg != "")
    {
        write("Why not just make the darkness globe, then GIVE it away.\n");
	return 1;
    }
    NF("You cannot pronounce the words properly.\n");

    if (check_gagged())
        return 1;
    if (check_combat())
	 return 1;

    set_spell_element(SS_ELEMENT_FIRE, 5);
    set_spell_form(SS_FORM_CONJURATION, 7);

    set_spell_fail(spell_wohs_fail);

    set_spell_time(2);
    set_spell_task(TASK_ROUTINE);

    set_spell_mana(50);
    set_find_target(find_caster);
    set_spell_message(nocturnus_message);
    set_spell_object(NOCTURNUS_OBJ);
    set_spell_ingredients( ({"nightshade", "torch"}) );
}

public int
do_nocturnus(string str)
{
    return cast_spell();
}

public void
nocturnus_message(object caster, object *targets)
{
    object tar = targets[0];
    int t = query_spell_result()[0];
    int dur; 
    
    tell_room(E(caster), QCTNAME(caster) + " utters an incantation, making the " +
	      "shadows around you solidify into pitch blackness.\n", caster); 

    
    caster->catch_msg("You weave the shadows into a globe of darkness.\n");

    
    set_spell_duration(240 + (t > 1000 ? 1000 : t));
    
}

