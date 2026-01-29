// blind_obj ("purity.c")
// creator(s):   Zielia 2007
// last update:
// purpose:     Tracks the purity blessing for entrance to the ziggurat
//		for those people who arrive via the pool
// note:
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "zigg.h"

private static object ob;

public void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_no_show();
    set_name(({"purity_obj","zigg::purity"}));
}

public void
remove_object()
{
    if (IS_CLONE)
    {
	ob->remove_prop(PROP_I_CLEANSED);
    }

    ::remove_object();
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!IS_CLONE)
	return;

    ob = ENV(TO); 

    ob->add_prop(PROP_I_CLEANSED, 2);
    /* Selectively remove these dirty-only items. */
    ob->query_subloc_obj("_kalad_dirty_subloc")->remove_object();
    ob->query_subloc_obj("stink_object_subloc")->remove_object();
    ob->query_subloc_obj("_fireplace_soot_subloc_")->remove_object();
    ob->query_subloc_obj("wearing_blood_object_subloc")->remove_object();
    present("DUNG_OBJ", ob)->remove_object();
    set_alarm(600.0, 0.0 , &remove_object());
}

public string
query_recover(void)	{ return 0; }
