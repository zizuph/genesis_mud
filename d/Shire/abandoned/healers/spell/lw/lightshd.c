#include "defs.h"
#include <stdproperties.h>
#include <macros.h>

//inherit EFFECT_SHADOW_FILE;
inherit "/d/Shire/healers/lib/spell/effect";
int
query_prop(string what)
{
    if(what==OBJ_I_LIGHT)
    {
	return qme()->query_prop(what)+query_power()/100+1;
    }
    else
	return qme()->query_prop(what);
}

string short()
{
    return qme()->short()+" (shining brightly)";
}

string
long(string arg)
{
    if (arg && arg=="light")
	return "It shines magically bright!\n";
    if (strlen(arg))
	return qme()->long(arg);
    return qme()->long(arg)+"\nIt shines as if magic struck it!\n";
}

init_effect(object spell_object, object caster, int result)
{
    set_element(ELEMENT_FIRE);
    set_duration(spell_object->query_spell_class()*5*60);
    set_power(1 + result/100);
    set_reducible(0);
    set_remove_on_dispel(0);
    environment(caster)->update_light(1);
    tell_room(environment(caster),
	"The "+QSHORT(qme())+" starts shining with an intense magical light!\n");
}

void
notify_dispel()
{
    environment(qme())->update_light(1);
}
