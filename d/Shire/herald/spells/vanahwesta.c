/* 
 *  Herald Vanahwesta spell
 *
 *  Updated and modified by for the new Spellcasting system
 *  By Igneous Feb 1998
 */

#include "spells.h"

inherit SPELL_INHERIT;

void
do_vanahwesta_spell(object caster, object *targets, int *resist, int result)
{
    if (resist[0] > random(100))
    {
        caster->catch_tell("Your prayer remains unheard.\n");
        return;
    }
    if (caster->query_alignment() < 950)
    {
        caster->catch_tell("Your prayer remains unheard.\n");
        return;
    }
    tell_room(targets[0], QCTNAME(caster) + " calls upon Orome to make "+
      "peace here.\n", caster);
    caster->catch_tell("You call upon Orome to stop the fighting.\n");
    if (targets[0]->query_prop(ROOM_I_INSIDE))
    {
	tell_room(targets[0], "A loud, deafening rumble shakes "+
	  "the ground!  After the rumbling subsides, a sense of calm and "+
	  "peace permeates the area.\n");
    }
    else
    {
	tell_room(targets[0], "Clouds gather above you and form a dense, "+
	  "gray blanket. Suddenly a bolt of lightning springs from the "+
	  "clouds and impacts on the ground!\n");
    }
    FIXEUID;
    make_spell_effect_object(query_spell_object(), caster, targets,
      resist, result);
}

int
create_vanahwesta_spell(object caster, object *targets, string args)
{
    if (member_array("orome peace",
	environment(caster)->query_magic_effects()->query_spell_effect_desc()) != -1)
    {
	caster->catch_tell("This already has already been granted with peace.\n");
	return 1;
    }
    default_herald_spell_config();
    set_spell_mana(80);
    set_spell_time(6);
    set_spell_task(TASK_ROUTINE - (caster->query_stat(SS_LAYMAN) / 2));
    set_spell_element(SS_ELEMENT_EARTH, 35);
    set_spell_form(SS_FORM_DIVINATION, 40);
    set_spell_peaceful(0);
    set_spell_ingredients(({ "_stop_spell_mushroom_" }));
    set_spell_effect(do_vanahwesta_spell);
    set_spell_object(SPELL_OBJECT_DIR + "stop_obj");
    return 0;
}
