/*
   know_me.c

   On request from Lars, this object if cloned autoloads with a wizard
   and sets the LIVE_I_ALWAYSKNOWN property. Thereby always showing
   the wizard on everyones who list.
*/

inherit "/std/object";

#include <macros.h>
#include <std.h>
#include <stdproperties.h>


string query_auto_load() { return MASTER; }

void create_object()
{
    set_name("mask");
    set_short("face mask");
    set_no_show();
}

void enter_env(object inv, object from)
{
    ::enter_env(inv, from);

    if (inv->query_wiz_level())
	inv->add_prop(LIVE_I_NEVERKNOWN, 1);
}

void leave_env(object inv, object to)
{
    ::leave_env(inv, to);

    if (inv->query_wiz_level())
	inv->remove_prop(LIVE_I_NEVERKNOWN);
}

int remove_object()
{
    if (environment())
	environment()->remove_prop(LIVE_I_ALWAYSKNOWN);
    ::remove_object();
}
