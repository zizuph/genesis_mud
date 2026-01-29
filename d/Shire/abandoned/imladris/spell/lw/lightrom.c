#include "defs.h"
#include <stdproperties.h>

inherit EFFECT_OBJECT_FILE;

#define LNAME	"_light_room_object_"

create_object()
{
    set_name("light");
    add_adj(({"conjured", "bright", "magical"}));
    set_short("A bright magical light in the room");
    set_long(
	"It seems like some magical force have sparkled this room with light.\n");
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_VOLUME, 0);
}

int
init_effect(object spell, object caster, int res)
{
    if(!qme() || !qme()->query_prop(ROOM_I_IS) || !living(caster) || !spell)
	return 0;

    set_element(ELEMENT_FIRE);
    set_duration(spell->query_spell_class()*5*60);
    set_power(1+res/10);
    set_reducible(1);

    add_prop(OBJ_I_LIGHT, "@@query_light@@");

    tell_room(qme(),
	"The room shines with a magically conjured light!\n");
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
    tell_room(qme(),
	"The magically conjured light fades out.\n");
}
