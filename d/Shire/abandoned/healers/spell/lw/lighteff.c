#include "defs.h"
#include <stdproperties.h>

//inherit EFFECT_OBJECT_FILE;
inherit "/d/Shire/healers/lib/spell/effobj";
#define SUBLOC "_light_effect_subloc_"

void
notify_dispel()
{
    set_this_player(qme());
    write("Your beam of light stops shining.\n");
    say(QCTNAME(TP) + "'s beam of light stops shining.\n");
    qme()->remove_subloc("_light_effect_subloc_");
}

string
show_subloc(mixed subloc, object on, object who)
{
    if(subloc!=SUBLOC)
	return "";
    if(who->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";
    if(who==ENV(TO))
	return "A beam of light springs out of your palm.\n";
    else
	return "A beam of light springs out of his palm.\n";
}

string
exa_palm()
{

    if (TP==ENV(TO))
	return("You have a beam of light springing magically out of your palm.\n");
    else
	return(QCTNAME(TP)+" has a beam of light springing out of "+HIS_HER(TP)+" palm.\n");
}

int
init_effect(object spell, object caster, int res)
{
    if(!living(qme()) || !living(caster) || !spell)
	return 0;

    set_element(ELEMENT_FIRE);
    set_duration(spell->query_spell_class()*5*60);
    set_power(1 + res / 10);
    set_reducible(1);

    set_name("_light_effect_");
    add_item(({"palm","light"}), "@@exa_palm@@");
    add_prop(OBJ_I_LIGHT, 1);

    set_this_player(qme());
    write("A beam of light springs out of your palm.\n");
    say("A beam of light springs out of " + QCTNAME(TP) + "'s palm.\n");

    qme()->add_subloc(SUBLOC, TO);
    return 1;
}
