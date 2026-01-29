#include "defs.h"

inherit SPELL_FILE;

create_spellobj()
{
    set_form(FORM_DIVINATION, 10);
    set_elem(ELEMENT_LIFE, 10);
    add_prop(SPELL_S_NAME,	    "identify magic");
    add_prop(SPELL_M_CLASSES,	    ([1:6]) );
    add_prop(SPELL_S_DESC,
	"Tells what sort of magic is present.");
    add_prop(SPELL_S_SYNTAX, "on/in <what>");
}

object *
area_of_effect(string str)
{
    if(!str) return 0;
    return parse_items_normal(str);
}

mixed
cast_identify_magic(object *obs, int power)
{
    mixed *proplist;
    int i, num, pow, showed;
    string obname;
    object ob;

    spell_msg();
    write("Power = " + power + "\n");

    for (i=0; i<sizeof(obs); i++)
    {
	showed = 0;
	ob = obs[i];
	proplist = ob->query_prop(MAGIC_AM_ID_INFO);
	pow = power / sizeof(obs);
	pow -= pow * ob->query_resistance(OBJ_I_RES_IDENTIFY);

	if (living(ob))
	    obname = QCTNAME(ob);
	else
	    obname = CAP(LANG_THESHORT(ob));
 
	for (i=0; i<sizeof(proplist); i+=2)
	    if (pow > proplist[i+1])
	    {
		caster->catch_msg(proplist[i]);
		showed = 1;
	    }
	if(!showed)
	    TP->catch_msg("The Identify Magic spell on "+obname+" shows nothing special.\n");
    }
}

void
do_instant_effect(object *targets, int res)
{
    string retval;

    retval = cast_identify_magic(targets, res);
    if(stringp(retval))
	write(retval);
}
