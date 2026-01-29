#include "defs.h"
#include <stdproperties.h>

//inherit EFFECT_SHADOW_FILE;
inherit "/d/Shire/healers/lib/spell/effect";
void
notify_dispel()
{
    qme()->remove_my_desc();
    qme()->remove_item(({"magical light", "room's light"}));
    tell_room(qme(), "The room stops shining.\n");
}

int
init_effect(object spell, object caster, int res)
{
    if(!qme()->query_prop(ROOM_I_IS))
	return 0;

    set_element(ELEMENT_LIFE);
    set_secondary_element(ELEMENT_LIFE);
    set_duration(caster->query_spell_level() * 60);
    set_power(1+res/10);
    set_reducible(1);
    tell_room(qme(),
	"A bright magical light starts shining here!\n");
    qme()->add_my_desc("@@room_desc@@");
    qme()->add_item(({"magical light", "room's light"}), "@@item_desc@@");
    return 1;
}

int
query_prop(string what)
{
    if(what == ROOM_I_LIGHT || what == OBJ_I_LIGHT || what == CONT_I_LIGHT)
	return query_power()/10+1;
    else
	return qme()->query_prop(what);
}

string short()
{
    return "A shining room.\n"+qme()->short();
}

string
room_desc()
{
    if(qme()->query_prop(ROOM_I_INSIDE))
	return "The room shines brightly, as if on a bright summers day!\n";
    else
	return "This place shines with a magical light.\n";
}

string
item_desc()
{
    return "A bright magical light seems to be shining here!\n";
}
