#include "defs.h"

inherit SPELL_FILE;

create_spellobj()
{
    set_form(FORM_DIVINATION, 10);
    set_elem(ELEMENT_AIR, 10);
    add_prop(SPELL_S_NAME,    "detect invisible");
    add_prop(SPELL_M_CLASSES, ([1:7, 3:13, 5:18, 10:25]) );
    add_prop(SPELL_S_DESC,
	"This spell makes the target more perceptive at invisible things.");
    add_prop(SPELL_S_SYNTAX, "on <who>");
}

object *
area_of_effect(string str)
{
    return parse_one_living(str, "'on' %l", 1);
}

mixed
cast_detect_invisible(object *targets, int res)
{
    object eff, who, tp=caster;
    int old_see;
    int str;

    who = targets[0];

    spell_message(caster, who, "Detect Invisible", 1);

    str = ( tp==who ? level(tp) : level(tp)/2) 
	* query_spell_class() 
	* res / 1000;

    if (str > 100) 
	str = 100;
    if (present("_det_invis_effect_", who))
	return;

    eff = clone_object(THIS_DIR + "inviseff");
    eff -> set_time(str * 10);
    eff -> set_strength(str);
    eff -> move(who);
    return 1;
}

void
do_instant_effect(object *targets, int res)
{
    string retval;

    retval = cast_detect_invisible(targets, res);
    if(stringp(retval))
	write(retval);
}
