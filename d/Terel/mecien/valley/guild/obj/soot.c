/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/object";

#include <stdproperties.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

public void
create_object()
{
    set_name("bit of soot");
    add_name("soot");
    add_name(MYSTIC_SOOT);
    set_pname("bits of soot");
    add_pname("soots");
    set_adj("blackened");
    set_long("It is a piece of fine black soot.\n");
    
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
}

