#include "defs.h"
#include <composite.h>

inherit SPELL_FILE;

create_spellobj()
{
    set_form(FORM_ABJURATION, 10);
    set_elem(ELEMENT_FIRE, 10);
    set_spell_name("aura");	
    set_classes(([ 1:3, 2:6, 3:10, 5:16, 10:22 ]));
    set_desc(
	"Creates a bright aura about the target, making him appear more powerful."
    );
    add_prop(SPELL_O_EFFECT, THIS_DIR + "aura_shd");
    set_syntax("on <living>");
}

int
has_not_aura(object target)
{
    return !target->has_protection();
}

object *
area_of_effect(string str)
{
    object *targets = ({});
	int i;

    notify_fail("Who do you want to cast aura on?\n"+query_syntax());

    if (!strlen(str))
	str = "on me";

    if (sizeof(targets = parse_livings(str, "'on'", 1)))
    {
	notify_fail("Sorry, target(s) already have aura or alkar.\n");
	targets = filter(targets, "has_not_aura", TO);
	return targets[0..query_spell_class()-1];
    }
    return targets; //({});
}

mixed
cast_aura(object *targets, int res)
{
	object ob, aura;
	int i;

    targets = FILTER_CAN_SEE(targets, caster);

    if (!sizeof(targets))
	return "No targets present!\n";

	//aura = clone_object(LW_DIR + "aura_shd");
	//aura->init_shadow(ob, 0);

	spell_message(caster, targets, "Aura Spell", 1);
    return 1;
}

void
do_instant_effect(object *targets, int res)
{
    string retval;
    retval = cast_aura(targets, res);
    if(stringp(retval))
	write(retval);
}
