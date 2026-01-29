/*
 *  Herald Ramar spell
 *
 *  Revised and Redone for the new Spellcasting system by
 *  Igneous Feb 1998
 */ 

#include "spells.h"

inherit SPELL_INHERIT;

static object gEagle;

void
do_ramar_spell(object caster, object *targets, int *resist, int result)
{
    if (resist[0])
    {
	caster->catch_tell("For some reson your messenger is unable "+
	  " to return to you.\n");
	return;
    }
    caster->catch_tell("You close your eyes and call upon Manwe for a "+
      "messenger.\nYou hear a shrill cry from on high, and your "+
      "messenger lands on your shoulder.\n");
    tell_room(targets[0], QCTNAME(caster) + " closes "+
      HIS_HER(caster)+" eyes in prayer.\nYou hear a shrill cry from "+
      "right above you as an eagle swoops down from the sky.\n", ({caster}));
    if (!objectp(gEagle))
    {
	FIXEUID;
	gEagle = clone_object(SPELL_OBJECT_DIR + "eagle");
	gEagle->move(caster,1);
    }
    else
    {
	gEagle->fly_to_someone(caster);   
    }
}

int
ramar_resist(object caster, object target, int element, int difficulty,
  int casting_sucess)
{
    object room;

    if (!objectp(gEagle))
	return 0;
    if (gEagle->query_busy())
	return 100;

    while (!room->query_prop(ROOM_I_IS))
    {
	if (!objectp(room))
	    room = environment(gEagle);
	else
	    room = environment(room);
    }

    if (room->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER ||
      room->query_prop(ROOM_I_INSIDE))
	return 100;

    return 0;
}

int
create_ramar_spell(object caster, object *targets, string args)
{
    if (present(gEagle, environment(this_object())))
    {
	caster->catch_tell("Your messenger is already with you!\n");
	return 1;
    }
    if (environment(caster)->query_prop(ROOM_I_INSIDE))
    {
	caster->catch_tell("You are unable to summon your messenger "+
	  "from indoors.\n");
	return 1;
    }
    if (environment(caster)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
    {
	caster->catch_tell("You are unable to summon your messenger "+
	  "from underwater.\n");
	return 1;
    }
    default_herald_spell_config();
    set_spell_time(8);
    set_spell_mana(35);
    set_spell_task(TASK_ROUTINE - (caster->query_stat(SS_LAYMAN) / 2));
    set_spell_ingredients(0);
    set_spell_element(SS_ELEMENT_LIFE, 20);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_effect(do_ramar_spell);
    set_spell_resist(ramar_resist);
    return 0;
}
