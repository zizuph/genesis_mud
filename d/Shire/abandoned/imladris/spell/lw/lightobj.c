#include "defs.h"
#include <stdproperties.h>

inherit EFFECT_OBJECT_FILE;

#define SUBLOC "_light_object_subloc_"
#define LNAME	"_light_object_"

int
init_effect(object spell, object caster, int res)
{
    if(!living(qme()) || !living(caster) || !spell)
	return 0;

    set_element(ELEMENT_FIRE);
    set_duration(spell->query_spell_class()*5*60);
    set_power(res / 10 + 1);
    set_reducible(1);
    set_name(LNAME);
    add_item(({"body","light"}), "@@exa_light@@");
    add_prop(OBJ_I_LIGHT, "@@query_light@@");

    set_this_player(qme());

    write("You stand amazed seeing that your body emits light!\n");
    say(QCTNAME(TP) + " stands amazed seeing that " + HIS_HER(TP) +
	" body emits light!\n");
    TP->add_subloc(SUBLOC, TO);
    unset_no_show();
    set_no_show_composite(1);
    return 1;
}

int
query_light()
{
    return query_power()/100 + 1;
}

void
notify_dispel()
{
    set_this_player(qme());
    write("Your illumination body stops glowing.\n");
    say(QCTNAME(TP) + "'s body stops glowing.\n");
    TP->remove_subloc(SUBLOC);
}

string
show_subloc(mixed subloc, object on, object who)
{
    if(subloc!=SUBLOC)
	return "";
    if(who->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";
    if(who==EO)
	return "Your entire body emits light!\n";
    else
	return "Strangly enough, "+HIS_HER(TP)+" entire body illuminates the area.\n";
}

string
exa_light()
{

    if(TP==EO)
	return("It seems like some magical force have sparkled your body with light.\n");
    else
	return(QCTNAME(TP)+" has a body illuminating light.\n");
}
