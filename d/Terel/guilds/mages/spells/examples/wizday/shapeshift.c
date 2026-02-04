#include "spells.h"
#include <macros.h>
#include <language.h>
#include <composite.h>
#include "/d/Khalakhor/sys/defs.h"

inherit SPELL_LIB;
inherit SPELL_INHERIT;

void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    object what = caster->query_prop(AVATAR_O_SHAPESHIFT);
    string desc;

    if (targets[0] != caster)
    {
	if (!living(targets[0]))
	    desc = LANG_THESHORT(targets[0]);
	else
	    desc = targets[0]->query_the_name(caster);
	if (random(100) < resist[0])
	{
	    caster->catch_tell("Your attempt to memorize "+desc+" fails.\n");
	    return;
	}

	if (interactive(targets[0]))
	{
	    caster->catch_tell("You are unable to take the form of another "+
	      "interactive player.\n");
	    return;
	}
	caster->catch_tell("You probe the form of "+desc+" intensely, "+
	  "with your magic, memorizing its features for later use.\n");
	tell_room(ENV(caster), (!living(targets[0]) ? capitalize(desc) :  
	    QCTNAME(targets[0])) + " glows slightly "+
	  "as "+QTNAME(caster)+" looks intensely upon it.\n", caster);
	caster->add_prop(AVATAR_O_SHAPESHIFT, targets[0]);
	return;
    }
    if (caster->query_avatar_shapeshift() ||
      random(100) < resist[0])
    {
	caster->catch_tell("Your spell fizzles into nothingness.\n");
	return;
    }

    caster->catch_tell("Completing the words for transformation and "+
      "alteration of life, you transform yourself into "+
      (living(what) ? what->query_the_name(caster) : LANG_THESHORT(what)) +
      ".\n");
    tell_room(ENV(caster), QCTNAME(caster) + " shimmers and "+
      "bubbles as "+HIS_HER(caster) +" body mutates and "+
      "twists itself into", caster);
    setuid(); seteuid(getuid());
    make_spell_effect_object(query_spell_object(), caster, targets,
      resist, result);
    tell_room(ENV(caster), " "+QCTNAME(caster)+"!\n", caster);
}

int
config_spell(object caster, object *targets, string args)
{
    set_spell_name("shapeshift");
    set_spell_desc("Shift your form into another.");
    set_spell_target(my_spell_target_one_present_object);

    config_default_spell();
    set_spell_mana(150);
    set_spell_time(10);
    set_spell_peaceful(1);
    set_spell_task(TASK_ROUTINE);
    set_spell_form(SS_FORM_TRANSMUTATION, 70);
    set_spell_element(SS_ELEMENT_LIFE, 80);
    set_spell_resist(spell_resist_beneficial);
    set_spell_object(SPELL_OBJ_DIR + "shapeshift");
    return 0;
}
