#include "spells.h"
#include <macros.h>
#include <options.h>
#include <language.h>

inherit SPELL_INHERIT;
inherit "/d/Genesis/newmagic/spells/tell";

int
config_spell(object caster, object *targets, string args)
{

    ::config_spell(caster, targets, args);
    config_default_spell();

    set_spell_name("tell");
    set_spell_desc("Tell something to another person");
    set_spell_target(target_tell);

    set_spell_time(2);
    set_spell_mana(10);
    set_spell_element(SS_ELEMENT_AIR, 50);
    set_spell_form(SS_FORM_DIVINATION, 40);
    return 0;
}

void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    if (caster->query_option(OPT_ECHO))
    {
	caster->catch_tell("You tell "+ targets[0]->query_met_name() +
	  ": " +query_tell_message() + "\n");
    }
    else
    {
	caster->catch_tell("Ok.\n");
    }
    targets[0]->catch_tell("From inside your head, you hear the "+
      "voice of "+caster->query_met_name()+" say: "+
      query_tell_message() + "\n");
}
