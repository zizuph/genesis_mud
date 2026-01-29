// blind_obj ("js_flush.c")
// creator(s):   Zielia 2006
// last update:
// purpose:      Blessing object for jazsis altar
// note:
// bug(s):
// to-do:

#include <macros.h>
#include <stdproperties.h>
#include "zigg.h"

inherit "/std/object";

public void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_no_show();
    set_name(({"JS::Flush"}));

    add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }));
    add_prop(MAGIC_I_RES_FIRE, 15);
    add_prop(MAGIC_I_RES_COLD, 15);
    add_prop(OBJ_S_WIZINFO, "This is a blessing that makes the bearer "+
	"temporarily resistant to fire (RES: 15) and cold (RES: 15).\n");

    add_prop(OBJ_I_NO_DROP, 1);

}

public void
remove_object(void)
{
    if (IS_CLONE)
    {
	object ob = present(EYES_NAME, ENV());
	ob->rem_ref("passion");

	ENV()->remove_magic_effect(TO);
	ENV()->catch_tell(
	    "The warmth that had filled you suddenly subsides.\n");
	ENV()->command("$shiver");
    }

    ::remove_object();
}

public void
enter_env(object to, object from)
{
    object ob = present(EYES_NAME, to);
    float time = itof(1500 + random(600));

    ::enter_env(to, from);

    to->catch_tell("You feel a pleasant warmth growing at your core and "+
	"spreading outward.\n");

    if (!objectp(ob))
    {
        ob = clone_object(EYES_OBJ);
        ob->move( to );
    }

    ob->add_ref("passion");
    to->add_magic_effect(TO);

    set_alarm(time, 0.0 , &remove_object());
}

public mixed
query_magic_protection(string prop, object protectee = previous_object())
{
    if (protectee == ENV())
    {
        if (prop == MAGIC_I_RES_FIRE)
        {
            protectee->catch_tell(
		"The heat outside you seems cool compared to "+
		"the burning warmth of Passion from within.\n");
            tell_room(ENV(protectee), QCTNAME(ENV())+ " seems impervious to "+
		"heat.\n",protectee, TO);
            return ({ 15, 1});
        }

        if (prop == MAGIC_I_RES_COLD)
        {
            protectee->catch_tell("You barely notice the cold around you as "+
		"a sensual warmth still warms you from within.\n");
            tell_room(ENV(protectee), QCTNAME(ENV())+ " seems impervious to "+
		"cold.\n",protectee, TO);
            return ({ 15, 1});
        }
    }
    else
        return ::query_magic_protection(prop, protectee);
}
