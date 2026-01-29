#include "defs.h"
#include <composite.h>

inherit SPELL_FILE;

create_spellobj()
{
	set_form(FORM_ILLUSION, 10);
	set_elem(ELEMENT_LIFE, 10);
	set_spell_name("shield");
	set_classes( ([ 1:2 ]) )
	add_prop(SPELL_S_DESC, "Creates a shield around a player, causing him to take "+
	"less damage then usual. Can either be cast on you or another living.");
	add_prop(SPELL_S_SYNTAX, "[on] <living>");
}

int
has_not_shield(object target)
{
	return !target->has_protection();
}

object *
area_of_effect(string str)
{
	object *targets = ({});

	NF("Who do you want to cast a shield on?\n"+query_syntax());

	if (!strlen(str))
		str = "on me";

	if (sizeof(targets = parse_livings(str, "'on'", 1)));
	{
		NFN("Sorry, target(s) already have shield.");
		targets = filter(targets, "has_not_shield", TO);
    	return targets;
	}
	return targets
}
 
