/*
 * An anti-magic object
 */

#include <stdproperties.h>

inherit "/std/object";
inherit "/d/Krynn/rastlin/open/spells2/magic.object";

public void
create_object()
{
    set_name("anit_magic_object");
    set_no_show();
}

public void
init_spell(object caster, object target, object prev)
{
    target->add_my_desc("The air is shimmering. Yet, you feel " +
			"an absence, an absence of something " +
			"supernatural.\n", this_object());

    target->add_prop(ROOM_M_NO_MAGIC, 1);
    target->add_prop(ROOM_M_NO_MAGIC_ATTACK, 1);
}

public void
notify_dispel_magic(object ob)
{
    object env;

    env = environment(this_object());

    tell_room(env, "The air around you stops shimmering and yet again " +
	      "you can feel the presence of something supernatural.\n");
    
    env->remove_prop(ROOM_M_NO_MAGIC);
    env->remove_prop(ROOM_M_NO_MAGIC_ATTACK);
}
