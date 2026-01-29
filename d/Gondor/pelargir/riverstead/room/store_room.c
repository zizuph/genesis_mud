/*
 *  NCAMP_ROOM + "store_room.c"
 *
 *  Last modified by Alto, 23 November 2002
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/lib/store_support";

#include <macros.h>
#include <stdproperties.h>
#include <math.h>
#include "/d/Gondor/defs.h"
#include "../ncamp_defs.h"

inherit NCAMP_LIB + "ncamp_funcs.c";

public void        create_gondor();
public string      long_desc();

public void
create_gondor()
{
    set_short("a small hut in the northwest corner of the settlement");
    set_long(&long_desc());

    hut_add_items();

    add_item(({"room", "area", "surroundings", "place",
        "cottage", "house", "hut", "cabin", "building"}), long_desc);

   
  if (!present("leather")) clone_object(NCAMP_ARM + "hleather")->move(TO);
  if (!present("shield")) clone_object(NCAMP_ARM + "hshield")->move(TO);
  if (!present("sword")) clone_object(NCAMP_WEP + "ncamp_hscim")->move(TO);

    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}

string
long_desc()
{
    return "A room to store goodies in.\n";
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    store_update(obj);
}

public void
reset_room()
{
    reset_store();
}
