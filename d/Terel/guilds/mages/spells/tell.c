inherit "/d/Genesis/newmagic/spell";

#include "spells.h"
#include <macros.h>
#include <options.h>
#include <language.h>
#include <filter_funs.h>

inherit SPELL_INHERIT;
inherit "/d/Genesis/newmagic/spells/tell";


void
concentrate_msg(object caster, object *targets, string args)
{
    caster->catch_tell("You call upon the wind to carry your voice to " +
		       targets[0]->query_met_name() + ". A small zephyr coaleses before you " +
		        "long enough to listen to your message then dissapates.\n");
    FILTER_IS_SEEN(caster, FILTER_PLAYERS(all_inventory(environment(caster)))
                                - ({ caster }))->catch_msg(QCTNAME(caster) + " speaks under " + HIS_HER(caster) +
				" breath. A small zephyr coalesces before " +HIM_HER(caster)+ " then " +
				"abruptly dissapates into nothingness.\n");
}

int
config_spell(object caster, object *targets, string args)
{
    ::config_spell(caster, targets, args);
    set_spell_name("voice");
    set_spell_desc("Tell something to another person");
    set_spell_target(target_tell);

    set_spell_time(2);
    set_spell_mana(10);
    set_spell_element(SS_ELEMENT_AIR, 50);
    set_spell_form(SS_FORM_DIVINATION, 40);

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

    targets[0]->catch_tell("You hear the voice of " +
		    (targets[0] == caster ? "yourself" : caster->query_the_name(caster))+
		    " carried upon a small zephyr which blows past, say: "+
                     query_tell_message() + "\n");

}

