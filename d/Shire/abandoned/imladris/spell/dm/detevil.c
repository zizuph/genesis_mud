#include "defs.h"

inherit SPELL_FILE;

create_spellobj()
{
    set_form(FORM_DIVINATION, 10);
    set_elem(ELEMENT_LIFE, 10);
    set_spell_name("detect evil");
    add_prop(SPELL_M_CLASSES, ([1:1]) );
    add_prop(SPELL_S_DESC,
	"Tells if a living is evil.");
    add_prop(SPELL_S_SYNTAX, "in <what>");
}

object *
area_of_effect(string str)
{
    if(!str) return 0;
    return parse_livings(str, "'in'");
}

mixed
cast_detect_evil(object *obs, int res)
{
    object ob = obs[0];
    int al = ob->query_alignment();

    if(ob==TP) {
	if(al>0)
	    write("You are not of an evil alignment.\n");
	else
	    write("You are "+TP->query_align_text()+".\n");
	return;
    }
    if(al>0) {
	TP->catch_msg(QCTNAME(ob)+" is not of an evil alignment.\n");
	return;
    }
    TP->catch_msg(QCTNAME(ob)+" is "+ob->query_align_text()+".\n");
}

void
do_instant_effect(object *targets, int res)
{
    string retval;

    retval = cast_detect_evil(targets, res);
    if(stringp(retval))
	write(retval);
}
