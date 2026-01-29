#include "defs.h"

inherit SPELL_FILE;

create_spellobj()
{
    set_form(FORM_DIVINATION, 10);
    set_elem(ELEMENT_LIFE, 10);
	set_name("detect good");
    set_classes( ([1:3]) );
    set_desc("Tells if a living is good.");
    set_syntax("in <what>");
}

object *
area_of_effect(string str)
{
    if(!str) return 0;
    return parse_livings(str, "'in'");
}

mixed
cast_detect_good(object *obs, int res)
{
    object ob = obs[0];
    int al = ob->query_alignment();

    if(ob==TP) {
	if(al<0)
	    write("You are not of a good alignment.\n");
	else
	    write("You are "+TP->query_align_text()+".\n");
	return;
    }
    if(al<0) {
	TP->catch_msg(QCTNAME(ob)+" is not of a good alignment.\n");
	return;
    }
    TP->catch_msg(QCTNAME(ob)+" is "+ob->query_align_text()+".\n");
}

void
do_instant_effect(object *targets, int res)
{
    string retval;

    retval = cast_detect_good(targets, res);
    if(stringp(retval))
	write(retval);
}
