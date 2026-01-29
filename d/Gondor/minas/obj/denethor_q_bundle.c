/*
 * /d/Gondor/minas/obj/denethor_q_bundle.c
 *
 * bundle of wood for the Denethor pyre quest
 *
 * Alto, 02 June 2001
 *
 */


inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

public void
destruct_me() 
{
    object room;
    if (living(room = environment()))
	     room = environment(room);
      tell_room(room, "The large heavy bundle breaks apart and scatters.\n");
      remove_object();
}

public void
do_destruct() 
{
    if (query_verb() == "drop")
    {
	   set_alarm(2.0, 0.0, destruct_me);
    return 0;
    }

    if (query_verb() == "give")
    {
	   set_alarm(2.0, 0.0, destruct_me);
    return 0;
    }

    if (query_verb() == "put")
    {
	   set_alarm(2.0, 0.0, destruct_me);
    return 0;
    }

}

void
create_object()
{
    set_name("bundle");
    add_name("_denethor_q_bundle_");
    set_adj("large");
    add_adj("heavy");
    set_pname("bundles");
    set_short("large heavy bundle");
    set_pshort("large heavy bundles");
    set_long("This is a large bundle of wood lashed together for transport.\n");
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_NO_DROP, do_destruct);

    seteuid(getuid(TO));
}
