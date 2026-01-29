inherit "/std/armour";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include "defs.h"
#include <ss_types.h>

void
create_armour()
{
    set_name("paw");
    set_adj(({"grizzly", "furry"}));
    set_short("grizzly paw");
    set_long(break_string("A grizzly paw. The paw from a dead "+
	"grizzly bear, which fits almost like a glove on the right "+
	"hand. The long dagger-like claws are still intact, making it "+
	"almost like a weapon.\n", 70));
    set_at(A_R_HAND);
    set_ac(40);
    set_af(this_object());
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 500);
}

int
wear()
{
    object tp = this_player();
    object to = this_object();

    tp->set_skill_extra(SS_UNARM_COMBAT, 20);
    tp->command("roar");
    return 0;
}

int
remove()
{
    object tp = this_player();
    object to = this_object();

    tp->set_skill_extra(SS_UNARM_COMBAT, 0);

    return 0;
}

void
leave_env(object ob, object to)
{
    ::leave_env(ob, to);
    if (interactive(ob))
	ob->set_skill_extra(SS_UNARM_COMBAT, 0);
}
