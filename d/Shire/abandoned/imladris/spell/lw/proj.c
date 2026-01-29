#include "defs.h"

inherit SPELL_FILE;

create_spellobj()
{
    set_spell_name("projected light");
    set_form(FORM_CONJURATION, 10);
    set_elem(ELEMENT_LIFE, 10);
    add_prop(SPELL_AM_MATERIALS,    0);
    add_prop(SPELL_O_EFFECT,	    LW_DIR + "lighteff");
    set_desc(
	"Beam of light (like a flashlight) springs from the caster's palm."
    );
    set_syntax("");
}

object *
find_targets(string str)
{
    if(strlen(str)) return ({});
    if(present("_light_effect_", TP))
	return notify_fail("You already have a beam of light on your palm.\n"),({});
    return ({ TP });
}

mixed
cast_projected_light(object *targets, int res)
{
    spell_message(caster, targets, "Projected Light", 1);
    EP->update_light(1);
}

void
do_instant_effect(object *targets, int res)
{
    string retval;

    retval = cast_projected_light(targets, res);
    if(stringp(retval))
	write(retval);
}
