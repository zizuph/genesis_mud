/*
   Diamond. Store Room to destruct items.

   collect_store.c
   -------

   Coded ........: January 1998
   By ...........: Kentari

   Latest update : January 1998
   By ...........: Kentari

*/

#include "../local.h"
#include <stdproperties.h>
inherit IN_BASE;
inherit "/lib/store_support";

public void
create_dim_room()
{
    set_short("The Kiln of the Collection Store");
    set_long("This is the inside of the Kiln of the Collection Store " +
	"in Diamond City. You are surrounded by magical flame, and " +
	"really shouldn't even be able to be in here.\n");
    add_exit(DIROOM + "collect","out");
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
	if (!living(ob))
     {
        set_alarm(0.1, 0.0, ob->remove_object);
     }
}

