//-*-C++-*-
// file name:      cloudsp.c
// creator(s):     Sirra May 2003
// last update:
// bug(s):         Has not been tested.
// to-do:			 Change the following: class, mana, ingredients, etc.
// Notes:			 This file used cilenze.c spell as a template.

/*
 *
 *
 * Description: Curse someone with a thundercloud that follows them around.
 * Class:       2
 * Ingredients:
 * Mana:        40 (1/3)
 * Tax:         N/A
 * Skills:      SS_ELEMENT_WATER     3
 *              SS_FORM_CONJURATION 4
 * Task:        TASK_ROUTINE
 * Restriction: Must not be engaged in combat,
 *              the caster must not be gagged and the caster must
 *              have something to cast the spell on.
 */

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <tasks.h>
#include <language.h>

#include "/d/Krynn/guilds/wohs/guild.h";
#include "/d/Krynn/common/defs.h"

inherit SPELL_STD;

int do_cloud(object tar);

public varargs int
config_spell(object caster, object *targets, string arg)
{
	set_spell_name("nubescuro");
	set_spell_desc("Curse someone with a thundercloud.");

	//set_spell_element(SS_ELEMENT_WATER, 3);
	//set_spell_form(SS_FORM_CONJURATION, 4);

	set_spell_time(4);
	//set_spell_task(TASK_ROUTINE);
	set_spell_task(TASK_SIMPLE);

	//set_spell_mana(40);
	set_spell_mana(1);
	set_spell_target(spell_target_one_present_living);
	set_spell_ingredients(({ "copper", "copper coin" }));

	set_spell_peaceful(1);
	set_spell_vocal(1);
}



public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
	object ob;
	object cloud;
	object tar = targets[0];
	object *effects = tar->query_magic_effects();

	tell_room(E(caster), QCTNAME(caster) + " chants so low it "
		+"sounds like a growl.\n", (({ caster})));

	caster->catch_msg("You chant in a dark growling voice, "
		+"conjuring thunderclouds as you concentrate on "
		+QTNAME(tar)+ ".\n");

	ob = make_spell_effect_object(do_cloud(tar), caster, tar, 0,
		result);
	ob->set_spell_duration(240);
}


int
do_cloud(object tar)
{
	object cloud;

	cloud = clone_object(SPELL_OBJ+"cloud.c");
	cloud->set_target(tar);

	return 1;
}



