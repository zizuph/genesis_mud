/*
 *  Herald Ramar spell
 *
 *  Revised and Redone for the new Spellcasting system by
 *  Igneous Feb 1998
 *  
 *  Borrowed for the Wild Elves sparrow messenger
 *  -- Finwe, Feb 2005
 */ 

#include "spells.h"

inherit SPELL_INHERIT;

static object gSwallow;

int mana_cost = 20,
    skill_min = 20;

void
do_summon_messenger(object caster, object *targets, int *resist, int result)
{
    if (resist[0])
    {
	    caster->catch_tell("For some reason, your swallow can't come to you.\n");
	    return;
    }

    caster->catch_tell("Within a few minutes a swallow swoops down and " +
        "lands in the palm of your hand.\n");
    tell_room(targets[0], "Within a few minutes, a small bird swoops " +
        "down and lands in the palm of " + HIS_HER(caster) + 
        " hand.\n", ({caster}));

    if (!objectp(gSwallow))
    {
	    FIXEUID;
	    gSwallow = clone_object(SPELL_OBJECT_DIR + "swallow");
	    gSwallow->move(caster,1);
    }
    else
    {
	    gSwallow->fly_to_someone(caster);   
    }
}

int
summon_resist(object caster, object target, int element, int difficulty,
  int casting_sucess)
{
    object room;

    if (!objectp(gSwallow))
	return 0;
    if (gSwallow->query_busy())
	return 100;

    while (!room->query_prop(ROOM_I_IS))
    {
	if (!objectp(room))
	    room = environment(gSwallow);
	else
	    room = environment(room);
    }

    if (room->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER ||
        room->query_prop(ROOM_I_INSIDE))
	return 100;

    return 0;
}

int
create_messenger_spell(object caster, object *targets, string args)
{
    if (present(gSwallow, environment(this_object())))
    {
	    caster->catch_tell("Your swallow is already with you!\n");
	    return 1;
    }

    if (environment(caster)->query_prop(ROOM_I_INSIDE))
    {
	    caster->catch_tell("You cannot call for your swallow while indoors.\n");
	    return 1;
    }

    if (environment(caster)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
    {
	    caster->catch_tell("You cannot call for your swallow while underwater.\n");
	    return 1;
    }

    default_wild_elf_spell_config();
    set_spell_time(8);
    set_spell_mana(mana_cost);
    set_spell_task(TASK_ROUTINE - (caster->query_stat(SS_RACE) / 2));
    set_spell_ingredients(0);
    set_spell_element(SS_ELEMENT_LIFE,  20);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_effect(do_summon_messenger);
    set_spell_resist(summon_resist);
    return 0;
}
